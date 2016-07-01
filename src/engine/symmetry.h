/**
 * symmetry.h
 * 13 Oct 2002
 * jah and suraj
 *
 * Analyses various symmetries of the bagchal board as defined
 * in Board.h. Two boards are said to be symmetriclly eqivalent
 * if one board has the same turn, number of shikaar left, number
 * of shikaar killed parameter as the other and one board can be
 * derived from the other by using one or more of the following
 * transformaitons:
 *
 * 0. Identity transformation
 *    [ a separate function is not provided for this, since, it
 *      can be checked by equals_Board ]
 * 1. Reflection along y=2
 * 2. Reflection along x=2
 * 3. Reflection along x=y
 * 4. Reflection along x=4-y
 * 5. clockwise rotation by right angle about (2,2)
 * 6. anti-clockwise rotation by right angle about (2,2)
 * 7. rotation by PI (180 degrees)
 *
 * The functions in this library determine whether two boards are
 * symmetrically eqivalent.
 */

#ifndef bagchal_engine_symmetry_h
#define bagchal_engine_symmetry_h

#include "Board.h"
#include "types.h"

Boolean_t checkReflectionYEq2_Symmetry (Board_t b, Board_t b1);
Boolean_t checkReflectionXEq2_Symmetry (Board_t, Board_t);
Boolean_t checkReflectionXEqY_Symmetry (Board_t, Board_t);
Boolean_t checkReflectionXEq4MnY_Symmetry (Board_t, Board_t);
Boolean_t checkRotationClockwise_Symmetry (Board_t, Board_t);
Boolean_t checkRotationAntiClockwise_Symmetry (Board_t, Board_t);
Boolean_t checkRotationPI_Symmetry (Board_t, Board_t);


Boolean_t isEquivalent_Symmetry (Board_t, Board_t);

#endif
