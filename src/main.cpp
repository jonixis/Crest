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
#include "Texture.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
  window = glfwCreateWindow(800, 600, "Crest", NULL, NULL);
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
      -0.5f, -0.5f, 0.0f, 0.0f, // index 0
      0.5f, -0.5f, 1.0f, 0.0f, // index 1
      0.5f, 0.5f, 1.0f, 1.0f, // index 2
      -0.5f, 0.5f, 0.0f, 1.0f // index 3
    };

    unsigned int indices[] = {
      0, 1, 2,
      2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;
    layout.push<float>(2); // Add vertex positions
    layout.push<float>(2); // Add vertex texture coords
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.5f, 0));

    glm::mat4 mvp = proj * view * model;

    Shader shader("res/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_color", 0.8f, 0.2f, 0.8f, 1.0f);
    shader.setUniformMat4f("u_MVP", mvp);

    Texture texture("res/textures/logo.png");
    texture.bind();
    shader.setUniform1i("u_texture", 0);

    // Unbind all
    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    Renderer renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char *)glGetString(410)); // workaround: hard coded glsl version
    ImGui::StyleColorsDark();

    bool show_demo_window = true;
    bool show_another_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float r = 0.0f;
    float increment = 0.01f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
      // /* Render here */
      renderer.clear();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      // Usually one would use materials for this and pass material to renderer
      shader.bind();
      shader.setUniform4f("u_color", r, 0.2f, 0.8f, 1.0f);

      renderer.draw(va, ib, shader);

      {
        static float f = 0.0f;
        static int counter = 0;
        ImGui::Text("Crest");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        ImGui::ColorEdit3("clear color", (float *)&clear_color);

        ImGui::Checkbox("Demo Window", &show_demo_window);
        ImGui::Checkbox("Another Window", &show_another_window);

        if (ImGui::Button("Button"))
          counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      }

      if (r > 1.0f || r < 0.0f)
        increment *= -1.0f;

      r += increment;

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  }

  glfwTerminate();
  return 0;
}
