/*****
 Grid game
 *****/
#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define BOARD_SIZE 11 // ***the create board function was copied from Aaron's example of the worksheet***
#define HORIZONTAL 'H'
#define VERTICAL 'V'

void instructions (){
/***This function is in charge of printing the instructions to play my game***/
      printw("Hello thank you for playing my game! Here are the instructions to\n");
      printw("\t         **** BATTLE SHIP ****\n");
      printw("Each player deploys his ships of lengths varying from 1 to 4 squares secretly on the \n");
      printw("square grid. Make sure that each player puts 4 (1 square ships), 3 (2 square ships), 2 (3\n");
      printw("square ships) and 1 (4 square ship) down. If not error message will appear! \n");
      printw("Then each player shoots at the other's grid by clicking a location. If the attacker \n hits one of the defenders ship a text with the message 'Hit!' or 'Miss!' will show up respectively. \n");
      printw("You try to deduce where the enemy ships are and sink them. First to do so wins. \n");
      printw("\t\t GOOD LUCK\n");
    //  printw("\t\t Click enter to start! \n");
     // refresh();
}  
 char **create_board() {
/***This function taken from Aaron's worksheet just allocates memory in the heap for the board***/
     char **board = malloc(sizeof(char *) * BOARD_SIZE);
     for (int r = 0; r < BOARD_SIZE; r++) {
         board[r] = malloc(sizeof(char) * BOARD_SIZE);
         for (int c = 0; c < BOARD_SIZE; c++) {
             board[r][c] = ' ';
         }
     }
     return board;
}

void print_board(char **board) { 
//***the print board function was copied from Aaron's example of the worksheet but modified to fit the needs of my game***/
     printw("---------------------------------------------\n");
     printw("|   ");
     printw("| %c |",'A' );
     for (char letters = 'B'; letters <'K';letters++){
         printw(" %c |",letters);
     }
     printw("\n");
     printw("---------------------------------------------\n");
     for (int r = 0; r < 10; r++) {
         if (r <= 9){
         printw("| %d ", r);
         }
         else {
             printw("|%d ",10);
         }
         for (int c = 0 ; c< 10; c++){
             printw("| ");
             if (board [r][c]== '@' || board [r][c]== '+'|| board [r][c]== '-'){
                 printw("%c ", board[r][c]);
             }
             else {
                 printw(" %c", board[r][c]);
            }
        }
         printw("|\n");
         printw("---------------------------------------------\n");
    }
}

int ship_radar (int row, int column, char** player_board){
/*** This fucntion just checks that when the player inputs a ship that there isnt a ship already on that specific
spot. So it returns 1 if nothing is there (true). If there is something there it returns 0 (false)
so that it basically prompts the user to input the coordinates of the ship again ***/
   // printf("we are in ship radar\n");
    if (player_board[row][column- 'A']== '@'){
        //printf("there is a boat here");
        return 0;
    }
    //printf("there is not a boat here");
    return 1;
}

int validNum (int num){
    if (num < 0 || num >9){
        return 0;
    }
    else if (getchar()!= '\n'){
        return 0;
    }
return 1;
}


void vertical_placer (int ship, char **player_board){
/*** For this vertical function this will basically ask the user for inputs of coordinates in which they want to place the ship
and it will check whether the coordinates are valid coordinates and if not its goning to prompt the udser
to enter a new value/char. ***/
    printw("*** PLACING SHIP VERTICALLY PLEASE FOLLOW DIRECTIONS BELOW ***\n");
    print_board(player_board);
    char column;
    int start;
    int end;
    int columns =0;
    int rows=0;
    //printf("%c\n",column);
    // use getchar and then subtract it from 0. 
    while (columns == 0){
        printw("This ship is of size %d, please specify the column you want to place it on. Acceptable coordinates (A-J)\n",ship);
        refresh();
        column = getch();
        column = toupper(column);
        refresh();
        if (column < 'A' || column > 'J'){
            clear();
            printw("Please put a valid coordinate (A-J) only.\n");
            refresh();
            columns =0;
        }
        else{
            columns =1;
        }
    }
    while (rows == 0){
        printw("\nGreat now input the row in which you want you ship to go. Acceptable coordinates (0-9)\n");
        start = getch();
        start = start - '0';
        if (validNum(start)){
            clear();
            printw("Please input valid coordinates for rows (0-9) ONLY\n");
            refresh();
            rows= 0;
        }
        else if ((end = start +ship -1) >9){
            clear();
            printw("Invalid input you want a coordinate that is going to be bigger than the grid\n");
            refresh();
            rows =0;
        }
        else{
            rows =1;
        }
    }
    //end = start +ship -1;
    if (ship_radar(start, column, player_board)==1){
        for (int i = start; i<=end;i++){ 
            player_board [i][column - 'A']= '@';// It was the same logic as using 
        }                               // getchar() and subtracting 0 to get the char to int but this is the opposite 
    }
    else{
        clear();
        printw("There is a ship in that coordinate already try again\n");
        refresh();
        vertical_placer(ship,player_board);
    }
    clear();
    print_board(player_board);
    refresh();
    printw("Once you are done viewing your board press any key\n");
    char keypressed = getch();
    if (keypressed == 'Y'){
        clear();
    }
    else{
        clear();
    }
}

void horizontal_placer (int ship, char **player_board){
/*** For this horizontal function this will basically ask the user for inputs of coordinates in which they want to place the ship
and it will check whether the coordinates are valid coordinates and if not its goning to prompt the udser
to enter a new value/char. ***/
    //printf("we made it to horizontal placer");
    printw("*** PLACING SHIP HORIZONTALLY PLEASE FOLLOW DIRECTIONS BELOW ***\n");
    print_board(player_board);
    int row;
    char start;
    char end;
    int rows=0;
    int columns =0;
    while (rows ==0){
        printw("This ship is of size %d, please specify the row you want to place it on. Acceptable coordinates (0-9) (Press Enter)\n",ship);
        row = getch(); // thank you for your help on this Aaron
        row = row - '0';
        refresh();
        if (validNum(row)){
            printw("Please put a valid coordinate (0-9) only.\n");
            getch();
            rows = 0;
        }
        else {
            rows =1;
        }
    }
    while (columns == 0 ){
        printw("\nGreat now input the column in which you want you ship to go. Acceptable coordinates (A-J)\n");
        printw("*** Only Press the Key you want to press DO NOT PRESS ENTER! ***\n");
        start = getch();
        start = toupper(start);
        refresh();
        if (start< 'A' || start > 'J'){
            clear();
            printw("INVALID %d Please input valid coordinates for columns (A-J) ONLY\n", start);
            refresh();
            columns=0;
        }
        else if ((end = start+ship -1) > 'J'){
            clear();
            printw("Invalid input you want to put ship past the grid of the game. Choose a shorter coordinate\n");
            refresh();
            columns =0;
        }
        else{
            columns =1;
        }
    }
    end = start+ship -1;
    if (ship_radar(row, end , player_board)==1){
        for (int i = start; i<=end;i++){ 
            player_board [row][i - 'A']= '@'; // for some guidance and I rewrote the code in my own way! It was the same logic as using 
        }
    }
    else if (ship_radar(row, end , player_board)==0){
        clear();
        printw("There is a ship in that location please try again! \n");
        refresh();
        horizontal_placer(ship, player_board);
    }   
        clear();
        printw("Board after coodinates are placed :)\n");
        print_board(player_board); 
        refresh();                          // getchar() and subtracting 0 to get the char to int but this is the opposite 
        printw("Click any key when you are done viewing your board...? \n");
        char answer = getch();
        answer = toupper(answer);
        refresh();
        if (answer == 'Y'){
            clear();
        }
        else{
            clear();
        }
    refresh();   
    }                     

void ship_orientation (char **player_board){
/*** This function asks the player on whether they want to place their ship 
vertical or horizontal and then depending on the input of the user it redirects the placement 
to othre functions and it does this for all 7 ships***/
    //printf("Made it to ship place!\n");
   // int shipSizes []= {1,1,1,2,2,3,4};
   // int total = 7;
    int shipSizes []= {3};
    int total = 1;
    int counter = 1;
    char orientation;
    print_board(player_board);
    for (int i =0 ; i< total; i++){
        printw("Placing ship number: %d/7 that is of size: %d\n",counter, shipSizes[i]);
        printw("Do you want your ship to be vertical or horizontal...?\n");
        printw("Use (H) or (h) for horizontal or (V) or (v) for vertical (Case insensitive)\n");
        printw("*** Only Press the Key you want to press DO NOT PRESS ENTER! ***\n");
        //refresh();
       // keypad(stdscr, TRUE);
        orientation = getch();
       // keypad(stdscr, TRUE);
        //getch(); 
        refresh();
        orientation= toupper(orientation); // takes care of the case insensitive bug
       // printf("this is what it prints: %c\n", orientation); // with the use of stackOF.
        counter++;
        if (orientation ==HORIZONTAL){
            clear();
            refresh();
            horizontal_placer(shipSizes[i],player_board);
        }
        else if(orientation == VERTICAL){
            clear();
            refresh();
            vertical_placer(shipSizes[i], player_board);
        }
        else{
            clear();
            printw("*** Invalid input %d, please use acceptable inputs (H) or (V) ***\n", orientation);
            refresh();
            counter--;
            i--;
        }
    }
    refresh();
}

int ship_attack(char ** enemy_board, int row, char column, char ** gameboard){
/*** This function is the same function that i had for ship radar but this one has print statements 
that will let the user know whether or not the attack was a success. ***/
    if (enemy_board [row][column- 'A']== '@'){
        printw("this hit was a: ***HIT***\n");
       // print_board(gameboard);

        return 1;
    }
    else if (enemy_board [row][column- 'A']== '+'){
        return 1;
    }
    printw("This hit was a: Miss...\n");
    //print_board(gameboard);
 //   refresh(); 
    return 0;
}

int game_over (char ** player_board){
/***This function was modified to fit my needs but its bascially the same logic from Aaron's worksheet, but there is not 
a malloc line of code for this function because all I need to check is if there is a '@ still in the board. ***/
    for (int x=0; x< BOARD_SIZE; x++){
        //printf("%d",x);
        for (int y = 0; y < BOARD_SIZE;y++){
            if (player_board[x][y]== '@'){
                return 0;
            }
        }
    }
    return 1;
}
void attack_input(int player, char ** enemy_board, char ** gameboard){
/***This function just prompts the user to set the coordinates of the attack and calls on the attack function
to see whether or not it was a hit or miss ***/
    printw("Player %d current state of misses and hits!: \n", player);
    print_board(gameboard);
    int row;
    char column;
    int columns =0;
    int rows = 0;
   // getch();
    while (columns ==0){
        printw("Player %d currently attacking...\n", player);
        printw("Please enter the coumn coordinates of your attack (Acceptable A-J Only)\n");
        refresh();
        column = getch();
        column = toupper(column);
        if (column < 'A' || column > 'J'){
            clear();
            printw("Invalid coordinates try again, you aren't attacking correctly :( \n");
            refresh();
            columns =0;
        }
        else {
            columns =1;
        }
    }
    while (rows == 0){
        printw("\nYAY, ok one last thing before we shoot. Input the row in which you want to send the attack to \n");
        printw("Please input valid coordinates for rows (0-9) ONLY\n");
        row = getch();
        row = row - '0';
        refresh();
        if (row < 0 || row > 9){
            clear();
            printw("Invalid coordinates try again, you aren't attacking correctly :( \n");
            refresh();
            rows =0;
        }
        else {
            rows =1;
        }
    }
    if (gameboard[row][column- 'A']== '+' || gameboard[row][column- 'A']== '-'){
        clear();
        printw("You tried attacking this coordinate please try another spot\n");
        refresh();
        if (gameboard[row][column- 'A']== '+'){
            gameboard[row][column- 'A'] = '+';
        }
        else {
           gameboard[row][column- 'A'] = '-'; 
        }
        attack_input(player, enemy_board,gameboard);
    }
    int result = ship_attack(enemy_board,row,column,gameboard);
    if (result ==1){
        gameboard[row][column- 'A'] = '+';
        enemy_board[row][column- 'A'] = '+';
        refresh();
    }
    else{
        gameboard[row][column- 'A']= '-';
        enemy_board[row][column- 'A'] = '-';
        refresh();
    }
    clear();
    printw("Player %d state of misses and hits after attack!: \n", player);
    print_board(gameboard);
    refresh();
    printw("When you are done looking at your board please press any key! \n");
    refresh();
    char keypressed = getch();
    keypressed = toupper(keypressed);
    if (keypressed == 'Y'){
        clear();
    }
    else{
        clear();
    }
}

void free_mem (char **board){ 

    for (int i = 0; i< BOARD_SIZE; i++){
        free(board[i]);
    }
    free(board);
}

int main() {
/*** This is the main which handles all of the calls of my game. I know it has a lot of print statements
ill correct these by the time the revisions are due. ***/  
    //WINDOW * win = newwin(100, 100, 100, 100);
    initscr();
    instructions();
    //printw("\n\n");
    int player = 1;
    char **player_1_board = create_board();
    char **player_2_board = create_board();
    char ** gameboard1 = create_board();
    char ** gameboard2 = create_board();
    printw("Player 1: \n \n");
   // print_board(player_1_board);
    printw("***Placing ships for player 1:***\n");
    refresh();
    ship_orientation(player_1_board);
    //clear();
    printw("Player 2: \n \n");
    //print_board(player_2_board);
    //printw("\n\n");
    printw("\n***Placing ships for player 2:***\n");
    ship_orientation(player_2_board);
    clear ();
    printw("*** All Boats Have Been Placed let the game Begin ! ***\n");
    printw("When attacking the + represents a hit on the board and the - represents a miss\n\n\n");
    refresh();
    while (!game_over (player_1_board) && !game_over (player_2_board)){
        if (player ==1){
            attack_input (player, player_2_board, gameboard2);
            player=2;
            if(game_over(player_2_board)){
                clear();
                printw("\n\n\n\n\t\t\t**** Player 1 wins the game! ****\n");
                refresh();
                //return 0;
            }
        }
        else {
            attack_input (player, player_1_board, gameboard1);
            player=1;
            if(game_over(player_1_board)){
                clear();
                printw("\n\n\n\n\t\t\t**** Player 2 wins the game! ****\n");
                refresh();
                //return 0;
            }
        }
    }
    free_mem(player_1_board);
    free_mem(player_2_board);
    free_mem(gameboard1);
    free_mem(gameboard2);
    printw("\t\t\t**** Click Any key to exit ****\n");
    char key = getch();
    key = toupper(key);
    if (key == 'Y'){
        endwin();
    }
    else {
        endwin();
    }

}
