#include "BaseOpenGLRenderer.h"

void BaseOpenGLRenderer::beginDraw() const {
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer.id);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void BaseOpenGLRenderer::draw(const RenderData& data) const {
	glBindVertexArray(data.vao);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);
}

void BaseOpenGLRenderer::endDraw() const {
	glBindVertexArray(0);

	if (framebuffer.id != 0) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(framebuffer.screenQuad.vao);
		glBindTexture(GL_TEXTURE_2D, framebuffer.textureAttachment);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void BaseOpenGLRenderer::update(const float dt) const {
	beginDraw();
	render();
	endDraw();
}

void BaseOpenGLRenderer::createFrameBuffer(const int winWidth, const int winHeight) {
	framebuffer = bufferConfigurator.createFrameBuffer({ winWidth, winHeight });
}

RenderData BaseOpenGLRenderer::configure(const Bindable& bindable, const int drawMode) {
	RenderData result = bufferConfigurator.configure(bindable, drawMode);
	buffers.push_back(BufferTriple(result.vao, result.ebo, result.vbo));

	return result;
}

BaseOpenGLRenderer::~BaseOpenGLRenderer() {
	for (int i = 0; i < buffers.size(); i++) {
		glDeleteVertexArrays(1, &buffers.at(i).vao);
		glDeleteBuffers(1, &buffers.at(i).ebo);
		glDeleteBuffers(1, &buffers.at(i).vbo);
	}
}