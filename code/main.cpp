#include "./Connector/headers/ImguiConnect.h"
#include "./Core/headers/App.h"

int main(int argc, char **argv) {
  App *application = new App();
  ImguiConnect(application, argc, argv);
  delete application;
  return 0;
}
