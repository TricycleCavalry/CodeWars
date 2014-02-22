#include "object.h"

GameObject::GameObject(int x){
  attribute = x;
}

int GameObject::getAttr(){
  return (int)attribute;
}

void GameObject::setAttr(int set){
  attribute = set;
}

void GameObject::setMessage(const char* new_message){
  message.assign(new_message);
}

const char* GameObject::getMessage(){
  return message.c_str();
}
  
GameObject::~GameObject(){
  printf("deleted Object (%p)\n", this);
}