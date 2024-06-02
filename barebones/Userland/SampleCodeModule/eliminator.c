/*#include <stdlib.h>
#include <stdio2.h>
#include <strings2.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PLAYER_RADIUS 2


int board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

char playercant;

typedef struct {
    int x;
    int y;
    int direction;
    int speed;
} PlayerPoint;

typedef struct {
    PlayerPoint player1;
    PlayerPoint player2;
} Game;


void initGame(Game *game){
    // Draw top and bottom border
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        board[i][0] = 1;
        board[i][SCREEN_HEIGHT - 1] = 1;
        putPixel();
    }

    // Draw left and right border
    for (int j = 0; j < SCREEN_HEIGHT; j++) {
        board[0][j] = 1;
        board[SCREEN_WIDTH - 1][j] = 1;
        putPixel();
    }

    game->player1.x = SCREEN_WIDTH / 2;
    game->player1.y = SCREEN_HEIGHT / 2;
    game->player1.direction = LEFT;
    game->player1.speed = 1;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            board[game->player1.x + i][game->player1.y + j] = 1;
        }
    }
    drawPlayer(&game->player1);

    if(playercant == '2'){

        game->player2.x = SCREEN_WIDTH / 2 + 100;
        game->player2.y = SCREEN_HEIGHT / 2 + 100;
        game->player2.direction = RIGHT;
        game->player2.speed = 1;
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                board[game->player2.x + i][game->player2.y + j] = 1;
            }
        }
        drawPlayer(&game->player2);
        
    }
}

void welcomeMessage(){
    printF("Press 1 for singleplayer Press 2 for multiplayer \n");
    while ((playercant = getLastPressedSC()) != '1' && playercant != '2')
        ;
    cleanScreen();
}

void gameOver(){
    cleanScreen();
    printF("Press ESC to go back \n");
    while (getLastPressedSC() != 27); // 27 corresponde a ESC
    cleanScreen();
}

int checkCollision(PlayerPoint *player){
    if(player->x + 2 <= SCREEN_WIDTH || player->y + 2 <= SCREEN_HEIGHT || player->x - 2 >= 0 || player->y - 2 >= 0){
        for (int i = -2; i <= 2; i++) {
            for (int j = -2; j <= 2; j++) {
                if(board[player->x + i][player->y + j] != 0){
                    return 0;
                }
            }
        }
        return 1;
    }
    return 0;
}


void drawPlayer(PlayerPoint *player){
   drawCircle(0x00FF00, player->x, player->y, PLAYER_RADIUS, PLAYER_RADIUS);
}

void drawInBetween(int axis1, int axis2){
    drawRectangle(0x00FF00, axis1, axis2, 1, 1);
}

void updatePosition(PlayerPoint *player){
    if (getLastPressedSC() == 'w' || getLastPressedSC() == 'W') //getLastPressedSC() es una función que devuelve la última tecla presionada
        if (player->direction != DOWN)
            player->direction = UP;
    if (getLastPressedSC() == 's' || getLastPressedSC() == 'S')
        if (player->direction != UP)
            player->direction = DOWN;
    if (getLastPressedSC() == 'a' || getLastPressedSC() == 'A')
        if (player->direction != RIGHT)
            player->direction = LEFT;
    if (getLastPressedSC() == 'd' || getLastPressedSC() == 'D')
        if (player->direction != LEFT)
            player->direction = RIGHT;
}


void updatePosition2(PlayerPoint *player){
   if (getLastPressedSC() == 'i' || getLastPressedSC() =='I') 
        if (player->direction != DOWN)
            player->direction = UP;
    if (getLastPressedSC() == 'k' || getLastPressedSC() == 'K')
        if (player->direction != UP)
            player->direction = DOWN;
    if (getLastPressedSC() == 'j' || getLastPressedSC() =='J')
        if (player->direction != RIGHT)
            player->direction = LEFT;
    if (getLastPressedSC() == 'l' || getLastPressedSC() == 'L')
        if (player->direction != LEFT)
            player->direction = RIGHT;
}

void movePlayer(PlayerPoint *player){
    switch (player->direction){
    case UP:
        player->y++;
        drawInBetween(player->x, player->y);
        break;
    case DOWN:
        player->y--;
        drawInBetween(player->x, player->y);
        break;
    case LEFT:
        player->x--;
        drawInBetween(player->x, player->y);
        break;
    case RIGHT:
        player->x++;
        drawInBetween(player->x, player->y);
        break;
    default:
        break;
    }
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            board[player->x + i][player->y + j] = 1;
        }
    }
}

void eliminator(){

    welcomeMessage();

    PlayerPoint player1;
    PlayerPoint player2;
    Game game;

    game.player1 = player1;
    game.player2 = player2;

    initGame(&game);
    
    int validP1 = 0, validP2 = 0;
    while (validP1 == 0 || validP2 == 0){

        updatePosition(&game.player1);
        movePlayer(&game.player1);
        drawPlayer(&game.player1);
        validP1 = checkCollision(&game.player1);

        if(playercant == '2'){
            updatePosition2(&game.player2);
            movePlayer(&game.player2);
            drawPlayer(&game.player2);
            validP2 = checkCollision(&game.player2);
        }
        if (getLastPressedSC() == 27)
            break;
    }
    gameOver();
}
*/