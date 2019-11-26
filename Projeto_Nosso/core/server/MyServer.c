#include "ACore.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Game.h"

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define MAX_CHAT_CLIENTS 2

#define CAIU 8  // variavel atribuida para verififcar se o person caiu
#define PLATAFORMA 1
#define POS_PERSON 5 // identifica o personagem na matriz       


const short int Mapa[LARGURA_MAPA][ALTURA_MAPA] = {
                    {0, 0, 7, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0},
                    {0, 10, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 10, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 7, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 8},
                    {0, 10, 0, 0, 10, 0, 7, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 8},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0},
                    {8, 1, 1, 1, 1, 1, 1, 1, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int cont = 0;

int main() 
{
  //inicializa o server 
  char client_names[MAX_CHAT_CLIENTS][LOGIN_MAX_SIZE];
  char str_buffer[BUFFER_SIZE], aux_buffer[BUFFER_SIZE];
  
  serverInit(MAX_JOGADORES);
  printf(" Servidor está a oline...!\n");
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
                    pacoteServidor.jogadores[0].x = 0;
                    comecou = 1;
                    broadcast(&pacoteServidor, sizeof(ServerPack));
                }
     }else{
       id = msg_ret.client_id;
        //insere a posicao dos jogadores numa matriz
        int atualizaJogadores[LARGURA_MAPA][ALTURA_MAPA] = {0};          
        for (i = 0; i < MAX_JOGADORES; i++){
             switch (pacoteCliente.tecla) {
                    case 1: //cima
                        if (pacoteServidor.jogadores[id].y > 0 && Mapa[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y-1] < POS_PERSON && atualizaJogadores[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y-1] == 0){
                            pacoteServidor.jogadores[id].x--;
                                                   }
                        break;
                    case 2: //baixo
                        if (pacoteServidor.jogadores[id].y < ALTURA_MAPA - 1 && Mapa[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y+1] < POS_PERSON && atualizaJogadores[pacoteServidor.jogadores[id].x][pacoteServidor.jogadores[id].y+1] == 0){
                            pacoteServidor.jogadores[id].y++;
                                                    }
                        break;
                    case 3: //esquerda
                        if (pacoteServidor.jogadores[id].x > 0 && Mapa[pacoteServidor.jogadores[id].x-1][pacoteServidor.jogadores[id].y] < POS_PERSON && atualizaJogadores[pacoteServidor.jogadores[id].x-1][pacoteServidor.jogadores[id].y] == 0){
                            pacoteServidor.jogadores[id].x--;
                                                  }
                        break;
                    case 4: //direita
                        if (pacoteServidor.jogadores[id].x < LARGURA_MAPA && Mapa[pacoteServidor.jogadores[id].x+1][pacoteServidor.jogadores[id].y] < POS_PERSON && atualizaJogadores[pacoteServidor.jogadores[id].x+1][pacoteServidor.jogadores[id].y] == 0){
                            pacoteServidor.jogadores[id].x++;
                                                  }
                        break;
                    case 5: //espaço - bate
                   

                            broadcast(&pacoteServidor, sizeof(ServerPack));
                            FPSLimit();
                        }
                        startTimer();

                        pacoteServidor.bate.bateu = -1;
                }
                if(1){
                    if((posyPerso>=365 && (posxPerso<20 || posxPerso>=830)) || (posxPerso>=830) || (posyPerso>365 && posxPerso<420)|| (posyPerso>265 && posxPerso>=450)){ // CAI // SERVIDOR
                        posyPerso = cair (tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso, lado);
                        pacoteServidor.jogadores[i].y = posyPerso;
                    } 
                    if(posxPerso>385 && posxPerso<430 && posyPerso == 365){ // PORTAL DEBAIXO // SERVIDOR
                        posxPerso = 465;
                        posyPerso = 265;
                        pacoteServidor.jogadores[i].y = posyPerso;
                        pacoteServidor.jogadores[i].x = posxPerso;
                        
                    }
                    if(posxPerso>=420 && posxPerso<460 && posyPerso == 265){ // PORTAL DE CIMA // SERVIDOR
                        posxPerso = 380;
                        posyPerso = 365;
                        pacoteServidor.jogadores[i].y = posyPerso;
                        pacoteServidor.jogadores[i].x = posxPerso;

                    }
                    if(posyPerso>600){ // RESSURGIR // SERVIDOR
                        if(contador%2==0){
                            posyPerso = 265;
                            posxPerso = resurgir(contador);
                            pacoteServidor.jogadores[i].y = posyPerso;
                            pacoteServidor.jogadores[i].x = posxPerso;
                        }else{
                            posyPerso = 365;
                            posxPerso = resurgir(contador);
                            pacoteServidor.jogadores[i].y = posyPerso;
                            pacoteServidor.jogadores[i].x = posxPerso;
                        }
                    }
                    
                    printf("%d %d\n", posxPerso, posyPerso);
                    if(noAr == 1 && cont==3){ //CAI DO PULO
                        posyPerso = pulaDesce(tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso);
                        teclaPulo = 0;
                        noAr = 0;
                        cont = 0;
                        pacoteServidor.jogadores[i].y = posyPerso;

                    }else if(teclaPulo == 1 && noAr == 0){ // PULA 
                        posyPerso = pulaSobe(tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso);
                        teclaPulo = 1;
                        cont ++;
                        pacoteServidor.jogadores[i].y = posyPerso;
                        if(cont<3){
                            noAr = 0;
                        }else{
                            noAr = 1;
                        }
                    }if(tecla == 2){ // DEFENDE // SERVIDOR
                        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                        al_draw_bitmap(plata, 455, 300, 0);
                        al_draw_bitmap(plata, 50, 400, 0);
                        if(inverte==0){
                        regiaoxPerso = 1*larguraPerso;
                        regiaoyPerso = 0*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem,regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
                        }else{
                        regiaoxPerso = 1*larguraPerso;
                        regiaoyPerso = 0*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
                        }
                        al_flip_display();
                        
                        tecla = 0;
                    }else if(tecla == 3){ // ESQUERDA
                        regiaoxPerso = 1*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso; // Server recebe info
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                        al_draw_bitmap(plata, 455, 300, 0);
                        al_draw_bitmap(plata, 50, 400, 0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
                        al_flip_display();
                        
                        tecla = 0;
                        inverte = 1;
                    }else if(tecla == 4){// DIREITA
                        regiaoxPerso = 1*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                        al_draw_bitmap(plata, 455, 300, 0);
                        al_draw_bitmap(plata, 50, 400, 0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
                        al_flip_display();
                        
                        tecla = 0;
                        inverte = 0;
                    }else if(tecla == 5){ // BATE // SERVIDOR
                        regiaoxPerso = 2*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                        al_draw_bitmap(plata, 455, 300, 0);
                        al_draw_bitmap(plata, 50, 400, 0);
                        if(inverte==0){
                        regiaoxPerso = 2*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
                        }else{
                        regiaoxPerso = 2*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
                        }
                        al_flip_display();
                        
                        tecla = 0;
                    }else if(tecla == 6 && staminaPerso>=200){ // DASH
                        posxPerso = dash(tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso,lado);
                        staminaPerso -= 200;
                        tecla = 0;
                        pacoteServidor.jogadores[i].x = posxPerso;
                    }else if(noAr==0) { // FICA PARADO
                        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                        al_draw_bitmap(plata, 455, 300, 0);
                        al_draw_bitmap(plata, 50, 400, 0);
                        if(inverte==0){
                        regiaoxPerso = 0*larguraPerso;
                        regiaoyPerso = 0*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso, alturaPerso, posxPerso,posyPerso,0);
                        }else{
                        regiaoxPerso = 0*larguraPerso;
                        regiaoyPerso = 1*alturaPerso;
                        pacoteServidor.posicao.yh = posyPerso;
                        pacoteServidor.posicao.xw = posxPerso;
                        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                        al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso,posyPerso,0);
                        }
                        al_flip_display();
                        tecla = 0;
                    }
                }
        }
    al_destroy_bitmap(mapa);
    al_destroy_bitmap(plata);
    al_destroy_font(fonte);
    al_destroy_bitmap(spritePersonagem);
    al_destroy_timer(timer);
    al_destroy_display(janela);
    al_destroy_event_queue(filaEventos);

    broadcast(&pacoteServidor, sizeof(ServerPack));
    //compensa o tempo que falta para o fim do tempo do frame
    FPSLimit();
            }
      //finaliza os modulos do allegro
      allegroEnd();
        }
    }
}
