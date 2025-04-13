#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Opaque type for a user to hold a handle to a heap to pass to the API
struct Heap_S;

struct Heap_S * HeapInit( int (* cmp)(const void * a, const void * b),
                          size_t element_size );
// bool HeapifyArray( const void * array, size_t length, size_t size_of_member, int (* comp)(const void * a, const void * b) );
// bool HeapInsert( const void * element );