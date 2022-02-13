#include "../headers/Context.h"

#include <queue>

namespace Context {
// private namespace
namespace {
UIData mUIData;
std::queue<char> mNextEvents;
} // namespace

void PushEvent(char event_) { mNextEvents.push(event_); }
char PopEvent() {
  char next = mNextEvents.front();
  mNextEvents.pop();
  return next;
}
bool EventsEmpty() { return mNextEvents.empty(); }
UIData &GetUIData() { return mUIData; };

}; // namespace Context
