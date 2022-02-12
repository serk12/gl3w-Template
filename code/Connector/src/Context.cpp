#include "../headers/Context.h"

Context::Context() : mUIData() {}

Context &Context::GetActualContext() {
  static Context actual;
  return actual;
}
void Context::PushEvent(char event_) { mNextEvents.push(event_); }
char Context::PopEvent() {
  char next = mNextEvents.front();
  mNextEvents.pop();
  return next;
}
