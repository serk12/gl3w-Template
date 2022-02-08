#include "./Connector/headers/ImguiConnect.h"
#include "./Core/headers/Hanbei.h"

int main(int argc, char **argv) {
  Hanbei *application = new Hanbei();
  ImguiConnect(application, argc, argv);
  delete application;
  return 0;
}
