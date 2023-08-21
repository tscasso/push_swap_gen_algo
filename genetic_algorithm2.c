/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genetic_algorithm2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:20:37 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/14 15:20:38 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


int evaluate_individual(t_individual *individual, t_hash_table *hash_table, t_node **stackA, t_node **stackB)
{
    t_node *stackA_copy = duplicate_stack(*stackA); // Dupliquez la stack A
    t_node *stackB_copy = duplicate_stack(*stackB); // Dupliquez la stack B
    int *moves = individual->moves;
    int num_moves = individual->num_moves;
    (void)hash_table;

    // Appliquez la séquence de mouvements à la copie de la stack A et B
    apply_moves(&stackA_copy, &stackB_copy, moves, num_moves);

    // Vérifiez si la stackA_copy est triée et la stackB_copy est vide
    if (is_stack_sorted(stackA_copy) && is_stack_empty(stackB_copy))
    {
printf("stack trie\n");
        free_stack(stackA_copy); // Libérez la mémoire de la copie de la stack A
        free_stack(stackB_copy); // Libérez la mémoire de la copie de la stack B
        return 0; // Individu valide, qualité 0 (meilleure qualité)
    }
    else
    {
printf("stack non trie\n");
printf("fin de la sequence\n");
        free_stack(stackA_copy); // Libérez la mémoire de la copie de la stack A
        free_stack(stackB_copy); // Libérez la mémoire de la copie de la stack B
        return 1; // Individu invalide, qualité 1 (pire qualité)
    }
}

void	evolve_population(t_individual *population, t_hash_table *hash_table, t_node **stackA, t_node **stackB)
{
    int	i;
    t_individual new_population[POPULATION_SIZE];

//     t_individual *new_population = malloc(sizeof(t_individual) * POPULATION_SIZE);
// if (new_population == NULL) {
//     fprintf(stderr, "Erreur : Impossible d'allouer de la mémoire pour new_population\n");
//     exit(EXIT_FAILURE);
// }

    printf("Starting evolution...\n");

    i = 0;
    while (i < POPULATION_SIZE)
    {
        apply_crossover(&population[i], &population[i + 1], &new_population[i]);
        apply_crossover(&population[i + 1], &population[i], &new_population[i + 1]);
        i += 2;
    }
    i = 0;
    while (i < POPULATION_SIZE)
    {
        if (random_chance(MUTATION_RATE))
        //printf("Applying mutation to individual %d...\n", i);
            apply_mutation(&population[i]);
        i++;
    }
    update_population_quality(new_population, hash_table, stackA, stackB);
}

int	random_chance(double probability)
{
    static int initialized = 0;
    
    if (!initialized) {
        srand(time(NULL)); // Initialiser une fois seulement
        initialized = 1;
    }
    double random_value = (double)rand() / RAND_MAX;
    //printf("random_chance: generated value = %lf\n", random_value); // Ajout pour le débogage
    return (random_value < probability);
}

void	apply_mutation(t_individual *individual)
{
    printf("apply_mutation: num_moves = %d\n", individual->num_moves); // Ajout pour le débogage

    if (individual->num_moves == 0) {
        fprintf(stderr, "Erreur : num_moves est égal à zéro\n");
        exit(EXIT_FAILURE);
    }

	int random_index = rand() % individual->num_moves;
	int random_move = choose_random_move();
	
	individual->moves[random_index] = random_move;
}


void	apply_crossover(t_individual *parent1, t_individual *parent2, t_individual *child)
{
	int	crossover_point;
	int	i;
	
	crossover_point = rand() % NUM_MOVES; // Point de croisement aleatoire 
	i = 0;
	while (i < crossover_point)
	{
		child->moves[i] = parent1->moves[i];
		i++;
	}
	while (i < NUM_MOVES)
	{
		child->moves[i] = parent2->moves[i];
		i++;
	}
    child->num_moves = parent2->num_moves;
}

// Met à jour la qualité de chaque individu dans la population

void	update_population_quality(t_individual *population, t_hash_table *hash_table, t_node **stackA, t_node **stackB)
{
    int i = 0;
    while (i < POPULATION_SIZE)
    {
        population[i].quality = evaluate_individual(&population[i], hash_table, stackA, stackB);
        i++;
    }
}

// Récupère le meilleur individu dans la population

t_individual	get_best_individual(t_individual *population)
{
    t_individual best_individual = population[0];
    int i = 1;
    while (i < POPULATION_SIZE)
    {
        if (population[i].quality < best_individual.quality)
        {
            best_individual = population[i];
        }
        i++;
    }
    return best_individual;
}

