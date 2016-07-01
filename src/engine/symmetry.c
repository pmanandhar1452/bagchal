/**
 * symmetry.c
 * 13 Oct 2002
 * jah and suraj
 *
 * Implementation for symmetry.h.
 */

#include "symmetry.h"


static
Boolean_t isEqual_Parameters (Board_t b1, Board_t b2) {
  return (
	  getNumberOfShikaarLeft_Board (b1) == getNumberOfShikaarLeft_Board (b2) &&
	  getNumberOfShikaarKilled_Board (b1) == getNumberOfShikaarKilled_Board (b2) &&
	  getTurn_Board (b1) == getTurn_Board (b2)
	  );
}

Boolean_t 
checkReflectionYEq2_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if (
	  getPieceAtPosition_Board (b1, i, j) !=
	  getPieceAtPosition_Board (b2, i, 4-j)  
	  ) return FALSE;
    }

  return TRUE;
  
}


Boolean_t checkReflectionXEq2_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, 4-i, j) 
	  ) return FALSE;
    }

  return TRUE;
  
}


Boolean_t checkReflectionXEqY_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, j, i) 
	  ) return FALSE;
    }

  return TRUE;
  
}

Boolean_t checkReflectionXEq4MnY_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, 4-j, 4-i) 
	  ) return FALSE;
    }

  return TRUE;
  
}


Boolean_t checkRotationClockwise_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, j, 4-i) 
	  ) return FALSE;
    }

  return TRUE;
  
}


Boolean_t checkRotationAntiClockwise_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, 4-j, i) 
	  ) return FALSE;
    }

  return TRUE;
  
}

Boolean_t checkRotationPI_Symmetry (Board_t b1, Board_t b2) {
  
  int i, j;
  
  if (!isEqual_Parameters (b1, b2)) return FALSE;

  for (j = 0; j < 5; j++)
  for (i = 0; i < 5; i++)
    {
      if ( 
	   getPieceAtPosition_Board (b1, i, j) !=
	   getPieceAtPosition_Board (b2, 4-i, 4-j) 
	  ) return FALSE;
    }

  return TRUE;
  
}


Boolean_t isEquivalent_Symmetry (Board_t b1, Board_t b2) {

  if (
      isEqual_Board (b1, b2) ||
      checkReflectionYEq2_Symmetry (b1, b2) ||
      checkReflectionXEq2_Symmetry (b1, b2) ||
      checkReflectionXEqY_Symmetry (b1, b2) ||
      checkReflectionXEq4MnY_Symmetry (b1, b2) ||
      checkRotationClockwise_Symmetry (b1, b2) ||
      checkRotationAntiClockwise_Symmetry (b1, b2) ||
      checkRotationPI_Symmetry (b1, b2)
      )
    return TRUE;

  return FALSE;

}
