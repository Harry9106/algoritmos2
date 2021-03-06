#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <limits.h>


value_t knapsack_backtracking(item_t *items, unsigned int array_length, weight_t max_weight)
{
	value_t resultado= 0;
	value_t seleccionado=0;
	value_t no_seleccionado=0;
	if (array_length==0)
		return resultado;
	else if (item_weight(items[array_length-1])>max_weight)
		resultado=knapsack_backtracking(items,array_length-1,max_weight);
	else
	{
		no_seleccionado=knapsack_backtracking(items,array_length-1,max_weight);
		seleccionado=item_value(items[array_length-1])+knapsack_backtracking(items,array_length-1,max_weight-item_weight(items[array_length-1]));
	 	if (seleccionado>no_seleccionado)
	 		resultado=seleccionado;
	 	else resultado=no_seleccionado;
	}
	return resultado;
}

unsigned int* *create_table(unsigned int array_length, weight_t max_weight)
{
	unsigned int* *matriz = calloc(array_length, sizeof(unsigned int*));
	for (unsigned int i = 0; i < array_length; i++) 
		matriz[i] = calloc(max_weight, sizeof(unsigned int));
	return matriz;
}		      

value_t knapsack_dynamic(item_t *items,unsigned int array_length, weight_t max_weight)
{
	unsigned int* *matriz=create_table(array_length+1, max_weight+1);
	for (unsigned int i=0; i<array_length+1; i++)
		matriz[i][0]=0;
	for (unsigned int i=0; i<max_weight+1; i++)
		matriz[0][i]=0;
	for (unsigned int i=1; i<array_length+1; i++)
	{
		for (unsigned int j=1; j<max_weight+1; j++)
		{
			item_t candidato=items[i-1];
			if (item_weight(candidato)>j)
				matriz[i][j]=matriz[i-1][j];
			else
			{
				unsigned int no_seleccionado=matriz[i-1][j];
				unsigned int seleccionado=item_value(candidato)+matriz[i-1][j-item_weight(candidato)];
				if (seleccionado>no_seleccionado)
	 				matriz[i][j]=seleccionado;
	 			else matriz[i][j]=no_seleccionado;
			}
		}
	}
	for (unsigned int i=0; i<array_length+1; i++)
	{
		for (unsigned int j=0; j<max_weight+1; j++)
		{
			printf("%d",matriz[i][j]);
			printf("   ");
		}
		printf("\n");
	}
	unsigned int res=matriz[array_length][max_weight];
	for (unsigned int i=0; i<array_length+1; i++)
		free(matriz[i]);
	free(matriz);
	matriz=NULL;
	return res;
}

value_t knapsack_dynamic_selection(item_t *items, bool *selected,unsigned int array_length,weight_t max_weight)
{
	unsigned int* *matriz=create_table(array_length+1, max_weight+1);
	for (unsigned int i=0; i<array_length+1; i++)
		matriz[i][0]=0;
	for (unsigned int i=0; i<max_weight+1; i++)
		matriz[0][i]=0;
	for (unsigned int i=1; i<array_length+1; i++)
	{
		for (unsigned int j=1; j<max_weight+1; j++)
		{
			item_t candidato=items[i-1];
			if (item_weight(candidato)>j)
				matriz[i][j]=matriz[i-1][j];
			else
			{
				unsigned int no_seleccionado=matriz[i-1][j];
				unsigned int seleccionado=item_value(candidato)+matriz[i-1][j-item_weight(candidato)];
				if (seleccionado>no_seleccionado)
	 				matriz[i][j]=seleccionado;
	 			else matriz[i][j]=no_seleccionado;
			}
		}
	}
	unsigned int i=array_length;
	unsigned int j=max_weight;
	while (i!=0)
	{
		if (matriz[i][j]==matriz[i-1][j])
		{
			selected[i-1]=false;
		}
		else
		{
			selected[i-1]=true;
			j=j-item_weight(items[i-1]);
		}
		i=i-1;
	}
	unsigned int res=matriz[array_length][max_weight];
	for (unsigned int i=0; i<array_length+1; i++)
		free(matriz[i]);
	free(matriz);
	matriz=NULL;
	return res;
}
