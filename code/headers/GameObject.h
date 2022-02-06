#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
  virtual void event(){};
  virtual void update(int dt){};
  virtual void draw() const {};
};

#endif
