#include <da.hpp>
#include <iostream>

int main() {
  // Create a dynamic array of integers with an SBO local buffer of 8 elements
  da<int, 8> numbers;

  // Push values
  numbers.m_push(10);
  numbers.m_push(20);

  // Insert at a specific index
  numbers.m_insert(1, 15);

  // Check size and capacity
  int size = numbers.m_getSize();
  int cap = numbers.m_getCapacity();

  std::cout << size << '/' << cap << '\n';

  // Pop from the back
  numbers.m_pop();

  return 0;
}