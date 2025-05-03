//
// Created by mymys on 4/28/2025.
//

#ifndef GROUP_PROJECT_V1_GROUPNAME_H
#define GROUP_PROJECT_V1_GROUPNAME_H

#include "constants.h"
#include <vector>
#include "BearGame.h"
using namespace std;

//Know where to move is #1

//N, S, E, W, NE, NW, SE, SW
int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int dy[] = {0, 0, 1, -1, 1, -1, 1, -1};



vector<Point_t> legalTigerMoves(vector<Token_t> &menTokens, Move_t &tiger){
    //We need to know board size (look at constants), we need to know where men are, need to know if on a diagonal
    vector<Point_t> possibleMoves;

    for(int i = 0; i < 8; i++) {
        //REGULAR MOVES
        int x = tiger.token.location.row + (dx[i]);
        int y = tiger.token.location.col + (dy[i]);

        //JUMP MOVES
        int x2 = tiger.token.location.row + (2 * dx[i]);
        int y2 = tiger.token.location.col + (2 * dy[i]);


        //for loop to check all jump moves
        //check to see if space is occupied by man, if it is -> check space past that, if not -> valid jump move
        for (const auto t: menTokens) {
            //Checks if men is on 1 space away from tiger
            if (t.color == BLUE && (t.location.row == x) && t.location.col == y){
                bool spaceIsEmpty = true;
                for(const auto other : menTokens){
                    //Checks if men are 2 spaces away
                    if(other.location.row == x2 && other.location.col == y2){
                        spaceIsEmpty = false;
                    }
                }
                //if space is empty and jump point is in bounds then push into possible moves
                if(spaceIsEmpty && validLocationGrid[x2][y2]){
                    Point_t p = {x2, y2};
                    possibleMoves.push_back(p);
                }
            }
        }

        //check all normal moves
        if(validLocationGrid[x][y]){
            bool spaceIsEmpty = true;
            for(const auto t : menTokens){
                if(t.location.row == x && t.location.col == y){
                    spaceIsEmpty = false;
                }
            }
            if(spaceIsEmpty){
                Point_t p = {x, y};
                possibleMoves.push_back(p);
            }
        }
    }

    return possibleMoves;
}

Move_t TigerTokenMove(vector<Token_t> tokens, Move_t moveTiger){
    cout << "IN TIGER MOVE" << endl;

    vector<Point_t> moveOptions = legalTigerMoves(tokens, moveTiger);
    //legalMove is in beargame.h check later
    cout << "TIGER CURRENT LOCATION: ";
    cout << moveTiger.token.location.row << " " << moveTiger.token.location.col << endl;
    cout << "Possible Moves:" << endl;
    for(int i = 0; i < moveOptions.size(); i++){
        cout << " (" << moveOptions[i].row << " " << moveOptions[i].col << ")";
    }
    cout << endl;

    return moveTiger;
}


Move_t Move_Team12(vector<Token_t> vector1, Color_t color) {
    Move_t move1;

    if(color == RED){//tiger turn
        move1.token = vector1[TIGER];

        move1 = TigerTokenMove(vector1, move1);
        move1.destination.row = move1.token.location.row + 1;
        move1.destination.col = move1.token.location.col;

        if(move1.destination.row >= 8){
            move1.destination.row = move1.token.location.row - 1;
        }

    } else{//men turn

    }

    return move1;
}




#endif //GROUP_PROJECT_V1_GROUPNAME_H
