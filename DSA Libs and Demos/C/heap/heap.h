#include <stdbool.h>
#include <stddef.h>

struct Heap_S
{
   void * heap;
   int (* cmp_fcn)(const void * a, const void * b);
   size_t size_of_member;
   size_t num_of_members;
   bool heap_initialized;
};

struct Heap_S * HeapInit( int (* cmp)(const void * a, const void * b), size_t size_of_member );
// bool HeapifyArray( const void * array, size_t length, size_t size_of_member, int (* comp)(const void * a, const void * b) );
// bool InsertIntoHeap( const void * element );