/**
 * MoveList_test.c
 * jaH
 * 2 Nov 2002
 *
 * Tests the implementation in MoveList.c.
 *
 * This does these simple tests in the move list:
 *
 *  1. Empty List
 *    1.1 delete (pop) from empty list
 *    1.2 find in empty list, and delete NULL
 *    1.3 add to empty list
 *
 *  2. Single Element list
 *    2.1 delete 
 *    2.2 find, and delete
 *    2.3 add
 *
 *  3. Multiple Element list (use 5 elements)
 *    3.1 delete
 *    3.2 find, and delete
 *    3.3 add
 */

#include "MoveList.h"
#include "test_utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void testEmptyList ();
void testSingleton ();
void testLongList ();

Move_t createTestMove ();
pMoveList_t createTestSingleton ();

int 
main () {

  srand (27);
  printf ("Testing move list.\n");

  testEmptyList ();
  testSingleton ();
  testLongList ();

  printf ("End of tests.\n");
  return 0;

}

void testSingleton () {

  pMoveList_t list, single, find;
  Move_t move;

  printf ("Testing singleton lists.\nCreating singleton list for popFront.\n");

  // pop front
  list = createTestSingleton ();
  print_move_list (list);

  printf ("Poping from front:\n");
  single = popFrontNode_MoveList (&list);
  printf ("remaining:\n");
  print_move_list (list);
  printf ("popped:\n");
  print_move_list (single);

  destroy_MoveList (&list);
  destroy_MoveList (&single);

  // pop back
  printf ("Creating singleton list for popBack.\n");
  list = createTestSingleton ();
  print_move_list (list);

  printf ("Poping from back:\n");
  single = popBackNode_MoveList (&list);
  printf ("remaining:\n");
  print_move_list (list);
  printf ("popped:\n");
  print_move_list (single);

  destroy_MoveList (&list);
  destroy_MoveList (&single);

  // join front null
  printf ("Creating singleton list for join with null front.\n");
  list = createTestSingleton ();
  print_move_list (list);

  printf ("After joining with NULL from front:\n");
  list = join_MoveList (createEmpty_MoveList(), list);
  print_move_list (list);

  destroy_MoveList (&list);

  // join back null
  printf ("Creating singleton list for join with null back.\n");
  list = createTestSingleton ();
  print_move_list (list);

  printf ("After joining with NULL from back:\n");
  list = join_MoveList (list, createEmpty_MoveList());
  print_move_list (list);

  destroy_MoveList (&list);

  // join two singleton
  printf ("Creating two singleton lists for joining.\n");
  list = createTestSingleton ();
  single = createTestSingleton ();
  print_move_list (list);
  print_move_list (single);

  printf ("After joining:\n");
  list = join_MoveList (list, single);
  print_move_list (list);

  destroy_MoveList (&list);

  // finding, separating
  printf ("Creating singleton list to find and separate.\n");
  move = createTestMove ();
  list = createSingleNode_MoveList (move);
  print_move_list (list);
  find = findMove_MoveList (list, move);
  assert (separateNode_MoveList (&list, find) == TRUE);
  printf ("After separation:\nOriginal:\n");
  print_move_list (list);  
  printf ("Separated:\n");
  print_move_list (find);
  destroy_MoveList (&list);
  destroy_MoveList (&find);

  printf ("End of singleton list tests.\n");

}

void testLongList () {

  pMoveList_t list, single, find;
  //Move_t move;

  printf ("Testing long lists.\nCreating long list for popFront.\n");

  // pop front, back
  list = createTestSingleton ();
  single = createTestSingleton ();
  list = join_MoveList (list, single);
  single = createTestSingleton ();
  list = join_MoveList (list, single);
  single = createTestSingleton ();
  list = join_MoveList (list, single);
  
  print_move_list (list);
  printf ("After popping front:\n");
  find = popFrontNode_MoveList (&list);
  print_move_list (list);
  printf ("Popped:\n");
  print_move_list (find);
  destroy_MoveList (&find);
  single = copy_MoveList (list);
  printf ("Copied:\n");
  print_move_list (single);
  printf ("After popping back:\n");
  find = popBackNode_MoveList (&list);
  print_move_list (list);
  printf ("Popped:\n");
  print_move_list (find);
  printf ("Copy:\n");
  print_move_list (single);
  destroy_MoveList (&find);
  destroy_MoveList (&single);
  destroy_MoveList (&list);
  
  
  printf ("End of long list tests.\n");

}

void
testEmptyList () {

  pMoveList_t list, single;

  printf ("Testing empty lists.\nCreating empty list.\n");
  
  list = createEmpty_MoveList ();
  assert (list == NULL);
  assert (join_MoveList (list, createEmpty_MoveList ()) == NULL);
  assert (popFrontNode_MoveList (&list) == NULL);
  assert (popBackNode_MoveList (&list) == NULL);
  single = createTestSingleton ();
  assert (separateNode_MoveList (&list, single) == FALSE);
  destroy_MoveList (&single);
  assert (findMove_MoveList (list, createTestMove ()) == NULL);
  assert (getLastNode_MoveList (list) == NULL);
  destroy_MoveList (&list);
  assert (list == NULL);
  printf ("End of Empty list tests.\n");

}

Move_t
createTestMove () {

  unsigned int type, x, y, dir;
  type = rand ()/(RAND_MAX/4);
  x = rand ()/(RAND_MAX/5);
  y = rand ()/(RAND_MAX/5);
  dir = rand ()/(RAND_MAX/8);

  return 
    create_Move (type, x, y, dir);

}

pMoveList_t 
createTestSingleton () {

  return
    createSingleNode_MoveList 
    (
     createTestMove()
     );

}
