/**
 * hash.c
 * jaH
 * 6 Nov 2002
 *
 * Implementation of hash.h
 */

#include "hash.h"
#include "debug.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

void initialise_ZobristTable_random ();
void allocate_HashTable ();
i64_t rand64 ();


// resizes the key to fit the table size
// the method of &ing with HASH_MASK takes all the higher order
// random bits out of play, generating them was useless!? So, I am
// sticking with the % version. Allegedly % is 200 times more CPU
// expensive than the alternative, let's see.
//#define resizeKey(key) (key % HASH_TABLE_SIZE)
#define resizeKey(key) (key & HASH_MASK)

#ifdef DEBUG_LEVEL_2

static Boolean_t 
tables_allocated = FALSE;

#endif // debug level 2

/**
 * The hash table is a dynamically allocated array. The array is
 * allocated during initialisation.  Checking allocation and
 * deallocation (checking that unallocated memory is not accessed) is
 * performed for each relevant operation if DEBUG_LEVEL_2 is defined.
 * There are no checks to ensure that the state maintained by this
 * module (one state per process) is thread safe.  So, it is best to
 * use this module in a single threaded environment or it shall be
 * encapsulated in a thread-safety package before using in a
 * multi-thread environment.
 */
static pHashElem_t HashTable;


/**
 * The ZobristTable stores random numbers that are used to generate
 * the key from a given board position.  Various parameters, such as,
 * the number of shikaar killed and number left are not taken into
 * account while generating the keys, since I am thinking along the
 * lines that there are once these numbers are changed the evaluation
 * is useless for the current game.  But they could be useful if we
 * are in the tree and the game has not progressed that far.  Still I
 * hope that the Zobrist system is robust enough that collissions of
 * importance will be few. 
 *
 * Notice that there is a separate variable besides the array. I could
 * have incorporated this variable in the array.  But it seems that it
 * is generally enough that a single variable is used for the 
 */

#define PIECE_TYPE_MAX 2
#define POSITION_X_MAX 5
#define POSITION_Y_MAX 5
#define TURN_MAX       2

static ZKey_t 
ZobristTable
[PIECE_TYPE_MAX][TURN_MAX]
[POSITION_X_MAX][POSITION_Y_MAX];


HashElem_t 
create_HashElement 
(Board_t b, unsigned int depth, unsigned int flags, int eval, Move_t m)
{

  HashElem_t hE;

#ifdef DEBUG_LEVEL_2
  // making sure we are where we are supposed to be
  //assert (isValid_Move (b, m));
  assert (depth >= 0 && depth < 256);
  assert (flags >= 0 && flags < 4);
#endif // DEBUG_LEVEL_2
  
  hE.board = b;
  hE.depth = depth;
  hE.flags = flags;
  hE.eval = eval;
  hE.best_move = m;
  
  return hE;
  
}


HashElem_t 
getHashElement (ZKey_t key)
{
  
#ifdef DEBUG_LEVEL_2
  assert (tables_allocated);
#endif // DEBUG_LEVEL_2
  
  key = resizeKey (key);
  return 
    HashTable[key];
  
}


void
setHashElement (ZKey_t key, HashElem_t hE)
{
  
#ifdef DEBUG_LEVEL_2
  assert (tables_allocated);
#endif // DEBUG_LEVEL_2
  
  key = resizeKey (key);
  HashTable[key] = hE;
  
}


Boolean_t 
isHashEmpty (HashElem_t hE)
{
  return 
    (getFlags_HashElem (hE) == HASH_FLAG_EMPTY);
}

Boolean_t 
isHashAtKeyEmpty (ZKey_t key)
{
  return 
    isHashEmpty (getHashElement(key));
}

void 
initialize_tables_random ()
{

#ifdef DEBUG_LEVEL_2
  assert(!tables_allocated);
#endif //DEBUG_LEVEL_2

  initialise_ZobristTable_random ();
  allocate_HashTable();
  
#ifdef DEBUG_LEVEL_2
  tables_allocated = TRUE;
#endif //DEBUG_LEVEL_2
  
}

void
allocate_HashTable ()
{
  HashTable = (pHashElem_t)calloc 
    (HASH_TABLE_SIZE, sizeof (HashElem_t));

  if (HashTable == NULL)
    {
      fprintf (stderr, "Error in allocating Hash Table.\n");
      fprintf (stderr, "Try decreasing the size of the table in hash.h\n");
      fprintf (stderr, "Mail the author (jaH) at jaa@ntc.net.np, ");
      fprintf (stderr, "if you have problems.\n");
      exit (-1);
    }

}


void
initialise_ZobristTable_random ()
{
  int i, j, k, l;
  for (i = 0; i < PIECE_TYPE_MAX; i++)
  for (j = 0; j < TURN_MAX; j++)
  for (k = 0; k < POSITION_X_MAX; k++)
  for (l = 0; l < POSITION_Y_MAX; l++)
    ZobristTable [i][j][k][l] = rand64 ();

}

i64_t
rand64 ()
{
  return 
    rand() ^ ((i64_t)rand() << 15) ^ ((i64_t)rand() << 30) ^
    ((i64_t)rand() << 45) ^ ((i64_t)rand() << 60);
}

void
initialize_tables_from_file (FILE *fp)
{ 
  // implementation postponed, i think there are more important things
  // than this!!
  initialize_tables_random ();
  
}

void
write_tables_to_file (FILE *fp)
{
  // postponed
  return;
}

void
destroy_tables ()
{
#ifdef DEBUG_LEVEL_2
  assert(tables_allocated);
#endif //DEBUG_LEVEL_2

  free (HashTable);  

#ifdef DEBUG_LEVEL_2
  tables_allocated = FALSE;
#endif //DEBUG_LEVEL_2
}

ZKey_t 
zobrist_board (Board_t b)
{
  int i, j;
  int turn;
  int piece;
  ZKey_t key = 0;
  
  turn = getTurn_Board (b);
  
  for (i = 0; i < POSITION_X_MAX; i++)
  for (j = 0; j < POSITION_Y_MAX; j++)
    {
      piece = getPieceAtPosition_Board (b, i, j);
      if (piece != PIECE_T_EMPTY)
        {
          key ^= ZobristTable [piece-1][turn][i][j];
        }
    }
  
  return key;
  
}
