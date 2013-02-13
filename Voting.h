/* 
 * File:   Voting.h
 * Author: owner
 *
 * Created on February 13, 2013, 12:45 PM
 */

#ifndef VOTING_H
#define	VOTING_H

// --------
// includes
// --------

#include <iostream> // istream, ostream

// ------------
// voting_read
// ------------

/**
* reads two ints into i and j
* @param r a std::istream
* @param i an int by reference
* @param j an int by reference
* @return true if that succeeds, false otherwise
*/
bool voting_read (std::istream&, int&, int&);

// ------------
// voting_eval
// ------------

/**
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @return the max cycle length in the range [i, j]
*/
int voting_eval (int, int);

// -------------
// voting_print
// -------------

/**
* prints the values of i, j, and v
* @param w a std::ostream
* @param i the beginning of the range, inclusive
* @param j the end of the range, inclusive
* @param v the max cycle length
*/
void voting_print (std::ostream&, int, int, int);

// -------------
// voting_solve
// -------------

/**
* read, eval, print loop
* @param r a std::istream
* @param w a std::ostream
*/
void voting_solve (std::istream&, std::ostream&);

#endif	/* VOTING_H */

