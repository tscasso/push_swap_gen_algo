/* ****************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:19:07 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 22:03:39 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	handle_error(void)
{
	fprintf(stderr, "Error\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char *argv[])
{
	t_node	*stackA;
	t_node	*stackB;
	t_arr	arr;
	

	stackA = NULL;
	stackB = NULL;
	(void)stackB;
	arr.len = 0;
	arr.av_ints = NULL;

	if (argc < 2)
		handle_error();

	init_and_check_stacks(argc, argv, &arr, &stackA);
	sort_stack(&stackA, &stackB);

printf("processus reussi\n");
	clear_stack_A(&stackA);
	clear_stack_B(&stackB);
	return (0);
}

