#include "BufferConfigurator.h"

RenderData BufferConfigurator::configure(const Bindable& bindable, const int drawMode) const {
	VertexData vertexData = bindable.vertexData;
	IndexData indexData = bindable.indexData;
	AttributeData attributeData = bindable.attributeData;
	int vertexComponentCount = bindable.vertexData.componentCount;

	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.count * vertexComponentCount * sizeof(GLuint), indexData.indices, GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, vertexData.count * vertexComponentCount * sizeof(GLfloat), vertexData.vertices, GL_STATIC_DRAW);

	// Next, we have to specify, how the vertex data is organized
	// Depending on the attribute data, we tell OpenGL on how the 
	// vertex data should get interpreted.
	for (int i = 0; i < attributeData.count; i++) {
		// We need the component count per attribute
		int componentCount = attributeData.attributeSizes[i];

		// We need the stride; it is calculated by 
		// the total count of components of a single vertex, multiplied
		// by the size of data type the attribute is using (the default is float)
		int stride = vertexComponentCount * sizeof(GLfloat);

		// We need an offset specifing the first component of attribute i
		// It is calculated by the sum of component count of the previous attributes.
		int offset = getOffset(i, attributeData);

		glVertexAttribPointer(i, componentCount, GL_FLOAT, GL_FALSE, stride, (GLvoid*) (offset * sizeof(GLfloat)));
		glEnableVertexAttribArray(i);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return { vao, ebo, vbo, indexData.count, drawMode };
}

ScreenQuad BufferConfigurator::configureScreenQuad(const Vec2& position, const Vec2& size) const {
	// Problem: We want to have custom rect on which the framebuffer's
	// content gets drawn. The input vectors are in pixel coordinates.
	// => We have to calculate a rectangle with correct position
	// and size in OpenGL NDC space.

	// Each point of this rect has to be calculated
	// depending on position and scale.
	// Finally, those points have to be transformed to NDC,
	// so OpenGL will render the rect properly.

	// Note: Typically, this calculation is done in a shader,
	// but in this simple case, we can pre-calculate this, because
	// those values will never change.

	// First, let's find out the size of default framebuffer.
	// This is the frame on which the custom rect gets drawn.
	// This size is necessary in order to transform from pixel to
	// relative coordinates.
	// This can be done by fetching viewport data.
	GLint* values = new GLint[4];
	glGetIntegerv(GL_VIEWPORT, values);

	// Transformation (scaling) from pixel to relative coordinates
	// depending on default framebuffer size
	Vec2 scaling = Vec2(1.f / values[2], 1.f / values[3]);

	// Transformation from relative to OpenGL
	// specific NDC space.
	// The order is: Pixel -> Relative -> NDC
	Vec2 ndcLeftBottom = toNDC(position * scaling);
	Vec2 ndcLeftTop = toNDC(Vec2(position.x, position.y + size.y) * scaling);
	Vec2 ndcRightBottom = toNDC(Vec2(position.x + size.x, position.y) * scaling);
	Vec2 ndcRightTop = toNDC(Vec2(position.x + size.x, position.y + size.y) * scaling);

	// Finally, the rect gets described by two triangles, which
	// consists of the previously calculated NDC coordiantes
	float quadVertices[] = {
		// positions							// texCoords
		ndcLeftTop.x,		ndcLeftTop.y,		0.0f, 1.0f,	//left up
		ndcLeftBottom.x,	ndcLeftBottom.y,	0.0f, 0.0f,	// left bottom
		ndcRightBottom.x,	ndcRightBottom.y,	1.0f, 0.0f,	// right bottom

		ndcLeftTop.x,		ndcLeftTop.y,		0.0f, 1.0f,	//left up
		ndcRightBottom.x,	ndcRightBottom.y,	1.0f, 0.0f,	// right bottom
		ndcRightTop.x,		ndcRightTop.y,		1.0f, 1.0f	// right up
	};

	// Standard buffer configuration & initialization
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)));

	return { quadVAO, quadVBO };
}

FrameBuffer BufferConfigurator::createFrameBuffer(const Vec2& position, const Vec2& size) const {
	unsigned int framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	unsigned int textureColorAttachment;
	glGenTextures(1, &textureColorAttachment);
	glBindTexture(GL_TEXTURE_2D, textureColorAttachment);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei) size.x, (GLsizei) size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorAttachment, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ScreenQuad screenQuad = configureScreenQuad(position, size);

	return FrameBuffer(framebuffer, textureColorAttachment, screenQuad, (int) size.x, (int) size.y);
}

int BufferConfigurator::getOffset(const int currAttribIndex, const AttributeData& attributeData) const {
	int result = 0;

	// Iterate over previous attributes and sum their component counts
	for (int i = currAttribIndex; i > 0; i--) {
		result += attributeData.attributeSizes[i - 1];
	}

	return result;
}