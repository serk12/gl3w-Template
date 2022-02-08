#include "./Core/headers/Hanbei.h"
#include "./headers/ImguiConnect.h"

int main(int argc, char **argv) {
  Hanbei *application = new Hanbei();
  ImguiConnect(application, argc, argv);
  delete application;
  return 0;
}
