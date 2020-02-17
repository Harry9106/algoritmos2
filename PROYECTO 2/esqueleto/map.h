#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdio.h>
#include "string.h"

/* map_t is a pointer to a node.
 * Note: The definition of the node structure should be in [map.c], 
 * and not here.
 */
typedef struct _node_t *map_t;

/* Key and value, both of type string */
typedef string_t key_t;
typedef string_t value_t;

/* Rename operations */
#define key_destroy string_destroy
#define key_eq string_eq
#define key_less string_less
#define key_dump string_dump
#define value_destroy string_destroy
#define value_dump string_dump

/* Creates an empty map.
 */
map_t map_empty();

/* Puts the [key] associated with the value [value] in the map.
 * If [key] is already in the map, its
 * old value is replaced by [value].
 */
map_t map_put(map_t map, key_t key, value_t value);

/* Returns a reference to the value associated with the given [key]. 
 * If [key] is not in the map, returns NULL.
 */
value_t map_get(map_t map, key_t key);

/* Returns true if the [key] is in the map, or false otherwise.
 */
bool map_contains(map_t map, key_t key);

/* Removes the key [key] from the map. If [key] is not in the
 * map, it does nothing and returns the map unchanged.
 */
map_t map_remove(map_t map, key_t key);

/* Prints the map in the given [file], showing each key and its definition.
 * Note: To print the map in the screen, use [map_dump(map, stdout)]. 
 * See "man stdout"
 */
void  map_dump(map_t map, FILE *file);

/* Destroys the map, by freeing all the allocated resources.
 */
map_t map_destroy(map_t map);

#endif
