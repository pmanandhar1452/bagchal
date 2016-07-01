/**
 * game_tree.h
 * 14 Dec 2002
 * jah and ram
 *
 * A Tree data structure for evaluation and moves, -- the
 * GAME TREE.
 * 
 * Each node of the tree is the hashElem structure.
 */

#ifndef bagchal_engine_game_tree_h
#define bagchal_engine_game_tree_h

#include "hash.h"

struct game_tree_node_tag {
	HashElem_t info;
	struct game_tree_node_tag * parent;
	struct game_tree_node_tag * first_child;
	struct game_tree_node_tag * next_brother;
};

typedef struct game_tree_node_tag GameTree_t;
typedef GameTree_t * pGameTree_t;

#define emptyGameTree NULL

/**
 * Allocates a new game tree node using malloc, remember
 * destroy each node created, by destroying any tree that
 * you create.
 */
pGameTree_t createGameTreeNode (HashElem_t info);

/**
 * Deallocate the game tree. starting at the given node.
 * The node is set to NULL after deallocation.
 */
void destroyGameTree (pGameTree_t * ppGameTree_t);

/**
 * Add child to node. 
 */
void addChildToGameTreeNode (pGameTree_t node, pGameTree_t new_child);

#define getParentGameTreeNode (gN) ((gN)->parent)
#define getFirstChildGameTreeNode (gN) ((gN)->first_child)
#define getBrotherGameTreeNode (gN) ((gN)->brother)
#define getGameTreeInfo (gN) ((gN)->info)

#endif