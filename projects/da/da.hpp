// NOTE: I hate this code, and want to burn it with fire. Don't ever implement this sh** again. Use std::vector or this implementation instead of making it again.

template <typename T>
class da {
private:
  T* a_data;
  int a_size;
  int a_capacity;

public:
  da(int capacity) {
    this->a_size = 0;
    if (capacity <= 1) {
      this->a_capacity = 1;
    } else {
      this->a_capacity = capacity;
    }
    this->a_data = new T[a_capacity];
  }

  ~da() {
    delete[] a_data;
  }

  int m_getSize() const { return a_size; }
  int m_getCapacity() const { return a_capacity; }

  void m_push(T value) {
    if (a_size == a_capacity) {
      T* temp = a_data; // Make a copy of a_data

      a_capacity *= 2; // Double a_capacity
      a_data = new T[a_capacity]; // Reset a_data

      for (int i = 0; i < a_size; i++) {
        // Copy all of the old data (temp) to the new version of a_data
        a_data[i] = temp[i];
      }

      delete[] temp; // Free temp from memory
    }

    a_data[a_size] = value; // Add the new value
    a_size++; // Increase the size by 1
  }

  void m_pop() {
    if (a_size == 0) { return; }
    a_size--;
  }

  void m_insert(int index, T value) {
    if (index < 0 || index > a_size) { return; }

    if (a_size == a_capacity) {
      T* temp = a_data; // Make a copy of a_data

      a_capacity *= 2; // Double a_capacity
      a_data = new T[a_capacity]; // Reset a_data

      for (int i = 0; i < a_size; i++) {
        // Copy all of the old data (temp) to the new version of a_data
        a_data[i] = temp[i];
      }

      delete[] temp; // Free temp from memory
    }

    for (int i = a_size - 1; i >= index; i--) {
      a_data[i + 1] = a_data[i];
    }

    a_data[index] = value;
    a_size++;
  }
};