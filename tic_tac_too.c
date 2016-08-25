
#include "tic_tac_too.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ROWS 3
#define COLUMNS 3
#define INPUT_MAX (81)
#define BOARDE '#'
#define EMPTY ' '
#define isempty(X) ((X) == EMPTY ? YES : NO)
#define PLAY_MOVE(M,T) board[(M).x][M.y] = T;
#define MOVES_MAX ROWS*COLUMNS

typedef enum {NO,YES}bool;
typedef enum {X = 'X',O = 'O'}turn;

typedef struct {
    int x;
    int y;
}Move;

/*print the board*/
static void print_board();
/*
 * get the move from the user
 * return the move.
 */
static Move get_move();
/*
 * checks if the last player won.
 * t - the last player.
 * move - the last place he went.
*/
static int won(turn t, Move move);
/*
 * all of this functions helps won to
 * check if the last player won or not.
 * t   - the last player.
 * loc - the last place that t went.
 */
static int up(turn t, Move loc);
static int down(turn t, Move loc);
static int left(turn t, Move loc);
static int right(turn t, Move loc);
static int up_left(turn t, Move loc);
static int down_right(turn t, Move loc);
static int up_right(turn t, Move loc);
static int down_left(turn t, Move loc);
/*clear the board*/
static int clear_board();

int display_instructions();

/*the board*/
char board[ROWS+2][COLUMNS+2] = {{BOARDE, BOARDE, BOARDE, BOARDE, BOARDE},
                                 {BOARDE, EMPTY, EMPTY, EMPTY, BOARDE},
                                 {BOARDE, EMPTY, EMPTY, EMPTY, BOARDE},
                                 {BOARDE, EMPTY, EMPTY, EMPTY, BOARDE},
                                 {BOARDE, BOARDE, BOARDE, BOARDE, BOARDE}
};

/*run the game.*/
int run_tic_tac_to() {
    int moves = 0;
    bool play = YES;
    turn t = X;
    bool game_over = NO;
    Move move;
    char again_in[INPUT_MAX];
    display_instructions();
    while (play == YES) {/*loop to run the game until the end*/
        /*loop to run a current game until the end*/
        for (moves = 0; !game_over && moves < MOVES_MAX; ++moves) {
            print_board();
            fprintf(stdout, "This is %c turn to move\n", t);
            move = get_move();/*get the player move.*/
            PLAY_MOVE(move,t);
            if (won(t, move)) {/*chick if the player won.*/
                print_board();
                fprintf(stdout, "%c won.\n", t);
                game_over = YES;
            }
            else if(moves == MOVES_MAX-1){/*case a tie.*/
                print_board();
                fprintf(stdout,"It's a tie!.\n");
            }
            t = (t == X ? O : X);
        }
        fprintf(stdout, "game over!\n");
        fprintf(stdout, "Do you want to play again?\nenter y for yes and anything else for no.\n");
        while (!(strtok(fgets(again_in,INPUT_MAX,stdin),", \t\n")));/*get the input until not an empty line */
        *again_in = tolower(*again_in);
        if (strcmp(again_in,"y") == 0) {
            play = YES;/*set all to default.*/
            game_over = NO;
            clear_board();
        }
        else play = NO;
    }
    return 0;
}

int display_instructions() {
    fputs("you enter the coordinates that you want in this format\n"
                  "(row) (comma of space) (column)\n"
                  "for example: if you want to go at the low left corner\n"
                  "you will enter 3, 1.\n",stdout);
    fputs("To start the game press enter.\n",stdout);
    while (getchar() != '\n');
    return 0;
}

/*clear the board.*/
static int clear_board() {
    int i,j;
    for (i = 1; i <= ROWS ; ++i) {
        for (j = 1; j <=COLUMNS; ++j) {
            board[i][j] = EMPTY;
        }
    }
    return 0;
}

/*get the move from the user.*/
static Move get_move() {
    Move move;
    char * del = " ,\t\n";
    char input[INPUT_MAX] = {0},* crdn;
    bool legal_input = NO;
    char *end;
    while (!legal_input){
        fputs("Enter your move: \n",stdout);
        /*check not empty line and get the first coordinate*/
        while (!(crdn = strtok(fgets(input,INPUT_MAX,stdin),del)));
        move.x = strtol(crdn,&end,10);/*convert the first coordinate*/
        if (*end){
            fprintf(stderr,"Not legal input.\n");
            continue;
        }/*get the second coordinate*/
        if(!(crdn = strtok(NULL,del))){
            fprintf(stderr,"Not enough coordinates enter your move again.\n");
            continue;
        }/*convert the second coordinate*/
        move.y = strtol(crdn,&end,10);
        if (*end){
            fprintf(stderr,"Not legal input.\n");
            continue;
        }/*chick the coordinates are legal*/
        if (move.x < 1 || move.x > ROWS || move.y < 1 || move.y > COLUMNS){
            fprintf(stderr,"Location is out of bounds.\n");
            continue;
        }
        if (!isempty(board[move.x][move.y])){
            fprintf(stderr,"location already been taken.\n");
            continue;
        }
        legal_input = YES;
    }
    return move;
}
/*print the board on the screen.*/
static void print_board() {
    int i,j;
    system("clear");
    for (i = 0; i < ROWS+2; ++i) {
        for (j = 0; j < COLUMNS+2; ++j) {
            printf("%c ",board[i][j]);
        }
        putchar('\n');
    }
}

#define WIN 3
/*chicks if the last player won.*/
static int won(turn t, Move loc) {
    if(up(t,loc)+down(t,loc)+1 == WIN || left(t,loc) + right(t,loc)+1 == WIN ||
       up_left(t,loc)+down_right(t,loc)+1 == WIN || up_right(t,loc)+down_left(t,loc)+1 == WIN)
        return YES;
    return NO;
}

static int up(turn t, Move loc){
    int i;
    for(i = 0,loc.x--;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,--loc.x);
    return i;
}

static int down(turn t, Move loc){
    int i;
    for(i = 0,loc.x++;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,++loc.x);
    return i;
}

static int left(turn t, Move loc){
    int i;
    for(i = 0,loc.y--;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,--loc.y);
    return i;
}

static int right(turn t, Move loc){
    int i;
    for(i = 0,loc.y++;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,++loc.y);
    return i;
}

static int up_left(turn t, Move loc){
    int i;
    for(i = 0,loc.x--,loc.y--;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,--loc.x,--loc.y);
    return i;
}

static int down_right(turn t, Move loc){
    int i;
    for(i = 0,loc.x++,loc.y++;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,++loc.x,++loc.y);
    return i;
}
static int up_right(turn t, Move loc){
    int i;
    for(i = 0,loc.x--,loc.y++;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,--loc.x,++loc.y);
    return i;
}
static int down_left(turn t, Move loc){
    int i;
    for(i = 0,loc.x++,loc.y--;board[loc.x][loc.y] != BOARDE && board[loc.x][loc.y] == t;++i,++loc.x,--loc.y);
    return i;
}
