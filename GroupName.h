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
Point_t points[] = {{-1,0}, {1, 0}, {0, 1},{0,-1}, {-1,1}, {-1,-1},{1,1}, {1,-1}};

bool validTigerDiagonalMove[GRID_ROW][GRID_COL] = {
        {0,0,0,0,1,0,0,0,0}, //top point
        {0,0,0,1,0,1,0,0,0}, //left top diagonal, right top diagonal
        {0,0,1,0,1,0,1,0,0}, //left, start, right
        {0,0,0,1,0,1,0,0,0}, //left bottom diagonal, right bottom diagonal
        {0,0,0,0,1,0,0,0,0}, //bottom point
        {0,0,0,1,0,1,0,0,0},
        {0,0,1,0,0,0,1,0,0},
        {0,1,0,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,0,1},
        {0,1,0,0,0,0,0,1,0},
        {0,0,1,0,0,0,1,0,0},
        {0,0,0,1,0,1,0,0,0},
        {0,0,0,0,1,0,0,0,0}
};

/*
vector<Point_t> legalTigerMoves(vector<Token_t> &menTokens, Move_t &tiger){
    //We need to know board size (look at constants), we need to know where men are, need to know if on a diagonal
    vector<Point_t> LegalMoves;
    vector<Point_t> possibleOneMoves, possibleTwoMoves;
    int x = tiger.token.location.row, y = tiger.token.location.col, x2, y2, x3,y3;

    bool spaceIsEmpty;
    *//*if(validTigerDiagonalMove[loc.row][loc.col]){
        pointAmount = 8;
    }*//*

    //N, S, E, W, NE, NW, SE, SW

    for(int i = 0; i < 4; i++){
        //Only need to check for one move because you cant jump over the out of bounds anyway
        if(validLocationGrid[x + (points[i].row)][y + (points[i].col)]){
            possibleOneMoves.push_back({x + (points[i].row), y + (points[i].col)});
            //Checks that jump is not an illegal move
            if(validLocationGrid[x + (2 * points[i].row)][y + (2 * points[i].col)]) {
                possibleTwoMoves.push_back({x + (2 * points[i].row), y + (2 * points[i].col)});
            }
        }
    }
    if(validTigerDiagonalMove[x][y]){ //If curr loc is on diagonal
        for(int j = 4; j < 8; j++){
            x2 = x + (points[j].row);
            y2 = y + (points[j].col);

            //Checks if diagonal grid location is legal
            if(validLocationGrid[x2][y2]){

                //Tells me if next move is on a diagonal
                if (validTigerDiagonalMove[x2][y2]) {
                    possibleOneMoves.push_back({x2, y2});
                }

                x3 = x + (2 * points[j].row);
                y3 = y + (2 * points[j].col);

                //Checks if double jump diagonal location is legal
                if (validTigerDiagonalMove[x3][y3] && validLocationGrid[x3][y3]) {
                    possibleTwoMoves.push_back({x3, y3});
                }
            }
        }
    }

    for (int j = 1; j < menTokens.size(); j++) {
        const auto& t = menTokens[j];
        //iterates through all possibleOneMoves which is the same as two moves
        for(int i = 0; i < possibleOneMoves.size(); i++){

            if (t.location.row == possibleOneMoves[i].row && t.location.col == possibleOneMoves[i].col){
                cout << "BLUE MAN ONE SPACE AWAY" << endl;
                spaceIsEmpty = true;
                for(int z = 1; z < menTokens.size(); z++){
                    const auto& l = menTokens[z];

                    //Checks if men are 2 spaces away
                    for(int a = 0; a < possibleTwoMoves.size(); a++){
                        if(l.location.row == possibleTwoMoves[a].row && l.location.col == possibleTwoMoves[a].col){
                            cout << "BLUE MAN TWO SPACES AWAY" << endl;
                            spaceIsEmpty = false;
                        }
                        //FIXME double check this belongs in loop later
                        if(spaceIsEmpty && validLocationGrid[possibleTwoMoves[a].row][possibleTwoMoves[a].col]){
                            Point_t p = {possibleTwoMoves[a].row, possibleTwoMoves[a].col};
                            LegalMoves.push_back(p);
                        }
                    }

                }
                //if space is empty and jump point is in bounds then push into possible moves

            }
        }

        //FIXME
        for(int i = 0; i < possibleOneMoves.size();i++){
            spaceIsEmpty = true;
            for(const auto t : menTokens){
                if(t.location.row == possibleOneMoves[i].row && t.location.col == possibleOneMoves[i].col){
                    spaceIsEmpty = false;
                    //Fixme check placement later
                }
                if(spaceIsEmpty){
                    Point_t p = {possibleOneMoves[i].row, possibleOneMoves[i].col};
                    LegalMoves.push_back(p);
                }
            }

        }

    }


    for(int i = 0; i < 8; i++) {
        //REGULAR MOVES
        //FIXMe if go back to this += is wrong chcek github
        x += (points[i].row);
        y += (points[i].col);

        //JUMP MOVES
        x2 = tiger.token.location.row + (2 * points[i].row);
        y2 = tiger.token.location.col + (2 * points[i].col);

        if(validTigerDiagonalMove[tiger.token.location.row][tiger.token.location.col]){ //If curr loc is on diagonal
            validTigerDiagonalMove[x][y]; //Tells me if next move is on a diagonal
            validTigerDiagonalMove[x2][y2]; //Tells me if a jump is on the diagonal
        }

        //for loop to check all jump moves
        //check to see if space is occupied by man, if it is -> check space past that, if not -> valid jump move
        //FIXME pretty sure this works problem is that it is looking for diagonal when it is not supposed to
        for (const auto t: menTokens) {
            //Checks if men is on 1 space away from tiger
            if (t.color == BLUE && t.location.row == x && t.location.col == y){
                cout << "BLUE MAN ONE SPACE AWAY" << endl;
                spaceIsEmpty = true;
                for(const auto other : menTokens){

                    //Checks if men are 2 spaces away
                    if(other.location.row == x2 && other.location.col == y2){
                        cout << "BLUE MAN TWO SPACES AWAY" << endl;
                        spaceIsEmpty = false;
                    }
                }
                //if space is empty and jump point is in bounds then push into possible moves
                if(spaceIsEmpty && validLocationGrid[x2][y2]){
                    Point_t p = {x2, y2};
                    LegalMoves.push_back(p);
                }
            }
        }

        //check all normal moves
        if(validLocationGrid[x][y]){
            spaceIsEmpty = true;
            for(const auto t : menTokens){
                if(t.location.row == x && t.location.col == y){
                    spaceIsEmpty = false;
                }
            }
            if(spaceIsEmpty){
                Point_t p = {x, y};
                LegalMoves.push_back(p);
            }
        }
    }

    return LegalMoves;
}*/
vector<Point_t> legalTigerMoves(vector<Token_t> &menTokens, Move_t &tiger){
    vector<Point_t> LegalMoves;
    vector<Point_t> possibleOneMoves, possibleTwoMoves;
    int x = tiger.token.location.row, y = tiger.token.location.col;

    // Direction vectors: N, S, E, W
    for(int i = 0; i < 4; i++){
        int x1 = x + points[i].row;
        int y1 = y + points[i].col;
        if(validLocationGrid[x1][y1]){
            possibleOneMoves.push_back({x1, y1});
        }

        int x2 = x + 2 * points[i].row;
        int y2 = y + 2 * points[i].col;
        if(validLocationGrid[x2][y2]){
            possibleTwoMoves.push_back({x2, y2});
        }
    }

    // Diagonal directions
    if(validTigerDiagonalMove[x][y]){
        for(int i = 4; i < 8; i++){
            int x1 = x + points[i].row;
            int y1 = y + points[i].col;
            if(validLocationGrid[x1][y1] && validTigerDiagonalMove[x1][y1]){
                possibleOneMoves.push_back({x1, y1});
            }

            int x2 = x + 2 * points[i].row;
            int y2 = y + 2 * points[i].col;
            if(validLocationGrid[x2][y2] && validTigerDiagonalMove[x2][y2]){
                possibleTwoMoves.push_back({x2, y2});
            }
        }
    }

    // One-step moves (only if no man is in that spot)
    for(const auto& move : possibleOneMoves){
        bool occupied = false;
        for(const auto& man : menTokens){
            if(man.location == move){
                occupied = true;
                break;
            }
        }
        if(!occupied){
            LegalMoves.push_back(move);
        }
    }

    // Two-step (jump) moves: must jump over a man and land on empty space
    for(int i = 0; i < possibleTwoMoves.size(); i++){
        // To check if there's a man in the middle of the jump
        int midX = (x + possibleTwoMoves[i].row) / 2;
        int midY = (y + possibleTwoMoves[i].col) / 2;

        bool manInMiddle = false;
        for(const auto& man : menTokens){
            if(man.location.row == midX && man.location.col == midY){
                manInMiddle = true;
                break;
            }
        }

        // Now check if landing space is unoccupied
        bool landingSpotFree = true;
        for(const auto& man : menTokens){
            if(man.location == possibleTwoMoves[i]){
                landingSpotFree = false;
                break;
            }
        }

        if(manInMiddle && landingSpotFree){
            LegalMoves.push_back(possibleTwoMoves[i]);
        }
    }

    return LegalMoves;
}

Move_t TigerTokenMove(vector<Token_t> tokens, Move_t moveTiger){
    cout << "IN TIGER MOVE" << endl;

    vector<Point_t> moveOptions = legalTigerMoves(tokens, moveTiger);


    cout << "TIGER CURRENT LOCATION: ";
    cout << moveTiger.token.location.row << " " << moveTiger.token.location.col << endl;
    cout << "Possible Moves:" << endl;
    for(int i = 0; i < moveOptions.size(); i++){
        cout << " (" << moveOptions[i].row << " " << moveOptions[i].col << ")";
        if(moveTiger.token.location.row < moveOptions[i].row){
            moveTiger.destination = moveOptions[i];
        }

        //JUMP conditions
        if(moveTiger.token.location.row + 2 == moveOptions[i].row){
            moveTiger.destination = moveOptions[i];
        }
        else if (moveTiger.token.location.row - 2 == moveOptions[i].row){
            moveTiger.destination = moveOptions[i];
        }
        else if(moveTiger.token.location.col - 2 == moveOptions[i].col){
            moveTiger.destination = moveOptions[i];
        }
        else if(moveTiger.token.location.col + 2 == moveOptions[i].col){
            moveTiger.destination = moveOptions[i];
        }
    }


    cout << endl;

    return moveTiger;
}


Move_t Move_Team12(vector<Token_t> vector1, Color_t color) {
    Move_t move1;

    //tiger turn
    if(color == RED){
        move1.token = vector1[TIGER];

        move1 = TigerTokenMove(vector1, move1);
        /*move1.destination.row = move1.token.location.row + 1;
        move1.destination.col = move1.token.location.col;

        if(move1.destination.row >= 8){
            move1.destination.row = move1.token.location.row - 1;
        }*/

    }
    else{//men turn

    }

    return move1;
}




#endif //GROUP_PROJECT_V1_GROUPNAME_H
