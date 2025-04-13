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
 * @param self Vector handleto be freed.
 */
void VectorFree( struct Vector_S * self );

/**
 * @brief Inserts an element into the vector.
 *
 * Adds a new element to the end of the vector, resizing the vector if necessary.
 *
 * @param self Vector handle
 * @param element A pointer to the element to be inserted.
 *                The memory pointed to must not overlap with the vector's memory.
 *
 * @return `true` if the insertion is successful, `false` otherwise.
 */
bool VectorInsert( struct Vector_S * self, const void * restrict element );

/**
 * @brief Retrieves the element at the specified index in the vector.
 *
 * Provides access to the element at the given index _without_ removing it.
 *
 * @param self Vector handle
 * @param idx The index of the element to retrieve.
 * 
 * @return A pointer to the element at the specified index, or NULL if the index
 *         is out of bounds.
 */
void * VectorGetElementAt( struct Vector_S * self, uint32_t idx );

/**
 * @brief Sets the value of an element at the specified index in the vector.
 *
 * Updates the element at the given index with the provided value.
 *
 * @param self Vector handle
 * @param idx The index of the element to update.
 * @param element A pointer to the new value to set at the specified index.
 *                The memory pointed to must not overlap with the vector's memory.
 * 
 * @return A pointer to the updated element, or NULL if the index is out of bounds.
 */
void * VectorSetElementAt( struct Vector_S * self,
                           uint32_t idx,
                           const void * restrict element );

/**
 * @brief Removes an element from the vector at the specified index.
 *
 * Deletes the element at the given index and shifts subsequent elements to fill
 * the gap.
 *
 * @param self Vector handle
 * @param idx The index of the element to be removed.
 * 
 * @return A pointer to the removed element, or NULL if the index is out of bounds.
 */
void * VectorRemoveElementAt( struct Vector_S * self, uint32_t idx );

/**
 * @brief Retrieves the number of elements in the vector.
 *
 * Returns the current number of elements stored in the vector.
 *
 * @param self Vector handle
 * 
 * @return The number of elements in the vector.
 */
uint32_t VectorLength( struct Vector_S * self );

/**
 * @brief Retrieves the last element in the vector.
 *
 * Provides access to the last element in the vector without removing it.
 *
 * @param self Vector handle
 * 
 * @return A pointer to the last element, or NULL if the vector is empty.
 */
void * VectorLastElement( struct Vector_S * self );

/**
 * @brief Clears all elements in the vector.
 *
 * Removes all elements from the vector, resetting its length to zero.
 * The allocated memory is not freed, allowing the vector to be reused.
 *
 * @param self Vector handle
 */
void VectorClear( struct Vector_S * self );
