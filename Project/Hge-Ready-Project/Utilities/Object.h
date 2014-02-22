/**
 * This is the main object that is actually used in the C++ code.
 * It is to be manipulated by Lua through the Lua wrapper object (which will
 * contain a pointer to this object).
 */
#ifndef _object_h_
#define _object_h_

// Notice that I don't need ANY Lua stuff in here...
#include <stdio.h>
#include <string>

class GameObject{
public:
  GameObject(int x);
  ~GameObject();

  int getAttr(void);
  void setAttr(int balance);

  void setMessage(const char* new_message);
  const char* getMessage(void);
private:
  int attribute;
  std::string message;
};
#endif