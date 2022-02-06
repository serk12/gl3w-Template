#include "./headers/Application.h"
#include "./headers/ImguiConnect.h"

int main(int argc, char **argv) {
  Application *application = new Application();
  ImguiConnect(application, argc, argv);
  delete application;
  return 0;
}
