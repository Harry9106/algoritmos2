#ifndef ITEM_H
#define ITEM_H
#include <stdbool.h>
#include "string.h"

typedef struct _item *item_t;
typedef unsigned int weight_t;
typedef unsigned int value_t;

/* Creates an item */
item_t item_create(string_t id, value_t value, weight_t weight);

/* Returns item's value */
value_t item_value(item_t item);

/* Returns item's weight */
weight_t item_weight(item_t item);

/* Returns item's id */
string_t item_id(item_t id);

/* Returns a dynamic array of items obtained from a file. Stores
 * the length of the array in *array_length 
 */
item_t *item_read_from_file(FILE *file, unsigned int *array_length);

/* Destroys the item */
item_t item_destroy(item_t item);

#endif
