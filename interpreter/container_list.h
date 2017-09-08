#pragma once

#include <stdlib.h>

namespace Container
{

template<typename T>
struct ListEntry
{
  ListEntry(T const& data) :
      data(data), next(nullptr)
  {
  }

  T data;
  ListEntry<T>* next;
};

template<typename T>
class ListIterator
{
public:
  ListIterator(ListEntry<T>* cur) :
      cur(cur)
  {
  }
  bool hasNext();
  T& next();

private:
  ListEntry<T>* cur;
};

template<typename T>
bool ListIterator<T>::hasNext()
{
  return cur;
}

template<typename T>
T& ListIterator<T>::next()
{
  T& data = cur->data;
  cur = cur->next;
  return data;
}

template<typename T>
class List
{
public:
  List() :
      root(nullptr)
  {
  }

  void add(T const& data);
  size_t length() const;
  ListIterator<T> getIterator() const;

private:
  ListEntry<T>* root;
};

template<typename T>
void List<T>::add(T const& data)
{
  ListEntry<T>* newEntry = new ListEntry<T>(data);
  newEntry->data = data;

  if (!root)
  {
    root = newEntry;
    return;
  }

  auto cur = root;
  while (cur->next)
  {
    cur = cur->next;
  }
  cur->next = newEntry;
}

template<typename T>
size_t List<T>::length() const
{
  size_t len = 0;
  for (auto cur = root; cur; cur = cur->next)
  {
    len++;
  }
  return len;
}

template<typename T>
ListIterator<T> List<T>::getIterator() const
{
  return ListIterator<T>(root);
}

}
