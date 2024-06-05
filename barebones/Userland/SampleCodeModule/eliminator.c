#include <stdio2.h>
#include <strings2.h>
#include <stdint.h>

// matrix is 128x96, which is 1024/8 x 768/8, therefore 8 is square size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 96

// define player 1 keys
#define     W       0x11
#define     A       0x1E
#define     S       0x1F
#define     D       0x20

// define player 2 keys
#define     I       0x17
#define     J       0x24
#define     K       0x25
#define     L       0x26

#define    LEFT    0
#define    RIGHT   1
#define    UP      2
#define    DOWN    3

#define PIXELSIZE       8

int board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

int playersQuant;
int alive = 1;
int speed;
int score = 0;
int winner;

typedef struct {
    int x;
    int y;
    int direction;
    uint32_t color;
} PlayerPoint;

PlayerPoint game[2];

void initGame() {
    clearMatrix();   // initiate matrix in 0s

    // Draw top and bottom border
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        board[i][0] = 1;
        board[i][SCREEN_HEIGHT - 1] = 1;
        drawrectangleAt(0xFF0000,i * PIXELSIZE , 0, PIXELSIZE, PIXELSIZE);
        drawrectangleAt(0xFF0000,i * PIXELSIZE , (SCREEN_HEIGHT - 1) * PIXELSIZE, PIXELSIZE, PIXELSIZE);
    }

    // Draw left and right border
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        board[0][j] = 1;
        board[SCREEN_WIDTH - 1][j] = 1;
        drawrectangleAt(0xFF0000, 0, j * PIXELSIZE, PIXELSIZE , PIXELSIZE);
        drawrectangleAt(0xFF0000, (SCREEN_WIDTH - 1) * PIXELSIZE, j * PIXELSIZE, PIXELSIZE, PIXELSIZE);
    }
    createPlayers();

    char read[1];

    alive = 1;
    while(alive == 1) {
        sleep(100 - (speed * 10));
        changePosition();
        checkCollision();
        drawPlayers();
        score += speed;
        uint32_t c = getScanCodeF();
        checkDirection(c);
    }
    gameOver();
}

void checkDirection(uint32_t direction) {
    if (direction == W || direction == A || direction == S || direction == D) {
        if( !( (game[0].direction == UP && direction == S ) 
        || (game[0].direction == DOWN && direction == W)
        || (game[0].direction == RIGHT && direction == A)
        || (game[0].direction == LEFT && direction == D)  )){
            changeDirection(&game[0], direction);
        }
    }
    if (playersQuant == 2 && (direction == I || direction == J || direction == K || direction == L) ) {
        if( !( (game[1].direction == UP && direction == K ) 
        || (game[1].direction == DOWN && direction == I)
        || (game[1].direction == RIGHT && direction == J)
        || (game[1].direction == LEFT && direction == L)  )){
            changeDirection(&game[1], direction);
        }
    }
}

int scToDir2(uint32_t dir) {
    if(dir == A || dir == J){
        return LEFT;
    }
    if(dir == D || dir == L){
        return RIGHT;
    }
    if(dir == S || dir == K){
        return DOWN;
    }
    if(dir == W || dir == I){
        return UP;
    }
}

void changeDirection(PlayerPoint * player, char direction) {
    player->direction = scToDir2(direction);
}

void changePosition() {
    switch (game[0].direction) {
        case LEFT:
            game[0].x--;
            break;
        case RIGHT:
            game[0].x++;
            break;
        case UP:
            game[0].y--;
            break;
        case DOWN:
            game[0].y++;
            break;    
        default:
            break;
        }
    if(playersQuant == 2){
        switch (game[1].direction) {
            case LEFT:
                game[1].x--;
                break;
            case RIGHT:
                game[1].x++;
                break;
            case UP:
                game[1].y--;
                break;
            case DOWN:
                game[1].y++;
                break;    
            default:
                break;
            }
        }
}

void drawPlayers() {
    paintPlayer(game[0]);
    if(playersQuant == 2){
        paintPlayer(game[1]);
    }
}

void checkCollision() {
        if(board[game[0].x][game[0].y] == 1){
            alive = 0;
            winner = 2;
            return;
        }
        else if( playersQuant == 2 && board[game[1].x][game[1].y] == 1 ){
            alive = 0;
            winner = 1;
            return;
        }
        board[game[0].x][game[0].y] = 1;
        if(playersQuant == 2){
            board[game[1].x][game[1].y] = 1;
        }
    }

    void paintPlayer(PlayerPoint player){
        drawrectangleAt(player.color,player.x * PIXELSIZE, player.y * PIXELSIZE, PIXELSIZE, PIXELSIZE);
    }


void welcomeMessage() {
    cleanScreen();
    biggerText();
    biggerText();
    putstringcoloratF("ELIMINATOR", 0x00FF00, 380, 300);
    putstringatF("Press space to start.", 250, 350);
    char read[2];
    read[1] = '\0';             //TODO: ARREGLAR
    read[0] = getcharF();
    while (read[0] != ' ');
    smallerText();
    printF("Press 1 for singleplayer, press 2 for multiplayer\n");
    read[0] = getcharF();
    putcharF(read[0]);putcharF('\n');
    if (read[0] != '1' && read[0] != '2') {
        putstringcolorF("Wrong parameter. Exiting game. Reenter to play again.\n", 0xFF0000);
        sleep(2000);
        return;
    }
    playersQuant = atoi(read);
    printF("Choose player(s) speed: 1 < 2 < 3 < 4 < 5\n");
    read[0] = getcharF();
    putcharF(read[0]);putcharF('\n');
    if (read[0] != '1' && read[0] != '2' && read[0] != '3' && read[0] != '4' && read[0] != '5') {
        putstringcolorF("Wrong parameter. Exiting game. Reenter to play again.\n", 0xFF0000);
        sleep(2000);
        return;
    }
    speed = atoi(read);
    cleanScreen();
    initGame();
}

void createPlayers() {
    PlayerPoint player;
    player.x = SCREEN_WIDTH/2;
    player.y = SCREEN_HEIGHT/2 + 25;
    player.color = 0x04D9FF;
    player.direction = UP;
    game[0] = player;
    paintPlayer(player);
    board[player.x][player.y] = 1;

    if(playersQuant == 2){
        PlayerPoint player2;
        player2.x = SCREEN_WIDTH/2;
        player2.y = SCREEN_HEIGHT/2 - 25;
        player2.color = 0x39FF14;
        player2.direction = DOWN;
        game[1] = player2;
        paintPlayer(player2);
        board[player2.x][player2.y] = 1;  
    }
}

void gameOver() {
    beepF(700, 100);
    biggerText();
    biggerText();
    putstringcoloratF("GAME OVER", 0xFF0000, 380, 300);
    sleep(3000);
    cleanScreen();
    if (playersQuant == 1) {
        putstringcoloratF("Score = ", 0xE5DE00, 350, 300);putstringcoloratF(itoa(score, 10), 0xE5DE00, 550, 300);
        sleep(3000);
    }
    if(playersQuant == 2) {
        putstringcoloratF("Player", 0xE5DE00, 300, 300);putstringcoloratF(itoa(winner, 10), 0xE5DE00, 480, 300);putstringcoloratF("wins.", 0xE5DE00, 550, 300);
        sleep(3000);
    }
    smallerText(); 
    putstringatF("Press SPACEBAR to go back \n", 270, 300);
    char read[1];
    while((read[0] = getcharF()) != ' ');
    smallerText();
    return;
}

void exitGame() {
    return;
}

void clearMatrix(){
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for(int j = 0 ; j < SCREEN_HEIGHT; j++){
            board[i][j] = 0;
        }
    }
}

void eliminator() {
    welcomeMessage();
    cleanScreen();
    return;
}

