#include "../headers/ImguiConnect.h"
#include "../headers/ImguiInterface.h"

#include <GL/gl3w.h>

#include <GL/freeglut.h>
#include <backends/imgui_impl_glut.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

ImguiConnect::ImguiConnect(ImguiInterface *application, int argc, char **argv) {
  mApplication = application;
  // GLUT initialization
  glutInit(&argc, argv);
  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(640, 480);

  glutCreateWindow(argv[0]);
  glutReshapeFunc(ResizeCallback);
  glutDisplayFunc(DrawCallback);
  glutIdleFunc(IdleCallback);
  glutKeyboardFunc(KeyPressed);
  glutKeyboardUpFunc(KeyReleased);
  glutSpecialFunc(SpecialKeyPressed);
  glutSpecialUpFunc(SpecialKeyReleased);
  glutMouseFunc(MouseCallBack);
  glutMotionFunc(MouseMove);

  // GL3W will take care of OpenGL extension functions
  gl3wInit();

  // Application instance initialization
  mApplication->init();
  if (!mApplication->load(argc, argv)) {
    std::cerr << "error loading" << std::endl;
    exit(1);
  }

  // Setup Dear ImGui context
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplGLUT_Init();
  ImGui_ImplOpenGL3_Init();

  mPrevTime = glutGet(GLUT_ELAPSED_TIME);
  // GLUT gains control of the application
  glutMainLoop();

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGLUT_Shutdown();
  ImGui::DestroyContext();
  mApplication = nullptr;
}

void ImguiConnect::KeyPressed(unsigned char key, int x, int y) {}
void ImguiConnect::KeyReleased(unsigned char key, int x, int y) {}
void ImguiConnect::SpecialKeyPressed(int key, int x, int y) {}
void ImguiConnect::SpecialKeyReleased(int key, int x, int y) {}
void ImguiConnect::MouseMove(int x, int y) {}
void ImguiConnect::MouseCallBack(int button, int state, int x, int y) {}
void ImguiConnect::ResizeCallback(int width, int height) {}
void ImguiConnect::RenderGui() {}
void ImguiConnect::DrawCallback() {}
void ImguiConnect::IdleCallback() {}
