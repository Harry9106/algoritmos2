#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dict.h"
#include "string.h"
#include "map.h"

// dict_t is a pointer to a structure.
struct _dict_t
{
	map_t map;
	unsigned int length;
};


/* Creates an empty dictionary 
 */
dict_t dict_empty()
{
	dict_t pd = calloc(1,sizeof(struct _dict_t));
	pd->map=map_empty();
	pd->length=0;
	
	return pd;
}

/* Adds a [word] and its definition [def] in the dictionary.
 * If [word] is already in the dictionary, its definition is replaced by [def].
 */
dict_t dict_add(dict_t dict, string_t word, string_t def)
{
	if (map_contains(dict->map,word))
	{
		dict->map=map_put(dict->map,word,def);
	}
	else
	{
		dict->map=map_put(dict->map,word,def);
		dict->length++;
	}
	
	return dict;
}

/* Returns the definition of the given [word], or NULL if [word] is not in 
 * the dictionary.
 * Note: Returns a reference to the string owned by the dictionary (not a copy).
 */
string_t dict_search(dict_t dict, string_t word)
{
	if (map_contains(dict->map,word))
	{
		return map_get(dict->map,word);
	}
	else
	{
		return NULL;
	}	
}

/* Returns true if the given word exists in the dictionary, and false otherwise.
 */
bool dict_exists(dict_t dict, string_t word)
{
	if (map_contains(dict->map,word)) 
		return true;
	else
		return false;
}

/* Returns the number of words contained in the dictionary.
 * Complexity O(1)
 */
unsigned int dict_length(dict_t dict)
{
	return dict->length;
}

/* Removes the given word from the dictionary. If
 * [word] is not in the dictionary, it does nothing and
 * returns the dict unchanged.
 */
dict_t dict_remove(dict_t dict, string_t word)
{
	if (dict_exists(dict,word)) 
	{
		dict->map=map_remove(dict->map,word);
		dict->length--;
		return dict;
	}
	else
		return dict;
}
/* Removes all the words from the dictionary.
 */
dict_t dict_remove_all(dict_t dict)
{
	dict->map=map_destroy(dict->map);
	dict->length=0;
	return dict;
}
/* Prints all the words and its definitions in
 * the given file.
 * Note: Use [dict_dump(dict, stdout)] to print in the screen.
 */
void dict_dump(dict_t dict, FILE *file)
{
	map_dump(dict->map, file);
}
/* Destroys the given dictionary, freeing all the allocated resources.
 */
dict_t dict_destroy(dict_t dict)
{
	map_destroy(dict->map);
	free(dict);
    dict = NULL;
    return dict;
}
