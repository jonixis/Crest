#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdio>
#include <Renderer.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <VertexBufferLayout.h>
#include <Shader.h>



int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Configure glfw */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Macos compatibility?

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  /* Load glad (extension loader library for modern OpenGL) */
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  // Scope to clean up ib and vb on stack before glfwterminate destroys opengl context
  {
    float positions[] = {
      -0.5f, -0.5f, // index 0
      0.5f, -0.5f, // index 1
      0.5f, 0.5f, // index 2
      -0.5f, 0.5f // index 3
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };

    VertexArray va;
    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("res/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.8f, 0.2f, 0.8f, 1.0f);

    // Unbind all
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
      // /* Render here */
      renderer.clear();

      // Usually one would use materials for this and pass material to renderer
      shader.bind();
      shader.setUniform4f("u_Color", r, 0.2f, 0.8f, 1.0f);

      renderer.draw(va, ib, shader);

      if (r > 1.0f)
        increment = -0.05f;
      else if (r < 0.0f)
        increment = 0.05f;

      r += increment;

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }

  }

  glfwTerminate();
  return 0;
}
