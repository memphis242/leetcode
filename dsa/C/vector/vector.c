/**
 * @file vector.c
 * @brief Implementation of a dynamic array (vector) in C.
 *
 * This file contains the implementation of a dynamic array, also known as a vector,
 * which provides functionalities for dynamic resizing, element access, and manipulation.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date April 12, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* Local Macro Definitions */

// Enforce a maximum length to help prevent extreme memory requests
#define TENTATIVE_MAX_VEC_LEN 100000 // 100,000
#if(SIZE_MAX < TENTATIVE_MAX_VEC_LEN)
   #define MAX_VECTOR_LENGTH  SIZE_MAX
#else
   #define MAX_VECTOR_LENGTH  TENTATIVE_MAX_VEC_LEN
#endif

/* Local Datatypes */

struct Vector_S
{
   void * vector;
   size_t element_size;
   uint32_t len;
};

/* Private Function Prototypes */

/* Public API Implementations */

// TODO: Support custom allocators passed in
struct Vector_S * VectorInit( size_t element_size, uint32_t initial_length )
{
   // Early return op
   // Invalid inputs
   if ( (element_size == 0) ||
        (initial_length > MAX_VECTOR_LENGTH) )
   {
      // TODO: Vector constructor exception → assert()?
      return NULL;
   }

   struct Vector_S * NewVec = (struct Vector_S *)malloc( sizeof(struct Vector_S) );
   NewVec->element_size = element_size;
   NewVec->len = initial_length;
   if ( 0 == initial_length )
   {
      NewVec->vector = NULL;
   }
   else
   {
      NewVec->vector = malloc( (size_t)(element_size * initial_length) );
   }

   return NewVec;
}

/* Private Function Implementations */
