/**
 * MoveList.h
 * 1 Nov 2002
 * jaH
 *
 * Operations on a traditional linked list of moves.
 */

#ifndef bagchal_engine_MoveList_h
#define bagchal_engine_MoveList_h


#include "move.h"


/**
 * The move list is the typical linear null terminated linked list.
 * A list of moves.
 */

struct move_list_node {

  Move_t move;
  struct move_list_node *pnext;

};

typedef struct move_list_node *pMoveList_t;


/**
 * returns NULL.
 */
pMoveList_t createEmpty_MoveList ();

/**
 * creates a node of the move list from the given move, in effect
 * creating a single node list. An allocation is made for the new
 * node. If memory allocation fails, the program crashes.
 */
pMoveList_t createSingleNode_MoveList (Move_t);

/**
 * retunrs a joined move list. No allocations are made. The first move
 * list is joined to the front of the second. If the first list is
 * empty, the second is returned.
 */
pMoveList_t join_MoveList (pMoveList_t, pMoveList_t);

/**
 * dellocate all nodes in the given list. The list is reset to NULL
 */
void destroy_MoveList (pMoveList_t*);

/**
 * Returns the mode in the first node of the list, no nodes are
 * deallocated.  If the given list is empty, NULL is returned; else
 * the list now points to the tail of the list. The returned node
 * can be treated as a single node list.
 */
pMoveList_t popFrontNode_MoveList (pMoveList_t*);

/**
 * Pops the last node from the given list. If the list was initially
 * empty, null is returned.
 */
pMoveList_t popBackNode_MoveList (pMoveList_t*);

/**
 * Finds the given node in the given list. TRUE is returned if the
 * ndoe is found, otherwise FALSE. The found node is removed from the
 * list. The node can now be treated as a single node list.
 */
Boolean_t separateNode_MoveList (pMoveList_t*, pMoveList_t node);

/**
 * Searches the moves in the given list and find the first match from the
 * start. If no move identical to the given move is found, NULL is returned
 * else the node containing the found move is returned. The list is not
 * altered in the process.
 */
pMoveList_t findMove_MoveList (pMoveList_t, Move_t);

/**
 * Retrieves the last node of the given move list. If the move list is
 * empty NULL is returned.
 */
pMoveList_t getLastNode_MoveList (pMoveList_t);

/**
 * Makes a copy of the move list. Both the lists are allocated, and
 * need to be destroyed for cleanup.
 */
pMoveList_t copy_MoveList (pMoveList_t);

/**
 * Counts the number of moves in the move list.
 */
unsigned int getNodeCount_MoveList (pMoveList_t);

#endif
