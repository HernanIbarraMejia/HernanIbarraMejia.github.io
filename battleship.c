#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//This  function makes every element of board 1 equal to those on board 2 (hence 122)
void equal_boards_122(char b1[11][11], char b2[11][11]);

//This function takes as an argument a board and then prints it
void display_board(char board[11][11]);

//This function alone takes care of moving a boat made of some "symbol" in an specified "board"
void move_boat(char board[11][11], char symbol);
    //This function, called by move_boat, moves a boat made of some "symbol" one space up (when possible)
    void move_up(char board[11][11], char symbol);
    //This function, called by move_boat, moves a boat made of some "symbol" one space left (when possible)
    void move_left(char board[11][11], char symbol);
    //This function, called by move_boat, moves a boat made of some "symbol" one space down (when possible)
    void move_down(char board[11][11], char symbol);
    //This function, called by move_boat, moves a boat made of some "symbol" one space right (when possible)
    void move_right(char board[11][11], char symbol);
    //This function, called by move_boat, rotates a boat made of some "symbol" (when possible)
    void move_rotate(char board[11][11], char symbol);
        //This function, called by move_rotate, returns 'H' if the boat is horizontal or 'V' otherwise.
        char orientation(char board[11][11], char symbol);
        //This function, called by move_rotate, rotates a vertical boat to an horizontal position
        //(The arguments i and j are the first instances of the symbol of the boat in the board,
        //counting from top to bottom and from left to right)
        void rotate_ver_to_hor (char board[11][11], char symbol, int lenght, int i, int j);
            //Tries to rotate the boat right and returns true if successful.
            bool rotate_right(char board[11][11], char symbol, int lenght, int i, int j);
            //Tries to rotate the boat left
            void rotate_left(char board[11][11], char symbol, int lenght, int i, int j);

        //Similar to rotate_ver_to_hor
        void rotate_hor_to_ver (char board[11][11], char symbol, int lenght, int i, int j);

            bool rotate_up(char board[11][11], char symbol, int lenght, int i, int j);

            void rotate_down(char board[11][11], char symbol, int lenght, int i, int j);

//This function tells you whether an item (or a boat for our purposes) is in the board
bool in_board(char board[11][11], char symbol);

//This functions tells if all the board's boats are sunk or not
bool dunked_on(char board[11][11]);

int main()
{
    //To know whether Player 1 or Player 2 won the game
    int winner;

    //Each player gets two boards: One where their ships go and one where they shoot the enemy
    char b_own_p1[11][11], b_enemy_p1[11][11], b_own_p2[11][11], b_enemy_p2[11][11];

    //Dummy variable, not to worry about
    char place_holder;

    //Setting the empty board: A 11 by 11 board with numbers from 0 to 9 in the first row and letters from A to J in the first column
    b_own_p1[0][0] = ' ';
    b_own_p1[0][1] = '0';
    b_own_p1[0][2] = '1';
    b_own_p1[0][3] = '2';
    b_own_p1[0][4] = '3';
    b_own_p1[0][5] = '4';
    b_own_p1[0][6] = '5';
    b_own_p1[0][7] = '6';
    b_own_p1[0][8] = '7';
    b_own_p1[0][9] = '8';
    b_own_p1[0][10] = '9';

    b_own_p1[1][0] = 'A';
    b_own_p1[2][0] = 'B';
    b_own_p1[3][0] = 'C';
    b_own_p1[4][0] = 'D';
    b_own_p1[5][0] = 'E';
    b_own_p1[6][0] = 'F';
    b_own_p1[7][0] = 'G';
    b_own_p1[8][0] = 'H';
    b_own_p1[9][0] = 'I';
    b_own_p1[10][0] = 'J';

    //Set all other elements to a empty space: ' '
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            //Exclusive or: ^
            //This is because the (0,0) needs also to be blank
            if(i == 0 ^ j == 0)
            {
                continue;
            }
            b_own_p1[i][j] = ' ';
        }
    }

    //At the start, all boards are empty
    equal_boards_122(b_enemy_p1, b_own_p1);
    equal_boards_122(b_own_p2, b_own_p1);
    equal_boards_122(b_enemy_p2, b_own_p1);

    //Start the game
    printf("Players! Welcome to Battleship. Both of you will get 5 ships, and you can place them wherever you like on your respective 10 by 10 boards.\n");
    printf("First, let Player 1 come and position their ships\n\n");
    printf("Your board, Player 1: \n");

    //Print the board
    display_board(b_own_p1);

    printf("\nYou get a ship that occupies five spaces, four spaces and two spaces. You also get two ships that occupy three spaces.\n\n");
    printf("Press SPACE when you are ready to place your ships\n");

    //getch() with the do-while will hold the execution of the code below until the player inputs a SPACE
    do
    {
        place_holder = getch();
    }
    while(place_holder != ' ');

    //This clears the console
    system("cls");

    //Now we put some boats

    //Aircraft Carrier (5 spaces)
    for(int i = 2; i <= 6; i++)
    {
        b_own_p1[i][10] = '$';
    }

    //Battleship (4 spaces)
    for(int i = 5; i <= 8; i++)
    {
        b_own_p1[i][8] = '&';
    }

    //Cruiser (3 spaces) x2
    for(int i = 3; i <= 5; i++)
    {
        b_own_p1[4][i] = '=';
        b_own_p1[6][i] = '~';
    }

    //Destroyer (2 spaces)
    b_own_p1[2][2] = '*';
    b_own_p1[3][2] = '*';

    //Make the two boards of the players equal
    equal_boards_122(b_own_p2, b_own_p1);

    //The character the player inputs when selecting a boat
    char select_a_boat;

    //In this do-while the whole selection for Player 1 process is made.
    do
    {
        //In this printf is what the whole selection process is going to look like
        printf("Player 1: your boats are numbered (in ascendant order of length) from 1 to 5. Press a number to select one! Press 0 when you are COMPLETLY done with the setup.\n\n");

        //Print the player's own board
        display_board(b_own_p1);

        //Print a legend of available boats
        printf("\n\n");
        printf("1. Destroyer              **\n");
        printf("2. Cruiser               ===\n");
        printf("3. Cruiser               ~~~\n");
        printf("4. Battleship           &&&&\n");
        printf("5. Aircraft Carrier    $$$$$\n\n");

        //Player inputs a number from 1 to 5 to select boat
        select_a_boat = getch();

        //We use the move_boat function to move the specified boat according to the user.
        //Notice the function takes as an input the symbol that the boat is drawn off, not a number.
        switch(select_a_boat)
        {
            case '1':
                move_boat(b_own_p1, '*');
                break;

            case '2':
                move_boat(b_own_p1, '=');
                break;

            case '3':
                move_boat(b_own_p1, '~');
                break;

            case '4':
                move_boat(b_own_p1, '&');
                break;

            case '5':
                move_boat(b_own_p1, '$');
                break;

            //If the player inputs anything other than a number from one to five, the console clears
            //and this iteration of the do-while ends. In the next iteration the board will be printed
            //again.
            default:
                system("cls");
                break;
        }

    }
    //The selection process ends when the players inputs a 0.
    while(select_a_boat != '0');

    //Same process, but for player 2
    do
    {
        printf("Player 2: your boats are numbered (in ascendant order of length) from 1 to 5. Press a number to select one! Press 0 when you are COMPLETLY done with the setup.\n\n");
        display_board(b_own_p2);
        printf("\n\n");
        printf("1. Destroyer              **\n");
        printf("2. Cruiser               ===\n");
        printf("3. Cruiser               ~~~\n");
        printf("4. Battleship           &&&&\n");
        printf("5. Aircraft Carrier    $$$$$\n\n");
        select_a_boat = getch();

        switch(select_a_boat)
        {
            case '1':
                move_boat(b_own_p2, '*');
                break;

            case '2':
                move_boat(b_own_p2, '=');
                break;

            case '3':
                move_boat(b_own_p2, '~');
                break;

            case '4':
                move_boat(b_own_p2, '&');
                break;

            case '5':
                move_boat(b_own_p2, '$');
                break;

            default:
                system("cls");
                break;
        }

    }
    while(select_a_boat != '0');

    //Press SPACE to start the game for real
    do
    {
        system("cls");
        printf("Player 1 should press SPACE to start the game for real");
        place_holder = getch();
        system("cls");
    }
    while(place_holder != ' ');

    //If the player hits something, this variable will hold the symbol that the boat that was hit is made of
    char what_i_hit;

    //This is the input of the Player when attacking eg. F7
    char attack[2];

    //The coordinates the player intends to attack
    int coordinate1, coordinate2;

    //This do-while contains the whole game, except the end
    do
    {
        //Player 1's turn
        printf("Player 1: Your Turn \n\n");

        //Print an empty board representing the enemy's board
        printf("This is your enemy's board:\n\n");
        display_board(b_enemy_p1);

        //Print Player 1's board
        printf("\n\nThis is your board:\n\n");
        display_board(b_own_p1);

        printf("Enter a coordinate for attacking (a capital letter and a number eg. F7) and press ENTER\n");

        //This do-while translates the coordinates inputed by the Player into coordinates of the board
        //eg. F7 to [6][8]
        do
        {
            //Get the input as a capital letter and a number
            gets(attack);

            //Convert the number in the string "attack" into an integer data type
            //By the way this is the column in the board
            coordinate2 = attack[1] - '0';
            coordinate2 ++;

            //According to the letter inputted, coordinate1 is set to an integer (the row)
            switch(attack[0])
            {
                case 'A':
                    coordinate1 = 1;
                    break;
                case 'B':
                    coordinate1 = 2;
                    break;
                case 'C':
                    coordinate1 = 3;
                    break;
                case 'D':
                    coordinate1 = 4;
                    break;
                case 'E':
                    coordinate1 = 5;
                    break;
                case 'F':
                    coordinate1 = 6;
                    break;
                case 'G':
                    coordinate1 = 7;
                    break;
                case 'H':
                    coordinate1 = 8;
                    break;
                case 'I':
                    coordinate1 = 9;
                    break;
                case 'J':
                    coordinate1 = 10;
                    break;
                case 'a':
                    coordinate1 = 1;
                    break;
                case 'b':
                    coordinate1 = 2;
                    break;
                case 'c':
                    coordinate1 = 3;
                    break;
                case 'd':
                    coordinate1 = 4;
                    break;
                case 'e':
                    coordinate1 = 5;
                    break;
                case 'f':
                    coordinate1 = 6;
                    break;
                case 'g':
                    coordinate1 = 7;
                    break;
                case 'h':
                    coordinate1 = 8;
                    break;
                case 'i':
                    coordinate1 = 9;
                    break;
                case 'j':
                    coordinate1 = 10;
                    break;
                default:
                    //This value of coordinate2 will keep the do-while running
                    //until the input is correct
                    coordinate2 = 11;
                    break;
            }
        }
        while (0 > coordinate2 && coordinate2 > 10);

        //Check whether the coordinates hit something in Player 2's board.

        //If it hits
        if(b_own_p2[coordinate1][coordinate2] != ' ')
        {
            //Set what_i_hit equal to the symbol the boat hit is made of
            what_i_hit = b_own_p2[coordinate1][coordinate2];
            //Put an 'X' on both Player 2's board and on the board Player 1 uses
            //To fire to the enemy
            b_enemy_p1[coordinate1][coordinate2] = 'X';
            b_own_p2[coordinate1][coordinate2] = 'X';
            //Clear
            system("cls");
            //Print the board Player 1 uses to fire to the enemy
            printf("This is your enemy's board:\n\n");
            display_board(b_enemy_p1);
            //Print Hit!!
            printf("\n\nHit!!\n");

            //If the boat is no longer on the enemy's board,
            //Print a message acknowledging you've destroyed a boat
            if(!(in_board(b_own_p2, what_i_hit)))
            {
                switch(what_i_hit)
                {
                    case '*':
                        printf("You've just destroyed a Destroyer!\n");
                        break;

                    case '=':
                        printf("You've just destroyed a Cruiser!\n");
                        break;

                    case '~':
                        printf("You've just destroyed a Cruiser!\n");
                        break;

                    case '&':
                        printf("You've just destroyed a Battleship!\n");
                        break;

                    case '$':
                        printf("You've just destroyed a Aircraft Carrier!\n");
                        break;
                    default:
                        break;
                }
            }
        }

        //If it doesn't hit
        else
        {
            //Put an 'M' on the Player 1's board where he fires to the enemy.
            b_enemy_p1[coordinate1][coordinate2] = 'M';
            //And prints it
            system("cls");
            printf("This is your enemy's board:\n\n");
            display_board(b_enemy_p1);
            printf("\n\n Sorry, you've missed!\n");
        }

        //Wait until the player puts a SPACE for the Player 2's turn to begin
        printf("When you are ready, press SPACE to pass your turn to Player 2.\n");

        do
        {
            place_holder = getch();
        }
        while(place_holder != ' ');

        //Clear
        system("cls");

        //If Player 2's board is out of ships then Player 1 wins
        if(dunked_on(b_own_p2))
        {
            //Player 1 wins
            winner = 1;
            //Go to the endgame.
            goto ENDGAME;
        }

        //Player 2's turn, similar structure
        printf("Player 2: Your Turn \n\n");
        printf("This is your enemy's board:\n\n");
        display_board(b_enemy_p2);
        printf("\n\nThis is your board:\n\n");
        display_board(b_own_p2);
        printf("Enter a coordinate for attacking (a capital letter and a number eg. F7)\n");
        do
        {
            gets(attack);
            coordinate2 = attack[1] - '0';
            coordinate2 ++;
            switch(attack[0])
            {
                case 'A':
                    coordinate1 = 1;
                    break;
                case 'B':
                    coordinate1 = 2;
                    break;
                case 'C':
                    coordinate1 = 3;
                    break;
                case 'D':
                    coordinate1 = 4;
                    break;
                case 'E':
                    coordinate1 = 5;
                    break;
                case 'F':
                    coordinate1 = 6;
                    break;
                case 'G':
                    coordinate1 = 7;
                    break;
                case 'H':
                    coordinate1 = 8;
                    break;
                case 'I':
                    coordinate1 = 9;
                    break;
                case 'J':
                    coordinate1 = 10;
                    break;
                case 'a':
                    coordinate1 = 1;
                    break;
                case 'b':
                    coordinate1 = 2;
                    break;
                case 'c':
                    coordinate1 = 3;
                    break;
                case 'd':
                    coordinate1 = 4;
                    break;
                case 'e':
                    coordinate1 = 5;
                    break;
                case 'f':
                    coordinate1 = 6;
                    break;
                case 'g':
                    coordinate1 = 7;
                    break;
                case 'h':
                    coordinate1 = 8;
                    break;
                case 'i':
                    coordinate1 = 9;
                    break;
                case 'j':
                    coordinate1 = 10;
                    break;
                default:
                    coordinate2 = 11;
                    break;
            }
        }
        while (0 > coordinate2 && coordinate2 > 10);

        if(b_own_p1[coordinate1][coordinate2] != ' ')
        {

            what_i_hit = b_own_p1[coordinate1][coordinate2];
            b_enemy_p2[coordinate1][coordinate2] = 'X';
            b_own_p1[coordinate1][coordinate2] = 'X';
            system("cls");
            printf("This is your enemy's board:\n\n");
            display_board(b_enemy_p2);
            printf("\n\nHit!!\n");
            if(!(in_board(b_own_p1, what_i_hit)))
            {
                switch(what_i_hit)
                {
                    case '*':
                        printf("You've just destroyed a Destroyer!\n");
                        break;

                    case '=':
                        printf("You've just destroyed a Cruiser!\n");
                        break;

                    case '~':
                        printf("You've just destroyed a Cruiser!\n");
                        break;

                    case '&':
                        printf("You've just destroyed a Battleship!\n");
                        break;

                    case '$':
                        printf("You've just destroyed a Aircraft Carrier!\n");
                        break;
                    default:
                        break;
                }
            }
        }

        else
        {
            b_enemy_p2[coordinate1][coordinate2] = 'M';
            system("cls");
            printf("This is your enemy's board:\n\n");
            display_board(b_enemy_p2);
            printf("\n\n Sorry, you've missed!\n");
        }

        printf("When you are ready, press SPACE to pass your turn to Player 1.\n");

        do
        {
            place_holder = getch();
        }
        while(place_holder != ' ');

        if(dunked_on(b_own_p1))
        {
            winner = 2;
            goto ENDGAME;
        }

        system("cls");

    }
    //This do-while will run forever. The only way to get out is by winning and following the two
    //"goto"s to the ENDGAME.
    while(1 == 1);

    //If someone wins, announce the winner and print all boards
    ENDGAME:
    system("cls");
    printf("Player %d has won the game!\n\n", winner);
    printf("Player 1's board:\n\n");
    display_board(b_own_p1);
    printf("\n\nPlayer 1's perspective of the enemy's board:\n\n");
    display_board(b_enemy_p1);
    printf("\n\nPlayer 2's board:\n\n");
    display_board(b_own_p2);
    printf("\n\nPlayer 2's perspective of the enemy's board:\n\n");
    display_board(b_enemy_p2);

    return 0;
}

void equal_boards_122(char b1[11][11], char b2[11][11])
{
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            b1[i][j] = b2[i][j];
        }
    }
}

void display_board(char board[11][11])
{
   for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            printf("%c ", board[i][j]);
            if(j == 10)
            {
                printf("\n");
            }
        }
    }
}

void move_boat(char board[11][11], char symbol)
{
    //Input of the player
    char move;
    //Clears board, just in case
    system("cls");
    //This do-while will run until the player is happy with the position of the boat
    do
    {
        //Basically what it does
        printf("Move the ship with WASD, rotate with R and press SPACE when you are done\n\n");
        //Prints the board
        display_board(board);
        //Gets the input
        move = getch();
        //According to the input, a function is called that does the job
        switch(move)
        {
            case 'W':
                move_up(board, symbol);
                break;
            case 'S':
                move_down(board, symbol);
                break;
            case 'A':
                move_left(board, symbol);
                break;
            case 'D':
                move_right(board, symbol);
                break;
            case 'R':
                move_rotate(board, symbol);
                break;
            case 'w':
                move_up(board, symbol);
                break;
            case 's':
                move_down(board, symbol);
                break;
            case 'a':
                move_left(board, symbol);
                break;
            case 'd':
                move_right(board, symbol);
                break;
            case 'r':
                move_rotate(board, symbol);
                break;
            default:
                break;

        }
        system("cls");
    }
    //Finish when SPACE is pressed
    while(move != ' ');
}

void move_up(char board[11][11], char symbol)
{
    //Don't worry about this variable, it does nothing
    int useless;
    //Check if the boat can move up
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            //If there is an instance of the symbol the boat is made of
            if(board[i][j] == symbol)
            {
                //If there is something up that is not more of the same boat
                if(board[i-1][j] != ' ' && board[i-1][j] != symbol)
                {
                    //Terminate the function
                    goto TERMINATE1;
                }
            }

        }
    }

    //Everything is alright then
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            //If a symbol is found
            if(board[i][j] == symbol)
            {
                //It is deleted
                board[i][j] = ' ';
                //And replaced with one symbol but up a space
                board[i-1][j] = symbol;
            }

        }
    }
    TERMINATE1: useless = 1;
}


//Similar to move_up
void move_left(char board[11][11], char symbol)
{
    int useless;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(board[i][j] == symbol)
            {
                if(board[i][j-1] != ' ' && board[i][j-1] != symbol)
                {
                    goto TERMINATE2;
                }
            }

        }
    }
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(board[i][j] == symbol)
            {
                board[i][j] = ' ';
                board[i][j-1] = symbol;
            }

        }
    }
    TERMINATE2: useless = 1;
}

//Similar to move_up
void move_down(char board[11][11], char symbol)
{
    int useless;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(board[i][j] == symbol)
            {
                if (i == 10)
                {
                    goto TERMINATE3;
                }
                if(board[i+1][j] != ' ' && board[i+1][j] != symbol)
                {
                    goto TERMINATE3;
                }
            }

        }
    }
    for(int i = 10; i >= 0; i--)
    {
        for(int j = 10; j >= 0; j--)
        {
            if(board[i][j] == symbol)
            {
                board[i][j] = ' ';
                board[i+1][j] = symbol;
            }

        }
    }
    TERMINATE3: useless = 1;
}

//Similar to move_up
void move_right(char board[11][11], char symbol)
{
    int useless;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(board[i][j] == symbol)
            {
                if (j == 10)
                {
                    goto TERMINATE4;
                }
                if(board[i][j+1] != ' ' && board[i][j+1] != symbol)
                {
                    goto TERMINATE4;
                }
            }

        }
    }
    for(int i = 10; i >= 0; i--)
    {
        for(int j = 10; j >= 0; j--)
        {
            if(board[i][j] == symbol)
            {
                board[i][j] = ' ';
                board[i][j+1] = symbol;
            }

        }
    }
    TERMINATE4: useless = 1;
}

//The real fun begins
void move_rotate(char board[11][11], char symbol)
{
    //Determine the orientation of the boat
    char initial_orientation = orientation(board, symbol);

    //If boat is horizontal
    if(initial_orientation == 'H')
    {
        //This particular search will always yield the first the first instance of the
        //symbol, from top to bottom and left to right.
        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                //When this instance is found
                if(board[i][j] == symbol)
                {
                    //Depending on the symbol, there are different inputs for
                    //rotate_hor_to_ver(). The lenghts (third argument varies)
                    //Notice that i,j is this first instance we were talking
                    //about. Then we TERMINATE the whole function.
                    switch(symbol)
                    {
                        case '*':
                            rotate_hor_to_ver(board, symbol, 2, i, j);
                            goto TERMINATE5;
                            break;

                        //This is the same lenght as '='
                        case '~':
                            goto CASEQUAL;
                            break;

                        case '=':
                            CASEQUAL:
                            rotate_hor_to_ver(board, symbol, 3, i, j);
                            goto TERMINATE5;
                            break;

                        case '&':
                            rotate_hor_to_ver(board, symbol, 4, i, j);
                            goto TERMINATE5;
                            break;

                        case '$':
                            rotate_hor_to_ver(board, symbol, 5, i, j);
                            goto TERMINATE5;
                            break;

                        //Never's going to happen
                        default:
                            break;
                    }
                }
            }
        }
    }
    //Similarly, if it is vertical
    else
    {
        for(int i = 0; i < 11; i++)
        {
            for(int j = 0; j < 11; j++)
            {
                if(board[i][j] == symbol)
                {
                    switch(symbol)
                    {
                        case '*':
                            rotate_ver_to_hor(board, symbol, 2, i, j);
                            goto TERMINATE5;
                            break;

                        case '~':
                            goto CASEQUAL1;
                            break;

                        case '=':
                            CASEQUAL1:
                            rotate_ver_to_hor(board, symbol, 3, i, j);
                            goto TERMINATE5;
                            break;

                        case '&':
                            rotate_ver_to_hor(board, symbol, 4, i, j);
                            goto TERMINATE5;
                            break;

                        case '$':
                            rotate_ver_to_hor(board, symbol, 5, i, j);
                            goto TERMINATE5;
                            break;

                        default:
                            break;
                    }
                }
            }
        }

    }
    //Terminate the process. initial_orientation is not doing anything now
    TERMINATE5: initial_orientation = 'D';
}

char orientation(char board[11][11], char symbol)
{
    //This is the character that is going to be returned, either 'V' or 'H'
    char result;
    //This particular search will always yield the first the first instance of the
    //symbol, from top to bottom and left to right.
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            //Instance found
            if(board[i][j] == symbol)
            {
                //If we are not at the rightmost side.
                if(j != 10)
                {
                    //Check if there is more boat at the right

                    //If yes
                    if(board[i][j+1] == symbol)
                    {
                        //The boat is horizontal
                        result = 'H';
                        //Terminate
                        goto HERE;
                    }

                    //If not
                    else
                    {
                        //The boat is vertical
                        result = 'V';
                        //Terminate
                        goto HERE;
                    }
                }

                //If we are at the rightmost side
                else
                {
                    //The boat is definetly vertical
                    result = 'V';
                    //Terminate
                    goto HERE;
                }
            }
        }
    }
    //return the result
    HERE: return result;
}

void rotate_ver_to_hor (char board[11][11], char symbol, int lenght, int i, int j)
{
    //This records the boolean output of the function rotate_right
    bool x;

    //If we are too much to the left
    if(j < lenght)
    {
        //Only try to rotate right
        rotate_right(board, symbol, lenght, i, j);
    }

    //If we are too much to the right
    else if(11 - j < lenght)
    {
        //Only try to rotate left
        rotate_left(board, symbol, lenght, i, j);
    }

    //If we are by the center
    else
    {
        //Try to rotate to the right
        x = rotate_right(board, symbol, lenght, i, j);
        //If not successful
        if(!x)
        {
            //Try to rotate to the left
            rotate_left(board, symbol, lenght, i, j);
        }
    }
}

//Similar to rotate_ver_to_hor
void rotate_hor_to_ver(char board[11][11], char symbol, int lenght, int i, int j)
{
    bool rotate_up(char board[11][11], char symbol, int lenght, int i, int j);

    bool x;

    if(i < lenght)
    {
        rotate_down(board, symbol, lenght, i, j);
    }

    else if(11 - i < lenght)
    {
        rotate_up(board, symbol, lenght, i, j);
    }

    else
    {
        x = rotate_up(board, symbol, lenght, i, j);

        if(!x)
        {
            rotate_down(board, symbol, lenght, i, j);
        }
    }
}

/*The four functions below are the most complicated in the whole program

Here is how rotate_up() works, the other three functions are similar:

The goal is to rotate an horizontal boat upwards, in a vertical position.

Say we have a boat like this:

        * * * *
        ^
        |
    board[i][j]

The leftmost (and upmost also in the other functions) is what i, j are the
coordinates of.

We check if the space directly above this coordinate is empty (like in this case)
If it is, we put a "symbol" in there

        *
        * * * *

We do this (checking every time if the space is free) until we reach the desired lenght:


        *
        *
        *
        * * * *

Now we erase all "symbol"s in the original row (except for the one in the original coordinate)

        *
        *
        *
        *

That's the best case scenario... but what if the space above was not free?:

        =

        * * * *

First, the check-insert algorithm continues until we reach the problem:

        =
        *
        * * * *

Seeing this, we erase all the progress made (that is, erase "symbol"s in that column
except for the original):

        =

        * * * *

Then we change "j" (the original column) to the one on the right and start the whole
process again:

        =

        * * * *

        to:

        =
          *
        * * * *

        to:

        = *
          *
        * * * *

        to:

          *
        = *
          *
        * * * *

        finally:

          *
        = *
          *
          *

If there were an obstacle in this column too, then we pass on to the next column
and so on. Only if we run out of columns then the function returns false.

Notes:

- In reality, changing 'j' was confusing so we instead defined the variable
  "current" to indicate the current column being checked.

- The other three functions work exactly the same but some change "i" instead, or
  look at rows instead of columns, etc. But in principle is the same algorithm.

*/

bool rotate_up(char board[11][11], char symbol, int lenght, int i, int j)
{
    //The return value. It indicates whether the rotation was successful or not
    bool success;
    //Current column being iterated on
    int current;
    for(current = j; current < j + lenght; current++)
    {
        //This is the check-insert algorithm
        for(int k = 1; k < lenght; k++)
        {
            //Checks
            //If space is free
            if(board[i-k][current] == ' ')
            {
                //Insert
                board[i-k][current] = symbol;

                //If this is the last iteration
                if(k == lenght - 1)
                {
                    //We did it!
                    success = true;
                    //In the original row
                    for(int u = 0; u < 11; u++)
                    {
                        //Erase all symbols that are not the in the current
                        if(board[i][u] == symbol && u != current)
                        {
                            board[i][u] = ' ';
                        }
                    }
                    //Terminate
                    goto TERMINATE6;
                }
            }

            //If space is not free
            else
            {
                //In the column, erase all progress
                for(int u = 0; u < 11; u++)
                {
                    if(board[u][current] == symbol && u != i)
                    {
                        board[u][current] = ' ';
                    }
                }

                //If this is the last column
                if(current == j + lenght - 1)
                {
                    //We've failed!
                    success = false;
                }
                //Stop trying in this column
                break;
            }
        }
    }
    TERMINATE6:
    return success;
}

void rotate_down(char board[11][11], char symbol, int lenght, int i, int j)
{
    int current;
    for(current = j; current < j + lenght; current++)
    {
        for(int k = 1; k < lenght; k++)
        {
            if(board[i+k][current] == ' ')
            {
                board[i+k][current] = symbol;

                if(k == lenght - 1)
                {
                    for(int u = 0; u < 11; u++)
                    {
                        if(board[i][u] == symbol && u != current)
                        {
                            board[i][u] = ' ';
                        }
                    }
                    goto TERMINATE7;
                }
            }
            else
            {
                for(int u = 0; u < 11; u++)
                {
                    if(board[u][current] == symbol && u != i)
                    {
                        board[u][current] = ' ';
                    }
                }
                break;
            }
        }
    }
    TERMINATE7: current = j+lenght+1;
}

bool rotate_right(char board[11][11], char symbol, int lenght, int i, int j)
{
    bool success;

    for(int current = i; current < i + lenght; current++)
    {
        for(int k = 1; k < lenght; k++)
        {
            if (board[current][j+k] == ' ')
            {
                board[current][j+k] = symbol;
                if(k == lenght - 1)
                {
                    success = true;
                    for(int u = 0; u < 11; u++)
                    {
                        if(board[u][j] == symbol && u != current)
                        {
                            board[u][j] = ' ';
                        }
                    }
                    goto TERMINATE8;
                }
            }
            else
            {
                for(int u = 0; u < 11; u++)
                {
                    if(board[current][u] == symbol && u != j)
                    {
                        board[current][u] = ' ';
                    }
                }

                if(current == i + lenght - 1)
                {
                    success = false;
                }
                break;
            }
        }
    }
    TERMINATE8:
    return success;
}


void rotate_left(char board[11][11], char symbol, int lenght, int i, int j)
{
    int current;

    for(current = i; current < i + lenght; current++)
    {
        for(int k = 1; k < lenght; k++)
        {
            if (board[current][j-k] == ' ')
            {
                board[current][j-k] = symbol;
                if(k == lenght - 1)
                {
                    for(int u = 0; u < 11; u++)
                    {
                        if(board[u][j] == symbol && u != current)
                        {
                            board[u][j] = ' ';
                        }
                    }
                    goto TERMINATE9;
                }
            }
            else
            {
                for(int u = 0; u < 11; u++)
                {
                    if(board[current][u] == symbol && u != j)
                    {
                        board[current][u] = ' ';
                    }
                }
                break;
            }
        }
    }
    TERMINATE9:
    current = i + lenght + 1;
}


bool in_board(char board[11][11], char symbol)
{
    //Search the board
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {

            //If there is at least one symbol
            if(board[i][j] == symbol)
            {
                //true
                return true;
            }
        }
    }
    //Otherwise, false
    return false;
}

bool dunked_on(char board[11][11])
{
    //Search the board (but leave the very first row and column
    //because is filled with letters and numbers)
    for(int i = 1; i < 11; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            //If there is an element that is not empty and its not an 'X'
            if(board[i][j] != 'X' && board[i][j] != ' ')
            {
                //The game isn't over yet
                return false;
            }
        }
    }
    //Otherwise, the game is over
    return true;
}
