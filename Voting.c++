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
#include <string>
#include <vector>

#include "Voting.h"

using namespace std;

#define NULL 0

//global variables
//maximum values allowed for program input
const int max_num_candidates = 20;
const int max_num_ballots = 1000;
const int max_chars_in_name = 80;

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

string voting_eval_winner(int ballots[max_num_ballots][max_num_candidates], int num_ballots, int num_candidates, string names[]) {
    //boolean to determine if there is a winner or winners after the current round
    //stores the number of votes a candidate receives in a round
    //-1 means they were eliminated in a previous round
    int num_votes_per_candidate[max_num_candidates];

    //values to keep track of most and least amount of votes for a round
    int most_votes = 0;
    int least_votes = max_num_ballots + 1;

    //stores the index we are considering for each ballot
    int ballot_positions[max_num_ballots];

    //store the ballot indexes for each candidate
    vector<int> ballots_by_candidate[num_candidates];

    //go through ballots and determine which of the remaining candidates each 
    //ballot is voting for this round
    for (int i = 0; i < num_ballots; i++) {
        int index_of_ballot = ballot_positions[i];
        int candidate_voted_for = ballots[i][index_of_ballot];
        num_votes_per_candidate[candidate_voted_for]++;
        ballots_by_candidate[candidate_voted_for].push_back(i);
    }

    //store the winner(s) and loser(s) for one round of voting as well as those
    //permanently eliminated from voting 
    vector<int> losers_this_round;
    vector<int> eliminated_candidates;

    string result = "";
    while (true) {
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

        if (most_votes > (num_ballots \ 2) || most_votes == least_votes) {
            //we have a winner or winners
            for (int i = 0; i < num_candidates; i++) {
                if (num_votes_per_candidate[i] == most_votes) {
                    result += names[i] + "\n";
                }
            }
            return result;
        } else {
            //determine losers and eliminate
            for (int i = 0; i < num_candidates; i++) {
                if (num_votes_per_candidate[i] == least_votes) {
                    losers_this_round.push_back(i);
                    eliminated_candidates.push_back(i);
                    num_votes_per_candidate[i] = -1;
                }
            }
        }

        //fix indexes for ballots cast for losers
        //for each candidate who lost this round
        for (int i = 0; i < losers_this_round.size(); i++) {
            int aloser = losers_this_round.at(i);
            vector<int> losers_ballots = ballots_by_candidate[aloser];
            //for each ballot that voted for this losing candidate 
            for (int j = 0; j < losers_ballots.size(); j++) {
                int current_ballot = losers_ballots.at(j);
                int this_ballots_next_index = ballot_positions[current_ballot];
                int next_candidate_on_balot = ballots[current_ballot][this_ballots_next_index];
                //find the next candidate who has not been eliminated
                while (num_votes_per_candidate[next_candidate_on_balot] = -1) {
                    this_ballots_next_index++;
                    next_candidate_on_balot = ballots[current_ballot][this_ballots_next_index];
                }
                //add vote and ballot to the next candidate on the ballot
                ballots_by_candidate[next_candidate_on_balot].push_back(current_ballot);
                num_votes_per_candidate[next_candidate_on_balot]++;
            }
        }
        losers_this_round.clear();
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
        answer = voting_eval_winner(ballots, num_ballots, num_candidates, names);

        //print the winner(s) for this case followed by a newline
        cout << answer;
    }

}
