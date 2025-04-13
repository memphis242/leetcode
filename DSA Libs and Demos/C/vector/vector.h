/**
 * @file vector.c
 * @brief API for a dynamic array (vector) in C.
 *
 * @author Abdulla Almosalami (memphis242)
 * @date April 12, 2025
 * @copyright MIT License
 */

/* File Inclusions */
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
// TODO: Exceptions

/* Public Macro Definitions */

/* Public Datatypes */

// Opaque type to act as a handle for the user to pass into the API
struct Vector_S;

/* Public API */

/**
 * @brief Constructor for the vector object
 *
 * Allocates memory for a dynamic array (vector) and initializes its properties.
 *
 * @param element_size The size of each element in the vector (in bytes).
 * @param initial_length The initial number of elements the vector can hold.
 *
 * @return A pointer to the initialized vector, or NULL if allocation fails.
 */
struct Vector_S * VectorInit( size_t element_size, uint32_t initial_length );

/**
 * @brief Frees the memory allocated for the vector.
 *
 * Releases all resources associated with the vector, including its internal data.
 *
 * @param self A pointer to the vector to be freed.
 */
void VectorFree( struct Vector_S * self );

/**
 * @brief Inserts an element into the vector.
 *
 * Adds a new element to the end of the vector, resizing the vector if necessary.
 *
 * @param self A pointer to the vector.
 * @param element A pointer to the element to be inserted.
 *                The memory pointed to must not overlap with the vector's memory.
 *
 * @return `true` if the insertion is successful, `false` otherwise.
 */
bool VectorInsert( struct Vector_S * self, const void * restrict element );

/**
 * @brief Removes an element from the vector at the specified index.
 *
 * Deletes the element at the given index and shifts subsequent elements to fill
 * the gap.
 *
 * @param self A pointer to the vector.
 * @param idx The index of the element to be removed.
 * 
 * @return A pointer to the removed element, or NULL if the index is out of bounds.
 */
void * VectorRemove( struct Vector_S * self, uint32_t idx );

void * VectorElementAt( struct Vector_S * self, uint32_t idx );

void * VectorSetElementAt( struct Vector_S * self,
                           uint32_t idx,
                           const void * restrict element );

uint32_t VectorLength( struct Vector_S * self );

void * VectorLastElement( struct Vector_S * self );

void VectorClear( struct Vector_S * self );
