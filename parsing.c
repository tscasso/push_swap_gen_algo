/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:21:42 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 20:42:06 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



char	**split_and_check(char *av_buf, t_arr *arr)
{
	char	**av_list;

	av_list = ft_split(av_buf, ' ');
	if (!av_list)
		handle_error();
	arr->len = 0;
	while (av_list[arr->len])
		++(arr->len);
	return (av_list);
}

void	allocate_av_ints(t_arr *arr)
{
	arr->av_ints = (int *)malloc(sizeof(int) * arr->len);
	if (!arr->av_ints)
		handle_error();
}

void	free_and_handle(char **av_list, t_arr *arr, int *error)
{
	int	i;

	i = arr->len;
	while(i--)
		free(av_list[i]);
	free(av_list);
	if (*error)
	{
		free(arr->av_ints);
		handle_error();
	}
}

void	init_stack(int len, int *av_ints, t_node **stackA)
{
	int	i;

	i = len - 1;
	while (i >= 0)
	{
		printf("Pushing value %d onto stackA\n", av_ints[i]);
//printf("\n\n\nFJHSHFUISDHUFHIOJSEJIFHSD: %p\n\n\n", stackA);
		push(stackA, av_ints[i]);
		i--;
	}
	// Print the contents of the stack for verification
    printf("Contents of stackA after initialization: ");
    t_node *current = *stackA;
//	int iiiii = 0;
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
//		iiiii++;
    }
//    printf("\nI = %d\n", iiiii);
}

void	push(t_node **top, int value)
{
	t_node	*newNode;

	newNode = (t_node *)malloc(sizeof(t_node));
	if (!newNode)
		handle_error();

	newNode->value = value;
	newNode->next = *top;
	*top = newNode;
}

char	**fill_array(char **av_buf, int argc, t_arr *arr)
{
	char	**ret;
	int		i;

	ret = malloc(sizeof(char *) * argc);
	ret[argc - 1] = NULL;
	i = 0;
	while (i < argc - 1)
	{
		ret[i] = ft_strdup(av_buf[i + 1]);
		i++;
	}
	arr->len = i ;
	return (ret);
}

void	init_and_check_stacks(int argc, char **av_buf, t_arr *arr, t_node **stackA)
{
	char	**av_list;
	int	error;
	int	i;

	i= 0;
	error = 0;
	if (argc == 2)
		av_list = split_and_check(av_buf[1], arr);
	else if (argc > 2)
		av_list = fill_array(av_buf, argc, arr);
	allocate_av_ints(arr);
	
	printf("Parse : ");
	while (av_list && av_list[i])
	{
		if (!check_is_digit(av_list[i]) || !check_int(av_list, arr->av_ints) 			|| !check_dup(arr->av_ints, arr->len))
			error = 1;
		printf("%s, ", av_list[i]);
		i ++;
	}
	printf("\n");

	
	free_and_handle(av_list, arr, &error);
//printf("\n\n\nFJHSHFUISDHUFHIOJSEJIFHSD: %p\n\n\n", stackA);
	init_stack(arr->len, arr->av_ints, stackA);




//exit(0);

}


