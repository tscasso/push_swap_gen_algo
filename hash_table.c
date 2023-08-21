/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:42:31 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/13 16:42:34 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	hash_function(int value, int table_size)
{
	unsigned long	hash;
	
	hash = (unsigned long)value;
	hash ^= (hash >> 20) ^ (hash >> 4);
	hash = hash ^ (hash >> 7) ^ (hash >> 4);
	return (hash % table_size);
}

void	insert_into_hash_table(t_hash_table *hash_table, int value)
{
	int	hash_index;
	
	hash_index = hash_function(value, hash_table->size);
	t_hash_node *new_node = (t_hash_node *)malloc(sizeof(t_hash_node));
	if (new_node == NULL)
		handle_error();
	new_node->value = value;
	new_node->next = hash_table->buckets[hash_index];
	hash_table->buckets[hash_index] = new_node;
	//printf("Valeur %d insérée dans la table de hachage à l'index %d\n", value, hash_index);
}

t_hash_table	*create_hash_table(void)
{
	t_hash_table *hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	
	if (hash_table == NULL)
		handle_error();

	// Initialisation de la table
	hash_table->size = HASH_TABLE_SIZE;
	hash_table->buckets = (t_hash_node **)calloc(HASH_TABLE_SIZE, sizeof(t_hash_node));
	
	if (hash_table->buckets == NULL)
	{
		free(hash_table);
		handle_error();
	}
	return (hash_table);
}

void free_hash_table(t_hash_table *hash_table)
{
    if (hash_table == NULL)
        return;

    int i = 0;
    while (i < hash_table->size) {
        t_hash_node *current = hash_table->buckets[i];
        while (current != NULL) {
            t_hash_node *temp = current;
            current = current->next;
            free(temp);
        }
        i++;
    }

    free(hash_table->buckets);
    free(hash_table);
}
