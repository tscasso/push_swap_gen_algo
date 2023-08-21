/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genetic_algorithm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 18:49:59 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/13 18:50:03 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Version original

void	initialize_population(t_individual *population)
{
	int	i;
	int	j;

	i = 0;
	while (i < POPULATION_SIZE)
	{
		population[i].num_moves = MAX_NUM_MOVES;
		//printf("Initialized individual %d with num_moves = %d\n", i, population[i].num_moves);
		population[i].quality = 0;
		j = 0;
		while (j < MAX_NUM_MOVES)
		{
			population[i].moves[j] = choose_random_move(); 
			j++;
		}
		i++;
	}
	//printf("initialize_population: num_moves = %d\n", population[0].num_moves); // Ajout pour le débogage
}
*/

// version 2 de initialize population

void initialize_population(t_individual *population)
{
    int i, j;

    i = 0;
    while (i < POPULATION_SIZE)
    {
        population[i].num_moves = rand() % (MAX_NUM_MOVES - 1) + 1; // Nombre aléatoire de mouvements entre 1 et MAX_NUM_MOVES
        population[i].quality = 0;
        
		// Limitez population[i].num_moves à un maximum de 10
        if (population[i].num_moves > NUM_MOVES) {
            population[i].num_moves = NUM_MOVES;
        }
		
        j = 0;
        while (j < population[i].num_moves)
        {
            population[i].moves[j] = choose_random_move();
            j++;
        }
        i++;
    }
}

void	selection(t_individual *population, int population_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < population_size)
	{
		j = i + rand() % (population_size - i);
		ft_swap_individuals(&population[i], &population[j]);
		i++;
	}
}

void	ft_swap_individuals(t_individual *ind1, t_individual *ind2)
{
	t_individual	temp;

	temp = *ind1;
	*ind1 = *ind2;
	*ind2 = temp;
}

void	optimize_with_genetic_algorithm(t_hash_table **hash_table, 
			t_node ***stackA, t_node ***stackB)
{
	t_individual	*population = malloc(sizeof(t_individual) * 500000);
	t_individual	*new_population = malloc(sizeof(t_individual) * 500000);


	if (!population || !new_population)
		return (write(1, "aaaaaa", 6), exit(1));
	// t_individual	new_population[POPULATION_SIZE];
	t_individual	best_individual;
	int				generation;

	generation = 0;
	printf("Initializing population...\n");
	initialize_population(population);
	//initialize_population(new_population);
	while (generation < MAX_GENERATIONS)
	{
		printf("Generation %d\n", generation);
		selection(population, POPULATION_SIZE);
		printf("Evolving population...\n");
		evolve_population(population, *hash_table, *stackA, *stackB);
		generation++;
	}
	best_individual = get_best_individual(new_population);
	apply_moves(*stackA, *stackB, best_individual.moves, best_individual.num_moves);
}
