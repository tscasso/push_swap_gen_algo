/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 20:45:10 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 22:04:07 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Vérifie si tous les caractères d'une chaîne sont des chiffres

#include <limits.h>
#include "push_swap.h"

int	check_is_digit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Vérifie s'il y a des doublons dans le tableau d'entiers

int	check_dup(int *arr, int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (arr[i] == arr[j])
				return (0);
		}
	}
	return (1);
}

// Vérifie si tous les entiers dans la chaîne sont dans la plage de int

int	check_int(char **av_list, int *av_ints)
{
	int i = 0;
	while (av_list[i])
	{
		long nbr = atol(av_list[i]);
		if (nbr < INT_MIN || nbr > INT_MAX)
			return (0);
		av_ints[i] = (int)nbr;
		i++;
	}

	return (1);
}
