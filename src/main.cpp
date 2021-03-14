#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <imgui.h>

#include "DemoMenu.h"
#include "DemoClearColor.h"
#include "DemoTexture2D.h"
#include "DemoCube.h"
#include "DemoModelLoader.h"

#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

#include "Renderer.h"

const unsigned int WINDOW_WIDTH = 1920;
const unsigned int WINDOW_HEIGHT = 1080;

int main(void) {
  GLFWwindow* window;

  if (!glfwInit())
    return -1;

  /* Configure glfw */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Macos compatibility?

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Crest", NULL, NULL);
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

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init((char *)glGetString(410)); // workaround: hard coded glsl version
  ImGui::StyleColorsDark();

  /* Initalize demos */
  Demo::Demo* currentDemo = nullptr;
  Demo::DemoMenu* demoMenu = new Demo::DemoMenu(currentDemo);
  currentDemo = demoMenu;

  // Set correct viewport size
  glm::ivec2 viewPortSize;
  glfwGetFramebufferSize(window, &viewPortSize.x, &viewPortSize.y);

  Demo::Settings demoClearColorSettings("Clear Color", viewPortSize);
  demoMenu->registerDemo<Demo::DemoClearColor>(demoClearColorSettings);

  Demo::Settings demoTexture2DSettings("Texture 2D", viewPortSize);
  demoMenu->registerDemo<Demo::DemoTexture2D>(demoTexture2DSettings);

  Demo::Settings demoCubeSettings("Cube", viewPortSize);
  demoMenu->registerDemo<Demo::DemoCube>(demoCubeSettings);

  Demo::Settings demoObjLoaderSettings("Model Loader", viewPortSize);
  demoMenu->registerDemo<Demo::DemoModelLoader>(demoObjLoaderSettings);

  /* RENDER LOOP */
  while (!glfwWindowShouldClose(window)) {

    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    Renderer::clear();

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
