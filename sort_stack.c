/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:37:27 by tscasso           #+#    #+#             */
/*   Updated: 2023/08/12 21:46:43 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"



void print_stack(t_node *stack)
{
    t_node *current = stack;
    printf("Contenu de la pile : ");
    while (current != NULL)
    {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void print_hash_table(t_hash_table *hash_table)
{
    printf("Contenu de la table de hachage :\n");
    for (int i = 0; i < hash_table->size; i++)
    {
        printf("Index %d : ", i);
        t_hash_node *current = hash_table->buckets[i];
        while (current != NULL)
        {
            printf("%d ", current->value);
            current = current->next;
        }
        printf("\n");
    }
}

void print_inorder(t_binary_node *root)
{
    if (root != NULL)
    {
        print_inorder(root->left);
        printf("%d ", root->value); // Affiche la valeur du nœud actuel
        print_inorder(root->right);
    }
}

void	sort_stack(t_node **stackA, t_node **stackB)
{
	t_binary_node	*binary_tree;
	t_hash_table	*hash_table;

	t_node *currentNode = *stackA; // Utilisez une variable temporaire pour parcourir la pile


	*stackB = (t_node *)malloc(sizeof(t_node));
    if (*stackB == NULL)
    {
        handle_error();
    }
    (*stackB)->value = 0; // Initialisation par défaut (ou autre valeur appropriée)
    (*stackB)->next = NULL;



	binary_tree = NULL;
	hash_table = create_hash_table();
	printf("Table de hachage créée avec une taille de %d\n", hash_table->size);
	//(void)stackB;

	// Vérification de la pile A avant la construction de l'arbre
    if (stackA == NULL || *stackA == NULL)
    {
        fprintf(stderr, "Erreur : stackA est NULL ou pointe vers une zone mémoire non valide.\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("La pile A est valide avant la construction de l'arbre.\n");
        print_stack(*stackA);
    } 

	// Etape 1 : Construction de l'arbre binaire
	printf("Construction de l'arbre binaire...\n");

	printf("Pile A avant l'insertion dans l'arbre:\n");
    print_stack(*stackA);

	while (currentNode != NULL)
{
    binary_tree = insert_into_binary_tree(binary_tree, currentNode->value);
    //printf("Valeur %d insérée dans l'arbre binaire\n", currentNode->value);
    currentNode = currentNode->next; // Avancez dans la pile sans modifier *stackA

	 //if (currentNode == NULL) {
            //fprintf(stderr, "Pointeur de pile A nul pendant la construction de l'arbre binaire\n");
            //exit(EXIT_FAILURE);
        //}
}
	 /* while (*stackA != NULL)
	{
		binary_tree = insert_into_binary_tree(binary_tree, (*stackA)->value);
		printf("Valeur %d insérée dans l'arbre binaire\n", (*stackA)->value);
		*stackA = (*stackA)->next;
	} */

	printf("Pile A avant le tri de l'arbre:\n");
    print_stack(*stackA);

	printf("Arbre binaire trié : ");
    	print_inorder(binary_tree);
    	printf("\n");

	// Vérification de la stack A avant la transmission de l'arbre
    printf("Vérification de la stack A avant transmission de l'arbre :\n");
    print_stack(*stackA);

	// Etape 2 : Transmission des valeurs de l'arbre à la table de hachage
	printf("Transmission des valeurs de l'arbre à la table de hachage...\n");
	inorder_traversal_and_transmit(binary_tree, hash_table);

	// Vérification des piles et de la table de hachage avant l'appel à l'algo génétique
    printf("Pile A avant l'appel à l'algo génétique:\n");
    print_stack(*stackA);
    printf("Pile B avant l'appel à l'algo génétique:\n");
    print_stack(*stackB);
    //printf("Contenu de la table de hachage avant l'appel à l'algo génétique:\n");
    //print_hash_table(hash_table);

	// Etape 3 : Utilisation de la table de hachage et de l'algo genetique
	printf("Transmission des valeurs de la table de hachage a l'algo genetique...\n");

	printf("Vérification de la stack A avant transmission a l'algo:\n");
    print_stack(*stackA);

	printf("Vérification de la stackB avant l'appel à optimize_with_genetic_algorithm...\n");
    if (stackB == NULL || *stackB == NULL) {
        printf("Erreur : stackB est NULL ou pointe vers une zone mémoire non valide.\n");
        // Vous pouvez décider de renvoyer une erreur, de terminer le programme, ou prendre une autre action appropriée.
    } else {
        printf("La stackB est valide, appel à optimize_with_genetic_algorithm...\n");
        printf("TTT: %p\n", &hash_table);
        printf("TTT: %p\n", &stackA);
        printf("TTT: %p\n", &stackB);
        optimize_with_genetic_algorithm(&hash_table, &stackA, &stackB);
    }
	
	/* optimize_with_genetic_algorithm(hash_table, stackA, stackB); */ 

	// Libération de la mémoire de l'arbre binaire et de la table de hachage
	free_binary_tree(binary_tree);
	free_hash_table(hash_table);	
}
