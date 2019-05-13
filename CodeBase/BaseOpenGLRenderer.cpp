#include "BaseOpenGLRenderer.h"

void BaseOpenGLRenderer::setup(int defaultFramebufferWidth, int defaultFramebufferHeight) {
	framebuffers.insert(pair<int, FrameBuffer>(0, FrameBuffer(defaultFramebufferWidth, defaultFramebufferHeight)));
}

void BaseOpenGLRenderer::beginDraw() const {
	// Clear all framebuffers
	for (const pair<int, FrameBuffer>& pair : framebuffers) {
		glBindFramebuffer(GL_FRAMEBUFFER, pair.second.id);

		glClearColor(CLEAR_COLOR, CLEAR_COLOR, CLEAR_COLOR, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

void BaseOpenGLRenderer::draw(const RenderData& data) const {
	glBindVertexArray(data.vao);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);
}

void BaseOpenGLRenderer::endDraw() const {
	glBindVertexArray(0);

	// If there is only default framebuffer present
	// there is nothing to to.
	if (framebuffers.size() == 1)
		return;

	// Bind back to default framebuffer in order to 
	// draw all quads with their texture attachments
	// Clearing is not necessary, because default
	// framebuffer gets cleared in beginDraw().
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Update viewport
	const FrameBuffer& defaultFramebuffer = framebuffers.at(0);
	glViewport(0, 0, defaultFramebuffer.width, defaultFramebuffer.height);

	// Iterate over all created buffers and render their quads
	// with corresponding texture attachments
	for (const pair<int, FrameBuffer>& pair : framebuffers) {
		const FrameBuffer& framebuffer = pair.second;

		// Default framebuffer does not have any attachments
		if (framebuffer.id == 0)
			continue;

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

int BaseOpenGLRenderer::createFrameBuffer(int x, int y, int winWidth, int winHeight) {
	const FrameBuffer& framebuffer = bufferConfigurator.createFrameBuffer({ x, y }, { winWidth, winHeight });
	framebuffers.insert(pair<int, FrameBuffer>(framebuffer.id, framebuffer));

	return framebuffer.id;
}

void BaseOpenGLRenderer::bindFrameBuffer(int identifier) const {
	glBindFramebuffer(GL_FRAMEBUFFER, identifier);

	const FrameBuffer& framebuffer = framebuffers.at(identifier);
	glViewport(0, 0, framebuffer.width, framebuffer.height);
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