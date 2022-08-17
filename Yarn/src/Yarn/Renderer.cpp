#include "Renderer.h"

void Renderer::prepare()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel& model)
{
	glBindVertexArray(model.getVaoID());
	glEnableVertexAttribArray(0);
	
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
