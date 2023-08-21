/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:19:26 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/14 15:19:28 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Duplique une stack donnée et renvoie un pointeur vers la nouvelle copie

t_node *duplicate_stack(t_node *stack)
{
    t_node *new_stack = NULL;
    t_node *current = stack;
    
    while (current != NULL)
    {
        push(&new_stack, current->value);
        current = current->next;
    }
    
    return new_stack;
}

// Vérifie si une stack est triée en ordre croissant

int	is_stack_sorted(t_node *stack)
{
    t_node *current = stack;
    
    while (current != NULL && current->next != NULL)
    {
        if (current->value > current->next->value)
            return 0; // La stack n'est pas triée
        current = current->next;
    }
    
    return 1; // La stack est triée
}

// Libère la mémoire d'une stack

void	free_stack(t_node *stack)
{
    t_node *current = stack;
    
    while (current != NULL)
    {
        t_node *temp = current;
        current = current->next;
        free(temp);
    }
}

// Vérifie si une stack est vide

int is_stack_empty(t_node *stack)
{
    return stack == NULL;
}

void clear_stack_A(t_node **stackA)
{
    while (!is_stack_empty(*stackA))
    {
        t_node *temp = *stackA;
        *stackA = (*stackA)->next;
        free(temp);
    }
}

void clear_stack_B(t_node **stackB)
{
    while (!is_stack_empty(*stackB))
    {
        t_node *temp = *stackB;
        *stackB = (*stackB)->next;
        free(temp);
    }
}