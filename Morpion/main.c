#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1
#define ROND 1
#define CROIX 2

// Declare functions
void initializeMorpion(char c_MorpionArray[3][3], char c_InitValue);
void printMorpion(char c_MorpionArray[3][3]);
int isInsideBounds(int c_NewMove);
int askForX(int n_xNewMove);
int askForY(int n_yNewMove);
int togglePlayer(int n_CurrentPlayer);
char WhatCharIsPlayer(int n_CurrentPlayer);
int isAlreadyTaken(char c_MorpionArray[3][3], int n_xNewMove, int n_yNewMove);
int isAPlayerWinning(char c_MorpionArray[3][3]);
void printWinner(int n_Win, char c_MorpionArray[3][3]);
void printCurrentPlayer(int n_CurrentPlayer);

int main(){

    // Declare the table, which will contain the Morpion
    char c_MorpionArray[3][3];

    // Declare the variables used to store the coordinates of the player's move
    int n_xNewMove, n_yNewMove;

    // Declare the variable used to keep track of which player is playing now
    int n_CurrentPlayer = CROIX;

    // Declare the variable that stocks which player wins
    int n_Win = 0;

    // Declare the variable that counts the number of moves done
    int n_MoveCounter = 0;

    // Initialize the Morpion table by giving each cell a " " for value
    initializeMorpion(c_MorpionArray, ' ');

    // Procedure of a turn, looping while the game isn't finished
    do{
        // Print the table on screen
        printMorpion(c_MorpionArray);

        // Ask the player to enter the coordinates of his next move until he gives an empty location
        do{
            printCurrentPlayer(n_CurrentPlayer);
            printf("Ou voulez vous jouer?\n\n");
            n_xNewMove = askForX(n_xNewMove);
            n_yNewMove = askForY(n_yNewMove);

            // Give a warning message if the cell is already taken
            if(isAlreadyTaken(c_MorpionArray, n_xNewMove, n_yNewMove) == true){
                printf("Un coup a deja ete joue a cet endroit\n");
            }
        } while(isAlreadyTaken(c_MorpionArray, n_xNewMove, n_yNewMove) == true);

        // Store 'X' or 'O' inside the Morpion array2D at the coordinates given by the player
        c_MorpionArray[n_yNewMove][n_xNewMove] = WhatCharIsPlayer(n_CurrentPlayer);

        // Check for the win of one of the players, if one is winning print which one
        n_Win = isAPlayerWinning(c_MorpionArray);

        // Print on screen who is the winner if there is one
        if(n_Win != 0){
            printWinner(n_Win, c_MorpionArray);
        }


        // Toggle the player, so we can start the next turn
        n_CurrentPlayer = togglePlayer(n_CurrentPlayer);

        // Increment the move counter
        n_MoveCounter++;

        // Print a message in case of a draw
        if((n_MoveCounter == 9) && (n_Win == 0)){
            printf("Egalite!");
            break;
        }

    } while(n_Win == 0);
    // Get out of the game loop if a player as won

    return 0;
}

// Initialize the array2D given in argument1 at the char value passed in argument2
void initializeMorpion(char c_MorpionArray[3][3], char c_InitValue){

    int i, j;

    // Loop through the table, and give each cell the char value " "
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){

            c_MorpionArray[i][j] = c_InitValue;

        }
    }
}

// Show the board of the Morpion on screen, by printing the array2D
void printMorpion(char c_MorpionArray[3][3]){

    int i, j;

    // Loop through the table, and give each cell the char value " "
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            // Print the value of the current cell
            printf("%c ", c_MorpionArray[i][j]);

            // Print the vertical separation between cells
            if(j < 2){
                printf("|");
            }
        }
        // New line
        printf("\n");

        // Print the horizontal separation between cells
        if(i < 2){
            printf("-- -- --\n");
        }
    }
    printf("\n");
}

// Check if the input of the player is inside the bounds of the Morpion
// if it is, return true, if not return false
int isInsideBounds(int c_NewMove){

    if((c_NewMove > 3) || (c_NewMove < 1)){
        return false;
    } else {
        return true;
    }
}

// Ask the player for a x coordinate for his move, and return it
int askForX(int n_xNewMove){
    do{
        printf("X: ");
        scanf("%d", &n_xNewMove);
        fflush(stdin);

        if(isInsideBounds(n_xNewMove) == false){
            printf("Entrez une coordonnee a l'interieur du tableau!\n");
        }
    } while(isInsideBounds(n_xNewMove) == false);

    return n_xNewMove - 1;
}

// Ask the player for a y coordinate for his move, and return it
int askForY(int n_yNewMove){
    do{
        printf("Y: ");
        scanf("%d", &n_yNewMove);
        fflush(stdin);

        if(isInsideBounds(n_yNewMove) == false){
            printf("Entrez une coordonnee a l'interieur du tableau!\n");
        }
    } while(isInsideBounds(n_yNewMove) == false);

    return n_yNewMove - 1;
}

// Toggle the player, so they play alternatively
int togglePlayer(int n_CurrentPlayer){

    if(n_CurrentPlayer == ROND){
        n_CurrentPlayer = CROIX;
    } else{
        n_CurrentPlayer = ROND;
    }

    return n_CurrentPlayer;
}

// Deduce the char 'X' or 'Y' from witch player is currently playing
char WhatCharIsPlayers(int n_CurrentPlayer){
    char whatChar;

    if(n_CurrentPlayer == ROND){
        whatChar = 'X';
    } else{
        whatChar = 'O';
    }

    return whatChar;
}

// Check is the place the player want to place his move is already taken or not
// Return true if it is already taken, return false is it isn't
int isAlreadyTaken(char c_MorpionArray[3][3], int n_xNewMove, int n_yNewMove){

    if(c_MorpionArray[n_yNewMove][n_xNewMove] == ' '){
        return false;
    } else {
        return true;
    }
}

// Check if a player is winning or not.
// if no player wins, return 0
// if the ROND player wins return ROND
// if the CROIX player wins return CROIX
int isAPlayerWinning(char c_MorpionArray[3][3]){
    int win = false;
    int i;

    // Check the completion of each row and columns
    for(i = 0; i<3; i++){
        // Check the completion by the same player of each rows
        if((c_MorpionArray[i][0] == c_MorpionArray[i][1]) && (c_MorpionArray[i][0] == c_MorpionArray[i][2]) && (c_MorpionArray[i][0] != ' ')){
            win = true;
        }
        // Check the completion by the same player of each column
        if((c_MorpionArray[0][i] == c_MorpionArray[1][i]) && (c_MorpionArray[0][i] == c_MorpionArray[2][i]) && (c_MorpionArray[0][i] != ' ')){
            win = true;
        }
    }

    // Check the completion by the same player of each diagonals
    if((c_MorpionArray[0][0] == c_MorpionArray[1][1]) && (c_MorpionArray[0][0] == c_MorpionArray[2][2]) && (c_MorpionArray[0][0] != ' ')){
        win = true;
    }
    if((c_MorpionArray[0][2] == c_MorpionArray[1][1]) && (c_MorpionArray[0][2] == c_MorpionArray[2][0]) && (c_MorpionArray[0][2] != ' ')){
        win = true;
    }

    return win;
}


// Print who the winner is
void printWinner(int n_Win, char c_MorpionArray[3][3]){
    if(n_Win == ROND){

        // Print the table on screen
        printMorpion(c_MorpionArray);
        printf("\nLe joueur qui joue les ronds a gagné!!!\n");

    } else if(n_Win == CROIX){

        // Print the table on screen
        printMorpion(c_MorpionArray);
        printf("\nLe joueur qui joue les croix a gagné!!!\n");

    }
}

// Print who is currently playing
void printCurrentPlayer(int n_CurrentPlayer){

    if(n_CurrentPlayer == ROND){
        printf("C'est a rond de jouer\n");
    } else if(n_CurrentPlayer == CROIX){
        printf("C'est a croix de jouer\n");
    } else {
        printf("Erreur: la variable n_CurrentPlayer est mal attribuée\n");
    }
}
