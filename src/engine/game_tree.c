/**
 * game_tree.c
 * 14 Dec 2002
 * jah and ram
 *
 * Implementation for game_tree.h.
 * 
 */

#include "game_tree.h"
#include "debug_malloc.h"

pGameTree_t createGameTreeNode (HashElem_t hE)
{
	pGameTree_t pTree = 
		(pGameTree_t)malloc_debug (sizeof (GameTree_t));
	pTree->info = hE;
	pTree->parent = NULL;
	pTree->first_child = NULL;
	pTree->next_brother = NULL;
	return pTree;
}

void destroyGameTree (pGameTree_t * pTree) {
	pGameTree_t child_iterator;
	
	if ((*pTree) == NULL) return;

	// free children
	for (
		child_iterator = (*pTree)->first_child;
		child_iterator != NULL;
		child_iterator = child_iterator->next_brother
		) 
			destroyGameTree (&child_iterator);

	// free self
	free_debug (*pTree);
	*pTree = NULL;
}