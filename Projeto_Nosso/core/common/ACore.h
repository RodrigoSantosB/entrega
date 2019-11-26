#ifndef GAME_H
#define GAME_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FPS 60
#define WIDTH  640
#define HEIGHT 480
#define IP_MAX_SIZE 100

#define LARGURA_MAPA 18
#define ALTURA_MAPA 10

#define MAX_JOGADORES 2

#define TILE 32
#define CIMA 1
#define BAIXO 2
#define DIR 3
#define ESQ 4
#define BATE 5
#define IMPULSO 6
#define SAIR 0

double startingTime;

ALLEGRO_DISPLAY *main_window;
ALLEGRO_EVENT_QUEUE *eventsQueue;

//========================
//FONT AND BITMAP POINTERS
//ALLEGRO_FONT *ubuntu;
ALLEGRO_FONT *start;
ALLEGRO_BITMAP *objects;
ALLEGRO_BITMAP *menuScreen;
//========================
//========================

//STRUCTs

typedef struct {
    int staminaPerso;
    int x;
    int y;
} Jogador;

typedef struct {
    int x;
    int y;
    int bateu;
} Bate;

typedef struct {
    int pula;
    int caiu;
    int xw; //defesa
    int yh;
} Posicao;

typedef struct {
    char mensagem[100];
    int valor;
    Jogador jogadores[MAX_JOGADORES];
    Bate bate;
    Posicao posicao;
}ServerPack;

typedef struct {
    int tecla;
    int comecou;
}ClientPack;

//MAIN ALLEGRO FUNCTIONS
bool coreInit();
bool windowInit(int W, int H, char title[]);
bool inputInit();
void allegroEnd();

//FPS CONTROL FUNCTIONS
void startTimer();
double getTimer();
void FPSLimit();

//RESOURCE LOADING FUNCTIONS
bool loadGraphics();
bool fontInit();

//INPUT READING FUNCTION
void readInput(ALLEGRO_EVENT event, char str[], int limit);


#endif
