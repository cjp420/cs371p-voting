// ----------------------------
// projects/voting/Voting.c++
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert> // assert
#include <iostream> // endl, istream, ostream

#include "Voting.h"

// ------------
// voting_read
// ------------

bool voting_read (std::istream& r, int& i, int& j) {
    r >> i;
    if (!r)
        return false;
    r >> j;
    assert(i > 0);
    assert(j > 0);
    return true;}

// ------------
// voting_eval
// ------------

int voting_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);
    // <your code>
    int v = 1;
    assert(v > 0);
    return v;}

// -------------
// voting_print
// -------------

void voting_print (std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;}

// -------------
// voting_solve
// -------------

void voting_solve (std::istream& r, std::ostream& w) {
    int i;
    int j;
    while (voting_read(r, i, j)) {
        const int v = voting_eval(i, j);
        voting_print(w, i, j, v);}}
