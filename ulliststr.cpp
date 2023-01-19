#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
using namespace std;
#include <iostream>

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


void ULListStr::push_back(const std::string& val){
  // 0 items in list
  if (head_ == nullptr){
    Item* newItem = new Item();
    newItem->val[newItem->last] = val;
    newItem->last++;
    newItem->next = nullptr;
    newItem->prev = nullptr;
    head_ = newItem;
    tail_ = newItem;
  }
  // tail is full
  else if (tail_->last == 10){
    Item* newItem = new Item();
    // tail_->next = newItem;
    Item* temp = tail_;
    temp->next = newItem;
    tail_ = newItem;
    tail_->prev = temp;
    tail_->next = nullptr;
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  // space in front
  else {
    tail_->val[tail_->last] = val;
    tail_->last++;
    
  }
  size_++;
}

void ULListStr::push_front(const std::string& val) {
  // 0 items in list
  if (head_ == nullptr){
    Item* newItem = new Item();
    newItem->first = 9;
    newItem->last = newItem->first+1;
    newItem->val[newItem->first] = val;
    // newItem->last++;
    newItem->next = nullptr;
    newItem->prev = nullptr;
    head_ = newItem;
    tail_ = newItem;
  }
  // space behind first
  else if (head_->first>0){
    head_->first--;
    head_->val[head_->first] = val;
  }
  // head is full
  else {
    Item* newItem = new Item();
    newItem->last = 10;
    newItem->first = newItem->last-1;
    newItem->val[newItem->first] = val;
    newItem->next = head_;
    head_->prev = newItem;
    head_ = newItem;
    head_->prev = nullptr;
  }
  size_++;
}

void ULListStr::pop_front(){
  // 0 items
  if (empty()){
    return;
  }
  // 1 item

  else if(head_->first == head_->last-1){
    if (head_ == tail_){
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else {
      // multiple items
      Item* curr = head_;
      head_ = head_->next;
      head_->prev = nullptr;
      delete curr;
    }
  }
  else {
    head_->first++;
  }
  size_--;
}

void ULListStr::pop_back(){
  if (empty()){
    return;
  }
  // 1 item
  else if(tail_->first == tail_->last-1 && head_ == tail_){
    if (head_ == tail_){
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    } else {
    // multiple items
    Item* curr = tail_;
    tail_ = tail_->prev;
    tail_->next == nullptr;
    delete curr;
    }
  } else {
    tail_->last--;
  }
  size_--;
}


std::string const & ULListStr::back() const {
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const {
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const {    
  if (loc >= size_){
    return NULL;
  }
  Item* temp = head_;
  size_t i = temp->first;
  size_t count = 0;
  while(count < loc){
    i++;
    if (i==temp->last){
      temp = temp->next;
      i = temp->first;
    }
    count++;
  }
  return &temp->val[i];
}