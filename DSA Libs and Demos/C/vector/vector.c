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
#define MAX_VECTOR_LENGTH  1000000 // 1 million

/* Local Datatypes */

struct Vector_S
{
   size_t element_size;
   uint32_t len;
};

/* Private Function Prototypes */

/* Public API Implementations */

/* Private Function Implementations */
