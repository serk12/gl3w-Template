#ifndef HANBEI_H
#define HANBEI_H

#include "../../Application/headers/Application.h"

class App : public Application {
public:
  App();
  bool Load(int argc_, char **argv_) override;
};

#endif
