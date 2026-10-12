#include "da.hpp"

#include <iostream>

using std::cout;

int main() {
  da<int> array(4);

  cout << array.m_getSize() << '/' << array.m_getCapacity() << "\n";

  array.m_push(255);
  array.m_push(250);
  array.m_push(245);
  array.m_push(240);
  array.m_insert(2, 4);

  cout << array.m_getSize() << '/' << array.m_getCapacity() << "\n";

  return 0;
}