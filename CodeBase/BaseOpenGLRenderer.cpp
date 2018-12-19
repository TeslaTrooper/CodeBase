#include "BaseOpenGLRenderer.h"

void BaseOpenGLRenderer::beginDraw(const int framebufferID) const {
	glBindFramebuffer(GL_FRAMEBUFFER, framebufferID);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void BaseOpenGLRenderer::draw(const RenderData data) const {
	glBindVertexArray(data.vao);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glDrawElements(data.drawMode, data.indexCount, GL_UNSIGNED_INT, 0);
}

void BaseOpenGLRenderer::endDraw() const {
	glBindVertexArray(0);
}