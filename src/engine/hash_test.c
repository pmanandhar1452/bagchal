/**
 * hash_test.c
 * jaH 12 Nov 2002
 *
 * Tests the implementation in hash.c and the concepts in hash.h
 *
 * Note that creating a hash table (as opposed to a linked list) can
 * be categorised as an omtimisation decision. It goes against
 * principle (remember Dijkstra's famous principle: Optimisation is
 * the root of all evil) that optimisation issues are handled before
 * the implementation at early stages of design. But, I believe that
 * bagchal is a special problem, not just another problem. It benefits
 * from all the research and experience that has gone into chess and
 * related games. I believe that chess provides significant
 * justification to implement a hash-table of evaluations. Also, the
 * alternatives such as linked list are not that easy and simple
 * either, and there are obvious flaws.
 *
 * The tests in this module are designed to test the following things
 * (which include both the concept and the implementation):
 *
 * A. Test for errors
 * B. Test for efficiency
 *   1. See that random moves are effectively distributed.
 *   2. See that non-random moves are effectively distributed
 *   3. Calibrate the collission rate for various table
 *      sizes/scenarios.
 *   4. Calculate the hash retrieval/storage/key-calcualation times.
 *
 * I will not be conducting a structurally or functionally oriented
 * hunt for errors test (the test cases in A). The exercise provided
 * by B will give me sufficient confidence that major bugs in the
 * program have been dealt with. So, in the interest of development
 * time, I will just carry out the tests designed to see the lower
 * parts. To make it easy to perform tests, I might have to remove
 * some of the static (private) declarations in the implementation so
 * that the private variables are more easily visible for
 * testing. Alternatively, I will use a debugger to inspect the
 * private variables.
 *
 */

#include "debug.h"
#include "hash.h"
#include <stdlib.h>
#include <stdio.h>

void testRandomCases (void);
Board_t generateRandomBoard ();
unsigned char get0To99Random ();
unsigned char generateRandomNumKilled();
unsigned char generateRandomNumLeft ();
void generateRandomCoordinates 
(Board_t, unsigned char*, unsigned char*);


int
main ()
{
  srand (17);
  printf ("Testing Hash Table Implementation.\n");
  printf ("Current hash size: %ld\n", HASH_TABLE_SIZE);
  
  testRandomCases();

  printf ("End of tests for hash table implementation.\n");
  return 0;
}

void 
testRandomCases ()
{
  unsigned int i;
  Board_t b, b1;
  Move_t move;
  ZKey_t key;
  HashElem_t hE;
  int collission = 0;

  move = create_Move (0, 0, 0, 0);

  printf ("Testing random cases.\n");
  initialize_tables_random ();
  b1 = generateRandomBoard ();
  for (i = 0; i < 10000; i++)
    {
      b = generateRandomBoard ();
      printf ("%d.\nRandom board: %lu\n", i, b);
      key = zobrist_board (b);
      printf ("Zobrist Key = %d\n", key);
      if (!isHashAtKeyEmpty (key))
        {
          printf ("hash collission!!");
          hE = getHashElement (key);
          printf (" [%d]\n", getEvaluation_HashElem (hE));
          collission++;
        }
      hE = create_HashElement 
        (b, 0, EVAL_FLAG_ALPHA, i, move);
      setHashElement (key, hE);
      
      // for previous board
      printf ("Previous board evaluation: ");
      key = zobrist_board (b1);
      if (isHashAtKeyEmpty (key))
        printf ("Empty!!\n");
      else 
        {
          hE = getHashElement (key);
          if ( isEqual_Board 
               ( getBoard_HashElem (hE),
                 b1
                 )
               )
            printf ("[same]");
          else 
            printf ("[different]");
          printf (" %d\n", getEvaluation_HashElem (hE));
        }
      b1 = b;
    }
  printf ("Collissions: %d\n", collission);
  destroy_tables ();
  printf ("End of random test cases.\n");

}

/**
 * Strategy for genrating random boards:
 * 
 * Randomly decide the number of shikaar killed from 0 to 10. This is
 * heavily skewed to the zero side of the spectrum. Generate a number
 * betwenn 0 to 99:
 *   0 to 20: 0 killed
 *  21 to 35: 1
 *  36 to 50: 2 
 *  51 to 60: 3
 *  61 to 70: 4
 *  71 to 75: 5
 *  76 to 80: 6
 *  81 to 85: 7
 *  86 to 90: 8
 *  91 to 95: 9
 *  96 to 99: 10
 *
 * Similarly compute the shikaar left. 
 * Give heavy weight to 0 shikaar left:
 *   0 to 30: 0 left
 *  31 to 45: 1
 *  46 to 60: 2 
 *  61 to 70: 3
 *  71 to 80: 4
 *  81 to 85: 5
 *  86 to 90: 6
 *  91 to 95: 7
 *  96 to 99: 8
 *
 * Deduct the shikaar killed and shikaar left from 20 to get the
 * shikaar on board. Start with an empty board and place the shikaar
 * and four tigers by generating the random co-ordinates to place each
 * of them, if the board position is already occupied, generate a new
 * position.
 */
Board_t
generateRandomBoard () 
{

  unsigned char s_left, s_killed, s_used, t_used;
  unsigned char x, y;
  Board_t b;
  
  s_left = generateRandomNumLeft ();
  s_killed = generateRandomNumKilled ();
  
  s_used = 20 - s_left - s_killed;
  t_used = 4;
  b = getEmptyBoard ();
  
  for (; s_used > 0; s_used--)
    {
      generateRandomCoordinates (b, &x, &y);
      setPieceAtPosition_Board 
        ( &b, PIECE_T_SHIKAAR, x, y );
    }

  for (; t_used > 0; t_used--)
    {
      generateRandomCoordinates (b, &x, &y);
      setPieceAtPosition_Board 
        ( &b, PIECE_T_TIGER, x, y );
    }

  return b;
  
}

unsigned char 
get0To99Random () 
{
  int r = rand ()/(RAND_MAX + 1.0) * 100;
  return r;
}

unsigned char 
generateRandomNumKilled()
{
  unsigned char r = get0To99Random ();
  
  if (r <= 20) return 0;
  if (r <= 35) return 1;
  if (r <= 50) return 2;
  if (r <= 60) return 3;
  if (r <= 70) return 4;
  if (r <= 75) return 5;
  if (r <= 80) return 6;
  if (r <= 85) return 7;
  if (r <= 90) return 8;
  if (r <= 95) return 9;
  if (r <= 99) return 10;
  return 0;
}

unsigned char 
generateRandomNumLeft ()
{
  unsigned char r = get0To99Random ();
  
  if (r <= 30) return 0;
  if (r <= 45) return 1;
  if (r <= 60) return 2;
  if (r <= 70) return 3;
  if (r <= 80) return 4;
  if (r <= 85) return 5;
  if (r <= 90) return 6;
  if (r <= 95) return 7;
  if (r <= 99) return 8;
  return 0;
  
}

void
generateRandomCoordinates 
(Board_t b, unsigned char* x, unsigned char* y)
{
  *x = rand()/(RAND_MAX + 1.0)*5;
  *y = rand()/(RAND_MAX + 1.0)*5;

  while (
         getPieceAtPosition_Board (b, *x, *y)
         != PIECE_T_EMPTY
         )
    {
      *x = rand()/(RAND_MAX + 1.0)*5;
      *y = rand()/(RAND_MAX + 1.0)*5;
    }
}

