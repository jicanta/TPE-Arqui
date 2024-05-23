#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define PLAYER_RADIUS 4


int board[SCREEN_WIDTH][SCREEN_HEIGHT] = {0};

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
    game->player1.x = SCREEN_WIDTH / 2;
    game->player1.y = SCREEN_HEIGHT / 2;
    game->player1.direction = LEFT;
    game->player1.speed = 1;
    board[game->player1.x][game->player1.y] = 1;

    game->player2.x = SCREEN_WIDTH / 2 + 100;
    game->player2.y = SCREEN_HEIGHT / 2 + 100;
    game->player2.direction = RIGHT;
    game->player2.speed = 1;
    board[game->player2.x][game->player2.y] = 2;
}

void welcomeMessage(){
    printFormat("Press any key to start \n");
    while (getchar());
}

void gameOver(){
    printFormat("Press ESC to go back \n");
    while (getChar() != 27); // 27 corresponde a ESC
}

int checkCollision(PlayerPoint *player){
    if( board[player.x][player.y] != 0 || player.x >= SCREEN_WIDTH || player.y >= SCREEN_HEIGHT){
        return 1;
    }
    return 0;
}

void drawPlayer(PlayerPoint *player){
    //Llamar función de driver de video para dibujar el punto y la linea en la pantalla por donde pasa el jugador
}

void updatePosition(PlayerPoint *player){
    //Llamar a función de driver de teclado para detectar teclas presionadas
}

