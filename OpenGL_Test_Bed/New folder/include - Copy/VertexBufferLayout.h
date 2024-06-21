#pragma once
#include <vector>
#include "glew.h"
#include "assert.h"
struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;


    static unsigned int GetSizeOfType(const unsigned int& type)
    {
        switch (type)
        {
            case GL_FLOAT:
            case GL_UNSIGNED_INT:
                return 4;

            case GL_UNSIGNED_BYTE:
                return 1;
        
            default:
                return 0;
                assert(false);
        }
    }
};

class VertexBufferLayout {

public:

    VertexBufferLayout()
        : m_Stride(0)
    {
    }

    template<typename t> void Push(unsigned int count)
    {
        assert(false);
        //static_assert(false);
    }

    template<> void Push<float>(unsigned int count)
    {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += sizeof(GLfloat) * count;
    }

    template<> void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += sizeof(GLuint) * count;

    }

    template<> void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += sizeof(GLubyte) * count;

    }

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
    inline const unsigned int GetStride() const { return m_Stride; }

private:

    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
};