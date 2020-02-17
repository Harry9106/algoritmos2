#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdbool.h>
#include "string.h"

/* dict_t is a pointer to a structure.
 * Note: The definition of the structure should be in [dict.c], not here.
 */
typedef struct _dict_t *dict_t;

/* Creates an empty dictionary 
 */
dict_t dict_empty();

/* Adds a [word] and its definition [def] in the dictionary.
 * If [word] is already in the dictionary, its definition is replaced by [def].
 */
dict_t dict_add(dict_t dict, string_t word, string_t def);

/* Returns the definition of the given [word], or NULL if [word] is not in 
 * the dictionary.
 * Note: Returns a reference to the string owned by the dictionary (not a copy).
 */
string_t dict_search(dict_t dict, string_t word);

/* Returns true if the given word exists in the dictionary, and false otherwise.
 */
bool dict_exists(dict_t dict, string_t word);

/* Returns the number of words contained in the dictionary.
 * Complexity O(1)
 */
unsigned int dict_length(dict_t dict);

/* Removes the given word from the dictionary. If
 * [word] is not in the dictionary, it does nothing and
 * returns the dict unchanged.
 */
dict_t dict_remove(dict_t dict, string_t word);

/* Removes all the words from the dictionary.
 */
dict_t dict_remove_all(dict_t dict);

/* Prints all the words and its definitions in
 * the given file.
 * Note: Use [dict_dump(dict, stdout)] to print in the screen.
 */
void dict_dump(dict_t dict, FILE *file);

/* Destroys the given dictionary, freeing all the allocated resources.
 */
dict_t dict_destroy(dict_t dict);

#endif
