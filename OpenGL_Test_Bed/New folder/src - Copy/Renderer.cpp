#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall()
{
    while (GLenum error = glGetError())
    {
        return false;
    }
    return true;
}

