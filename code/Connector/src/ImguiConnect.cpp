#include "../headers/ApplicationInterface.h"
#include "../headers/ImguiConnect.h"

#include <GL/gl3w.h>

#include <GL/freeglut.h>
#include <backends/imgui_impl_glut.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>

#define TIME_PER_FRAME 1000.f / 60.f // Approx. 60 fps

ImguiConnect::ImguiConnect(ApplicationInterface *application, int argc,
                           char **argv) {
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
  glClearColor(1.f, 1.f, 1.f, 1.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  mApplication->Init();
  if (!mApplication->Load(argc, argv)) {
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
  delete mApplication;
  mApplication = nullptr;
}

void ImguiConnect::KeyPressed(unsigned char key, int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.key = key;
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  uiContext.keyPressed = true;
  mApplication->Event(UIEvent::Key);
}

void ImguiConnect::KeyReleased(unsigned char key, int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.key = key;
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  uiContext.keyPressed = false;
  mApplication->Event(UIEvent::Key);
}

void ImguiConnect::SpecialKeyPressed(int key, int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.specialKey = key;
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  uiContext.specialKeyPressed = true;
  mApplication->Event(UIEvent::SpecialKey);
}

void ImguiConnect::SpecialKeyReleased(int key, int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.specialKey = key;
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  uiContext.specialKeyPressed = false;
  mApplication->Event(UIEvent::SpecialKey);
}

void ImguiConnect::MouseMove(int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  mApplication->Event(UIEvent::MouseMove);
}

void ImguiConnect::MouseCallBack(int button, int state, int x, int y) {
  auto &uiContext = Context::GetUIData();
  uiContext.mouseButton = button;
  uiContext.mouseState = state;
  uiContext.mouseX = x;
  uiContext.mouseY = y;
  mApplication->Event(UIEvent::MouseClick);
}

void ImguiConnect::ResizeCallback(int width, int height) {
  ImGui_ImplGLUT_ReshapeFunc(width, height);
  glViewport(0, 0, width, height);
  auto &uiContext = Context::GetUIData();
  uiContext.width = width;
  uiContext.height = height;
  mApplication->Event(UIEvent::Resize);
}

void ImguiConnect::DrawCallback() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mApplication->Draw();
  glutSwapBuffers();
  glutPostRedisplay();
}

void ImguiConnect::IdleCallback() {
  while (!Context::EventsEmpty()) {
    char event = Context::PopEvent();
    mApplication->Event(event);
  }

  int currentTime = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = currentTime - mPrevTime;
  if (deltaTime > TIME_PER_FRAME) {
    // Every time we enter here is equivalent to a game loop execution
    if (!mApplication->Update(deltaTime)) {
      glutLeaveMainLoop();
      return;
    }
    mPrevTime = currentTime;
    glutPostRedisplay();
  }
}
