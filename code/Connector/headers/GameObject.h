#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

// game object pattern
class GameObject {
public:
  // Chain of Responsibility
  virtual bool Event(char event_) { return false; };
  // exit application
  virtual bool Update(int dt_) { return false; };
  virtual void Draw() const {};
};

#endif
