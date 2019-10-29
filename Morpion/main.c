#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1
#define ROND 1
#define CROIX 2

// Declare functions
void initializeMorpion(char cMorpionArray[3][3], char cInitValue);
void printMorpion(char cMorpionArray[3][3]);
int isInsideBounds(int NewMove);
int askForX(int xNewMove);
int askForY(int yNewMove);
int togglePlayer(int dCurrentPlayer);
char cWhatCharIsPlayer(int dCurrentPlayer);
int isAlreadyTaken(char cMorpionArray[3][3], int xNewMove, int yNewMove);
int isAPlayerWinning(char cMorpionArray[3][3]);
void printWinner(int dWin, char cMorpionArray[3][3]);
void printCurrentPlayer(int dCurrentPlayer);

int main()
{
    // Declare the table, which will contain the Morpion
    char cMorpionArray[3][3];

    // Declare the variables used to store the coordinates of the player's move
    int xNewMove, yNewMove;

    // Declare the variable used to keep track of which player is playing now
    int dCurrentPlayer = CROIX;

    // Declare the variable that stocks which player wins
    int dWin = 0;

    // Declare the variable that counts the number of moves done
    int dMoveCounter = 0;

    // Initialize the Morpion table by giving each cell a " " for value
    initializeMorpion(cMorpionArray, ' ');

    // Procedure of a turn, looping while the game isn't finished
    do{
        // Print the table on screen
        printMorpion(cMorpionArray);

        // Ask the player to enter the coordinates of his next move until he gives an empty location
        do{
            printCurrentPlayer(dCurrentPlayer);
            printf("Ou voulez vous jouer?\n\n");
            xNewMove = askForX(xNewMove);
            yNewMove = askForY(yNewMove);

            // Give a warning message if the cell is already taken
            if(isAlreadyTaken(cMorpionArray, xNewMove, yNewMove) == true){
                printf("Un coup a deja ete joue a cet endroit\n");
            }
        } while(isAlreadyTaken(cMorpionArray, xNewMove, yNewMove) == true);

        // Store 'X' or 'O' inside the Morpion array2D at the coordinates given by the player
        cMorpionArray[yNewMove][xNewMove] = cWhatCharIsPlayer(dCurrentPlayer);

        // Check for the win of one of the players, if one is winning print which one
        dWin = isAPlayerWinning(cMorpionArray);

        // Print on screen who is the winner if there is one
        if(dWin != 0){
            printWinner(dWin, cMorpionArray);
        }


        // Toggle the player, so we can start the next turn
        dCurrentPlayer = togglePlayer(dCurrentPlayer);

        // Increment the move counter
        dMoveCounter++;

        // Print a message in case of a draw
        if((dMoveCounter == 9) && (dWin == 0)){
            printf("Egalite!");
            break;
        }

    } while(dWin == 0);
    // Get out of the game loop if a player as won

    return 0;
}

// Initialize the array2D given in argument1 at the char value passed in argument2
void initializeMorpion(char cMorpionArray[3][3], char cInitValue){

    int i, j;

    // Loop through the table, and give each cell the char value " "
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){

            cMorpionArray[i][j] = cInitValue;

        }
    }
}

// Show the board of the Morpion on screen, by printing the array2D
void printMorpion(char cMorpionArray[3][3]){

    int i, j;

    // Loop through the table, and give each cell the char value " "
    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            // Print the value of the current cell
            printf("%c ", cMorpionArray[i][j]);

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
int isInsideBounds(int NewMove){

    if((NewMove > 3) || (NewMove < 1)){
        return false;
    } else {
        return true;
    }
}

// Ask the player for a x coordinate for his move, and return it
int askForX(int xNewMove){
    do{
        printf("X: ");
        scanf("%d", &xNewMove);
        fflush(stdin);

        if(isInsideBounds(xNewMove) == false){
            printf("Entrez une coordonnee a l'interieur du tableau!\n");
        }
    } while(isInsideBounds(xNewMove) == false);

    return xNewMove - 1;
}

// Ask the player for a y coordinate for his move, and return it
int askForY(int yNewMove){
    do{
        printf("Y: ");
        scanf("%d", &yNewMove);
        fflush(stdin);

        if(isInsideBounds(yNewMove) == false){
            printf("Entrez une coordonnee a l'interieur du tableau!\n");
        }
    } while(isInsideBounds(yNewMove) == false);

    return yNewMove - 1;
}

// Toggle the player, so they play alternatively
int togglePlayer(int dCurrentPlayer){

    if(dCurrentPlayer == ROND){
        dCurrentPlayer = CROIX;
    } else{
        dCurrentPlayer = ROND;
    }

    return dCurrentPlayer;
}

// Deduce the char 'X' or 'Y' from witch player is currently playing
char cWhatCharIsPlayer(int dCurrentPlayer){
    char whatChar;

    if(dCurrentPlayer == ROND){
        whatChar = 'X';
    } else{
        whatChar = 'O';
    }

    return whatChar;
}

// Check is the place the player want to place his move is already taken or not
// Return true if it is already taken, return false is it isn't
int isAlreadyTaken(char cMorpionArray[3][3], int xNewMove, int yNewMove){

    if(cMorpionArray[yNewMove][xNewMove] == ' '){
        return false;
    } else {
        return true;
    }
}

// Check if a player is winning or not.
// if no player wins, return 0
// if the ROND player wins return ROND
// if the CROIX player wins return CROIX
int isAPlayerWinning(char cMorpionArray[3][3]){
    int win = false;
    int i;

    // Check the completion of each row and columns
    for(i = 0; i<3; i++){
        // Check the completion by the same player of each rows
        if((cMorpionArray[i][0] == cMorpionArray[i][1]) && (cMorpionArray[i][0] == cMorpionArray[i][2]) && (cMorpionArray[i][0] != ' ')){
            win = true;
        }
        // Check the completion by the same player of each column
        if((cMorpionArray[0][i] == cMorpionArray[1][i]) && (cMorpionArray[0][i] == cMorpionArray[2][i]) && (cMorpionArray[0][i] != ' ')){
            win = true;
        }
    }

    // Check the completion by the same player of each diagonals
    if((cMorpionArray[0][0] == cMorpionArray[1][1]) && (cMorpionArray[0][0] == cMorpionArray[2][2]) && (cMorpionArray[0][0] != ' ')){
        win = true;
    }
    if((cMorpionArray[0][2] == cMorpionArray[1][1]) && (cMorpionArray[0][2] == cMorpionArray[2][0]) && (cMorpionArray[0][2] != ' ')){
        win = true;
    }

    return win;
}


// Print who the winner is
void printWinner(int dWin, char cMorpionArray[3][3]){
    if(dWin == ROND){

        // Print the table on screen
        printMorpion(cMorpionArray);
        printf("\nLe joueur qui joue les ronds a gagné!!!\n");

    } else if(dWin == CROIX){

        // Print the table on screen
        printMorpion(cMorpionArray);
        printf("\nLe joueur qui joue les croix a gagné!!!\n");

    }
}

// Print who is currently playing
void printCurrentPlayer(int dCurrentPlayer){

    if(dCurrentPlayer == ROND){
        printf("C'est a rond de jouer\n");
    } else if(dCurrentPlayer == CROIX){
        printf("C'est a croix de jouer\n");
    } else {
        printf("Erreur: la variable dCurrentPlayer est mal attribuée\n");
    }
}
