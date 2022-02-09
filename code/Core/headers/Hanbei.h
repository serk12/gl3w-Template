#ifndef HANBEI_H
#define HANBEI_H

#include "../../Application/headers/Application.h"

class Hanbei : public Application {
public:
  Hanbei();
  bool Load(int argc_, char **argv_) override;
};

#endif
