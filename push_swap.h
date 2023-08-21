/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 17:56:56 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 17:56:59 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>

# include "libft/libft.h"

/* Constants */

# define HASH_TABLE_SIZE 500
 
# define SWAP_A 1
# define SWAP_B 2
# define SWAP_AB 3
# define PUSH_A 4
# define PUSH_B 5
# define ROTATE_A 6
# define ROTATE_B 7
# define ROTATE_AB 8
# define REVERSE_ROTATE_A 9
# define REVERSE_ROTATE_B 10
# define REVERSE_ROTATE_AB 11
# define INVALID_MOVE -1

# define NUM_MOVES 500
# define MAX_NUM_MOVES 1000
# define MUTATION_RATE 0.1
# define POPULATION_SIZE 10
# define MAX_GENERATIONS 10

/* structure representant un element de la pile */

typedef struct s_node
{
	int value;
	struct s_node *next;
} t_node;

/* structure pour stocker des informations sur un tableau d'entiers */

typedef struct s_arr
{
	int len;
	int *av_ints;
} t_arr;

// Structure pour représenter les nœuds de l'arbre binaire

typedef struct s_binary_node
{
    	int value;
    	struct s_binary_node *left;
    	struct s_binary_node *right;
} t_binary_node;

/* Structure pour la table de hachage */

typedef struct s_hash_table
{
	int size;
	struct s_hash_node **buckets;
} t_hash_table;

/* Structure pour representer les noeuds de la table */

typedef struct s_hash_node
{
	int value;
	struct s_hash_node *next;
} t_hash_node;

typedef struct s_individual
{
    	int quality;
    	int moves[MAX_NUM_MOVES];
    	int num_moves;
} t_individual;

/* Parsing functions */

int     check_is_digit(char *str);
int     check_dup(int *arr, int len);
int     check_int(char **av_list, int *av_ints);

void    init_and_check_stacks(int argc, char **av_buf, t_arr *arr, t_node **stackA);
void    push(t_node **top, int value);
void    init_stack(int len, int *av_ints, t_node **stackA);
void    free_and_handle(char **av_list, t_arr *arr, int *error);
void    allocate_av_ints(t_arr *arr);

char    **split_and_check(char *av_buf, t_arr *arr);

/* Error function */

void	handle_error(void);

/* Sorting function */

void	sort_stack(t_node **stackA, t_node **stackB);

/* Binary tree functions */

t_binary_node	*insert_into_binary_tree(t_binary_node *root, int value);
void		inorder_traversal_and_transmit(t_binary_node *root, t_hash_table *hash_table);
void		free_binary_tree(t_binary_node *root);

/* Hash table functions */

t_hash_table	*create_hash_table(void);
void	insert_into_hash_table(t_hash_table *hash_table, int value);
int		hash_function(int value, int table_size);
void	free_hash_table(t_hash_table *hash_table);

/* Genetic algorithm */

void		optimize_with_genetic_algorithm(t_hash_table **hash_table, t_node ***stackA, t_node ***stackB);
int		random_chance(double probability);
void	evolve_population(t_individual *population, t_hash_table *hash_table, t_node **stackA, t_node **stackB);
void	apply_crossover(t_individual *parent1, t_individual *parent2, t_individual *child);
void	initialize_population(t_individual *population);
void	selection(t_individual *population, int population_size);
void	ft_swap_individuals(t_individual *ind1, t_individual *ind2);
void	apply_mutation(t_individual *individual);
void		update_population_quality(t_individual *population, t_hash_table *hash_table, t_node **stackA, t_node **stackB);
t_individual	get_best_individual(t_individual *population);
int 	evaluate_individual(t_individual *individual, t_hash_table *hash_table, t_node **stackA, t_node **stackB);

/* Moves */

int	choose_random_move();
void	apply_moves(t_node **stackA, t_node **stackB, int *moves, int num_moves);

void apply_swap_a(t_node **stackA);
void apply_swap_b(t_node **stackB);
void apply_swap_ab(t_node **stackA, t_node **stackB);
void apply_push_a(t_node **stackA, t_node **stackB);
void apply_push_b(t_node **stackA, t_node **stackB);
void apply_rotate_a(t_node **stackA);
void apply_rotate_b(t_node **stackB);
void apply_rotate_ab(t_node **stackA, t_node **stackB);
void apply_reverse_rotate_a(t_node **stackA);
void apply_reverse_rotate_b(t_node **stackB);
void apply_reverse_rotate_ab(t_node **stackA, t_node **stackB);

/* Stack operations */ 

t_node		*duplicate_stack(t_node *stack);
int		is_stack_sorted(t_node *stack);
void		free_stack(t_node *stack);
int		is_stack_empty(t_node *stack);
void	clear_stack_A(t_node **stackA);
void	clear_stack_B(t_node **stackB);

void print_stack(t_node *stack);
void print_hash_table(t_hash_table *hash_table);








#endif 
