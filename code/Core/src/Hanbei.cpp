#include "../headers/Hanbei.h"
#include "../headers/HanbeiGui.h"

bool Hanbei::Load(int argc_, char **argv_) {
  mScene = new HanbeiGui();
  return true;
}
