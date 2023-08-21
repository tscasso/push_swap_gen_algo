/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:24:04 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 21:47:58 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


// Fonction d'insertion dans l'arbre binaire

t_binary_node	*insert_into_binary_tree(t_binary_node *root, int value)
{
    if (root == NULL)
    {
        t_binary_node *newNode = (t_binary_node *)malloc(sizeof(t_binary_node));
        if (newNode == NULL)
            handle_error();  // Gérer l'erreur d'allocation mémoire
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return (newNode);
    }
    if (value < root->value) 
        root->left = insert_into_binary_tree(root->left, value);
    else 
        root->right = insert_into_binary_tree(root->right, value);

    return (root);
}

// Fonction de parcours inordre de l'arbre binaire avec transmission à la table de hachage

void	inorder_traversal_and_transmit(t_binary_node *root, t_hash_table *hash_table)
{
    if (root != NULL)
    {
        inorder_traversal_and_transmit(root->left, hash_table);
        insert_into_hash_table(hash_table, root->value); // Transmet la valeur à la table de hachage
        inorder_traversal_and_transmit(root->right, hash_table);
    }
}

// Fonction pour libérer la mémoire de l'arbre binaire
void	free_binary_tree(t_binary_node *root) 
{
    if (root != NULL)
    {
        free_binary_tree(root->left);
        free_binary_tree(root->right);
        free(root);
    }
}
