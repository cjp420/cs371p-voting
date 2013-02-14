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
#include <string.h>

#include "Voting.h"

using namespace std;

#define NULL 0

//global variables
//maximum values allowed for program input
const int max_num_candidates = 20;
const int max_num_ballots = 1000;
const int max_chars_in_name = 80;

// ------------
// voting_read
// ------------

// ------------
// voting_eval
// ------------

int voting_eval(int i, int j) {
    assert(i > 0);
    assert(j > 0);
    // <your code>
    int v = 1;
    assert(v > 0);
    return v;
}

// -------------
// voting_print
// -------------

void voting_print(std::ostream& w, int i, int j, int v) {
    assert(i > 0);
    assert(j > 0);
    assert(v > 0);
    w << i << " " << j << " " << v << std::endl;
}

// ---------------------
// voting_read_num_cases
// ---------------------

int voting_read_line_with_number(std::istream& r) {
    int num;
    string input = "";
    getline(r, input);
    stringstream s(input);
    s >> num;
    assert(num > 0);
    return num;
}

bool voting_read_names(std::istream& r, string names[max_num_candidates], int num_candidates) {
    string input = "";
    for (int i = 0; i < num_candidates; i++) {
        if (!r)
            return false;
        getline(r, input);
        names[i] = string(input, 0, max_chars_in_name);
    }
    return true;
}

bool voting_read_ballots(std::istream& r, int ballots [max_num_ballots][max_num_candidates], int &num_ballots, int num_candidates) {
    if (!r)
        return false;
    int n = 0;
    string input = "";
    stringstream s;
    while (getline(r, input)) {
        for (int i = 0; i < num_candidates; i++) {
            char c = input.at(i);
            s << c;
            s >> ballots [n] [i];
        }
        n++;
    }
    num_ballots = n;
    return true;
}

string voting_eval_winner(int ballots [max_num_ballots][max_num_candidates], int num_ballots, int num_candidates) {
    //boolean to determine if there is a winner or winners after the current round
    //stores the number of votes a candidate receives in a round
    //-1 means they were eliminated in a previous round
    int num_votes_per_candidate [max_num_candidates];

    //values to keep track of most and least amount of votes for a round
    int most_votes = 0;
    int least_votes = max_num_ballots + 1;

    //stores the index we are considering for each ballot
    int ballot_positions [max_num_ballots];
    
    //store the winner(s) and loser(s) for one round of voting as well as those
    //permanently eliminated from voting 
    int winners_this_round [num_candidates];
    int losers_this_round [num_candidates - 1];
    int eliminated_candidates [num_candidates - 1];
    
    //go through ballots and determine which of the remaining candidates each 
    //ballot is voting for this round
    for(int i = 0; i < num_ballots; i++) {
        int index_of_ballot = ballot_positions [i];
        int candidate_voted_for = ballots[i][index_of_ballot];
        num_votes_per_candidate[candidate_voted_for]++;
    }
    
    int vote_total_for_candidate;
    //Determine max and min # of votes
    for (int i = 0; i < num_candidates; i++) {
        vote_total_for_candidate = num_votes_per_candidate[i];
        if (vote_total_for_candidate != -1) {
            if (vote_total_for_candidate > most_votes)
                most_votes = vote_total_for_candidate;
            if (vote_total_for_candidate < least_votes)
                least_votes = vote_total_for_candidate;
        }
    }
    
    //test for case where all remaining candidates are tied
    if (most_votes == least_votes){
        //we have a tie between all remaining candidates.
    }
        
}


// -------------
// voting_solve
// -------------

void voting_solve(std::istream& r, std::ostream& w) {
    //int to count the number of ballots read from input
    int num_ballots = 0;

    //read number of cases;
    const int num_cases = voting_read_line_with_number(r);

    //string to hold the winner(s) of one case
    string answer = "";

    //loop to read and determine a winner from each case
    for (int i = 0; i < num_cases; i++) {

        //read number of candidates
        int num_candidates = voting_read_line_with_number(r);

        //array of pointers to strings to hold candidate names
        string * names [max_num_candidates];

        //read the names of the candidates
        voting_read_names(cin, names, num_candidates);\

        //two-dimensional array of ints to hold the votes on each ballot
        int ballots [max_num_ballots][max_num_candidates];

        //read the ballots
        voting_read_ballots(r, ballots, num_ballots, num_candidates);

        //evaluate the case to determine winners
        answer = voting_eval_winner(ballots, num_ballots, num_candidates);

        //print the winner(s) for this case followed by a newline
        cout << answer;
    }

}
