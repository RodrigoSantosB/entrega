#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 2

#define CAIU 8  // variavel atribuida para verififcar se o person caiu
#define PLATAFORMA 1
#define POS_PERSON 5 // identifica o personagem na matriz


const short int mapa[LARGURA_MAPA][ALTURA_MAPA] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,},
    {0, 0, 0, 10, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
    {0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0},
    {0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 8},
    {0, 0, 0, 0, 0, 7, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };



int main() 
{
  //inicializa o server 
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  
  serverInit(MAX_JOGADORES);
  printf("Servidor está a mil...!\n");
  int sair = 0;

  ServerPack pacoteServidor;
  ClientPack pacoteCliente;
  int comecou = 0;

  //seta os jogadores em uma posição no mapa 
  for (int i = 0; i < MAX_JOGADORES; i++){
      pacoteServidor.jogadores[i].staminaPerso = 0;
      pacoteServidor.jogadores[i].staminaPerso = 0;

      switch(i){
          case 0:
              (pacoteServidor.jogadores[i]).x = 10;
              (pacoteServidor.jogadores[i]).y = 10;
              break;
          case 1:
              (pacoteServidor.jogadores[i]).x = 7;
              (pacoteServidor.jogadores[i]).y = 7;
              break;
        }
      (pacoteServidor.jogadores[i]).tile = 0;
      (pacoteServidor.jogadores[i]).character = i;
  }

 
  while (1) 
  {
    startTimer();

    //realiza conexao com o cliente
    int id = acceptConnection();
    if (id != NO_CONNECTION) {
      recvMsgFromClient(client_names[id], id, WAIT_FOR_IT);
      printf("%s connected id = %d\n", client_names[id], id);
      sendMsgToClient(&id, sizeof(int), id);
      pacoteServidor.jogadores[id].staminaPerso = 1000;
      printf("ID: %d conctou-se\n", id);
    }
    //Recebe a mensagem
    struct msg_ret_t msg_ret = recvMsg(&pacoteCliente);
    if (msg_ret.status == MESSAGE_OK) {
      if(!comecou){
        if (pacoteCliente.comecou == 1) {
                    pacoteServidor.jogadores[0].tile = 0;
                    comecou = 1;
                    broadcast(&pacoteServidor, sizeof(ServerPack));
                }
     }else{
       id = msg_ret.client_id;
        //insere a posicao dos jogadores numa matriz
        int atualizaJogadores[LARGURA_MAPA][ALTURA_MAPA] = {0};
        for (int i = 0; i < MAX_JOGADORES; i++)
          if (pacoteServidor.jogadores[i].staminaPerso > 0)
              atualizaJogadores[pacoteServidor.jogadores[i].x][pacoteServidor.jogadores[i].y] = POS_PERSON;

              switch(pacoteCliente.tecla){

                    case 1: //cima
                        if (pacoteServidor.jogadores[id].y > 0 && mapa[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y-1] < CAIU && atualizaJogadores[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y-1] == POS_PERSON){
                            pacoteServidor.jogadores[id].y--;
                            pacoteServidor.jogadores[id].tile = CIMA;
                        }
                        break;
                    case 2: //baixo
                        if (pacoteServidor.jogadores[id].y < ALTURA_MAPA - 1 && mapa[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y+1] < CAIU && atualizaJogadores[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y+1] == POS_PERSON){
                            pacoteServidor.jogadores[id].y++;
                            pacoteServidor.jogadores[id].tile = BAIXO;
                        }
                        break;
                    case 3: //esquerda
                        if (pacoteServidor.jogadores[id].x > POS_PERSON && mapa[pacoteServidor.jogadores[id].x-1][pacoteServidor.jogadores[id].y] < CAIU && atualizaJogadores[pacoteServidor.jogadores[id].x-1][pacoteServidor.jogadores[id].y] == POS_PERSON){
                            pacoteServidor.jogadores[id].x--;
                            pacoteServidor.jogadores[id].tile = ESQ;
                        }
                        break;
                    case 4: //direita
                        if (pacoteServidor.jogadores[id].x < LARGURA_MAPA && mapa[pacoteServidor.jogadores[id].x+1][pacoteServidor.jogadores[id].y] < CAIU && atualizaJogadores[pacoteServidor.jogadores[id].x+1][pacoteServidor.jogadores[id].y] == POS_PERSON){
                            pacoteServidor.jogadores[id].x++;
                            pacoteServidor.jogadores[id].tile = DIR;
                        }
                        break;
                    case 5: //espaço - bate
                        pacoteServidor.bate.tile = pacoteServidor.jogadores[id].tile;
                        pacoteServidor.bate.x = pacoteServidor.jogadores[id].x;
                        pacoteServidor.bate.y = pacoteServidor.jogadores[id].y;

                        FPSLimit();
                        startTimer();
                        pacoteServidor.bate.tile = -1;
                    case 6: // Sair
                        break;
              }
        }
    }
    
      broadcast(&pacoteServidor, sizeof(ServerPack));

      //compensa o tempo que falta para o fim do tempo do frame
      FPSLimit();
  }
      //finaliza os modulos do allegro
      allegroEnd();
}
 
    
