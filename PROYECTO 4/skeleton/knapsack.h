#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <stdbool.h>
#include "item.h"

/* Especificaciones en enunciado */

value_t knapsack_backtracking(item_t *items,
			      unsigned int array_length, weight_t max_weight);

value_t knapsack_dynamic(item_t *items,
			 unsigned array_length, weight_t max_weight);

value_t knapsack_dynamic_selection(item_t *items, bool *selected,
				   unsigned int array_length,
				   weight_t max_weight);

#endif
