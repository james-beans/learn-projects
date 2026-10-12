# da
> Dynamic Arrays

This library is a simple single-header implementation of C++ dynamic arrays. It should work with both the standard C++ library and freestanding C++. (GNU EFI supported built in with some setup required; Bare metal requires you to make a memory allocator and the `new` and `delete` keywords)

## License
da is licensed under the [MPLv2](../../LICENSE).

## Examples
With the C++ standard library:
```cpp
#include <da.hpp>
#include <iostream> // Optional, for printing

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
  int cap  = numbers.m_getCapacity();

  std::cout << size << '/' << cap << '\n'; // Print (Optional)

  // Pop from the back
  numbers.m_pop();

  return 0;
}
```

Without the C++ standard library (GNU EFI):
```cpp
#include <da.hpp> // Automatically includes <efi.h> if it can find it

// Custom function declarations for printing; Optional
void print_int(int n);
void print(const char16_t* s);

EFI_SYSTEM_TABLE* SystemTable = nullptr;

extern "C" EFI_STATUS efi_main(EFI_HANDLE IH, EFI_SYSTEM_TABLE* ST) {
  SystemTable = ST;

  // Create a dynamic array of integers with an SBO local buffer of 8 elements
  da<int, 8> numbers;

  // Push values
  numbers.m_push(10);
  numbers.m_push(20);

  // Insert at a specific index
  numbers.m_insert(1, 15);

  // Check size and capacity
  int size = numbers.m_getSize();
  int cap  = numbers.m_getCapacity();

  // Print (Optional)
  print_int(size);
  print(u"/");
  print_int(cap);
  print(u"\r\n");

  // Pop from the back
  numbers.m_pop();

  return EFI_SUCCESS;
}

// Optional:

void print_int(int n) {
  if (n < 0) {
    SystemTable->ConOut->OutputString(SystemTable->ConOut, const_cast<CHAR16*>(u"-"));
    n = -n;
  }
  char16_t buf[2] = { static_cast<char16_t>(u'0' + (n % 10)), 0 };
  if (n >= 10) { print_int(n / 10); }
  SystemTable->ConOut->OutputString(SystemTable->ConOut, reinterpret_cast<CHAR16*>(buf));
}

void print(const char16_t* s) {
  SystemTable->ConOut->OutputString(SystemTable->ConOut, const_cast<CHAR16*>(reinterpret_cast<const CHAR16*>(s)));
}
```

## API
### Instantiation
To create an instance of `da`, specify your type `T` and an optional SBO capacity `N`:
```cpp
da<T, N> name;
```
*(If `N > 0`, the array allocates up to `N` elements on the stack before seamlessly migrating to the heap)*

### Public Methods
- `void m_push(T value);`
  - Appends an element to the back of the array, automatically expanding capacity and migrating to the heap if necessary.
- `void m_pop();`
  - Removes the element at the back of the array via a lazy decrement.
- `void m_insert(int index, T value);`
  - Inserts an element at the specified index, shifting subsequent elements to the right and expanding capacity if needed.
- `void m_getSize() const;`
  - Returns the current number of elements stored in the array.
- `void m_getCapacity() const;`
  - Returns the total allocated capacity of the array.