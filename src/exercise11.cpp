#include "exercises.h"
#include "soil/SOIL.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern glm::vec3 rotationWithKeyCode(SDL_Keycode code);

int main11(int argc, char **argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);

    SDL_Event windowEvent;


    //
    //= OPENGL init
    //

    float vertices[] = {
    // Position         Color               Texcoords
        -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Top-left
         0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // Top-right
         0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Bottom-left
    };

    // Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Vertex Buffer Object
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create an element array
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLuint ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char const *vs = readcontent("vertex10.vsh");
    printf("%s\n", vs);
    glShaderSource(vertexShader, 1, &vs, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    char const *fs = readcontent("fragment10.fsh");
    printf("%s\n", fs);
    glShaderSource(fragmentShader, 1, &fs, NULL);
    glCompileShader(fragmentShader);

    printf("Compile Shader Error %d\n", glGetError());
    // Link the vertex and fragment into a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    printf("glAttachShader Vertex Error %d\n", glGetError());
    glAttachShader(shaderProgram, fragmentShader);
    printf("glAttachShader Fragment Error %d\n", glGetError());
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    printf("glUseProgram Error %d\n", glGetError());

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
            7*sizeof(GLfloat), 0);

    GLint colorAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colorAttrib);
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE,
            7*sizeof(GLfloat), (void*)(2*sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE,
            7*sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));


    int w, h;
    unsigned char *image= SOIL_load_image("sample.png", &w, &h, 0, SOIL_LOAD_RGB);

    printf("Width %d Height %d\n", w, h);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    printf("glTexParameteri Error %d\n", glGetError());


    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    //
    //= OPENGL end
    //


    GLint uniformTime = glGetUniformLocation(shaderProgram, "time");



    float g_rotationVelocity = 0;
    glm::vec3 g_rotationVec3 = glm::vec3(0, 0, 0);
    glm::mat4 g_modelTransformation;


    SDL_bool done = SDL_FALSE;
    while(!done)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            switch(windowEvent.type)
            {
                case SDL_QUIT:
                    {
                        done = SDL_TRUE;
                        break;
                    }
                case SDL_KEYDOWN:
                    {
                        SDL_Keycode keyCode = windowEvent.key.keysym.sym;
                        g_rotationVec3 = rotationWithKeyCode(keyCode);
                        g_rotationVelocity = 10;
                        break;
                    }
            }
        }

        GLfloat t = SDL_GetTicks();
        glUniform1f(uniformTime, t);

        // Clear the screen to black
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Model transformation
        //glm::mat4 modelTransformation;
        if (g_rotationVelocity > 0)
        {
            g_modelTransformation = glm::rotate(g_modelTransformation, (float)((float)g_rotationVelocity * 2 * M_PI/180.0), g_rotationVec3);
            g_rotationVelocity -= 0.5;
        }
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(g_modelTransformation));



        // View transformation
        glm::mat4 viewTransformation = glm::lookAt(
                glm::vec3(1.2f, 1.2f, 1.2f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(viewTransformation));

        // Projection transformation
        glm::mat4 projectionTransformation = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 10.0f);
        glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(projectionTransformation));


        // Draw things on framebuffer
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap buffers
        SDL_GL_SwapWindow(window);
    }

    //glDeleteTextures(1, &tex);

    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}

glm::vec3 rotationWithKeyCode(SDL_Keycode code)
{
    glm::vec3 rotation = glm::vec3(0, 0, 0);
    switch(code)
    {
        case SDLK_z:
            {
                rotation.z = 1.0;
                break;
            }
        case SDLK_x:
            {
                rotation.x = 1.0f;
                break;
            }
        case SDLK_y:
            {
                rotation.y = 1.0f;
                break;
            }
        default:
            {
                break;
            }
    }

    return rotation;
}
