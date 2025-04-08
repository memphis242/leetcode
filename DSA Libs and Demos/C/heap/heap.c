#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "heap.h"

#define MAX_NUM_OF_HEAP_NODES    10000000u   // 10 million
#define MAX_HEAP_HEIGHT          24u         // ⌈ log2(10,000,000) ⌉

struct Heap_S * HeapInit( int (* cmp)(const void * a, const void * b), size_t element_size )
{
   struct Heap_S * HeapInstance = (struct Heap_S *)malloc( sizeof(struct Heap_S) );
   HeapInstance->cmp_fcn = cmp;
   HeapInstance->heap = NULL;
   HeapInstance->element_size = element_size;
   HeapInstance->len = 0;

   return HeapInstance;
}

// struct Heap_S * Heapify( const void * arr, uint32_t num_of_elms, size_t element_size,
//                          int (* cmp)(const void * a, const void * b) )
// {
//    // Early return opportunities
//    if ( (NULL == arr) || (0 == num_of_elms) || (0 == element_size) ||
//         (num_of_elms > MAX_NUM_OF_HEAP_NODES) || (NULL == cmp) )
//    {
//       // Invalid arguments passed in!
//       return NULL;
//    }
// 
//    struct Heap_S * HeapInstance = (struct Heap_S *)malloc( element_size );
//    if ( NULL == HeapInstance )
//    {
//       // Failed to dynamically allocate memory!
//       return NULL;
//    }
// 
//    HeapInstance->cmp_fcn = cmp;
//    HeapInstance->element_size = element_size;
//    uint8_t * ptr = arr;
//    for ( uint32_t i = 0; i < num_of_elms; i++ )
//    {
//       HeapInsert( HeapInstance->heap, ptr );
//       ptr += element_size;
//    }
// 
//    return HeapInstance;
// }

bool InsertIntoHeap( struct Heap_S * self, const void * element )
{
   // Early return opportunity
   if ( (NULL == element) || (NULL == self) )
   {
      return false;
   }

   else if ( (0 == self->len) || (NULL == self->heap) )
   {
      // Heap has no elements yet, so ez-pz insertion!
      (void)memcpy( self->heap, element, self->element_size );
      self->len = 1;

      return true;
   }

   // Insert to the bottom layer's left-most open spot.
   // For array implementations, this is simply arr[self->len]!
   uint8_t * ptr_root = (uint8_t *)self->heap;
   uint8_t * ptr_new_mem = ptr_root + (self->len * self->element_size);
   (void)memcpy( ptr_new_mem, element, self->element_size );

   // Check against parent and perform necessary bubble-up swaps until the necessary heap property is satisfied
   size_t present_idx = HeapSize;
   size_t parent_idx = (present_idx - 1) / 2;
   size_t idx_diff = present_idx - parent_idx;
   uint8_t * ptr_to_inserted_element = ptr_new_mem;
   uint8_t * ptr_to_parent = ptr_to_inserted_element - (idx_diff * SizeOfMember);
   unsigned long long int counter = 0;
   void * temp = malloc(SizeOfMember);
   // Until newly inserted element's position respects the heap property...
   while ( (present_idx != 0) && (CompareElements( element, ptr_to_parent ) > 0) && (counter < MAX_HEAP_HEIGHT) )
   {
      // Swap
      if ( NULL == temp )
      {
         // Failed to dynamically allocate memory!
         return false;
      }

      // c = a
      (void)memcpy(temp, element, SizeOfMember);
      // a = b
      (void)memcpy(element, ptr_to_inserted_element, SizeOfMember);
      // b = c
      (void)memcpy(ptr_to_inserted_element, temp, SizeOfMember);

      counter++;
      present_idx = parent_idx;
      parent_idx = (present_idx - 1) / 2;
      idx_diff = present_idx - parent_idx;
      ptr_to_inserted_element = ptr_to_parent;
      ptr_to_parent = ptr_to_inserted_element - (idx_diff * SizeOfMember);
   }
   free(temp);

   return true;
}
