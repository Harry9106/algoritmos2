#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "string.h"



struct _node_t
{
	string_t key;
	string_t value;
	struct _node_t *next;
};

/*Creates non-empty node
*/
map_t create_node(key_t key, value_t value)
{
	map_t map=NULL;
	map=calloc(1,sizeof(struct _node_t));
	map->key=key;
	map->value=value;
	map->next=NULL;
	return map;
}

/* Creates an empty map.
 */
map_t map_empty()
{
	return NULL;
}



/* Puts the [key] associated with the value [value] in the map.
 * If [key] is already in the map, its
 * old value is replaced by [value].
 */
map_t map_put(map_t map, key_t key, value_t value)
{
	if (map_contains(map, key))
	{
		map_t aux = map;
		if (aux==NULL)	//CASO LISTA VACIA
		{
			map=create_node(key,value);
		}
		else if (aux->next==NULL)	//CASO LISTA CON SOLO UN NODO
		{
			if(string_eq(key,aux->key))
			{
				string_destroy(map->key);
				string_destroy(map->value);
				free(map);
				map=create_node(key,value);
			}
			else
				aux->next=create_node(key,value);
		}
		else	//CASO LISTA CON 2 O MAS NODOS
		{ 
			while(aux!=NULL)
			{
				if(string_eq(key,aux->key))
				{
					string_destroy(aux->key);
					string_destroy(aux->value);
					aux->key=key;
					aux->value=value;
					return map;
				}
				if (aux->next==NULL)
					aux->next = create_node(key,value);
				aux=aux->next;
			}
		}
		aux = NULL;
		return map;
	}
	else // ESTE ES EL PUNTO ESTRELLA PARA INSERTAR UN NODO ALFABETICAMENTE
	{
		map_t aux = map;
		if (aux==NULL)	//CASO LISTA VACIA
			map=create_node(key,value);
		else if (string_less(key,aux->key))	//CASO LISTA CON UN SOLO NODO
		{
			map=create_node(key,value);
			map->next=aux;
		}
		else	//CASO LISTA CON 2 O MAS NODOS
		{
			map_t temp_node=NULL;
			while(aux->next!=NULL)
			{
				temp_node=aux->next;
				if(string_less(key,temp_node->key))
				{
					aux->next=create_node(key,value);
					aux=aux->next;
					aux->next=temp_node;
					temp_node=NULL;
					return map;
				}
				aux=aux->next;
			}
			temp_node=NULL;
			aux->next=create_node(key,value);
		}
		aux = NULL;
		return map;
	}
}


/* Returns a reference to the value associated with the given [key]. 
 * If [key] is not in the map, returns NULL.
 */
value_t map_get(map_t map, key_t key)
{
	map_t aux=map;
	while(aux!=NULL)
	{
		if (string_eq(key,aux->key))
		{
			return aux->value;
		}
		aux=aux->next;
	}
	return NULL;
}

/* Returns true if the [key] is in the map, or false otherwise.
 */
bool map_contains(map_t map, key_t key)
{
	map_t aux=map;
	while(aux != NULL)
	{
		if (string_eq(key,aux->key))
			return true;
		else aux=aux->next;
	}
	return false;
}

/* Removes the key [key] from the map. If [key] is not in the
 * map, it does nothing and returns the map unchanged.
 */
map_t map_remove(map_t map, key_t key)
{
	if (map==NULL)	//CASO LISTA VACIA
		return map;
	else if (string_eq(key,map->key))	//CASO LISTA CON SOLO UN NODO
	{
		map_t aux=map;
		map=map->next;
		string_destroy(aux->key);
		string_destroy(aux->value);
		free(aux);
		aux=NULL;
	}
	else	//CASO LISTA CON 2 O MAS NODOS
	{
		map_t anterior=map;
		map_t iterator=map->next;
		while(iterator!=NULL)
		{
			if (string_eq(key,iterator->key))
			{
				anterior->next=iterator->next;
				string_destroy(iterator->key);
				string_destroy(iterator->value);
				free(iterator);
				anterior=NULL;
				iterator=NULL;
			}
			else
			{
				anterior=iterator;
				iterator=iterator->next;
			}
		}
	}
	return map;
}

/* Prints the map in the given [file], showing each key and its definition.
 * Note: To print the map in the screen, use [map_dump(map, stdout)]. 
 * See "man stdout"
 */
void  map_dump(map_t map, FILE *file)
{
	while(map!=NULL)
	{
		string_t a = string_create(": ");
		string_t b = string_create(".\n");
		string_dump(map->key, file);
		string_dump(a, file);
		string_dump(map->value, file);
		string_dump(b, file);
		string_destroy(a);
		string_destroy(b);
		map=map->next;
	}
}

/* Destroys the map, by freeing all the allocated resources.
 */
map_t map_destroy(map_t map)
{
	if (map==NULL)	//CASO LISTA VACIA
		return map;
	else if (map!=NULL && map->next==NULL)	//CASO LISTA CON SOLO UN NODO
	{
		string_destroy(map->key);
		string_destroy(map->value);
		free(map);
		map=NULL;
		return map;
	}
	else	//CASO LISTA CON 2 O MAS NODOS
	{
		map_t temp_node=NULL;
		while(map!=NULL)
		{
			temp_node=map->next;
			string_destroy(map->key);
			string_destroy(map->value);
			free(map);
			map=temp_node;
		}
		temp_node=NULL;
		return map;
	}
}

