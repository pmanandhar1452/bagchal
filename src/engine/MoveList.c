/**
 * MoveList.c
 * jaH
 * 2 Nov 2002
 */

#include "MoveList.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

pMoveList_t createEmpty_MoveList () { return NULL; }

pMoveList_t 
createSingleNode_MoveList (Move_t m) {

  pMoveList_t l;
  l = (pMoveList_t)malloc (sizeof (struct move_list_node));
  assert (l != NULL);

  l->move = m;
  l->pnext = NULL;

  return l;

}

pMoveList_t 
join_MoveList (pMoveList_t l1, pMoveList_t l2) {

  pMoveList_t last;

  if ( l1 == NULL ) return l2;
  if ( l2 == NULL ) return l1;
  
  last = getLastNode_MoveList (l1);
  last->pnext = l2;
  return l1;

}


void 
destroy_MoveList (pMoveList_t *pList) {

  pMoveList_t temp;
  
  while (*pList != NULL) 
    {
      temp = *pList;
      *pList = (*pList)->pnext;
      free (temp);
    }

}

pMoveList_t 
popFrontNode_MoveList (pMoveList_t *pList) {

  pMoveList_t front;

  if ( *pList == NULL ) return NULL;
  
  front = *pList;
  *pList = (*pList)->pnext;
  front->pnext = NULL;

  return front;

}


pMoveList_t 
popBackNode_MoveList (pMoveList_t *pList) {

  pMoveList_t last, runner;
  
  if ( *pList == NULL ) return NULL;

  runner = NULL;
  for ( last = *pList; last->pnext != NULL; ) {
    runner = last;
    last = last->pnext;
  }

  if ( runner != NULL ) runner->pnext = NULL;
  else *pList = NULL;

  return last;

}

Boolean_t 
separateNode_MoveList (pMoveList_t *pList, pMoveList_t node) {

  pMoveList_t runner, follower;

  if ( (*pList == NULL) || (node == NULL) ) return FALSE;

  runner = *pList;
  follower = NULL;
  while ( (runner != node) && (runner != NULL) ) {
    follower = runner;
    runner = runner->pnext;
  }

  if ( runner == node ) 
    { 
      // found
      if ( follower == NULL ) 
        { 
          //first node
          *pList = runner->pnext;
          runner->pnext = NULL;
          return TRUE;
        }
      else
        {
          follower->pnext = runner->pnext;
          runner->pnext = NULL;
          return TRUE;
        }
    }

  // not found
  return FALSE;

}

pMoveList_t 
findMove_MoveList (pMoveList_t list, Move_t move) {

  pMoveList_t runner;

  for (
       runner = list;
       runner != NULL;
       runner = runner->pnext
       )
    {
      if ( equals_Move ( list->move, move ) )
        return runner;
    }

  return NULL;

}

pMoveList_t 
getLastNode_MoveList (pMoveList_t list) {

  pMoveList_t runner;

  if ( list == NULL ) return NULL;

  for (
       runner = list;
       runner->pnext != NULL;
       runner = runner->pnext
       );

  return runner;

}

pMoveList_t
copy_MoveList (pMoveList_t list)
{

  pMoveList_t new_list, runner;
  
  new_list = createEmpty_MoveList ();
  for (
       runner = list;
       runner != NULL;
       runner = runner->pnext
       )
    new_list = join_MoveList 
      (
       new_list, 
       createSingleNode_MoveList 
       (runner->move)
       );
  return new_list;

}

unsigned int
getNodeCount_MoveList (pMoveList_t list) 
{

  unsigned int c = 0;
  pMoveList_t runner;
  for (
       runner = list;
       runner != NULL;
       runner = runner->pnext
       )
    c++;

  return c;


}
