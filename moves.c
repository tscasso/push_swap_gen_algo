/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:27:00 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/13 21:27:02 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

 int	choose_random_move()
{

	int random_value = rand() % 11; // Génère un nombre aléatoire entre 0 et 10
   	switch (random_value)
	{
		case 0:
			return (SWAP_A);
		case 1:
			return (SWAP_B);
		case 2:
			return (SWAP_AB);
		case 3:
			return (PUSH_A);
		case 4:
			return (PUSH_B);
		case 5:
			return (ROTATE_A);
		case 6:
			return (ROTATE_B);
		case 7:
			return (ROTATE_AB);
		case 8:
			return (REVERSE_ROTATE_A);
		case 9:
			return (REVERSE_ROTATE_B);
		case 10:
			return (REVERSE_ROTATE_AB);
		default:
		// En cas de problème, retournez un mouvement invalide
			return (INVALID_MOVE);
	}
}

 void	apply_moves(t_node **stackA, t_node **stackB, int *moves, int num_moves)
{
    int 	i;
    
	i = 0;
	while (i < num_moves)
	{
		if (moves[i] == SWAP_A)
        {
			apply_swap_a(stackA);
            write(1, "sa", 2);
            write(1, "\n", 1);
        }
		else if (moves[i] == SWAP_B)
        {
			apply_swap_b(stackB);
             write(1, "sb", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == SWAP_AB)
        {
			apply_swap_ab(stackA, stackB);
            write(1, "ss", 2);
            write(1, "\n", 1);
        }
		else if (moves[i] == PUSH_A)
        {
			apply_push_a(stackA, stackB);
             write(1, "pa", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == PUSH_B)
        {
			apply_push_b(stackA, stackB);
             write(1, "pb", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == ROTATE_A)
        {
			apply_rotate_a(stackA);
             write(1, "ra", 2);
             write(1, "\n", 1);
        }    
		else if (moves[i] == ROTATE_B)
        {
			apply_rotate_b(stackB);
             write(1, "rb", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == ROTATE_AB)
        {
			apply_rotate_ab(stackA, stackB);
             write(1, "rr", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == REVERSE_ROTATE_A)
        {
			apply_reverse_rotate_a(stackA);
             write(1, "rra", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == REVERSE_ROTATE_B)
        {
			apply_reverse_rotate_b(stackB);
             write(1, "rrb", 2);
             write(1, "\n", 1);
        }
		else if (moves[i] == REVERSE_ROTATE_AB)
        {
			apply_reverse_rotate_ab(stackA, stackB);
             write(1, "rrr", 2);
             write(1, "\n", 1);
        }
		i++;
	}
}


 void apply_swap_a(t_node **stackA)
{
    if (*stackA && (*stackA)->next)
    {
        t_node *tmp = *stackA;
        *stackA = (*stackA)->next;
        tmp->next = (*stackA)->next;
        (*stackA)->next = tmp;
    }
}

 void apply_swap_b(t_node **stackB)
{
    if (*stackB && (*stackB)->next)
    {
        t_node *tmp = *stackB;
        *stackB = (*stackB)->next;
        tmp->next = (*stackB)->next;
        (*stackB)->next = tmp;
    }
}

 void apply_swap_ab(t_node **stackA, t_node **stackB)
{
    apply_swap_a(stackA);
    apply_swap_b(stackB);
}

 void apply_push_a(t_node **stackA, t_node **stackB)
{
    if (*stackB)
    {
        t_node *tmp = *stackB;
        *stackB = (*stackB)->next;
        tmp->next = *stackA;
        *stackA = tmp;
    }
}

 void apply_push_b(t_node **stackA, t_node **stackB)
{
    if (*stackA)
    {
        t_node *tmp = *stackA;
        *stackA = (*stackA)->next;
        tmp->next = *stackB;
        *stackB = tmp;
    }
}

 void apply_rotate_a(t_node **stackA)
{
    if (*stackA && (*stackA)->next)
    {
        t_node *tmp = *stackA;
        *stackA = (*stackA)->next;
        tmp->next = NULL;
        t_node *current = *stackA;
        while (current->next)
            current = current->next;
        current->next = tmp;
    }
}

 void apply_rotate_b(t_node **stackB)
{
    if (*stackB && (*stackB)->next)
    {
        t_node *tmp = *stackB;
        *stackB = (*stackB)->next;
        tmp->next = NULL;
        t_node *current = *stackB;
        while (current->next)
            current = current->next;
        current->next = tmp;
    }
}

 void apply_rotate_ab(t_node **stackA, t_node **stackB)
{
    apply_rotate_a(stackA);
    apply_rotate_b(stackB);
}

 void apply_reverse_rotate_a(t_node **stackA)
{
    if (*stackA && (*stackA)->next)
    {
        t_node *last = *stackA;
        t_node *prev = NULL;
        while (last->next)
        {
            prev = last;
            last = last->next;
        }
        prev->next = NULL;
        last->next = *stackA;
        *stackA = last;
    }
}

 void apply_reverse_rotate_b(t_node **stackB)
{
    if (*stackB && (*stackB)->next)
    {
        t_node *last = *stackB;
        t_node *prev = NULL;
        while (last->next)
        {
            prev = last;
            last = last->next;
        }
        prev->next = NULL;
        last->next = *stackB;
        *stackB = last;
    }
}

 void apply_reverse_rotate_ab(t_node **stackA, t_node **stackB)
{
    apply_reverse_rotate_a(stackA);
    apply_reverse_rotate_b(stackB);
}




