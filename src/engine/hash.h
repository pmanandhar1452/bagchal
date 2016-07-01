/**
 * hash.h
 * 6 Nov 2002
 * jaH
 *
 * 
 * The hash table is used in the engine to remember previous board
 * positions so that expensive computations need not be performed
 * repeatedly on the smae position.  The principle used here is
 * the famous zobrist key hashing.  [I need not quote the original
 * author here since it is so famous!]
 *
 * Today, I was thinking whether it might be possible to build a
 * complete game tablebase for bagchal.  Since bagchal is not complex
 * as chess, I tried to calculate the ammount of memory it would
 * require to store the complete evaluation table.  I envisioned that
 * the time factor would not be important for such a table.  We could
 * work with an incomplete table and slowly improve the table for each
 * game played.
 *
 * For the table to be complete, it would need to store an evaluation
 * for each possible board. Some 'trivial' computation shows that at
 * most about 50 bits are enough to store all the boards in a bagchal
 * game.  This means that we need 2^50 addresses to store the
 * evaluation and possibly the next move.  If it takes 1 byte to store
 * such information, then this would calculate to 1024 tera bytes.  I
 * think this amount of storage would be trivially available in the
 * near future and it might be possible to start thinking about
 * creating such a table.  But for now, I will be content with a more
 * modest table.
 *
 * This header file define a changable constant called the
 * HASH_BIT_SIZE.  A table of this size is created during
 * initialisation using the calloc system call. In addition, the
 * system can load the table from previous runs from a memory-dump
 * file in the file system.  This file stores the zobrist keys and
 * some other meta-information (e.g. the HASH_BIT_SIZE).  The file is
 * directly loaded into the hash table to give the engine a head
 * start.  The hash table will store the following information for
 * each key:
 *
 * 1. The board
 *    The board must be stored in the hash table since we are not
 *    conceiving a perfect hash function. The board will be used to
 *    detect collissions.  Currently I am considering an always
 *    replace strategy when confronted with a collission.
 *    Our board is 64 bits. (8 bytes)
 *
 * 2. The evaluation.  Alpha and Beta values.
 *    Ofcourse.  For the current versions, I am imagining a one byte
 *    evaluation value.  The evaluation function is too simple.  I might
 *    consider increasing this value, if one byte proves to be too
 *    little.  
 *
 * 3. A flag to indicate whether the evaluation value is ALPHA, BETA,
 *    or EXACT. This will take 2 bits.
 *
 * 4. The depth of evaluation.
 *    One byte.  I don't expect to search too deep.
 *
 * 5. The best move found. The best move will be stored in 2 bytes,
 *    since it takes 11 bits to store a move. The beast move is stored
 *    to improve move ordering in search.
 *
 * So, we can expect about 12 to 16 bytes for each hash table element.
 * This means a 10bit hash table will take avout 2^10 * 16 bytes,
 * which is equal to 16Kb.  A 20bit table will take about 16Mb and a 30
 * bit table will take about 16Gb!!
 *
 * For a nice introduction to Zobrist keys and chess programming in
 * general, see: http://www.seanet.com/~brucemo/topics/topics.htm
 * Chess programming introduction by Bruce Moreland. By the time you
 * read this the link might be broken, hopefully not.
 */

#ifndef bagchal_engine_hash_h
#define bagchal_engine_hash_h

#include "move.h"
#include <stdio.h>

// use 64 bit zobrist keys I am confised of using 62bit/32bit keys or
// using Zobrist keys at all The bit board it-self seems to be a
// pretty nice key. I might experiment with that idea some time.
typedef i64_t ZKey_t;

// use integer values between 1 and 32
#define HASH_BIT_SIZE 21 

// the number of elements in the hash table 2^HASH_BIT_SIZE
#define HASH_TABLE_SIZE ((ZKey_t)1<<(HASH_BIT_SIZE))

// the mask that can be used to trim random numbers, or zobrist keys
#define HASH_MASK (HASH_TABLE_SIZE-1)

// Flags that are used to indicate whether the stored evaluation is
// exact, alpha or beta, or empty which means that this hash element
// has not been filled yet

#define HASH_FLAG_EMPTY 0
#define EVAL_FLAG_EXACT 1
#define EVAL_FLAG_ALPHA 2
#define EVAL_FLAG_BETA  3

/**
 * The hash element. Please do not access the elements directly. Use
 * the get and set functions.
 */

struct hashE_tag {

  Board_t board;
  unsigned int depth:8;
  unsigned int flags:2;
  int eval;
  Move_t best_move;

};

typedef struct hashE_tag HashElem_t;
typedef HashElem_t * pHashElem_t;

/**
 * Creates a hash element.
 */
HashElem_t create_HashElement 
(Board_t, unsigned int depth, unsigned int flags, int eval, Move_t);

/**
 * Returns the hash element at the given key. The key need not be
 * masked. This function will mask/or rotate or whatever the key to
 * suite the hash table size.
 */
HashElem_t getHashElement (ZKey_t);

/**
 * Unconditionally sets the hash entry at the given key, with the
 * given element replacing the old element.
 */
void setHashElement (ZKey_t, HashElem_t);

/**
 * Checks whether the given hash elment, or the hash element at the
 * given key are empty.
 */
Boolean_t isHashEmpty (HashElem_t);
Boolean_t isHashAtKeyEmpty (ZKey_t);

/**
 * HashElem access functions. Defined as macros for efficeincy.
 */
#define getDepth_HashElem(hE)      ((hE).depth)
#define getBoard_HashElem(hE)      ((hE).board)
#define getEvaluation_HashElem(hE) ((hE).eval)
#define getFlags_HashElem(hE)      ((hE).flags)
#define getBestMove_HashElem(hE)   ((hE).best_move)

/**
 * Initializes the zobrist table by generating random numbers.
 * Allocates the hash table, and clears the memory to empty the hash
 * table. The rand() function of stdlib is used to generate
 * psuedo-random numbers.
 */
void initialize_tables_random ();

/**
 * Initilizes the zobrist table and hash table from the given open
 * file.  The file format is as follows: The first 4 bytes store the
 * number of bits used in addressing the hash table.  Next comes the
 * zobrist table used for hashing and next comes the real hash
 * table.  The functions fwrite and fread of stdio are used to write
 * the files.  So, whey will not be particularly portable across
 * machines, at least not without any conversion.
 *
 * Important Note: I do not intend to fully implement this feature at
 * this stage. It could be quite a late addition in the final release.
 */
void initialize_tables_from_file (FILE *);

/**
 * Free any allocated memory for tables.
 */
void destroy_tables ();

/**
 * Write the tables to the given file.
 */
void write_tables_to_file (FILE *);


/**
 * Returns the zobrist key for the board. I might experiment with
 * returning the board itself!! (just to see if it works for bagchal,
 * if not for chess)
 */
ZKey_t zobrist_board (Board_t);

/**
 * Changes the zobrist key to the new key as required by the
 * move. Removed from the interface to un-complicate things at this
 * stage of the project.
 */
//ZKey_t zobrist_move_do (Move_t, ZKey_t);

/**
 * Undos a move in the zobrist key.
 */
//ZKey_t zobrist_move_undo (Move_t, ZKey_t);



#endif // bagchal_engine_hash_h
