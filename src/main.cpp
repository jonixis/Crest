#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Renderer.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "demos/DemoMenu.h"
#include "demos/DemoClearColor.h"
#include "demos/DemoTexture2D.h"

int main(void) {
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  /* Configure glfw */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Macos compatibility?

  window = glfwCreateWindow(800, 600, "Crest", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  /* Load glad (extension loader library for modern OpenGL) */
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

  Renderer renderer;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init((char *)glGetString(410)); // workaround: hard coded glsl version
  ImGui::StyleColorsDark();

  Demo::Demo* currentDemo = nullptr;
  Demo::DemoMenu* demoMenu = new Demo::DemoMenu(currentDemo);
  currentDemo = demoMenu;

  demoMenu->registerDemo<Demo::DemoClearColor>("Clear Color");
  demoMenu->registerDemo<Demo::DemoTexture2D>("2D Texture");

  /* RENDER LOOP */
  while (!glfwWindowShouldClose(window)) {

    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    renderer.clear();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    if (currentDemo) {
      currentDemo->onUpdate(0.0f);
      currentDemo->onRender();
      ImGui::Begin("Demos");
      if (currentDemo != demoMenu && ImGui::Button("Back")) {
        delete currentDemo;
        currentDemo = demoMenu;
      }

      currentDemo->onImGuiRender();
      ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  delete currentDemo;
  if (currentDemo != demoMenu)
    delete demoMenu;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}
