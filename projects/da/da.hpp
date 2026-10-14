/*
 * Copyright (c) 2026- James-beans
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL version 2 was not distributed
 * with this file, You can obtain one at https://mozilla.org/MPL/2.0/ .
 */

// NOTE: I hate this code, and want to burn it with fire. Don't ever implement this sh** again.

#if !((defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) >= 202302L)
  #error "da.hpp requires at least C++23."
#endif

#ifndef DA_HPP
  #define DA_HPP

  #ifndef _SIZE_T_DEFINED
    #define _SIZE_T_DEFINED
typedef decltype(sizeof(0)) size_t;
  #endif // _SIZE_T_DEFINED

  #if __has_include(<efi.h>)
    #include <efi.h>

// Expected global system table provided by user's GNU EFI environment
extern EFI_SYSTEM_TABLE* SystemTable;

extern "C" {
  inline void* __da_uefi_allocate(size_t size) {
    if (size == 0) { size = 1; }
    void* buffer = nullptr;

    if (SystemTable && SystemTable->BootServices) {
      if (EFI_ERROR(SystemTable->BootServices->AllocatePool(EfiLoaderData, size, &buffer))) {
        return nullptr;
      }
    }
    return buffer;
  }

  inline void __da_uefi_deallocate(void* ptr) {
    if (ptr && SystemTable && SystemTable->BootServices) {
      SystemTable->BootServices->FreePool(ptr);
    }
  }
}

inline void* operator new(size_t size) { return __da_uefi_allocate(size); }
inline void* operator new[](size_t size) { return __da_uefi_allocate(size); }
inline void operator delete(void* ptr) noexcept { return __da_uefi_deallocate(ptr); }
inline void operator delete[](void* ptr) noexcept { return __da_uefi_deallocate(ptr); }
inline void operator delete(void* ptr, size_t) noexcept { return __da_uefi_deallocate(ptr); }
inline void operator delete[](void* ptr, size_t) noexcept { return __da_uefi_deallocate(ptr); }
  #endif // __has_include(<efi.h>)

template <typename T, size_t N = 0>
class da {
private:
  T* a_data;                // Pointer to current active storage (stack buffer or heap)
  int a_size;               // Number of elements currently stored
  int a_capacity;           // Total allocated capacity before needing a resize
  bool a_is_heap_allocated; // Tracks whether a_data points to heap memory or the stack buffer

  // SBO local storage buffer
  // Prevents object construction until elements are placed.
  alignas(T) char a_local_buffer[N * sizeof(T)];

  // Private helper to cast the raw local buffer into a typed T pointer
  T* m_getLocalBuffer() { return reinterpret_cast<T*>(a_local_buffer); }

  const T* m_getLocalBuffer() const { return reinterpret_cast<const T*>(a_local_buffer); }

public:
  // Sets up either stack SBO storage or heap allocation
  da(int capacity = (N > 0 ? N : 1)) {
    this->a_size = 0;
    int initial_cap = capacity <= 1 ? 1 : capacity;

    // If SBO is enabled (N > 0) and requested capacity fits within the local buffer limit
    if (N > 0 && initial_cap <= static_cast<int>(N)) {
      this->a_capacity = N;
      this->a_data = m_getLocalBuffer();
      this->a_is_heap_allocated = false; // Using stack buffer
    } else {
      // Otherwise, allocate dynamically on the heap
      this->a_capacity = initial_cap;
      this->a_data = new T[this->a_capacity];
      this->a_is_heap_allocated = true; // Using heap allocation
    }
  }

  // Only frees memory via `delete[]` if data was allocated on the heap
  ~da() {
    if (a_is_heap_allocated) { delete[] a_data; }
  }

  int m_getSize() const { return a_size; }
  int m_getCapacity() const { return a_capacity; }

  // Push element to the back, automatically growing and migrating to heap if capacity is exceeded
  void m_push(T value) {
    if (a_size == a_capacity) {
      int new_capacity = a_capacity * 2;
      T* new_data = new T[new_capacity]; // Always migrate or grow onto the heap on resize

      // Copy existing elements over to the new buffer
      for (int i = 0; i < a_size; i++) { new_data[i] = a_data[i]; }

      // Clean up old memory only if it was previously on the heap
      if (a_is_heap_allocated) { delete[] a_data; }

      a_data = new_data;
      a_capacity = new_capacity;
      a_is_heap_allocated = true; // Now officially heap-allocated
    }

    a_data[a_size] = value;
    a_size++;
  }

  // Pop element from the back (lazy decrement)
  void m_pop() {
    if (a_size == 0) { return; }
    a_size--;
  }

  // Insert element at a specific index, shifting elements and handling expansion if needed
  void m_insert(int index, T value) {
    if (index < 0 || index > a_size) { return; }

    if (a_size == a_capacity) {
      int new_capacity = a_capacity * 2;
      T* new_data = new T[new_capacity];

      for (int i = 0; i < a_size; i++) { new_data[i] = a_data[i]; }

      if (a_is_heap_allocated) { delete[] a_data; }

      a_data = new_data;
      a_capacity = new_capacity;
      a_is_heap_allocated = true;
    }

    // Shift elements to the right to make space for the new insertion
    for (int i = a_size - 1; i >= index; i--) { a_data[i + 1] = a_data[i]; }

    a_data[index] = value;
    a_size++;
  }
};

#endif // DA_HPP