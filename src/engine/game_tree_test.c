/**
 * game_tree_test.c
 * 14 Dec 2002
 * jah and ram
 *
 * Tests for game_tree.h.
 * We are trying TestFirstDesign for the first time in
 * this project.
 * 
 */

#include "game_tree.h"
#include "move.h"

// Prints the game tree one node at a time
void printTree (pGameTree_t);

void testEmptyTree ();
void testSingleNodeTree ();

void 
printTree (pGameTree_t tree) 
{
	pGameTree_t child_iterator;
	
	if (tree == NULL) return;

	printf ("TreeNode At: %x\n", tree);

	// printing info postposed
	//printf ("Info: "); 
	//print_bits (getBoard_HashElem(getGameTreeInfo (tree)));
	//printf ("\neval: %d flags: %d ", 
	//		getEvaluation_HashElem (
	printf ("Parent: %x", tree->parent);
	printf ("FirstChild: %x", tree->first_child);
	printf ("NextBrother: %x", tree->next_brother);
	
	for (
		child_iterator = tree->first_child;
		child_iterator != NULL;
		child_iterator = child_iterator->next_brother
		)
			printTree (child_iterator);

}


int main ()
{
	testEmptyTree ();
	testSingleNodeTree ();
	testSinglePly ();
	return 0;
}



void testEmptyTree () 
{
	pGameTree_t eT = emptyGameTree;
	printTree (eT);
	destroyGameTree (&eT);
}

void testSingleNodeTree ()
{
	Move_t move = create_Move (0, 0, 0, 0);

	pGameTree_t snT;
	HashElem_t hE = create_HashElement (
		getEmptyBoard (), 0, 0, 0, move);
	snT = createGameTreeNode (hE);
	printTree (snT);
	destroyGameTree (&snT);

}