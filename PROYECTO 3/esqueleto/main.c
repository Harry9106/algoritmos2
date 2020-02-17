#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "dict_helpers.h"
#include "string.h"

void menu()
{
	printf(" \nChoose what you want to do. Options are:\n \n        **************************************************************\n        * z: Size of the dictionary                                  *\n        * s: Search for a definition in the dict                     *\n        * a: Add a new word to the dict                              *\n        * r: Remove a word from the dict                             *\n        * c: Change a definition to the dict                         *\n        * e: Empty the dict                                          *\n        * h: Show the dict in stdout                                 *\n        * l: Load the dict from a file                               *\n        * u: Dump the dict to a file                                 *\n        * q: Quit                                                    *\n        **************************************************************\n \nPlease enter your choice: ");
}

int main() 
{
	bool quit = false;
	dict_t dict= dict_empty();        
    while(quit==false) 
    {
		menu();
		string_t in = readstring_from_stdin();
		const char* choice=string_ref(in);
		switch(choice[0])
		{
			case 'z':
			{
				int res = dict_length(dict);
				printf("	-> The size of the dict is %d.\n",res);
			}
			break;
			case 's':
			{
						printf("	Please enter the word to search in the dict:");
						string_t inword=readstring_from_stdin();
						if (dict_exists(dict,inword))
						{
							const char* key=string_ref(inword);
							string_t aux = dict_search(dict, inword);
							const char* value=string_ref(aux);
							printf("	-> The definition of '%s' is: %s.",key, value);
							aux=NULL;
						}
						else
							printf("	-> The word does not exist in the dict.\n");
				     	inword=string_destroy(inword);
			}
			break;
					case 'a':
						{                            
								printf("	Please enter the word to add into the dict:");
								string_t inword = readstring_from_stdin();
								if (dict_exists(dict,inword))
								{
									printf("	-> The word is already in the dict.\n");
									string_destroy(inword);
								}
								else
								{
									printf("	Please enter the definition:");
									string_t indef = readstring_from_stdin();
									dict=dict_add(dict, inword, indef);
									printf("	-> The word and definition were added.\n");

								}
						
				        }
						break;
					case 'r':
						{
							printf("	Please enter the word to delete from the dict: ");
							string_t inword = readstring_from_stdin();
							if (dict_exists(dict,inword))
							{
								dict=dict_remove(dict,inword);
								printf("	-> The word was removed.\n");
							}
							else
								printf("	-> The word does not exist in the dict.\n");
							string_destroy(inword);
						}
						break;
					case 'c':
						{
							printf("	Please enter the word to replace in the dict: ");
							string_t inword = readstring_from_stdin();
							if (dict_exists(dict,inword))
							{
								printf("	Please enter the new definition: ");
								string_t invalue = readstring_from_stdin();
								dict=dict_add(dict,inword,invalue);
								printf("	-> The definition was replaced.\n");
							}
							else
							{
								printf("	-> The word does not exist in the dict.\n");
								string_destroy(inword);
							}
						}
						break;
					case 'e':
						{
							dict=dict_remove_all(dict);
							printf("	-> All words were removed.\n");
						}
						break;
					case 'h':
						{
							dict_dump(dict,stdout);
						}
						break;
					case 'l':
						{
							printf("	Please enter the filename to load the dict from: ");
						    string_t ruta = readstring_from_stdin();
						    const char* failruta = string_ref(ruta);                
						    dict_t fload = dict_from_file(ruta);
						    if (fload!=NULL)
						    {
						        dict_t aux = dict;
						        dict = fload;
						        dict_destroy(aux);
						        printf("	-> The dictionary was successfully loaded. \n");
						    }
						    else
						    {
						        printf("	Can not load dict from filename %s \n",failruta);   
						    }
						    string_destroy(ruta);
						}
						break;
					case 'u':
						{
							printf("    Please enter the filename to dump the file: ");
						    string_t failname = readstring_from_stdin();
						    dict_to_file(dict, failname);
						    printf("    -> The diccionary was successfully dumped. \n");                
							string_destroy(failname);
						}
						break;
					case 'q':
						{
							quit=true;
							printf("	-> Exiting.\n");
						}
						break;
					default:
						printf(" '%s' is invalid. Please choose a valid option.\n",choice);
						break;
		}
		string_destroy(in);
	}
	dict_destroy(dict);
	return 0;
}
