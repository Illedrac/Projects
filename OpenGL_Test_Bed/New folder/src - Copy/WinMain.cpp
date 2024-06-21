#include "glew.h"
#include "glfw3.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    if (!stream.is_open())
    {
        std::cout << "File " << filepath << " Not Found!\n";
    }

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };


    std::string line;

    // Stack allocated array of stringstreams. One for vertex shader one for fragment
    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
    
        if (line.find("#shader") != std::string::npos)
        {
        
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }

        else
        {
            //Enum crafted such that 0th element is vertex and 1st is fragment
            //Thust we can just use the type as the index
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    GLCall(glShaderSource(id, 1, &src, nullptr));

    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*) _malloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader.\n";
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
  
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));

    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;

}


int WinMain()
{
    GLFWwindow* window;

    if (!glfwInit()) 
    {
        return -1;
    }

    window = glfwCreateWindow(750, 750, "Test", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Glew Init Error!" << std::endl;
    }

    float positions[8] = {
         -0.5f, -0.5f,
          0.5f, -0.5f,
          0.5f,  0.5f,
         -0.5f,  0.5f
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    
    VertexArray* va = new VertexArray();

    VertexBuffer* vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    va->AddBuffer(*vb, layout);

    IndexBuffer* ib = new IndexBuffer(indices, 6);
        
    ShaderProgramSource source = ParseShader("resources/shaders/Basic.shader");

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
    GLCall(glUseProgram(shader));

    int uniform_location = glGetUniformLocation(shader, "u_Color");

    assert(uniform_location != -1);
    
    glUniform4f(uniform_location, 0.0f, 1.0f, 1.0f, 1.0f);

    float b = 1.0f;
    float increment = 0.005f;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        if (b > 1.0f || b < 0.0f)
            increment *= -1.0f;

        b -= increment;

        glUniform4f(uniform_location, 0.5f, 0.05f, b, 1.0f);

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());
    }

    GLCall(glDeleteProgram(shader));

    delete vb;
    delete ib;

    glfwTerminate();

    return 1;
}