#include "ACore.h"
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"menu.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


/******/
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/******/

#define MSG_MAX_SIZE 350
#define BUFFER_SIZE (MSG_MAX_SIZE + 100)
#define LOGIN_MAX_SIZE 13
#define HIST_MAX_SIZE 200

#define LARGURA 640
#define ALTURA 480
#define MAX_LOG_SIZE 17

void printConnectScreen(char str[]);
void printChatLog( char chatLog[][MSG_MAX_SIZE]);
void printLobbyText(char str[]);
void printLoginScreen(char str[]);

/****************************************************************/

/*****************************************************************/

enum conn_ret_t tryConnect(char IP[]) {
  char server_ip[30];
  printf("Please enter the server IP: ");
  //scanf(" %s", server_ip);
  //getchar();
  return connectToServer(IP);
}

void printHello() {
  puts("Hello! Wellcome to simple chat example.");
  puts("We need some infos to start up!");
}

void assertConnection(char IP[], char login[]) {
  printHello();
  enum conn_ret_t ans = tryConnect(IP);

  while (ans != SERVER_UP) 
  {
    if (ans == SERVER_DOWN) {
      puts("Server is down!");
    } else if (ans == SERVER_FULL) {
      puts("Server is full!");
    } else if (ans == SERVER_CLOSED) {
      puts("Server is closed for new connections!");
    } else {
      puts("Server didn't respond to connection!");
    }
    printf("Want to try again? [y/n] ");
    int res;
    while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n'){
      puts("anh???");
    }
    if (res == 'n') {
      exit(EXIT_SUCCESS);
    }
    ans = tryConnect(IP);
  }
  //char login[LOGIN_MAX_SIZE + 4];
  //printf("Please enter your login (limit = %d): ", LOGIN_MAX_SIZE);
  //scanf(" %[^\n]", login);
  //getchar();
  int len = (int)strlen(login);
  sendMsgToServer(login, len + 1);
}

void runChat() {
  char str_buffer[BUFFER_SIZE], type_buffer[MSG_MAX_SIZE] = {0};
  char msg_history[HIST_MAX_SIZE][MSG_MAX_SIZE] = {{0}};
  int type_pointer = 0;
  
  while (1) {
    // LER UMA TECLA DIGITADA
    char ch = getch();
    if (ch == '\n') {
      type_buffer[type_pointer++] = '\0';
      int ret = sendMsgToServer((void *)type_buffer, type_pointer);
      if (ret == SERVER_DISCONNECTED) {
        return;
      }
      type_pointer = 0;
      type_buffer[type_pointer] = '\0';
    } else if (ch == 127 || ch == 8) {
      if (type_pointer > 0) {
        --type_pointer;
        type_buffer[type_pointer] = '\0';
      }
    } else if (ch != NO_KEY_PRESSED && type_pointer + 1 < MSG_MAX_SIZE) {
      type_buffer[type_pointer++] = ch;
      type_buffer[type_pointer] = '\0';
      
    }

    // LER UMA MENSAGEM DO SERVIDOR
    int ret = recvMsgFromServer(str_buffer, DONT_WAIT);
    if (ret == SERVER_DISCONNECTED) {
      return;
    } else if (ret != NO_MESSAGE) {
      int i;
      for (i = 0; i < HIST_MAX_SIZE - 1; ++i) {
        strcpy(msg_history[i], msg_history[i + 1]);
      }
      strcpy(msg_history[HIST_MAX_SIZE - 1], str_buffer);
    }

    // PRINTAR NOVO ESTADO DO CHAT
    system("clear");
    int i;
    for (i = 0; i < HIST_MAX_SIZE; ++i) {
      printf("%s\n", msg_history[i]);
    }
    printf("\nYour message: %s\n", type_buffer);
  }
}

int main() 
{
    //A primeira coisa a ser feita é inicializar os módulos centrais. Caso algum deles falhe, o programa já para por aí.
    if (!coreInit())
        return -1;

    //Agora vamos criar a nossa janela. Largura e Altura em pixels, o título é uma string.
    if (!windowInit(LARGURA, ALTURA, "Allegro Example - Graphical Chat"))
        return -1;

    //Agora inicializamos nosso teclado e mouse, para que a janela responda às entradas deles
    if (!inputInit())
        return -1;

    //Agora inicializamos nossas fontes
    if(!fontInit())
      return -1;

    //E por fim todas as imagens que vamos utilizar no programa.
    if(!loadGraphics())
        return -1;

    //para sair do jogo
    bool lobby = true;
    bool connectScreen = true;
    bool loginScreen = true;
 
    //Criamos uma nova estrutura que será enviada e recebida do servidor.
    DADOS pacote;

    //Exemplo de como colocar uma carga inicial no pacote
    char msg[]={"Oi Servidor!"};
    strcpy(pacote.mensagem, msg);
    pacote.valor = 42;

    //Esse IP irá nos conectar a "nós mesmos", apenas para efeito de testes.
    char ServerIP[30]={"127.0.0.1"};

    //para guardar o log do chat
    char chatLog[MAX_LOG_SIZE][MSG_MAX_SIZE] = {{0}};
    //mensagem pra ser mandada no lobby
    char lobbyMessage[110]={0}; 
    //para guardar o login
    char loginMsg[BUFFER_SIZE]={0};
    //connectToServer(ServerIP);

    int i;
    

    while(connectScreen)
    {
        startTimer();

        while(!al_is_event_queue_empty(eventsQueue))
        {
            ALLEGRO_EVENT connectEvent;
            al_wait_for_event(eventsQueue, &connectEvent);

            readInput(connectEvent, ServerIP, IP_MAX_SIZE);

            if (connectEvent.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(connectEvent.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ENTER:
                        connectScreen = false;
                        break;
                }
            }

            if(connectEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                connectScreen = false;
                loginScreen = false;
                lobby = false;
                //quit = true;
            }
        }

        printConnectScreen(ServerIP);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        FPSLimit();
    }

    while(loginScreen)
    {
        startTimer();


        while(!al_is_event_queue_empty(eventsQueue))
        {
            ALLEGRO_EVENT loginEvent;
            al_wait_for_event(eventsQueue, &loginEvent);

            readInput(loginEvent, loginMsg, LOGIN_MAX_SIZE);

            if (loginEvent.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(loginEvent.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ENTER:
                        loginScreen = false;
                        break;
                }
            }

            if(loginEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                loginScreen = false;
                lobby = false;
            }
        }


        printLoginScreen(loginMsg);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
        FPSLimit();
    }

    //Realiza conexão com o server
    assertConnection(ServerIP, loginMsg);



    while(lobby)
    {
        startTimer();

        int rec = recvMsgFromServer(&pacote, DONT_WAIT);

        //recebe as mensagens do servidor (jogador se conectou, avisos, etc)
        if(rec != NO_MESSAGE){ 

                //printf("RECEIVED: %s\n", pacote.mensagem);

                for(i = 0; i < MAX_LOG_SIZE - 1; ++i)
                    strcpy(chatLog[i], chatLog[i+1]);
                
                strcpy(chatLog[MAX_LOG_SIZE - 1], pacote.mensagem);
                
                pacote.mensagem[0]='\0';
        }

        while(!al_is_event_queue_empty(eventsQueue))
        {
            ALLEGRO_EVENT lobbyEvent;
            al_wait_for_event(eventsQueue, &lobbyEvent);

            readInput(lobbyEvent, lobbyMessage, MSG_MAX_SIZE);



            if (lobbyEvent.type == ALLEGRO_EVENT_KEY_DOWN)
            {
                switch(lobbyEvent.keyboard.keycode)
                {
                    case ALLEGRO_KEY_ENTER:
                        strcpy(pacote.mensagem, lobbyMessage);
                        sendMsgToServer(&pacote, sizeof(DADOS));
                        lobbyMessage[0]='\0';
                        break;
                }
            }

            if(lobbyEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                lobby = false;
                //quit=true;
            }
        }

        printLobbyText(lobbyMessage);
        printChatLog(chatLog);
        al_flip_display();


////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_BITMAP *menuInicial = NULL, *menuControles = NULL, *menuCreditos = NULL;
    ALLEGRO_FONT *fonteMaior = NULL;
    ALLEGRO_FONT *fonteMenor = NULL;
    ALLEGRO_EVENT_QUEUE *filaEventosJanela = NULL, *filaEventosMouse = NULL;
    int opcao, jogar=0;

    if(!al_init()){
        printf("NÃO INICIALIZOU O ALLEGRO\n");
        return 0;
    }

    if(!al_init_image_addon()){
        printf("NÃO INICIALIZOU O menuInicial\n");
        return 0;
    }

    if(!al_init_font_addon()){
        printf("NÃO INICIALIZOU O TEXTO\n");
        return 0;
    }

    if(!al_init_ttf_addon()){
        printf("NÃO INICIALIZOU O TTF\n");
        return 0;
    }

    menuInicial = al_load_bitmap("menu/img/jogo.png");
    if(!menuInicial){
        printf("NÃO CARREGOU A menuInicial\n");
        return 0;
    }

    menuControles = al_load_bitmap("menu/img/menuControles.png");
    if(!menuControles){
        printf("NÃO CARREGOU A menuControles\n");
        return 0;
    }
    menuCreditos = al_load_bitmap("menu/img/menuCreditos.png");
    if(!menuControles){
        printf("NÃO CARREGOU A menuCreditos\n");
        return 0;
    }

    janela = al_create_display(al_get_bitmap_width(menuInicial),al_get_bitmap_height(menuInicial));
    if(!janela){
        printf("NÃO CRIOU A JANELA\n");
        return 0;
    }
    
    fonteMaior = al_load_font("menu/fonts/fonte.ttf", 100, 0);
    if(!fonteMaior){
        al_destroy_display(janela);
        printf("NÃO CARREGOU A FONTE\n");
        return 0;
    }

    fonteMenor = al_load_font("menu/fonts/fonte.ttf", 40, 0);
    if(!fonteMenor){
        al_destroy_display(janela);
        printf("NÃO CARREGOU A FONTE\n");
        return 0;
    }

    filaEventosMouse = al_create_event_queue();
    filaEventosJanela = al_create_event_queue();
    if(!filaEventosJanela || !filaEventosMouse){
        al_destroy_display(janela);
        printf("NÃO CRIOU A FILA DE EVENTOS");
        return 0;
    }

    al_install_mouse();
    if(!al_install_mouse()){
        al_destroy_display(janela);
        printf("NAO INSTALOU O MOUSE");
        return 0;
    }   

    al_set_window_title(janela, "Menu Inicial");
    al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
    if(!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT)){
        al_destroy_display(janela);
        printf("NÃO SETOU O CURSOR PADRÃO");
        return 0;
    }

    int flagJanela = 1;

    while(!jogar){
        opcao = menuCompleto(menuInicial, menuControles, fonteMaior, fonteMenor, filaEventosMouse, janela);
        if(flagJanela){
            printf("Conseguiu\n");
            flagJanela = 0;
        }

        switch(opcao){
            case 1: //SAIR
                printf("Sair\n");
                exit(-1);
                break;
                
            case 2: //CONTROLES
                opcaoControles(menuControles, filaEventosMouse, janela, menuInicial);
                printf("Saiu Menu controles\n");
                flagJanela = 1; 
                break;

            case 3: //CREDITOS
                opcaoCreditos(menuCreditos, filaEventosMouse, janela, menuInicial);
                printf("Saiu Menu creditos\n");
                flagJanela = 1;
                break;

            case 4: //JOGAR
                printf("VAI COMEÇAR\n");
                jogar = 1;
                break;
        }
    }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////





                
                al_clear_to_color(al_map_rgb(0, 0, 0));
                FPSLimit();
            }

        //puts("Welcome to the chat example");
        //puts("Just type your messages e talk to your freinds");
        //puts("Press [Enter] to continue");

        /*while(1) {
            runChat();
            printf("Server disconnected! Want to try again? [Y/n] ");
            int res;

            while (res = tolower(getchar()), res != 'n' && res != 'y' && res != '\n')
            puts("anh???");

            if (res == 'y' || res == '\n') 
                assertConnection(ServerIP, loginMsg);
        
            else 
                break;

        }*/


        allegroEnd();

  return 0;
}

//========================================================FUNCTIONS========================================================
void printConnectScreen(char str[])
{
    al_draw_bitmap(menuScreen,0,0,0);

    al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2, 120, ALLEGRO_ALIGN_CENTRE, "Digite o IP do server:");

    if (strlen(str) > 0)
    {
        al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }
    else
    {
        al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "0.0.0.0");
    }
}


void printChatLog( char chatLog[][MSG_MAX_SIZE])
{
    int i;
    int initialY = 60;
    int spacing = al_get_font_ascent(start)+5;
    
    for(i = 0; i < MAX_LOG_SIZE; ++i)
    {
        al_draw_text(start, al_map_rgb(165,42,42), 40, initialY + (i*spacing), ALLEGRO_ALIGN_LEFT, chatLog[i]);
    }


}

void printLobbyText(char str[])
{
    al_draw_bitmap(menuScreen,0,0,0);

    al_draw_text(start, al_map_rgb(165,42,42), 20, 30, ALLEGRO_ALIGN_LEFT, "vo trancar o curso");

    if (strlen(str) > 0)
    {
        al_draw_text(start, al_map_rgb(165,42,42), 20,
                     (HEIGHT - al_get_font_ascent(start)) - 20,
                     ALLEGRO_ALIGN_LEFT, str);
    }
    else
    {
        al_draw_text(start, al_map_rgb(165,42,42), 20,
                     (HEIGHT - al_get_font_ascent(start)) - 20,
                     ALLEGRO_ALIGN_LEFT, "type anything to chat...");
    }
}

void printLoginScreen(char str[])
{
    al_draw_bitmap(menuScreen,0,0,0);

    al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2, 30, ALLEGRO_ALIGN_CENTRE, "Digite o Login desejado: ");

    if (strlen(str) > 0)
    {
        al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, str);
    }
    else
    {
        al_draw_text(start, al_map_rgb(165,42,42), WIDTH / 2,
                     (HEIGHT - al_get_font_ascent(start)) / 2,
                     ALLEGRO_ALIGN_CENTRE, "<login>");
    }
}
