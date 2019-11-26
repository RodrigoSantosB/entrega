#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 3

#define CAIU 8
#define PLATAFORMA 1
#define POS_PERSON 5

const short int mapa[ALTURA_MAPA][LARGURA_MAPA] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 10, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
    {0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0},
    {0, 0, 7, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 8},
    {0, 0, 0, 0, 0, 7, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {8, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

};



int main() 
{
  //inicializa o server 
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  
  serverInit(MAX_JOGADORES);
  printf("Server is running!\n");
  int sair = 0;

  ServerPack pacoteServidor;
  ClientPack pacoteCliente;
  int comecou = 0;

  //seta os jogadores em uma posição no mapa 
  for (int i = 0; i < MAX_JOGADORES; i++){
      pacoteServidor.jogadores[i].hp = 0;
      pacoteServidor.jogadores[i].hp = 0;

      switch(i){
          case 0:
              pacoteServidor.jogadores[i].x = 10;
              pacoteServidor.jogadores[i].y = 10;
              break;
          case 1:
              pacoteServidor.jogadores[i].x = 7;
              pacoteServidor.jogadores[i].y = 7;
              break;
              pacoteServidor.jogadores[i].tile = 0;
              pacoteServidor.jogadores[i].character = i;
        }
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
      pacoteServidor.jogadores[id].hp = 100;
      printf("%d conctou-se\n", id);
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
          if (pacoteServidor.jogadores[i].hp > 0)
              atualizaJogadores[pacoteServidor.jogadores[i].x][pacoteServidor.jogadores[i].y] = i + 1;
              

    }
  }
}
}
