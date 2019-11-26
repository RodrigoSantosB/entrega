#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <unistd.h>

// CRIAR STRUCT DO PERSONAGEM

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_BITMAP *mapa = NULL, *plata = NULL, *spritePersonagem = NULL, *spritePortal = NULL;
ALLEGRO_EVENT_QUEUE *filaEventos = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_TIMER *timer = NULL;
int sair = 0, tecla = 0, teclaPulo = 0, inverte = 0, lado = 0, i=0, noAr = 0, cont = 0;
int alturaPerso = 49, larguraPerso = 48, regiaoxPerso = 0, regiaoyPerso = 0, posxPerso = 455, posyPerso = 265;
int alturaPortal = 100, larguraPortal = 100, regiaoxPortal1 = 400, regiaoyPortal1 = 0, posxPortal1 = 365, 
posyPortal1 = 325, regiaoxPortal2 = 400, regiaoyPortal2 = 0, posxPortal2 = 420, posyPortal2 = 225;
int vidaPerso = 300, staminaPerso = 1000;


int resurgir(int contador){
    if(posyPerso==365){
        if(contador%3==0){
            posxPerso = 35;
        }else if(contador%5==0){
            posxPerso = 135;
        }else if(contador%7==0){
            posxPerso = 235;
        }else{
            posxPerso = 335;
        }
    }else if(posyPerso==265){
        if(contador%3==0){
            posxPerso = 505;
        }else if(contador%5==0){
            posxPerso = 605;
        }else if(contador%7==0){
            posxPerso = 705;
        }else{
            posxPerso = 805;
        }

    }       
    return posxPerso;
} // ISSO TEM QUE SER NO SERVIDOR

int pulaSobe(){
    int i, k;
    if(inverte==0){
        regiaoxPerso = 2*larguraPerso;
        regiaoyPerso = 0*alturaPerso;

        posyPerso-=20;
        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
        al_draw_bitmap(plata, 455, 300, 0);
        al_draw_bitmap(plata, 50, 400, 0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
        al_draw_bitmap_region(spritePersonagem,regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
        al_flip_display();
        
          
    }else{
        regiaoxPerso = 2*larguraPerso;
        regiaoyPerso = 0*alturaPerso;

        posyPerso-=20;
        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
        al_draw_bitmap(plata, 455, 300, 0);
        al_draw_bitmap(plata, 50, 400, 0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
        al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
        al_flip_display();
        
        
    }
    al_flip_display();
    return posyPerso;
}

int pulaDesce(){
    int i, k;
    if(inverte==0){
        regiaoxPerso = 2*larguraPerso;
        regiaoyPerso = 0*alturaPerso;
        for(i=0; i<3; i++){
            posyPerso+=20;
            al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
            al_draw_bitmap(plata, 455, 300, 0);
            al_draw_bitmap(plata, 50, 400, 0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
            al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
            al_flip_display();
            
        }
        
        
    }else{
        regiaoxPerso = 2*larguraPerso;
        regiaoyPerso = 0*alturaPerso;
        for(i=0; i<3; i++){
            posyPerso+=20;
            al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
            al_draw_bitmap(plata, 455, 300, 0);
            al_draw_bitmap(plata, 50, 400, 0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
            al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
            al_flip_display();
            
        }
    }
    al_flip_display();
    return posyPerso;
}

int dash(){
    int i;
    if(inverte==0){
        regiaoxPerso = 1*larguraPerso;
        regiaoyPerso = 1*alturaPerso;
        for(i=0;i<3; i++){
            posxPerso+=15;
            al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
            al_draw_bitmap(plata, 455, 300, 0);
            al_draw_bitmap(plata, 50, 400, 0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
            al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
            al_flip_display();
            
        }
        return posxPerso;
    }else{
        regiaoxPerso = 1*larguraPerso;
        regiaoyPerso = 1*alturaPerso;
        for(i=0; i<3; i++){
            posxPerso-=15;
            al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
            al_draw_bitmap(plata, 455, 300, 0);
            al_draw_bitmap(plata, 50, 400, 0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
            al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
            al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
            al_flip_display();
            
        }
        return posxPerso;
        }           
}

int cair(int tecla, int inverte, int regiaoxPerso, int regiaoyPerso, int larguraPerso, int alturaPerso, int posxPerso, int posyPerso, int lado){
        regiaoxPerso = 2*larguraPerso;
        regiaoyPerso = 0*alturaPerso;
        posyPerso+=10;
        al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
        al_draw_bitmap(plata, 455, 300, 0);
        al_draw_bitmap(plata, 50, 400, 0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
        al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
        al_draw_bitmap_region(spritePersonagem,regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
        al_flip_display();
        
    return posyPerso;

} // ISSO TEM QUE SER NO SERVIDOR

void inicializaTudo() {
    if(!al_init()){
        printf("al init\n");
    }
    if(!al_init_image_addon()){
        printf("al init image\n");
    }
    if(!al_init_font_addon()){
        printf("al init font\n");
    }
    if(!al_init_ttf_addon()){
        printf("al init ttf\n");
    }
    if(!al_install_keyboard()){
        printf("keyboard\n");
    }
    if(!al_install_mouse()){
        printf("mouse\n");
    }
    timer = al_create_timer(1.0 / 60);
    if(!timer){
        printf("timer");
    } 
    mapa = al_load_bitmap("img/mapa.png");
    if(!mapa){
        printf("mapa\n");
    }
    plata = al_load_bitmap("img/plata.png");
    if(!plata){
        printf("plata\n");
    }
    janela = al_create_display(al_get_bitmap_width(mapa), al_get_bitmap_height(mapa));
    if(!janela){
        printf("janela\n");
    }
    spritePersonagem = al_load_bitmap("sprites/sprite1.png");
    if(!spritePersonagem){
        printf("spritePersonagem\n");
    }
    spritePortal = al_load_bitmap("sprites/sprite2.png");
    if(!spritePersonagem){
        printf("spritePortal\n");
    }
    al_convert_mask_to_alpha(spritePersonagem, al_map_rgb(255, 0, 232));
    al_convert_mask_to_alpha(spritePortal, al_map_rgb(0, 0, 254));

    filaEventos = al_create_event_queue();
    if(!filaEventos){
        printf("filaEventos\n");
    }
    fonte = al_load_font("fonts/fonte.ttf", 30, 0);
    if(!fonte){
        printf("fonte contador\n");
    }
}

int main(void){
    //FAZER CONEXÃO COM O SERVIDOR (enum conn_ret_t connectToServer(const char *server_IP);)
    

    // Inicializa tudo que precisa
    inicializaTudo();

    al_set_window_title(janela, "CInhalla");
    al_register_event_source(filaEventos, al_get_keyboard_event_source());
    al_register_event_source(filaEventos, al_get_display_event_source(janela));
    al_register_event_source(filaEventos, al_get_timer_event_source(timer));
    al_start_timer(timer);
    al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
    al_draw_bitmap(plata, 455, 300, 0);
    al_draw_bitmap(plata, 50, 400, 0);
    al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
    al_draw_bitmap_region(spritePortal,regiaoxPortal1,regiaoyPortal1,larguraPortal,alturaPortal,posxPortal1,posyPortal1,0);
    al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
    al_flip_display();
    
    while(!sair){   
        int contador;
        contador ++;
        if(staminaPerso<1000){
            staminaPerso++;
            printf("stamina %d ", staminaPerso);        }
        while(!al_is_event_queue_empty(filaEventos)){
            ALLEGRO_EVENT evento;
            al_wait_for_event(filaEventos, &evento);
                if(evento.type == ALLEGRO_EVENT_KEY_DOWN){ 
                    switch(evento.keyboard.keycode){ 
                        case ALLEGRO_KEY_W : // TECLA W
                            teclaPulo = 1;
                            break;
                        case ALLEGRO_KEY_S : // TECLA S
                            tecla = 2;
                            break;
                        case ALLEGRO_KEY_A : // TECLA A
                            posxPerso -= 30;
                            tecla = 3;
                            break;
                        case ALLEGRO_KEY_D : // TECLA D
                            posxPerso += 30;
                            tecla = 4;
                            break;
                        case ALLEGRO_KEY_SPACE : // TECLA ESPAÇO
                            tecla = 5;
                            break;
                        case ALLEGRO_KEY_N: // TECLA N
                            tecla = 6;
                            break;
                        case ALLEGRO_KEY_ESCAPE: // TECLA ESC
                            sair = 1;
                            break;
                    }
                }else if(evento.type = ALLEGRO_EVENT_KEY_UP){

                }
            }

        if(1){
            if((posyPerso>=365 && (posxPerso<20 || posxPerso>=830)) || (posxPerso>=830) || (posyPerso>365 && posxPerso<420)|| (posyPerso>265 && posxPerso>=450)){ // CAI // SERVIDOR
                posyPerso = cair (tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso, lado);
            } 
            if(posxPerso>385 && posxPerso<430 && posyPerso == 365){ // PORTAL DEBAIXO // SERVIDOR
                posxPerso = 465;
                posyPerso = 265;
            }
            if(posxPerso>=420 && posxPerso<460 && posyPerso == 265){ // PORTAL DE CIMA // SERVIDOR
                posxPerso = 380;
                posyPerso = 365;
            }
            if(posyPerso>600){ // RESSURGIR // SERVIDOR
                if(contador%2==0){
                    posyPerso = 265;
                    posxPerso = resurgir(contador);
                }else{
                    posyPerso = 365;
                    posxPerso = resurgir(contador);
                }
            }
            
            printf("%d %d\n", posxPerso, posyPerso);
            if(noAr == 1 && cont==3){ //CAI DO PULO
                posyPerso = pulaDesce(tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso);
                teclaPulo = 0;
                noAr = 0;
                cont = 0;
            }else if(teclaPulo == 1 && noAr == 0){ // PULA 
                posyPerso = pulaSobe(tecla, inverte, regiaoxPerso, regiaoyPerso, larguraPerso, alturaPerso, posxPerso, posyPerso);
                teclaPulo = 1;
                cont ++;
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
                al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                al_draw_bitmap_region(spritePersonagem,regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
                }else{
                regiaoxPerso = 1*larguraPerso;
                regiaoyPerso = 0*alturaPerso;
                al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                al_draw_bitmap_region(spritePersonagem, regiaoxPerso, regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,ALLEGRO_FLIP_HORIZONTAL);
                }
                al_flip_display();
                
                tecla = 0;
            }else if(tecla == 3){ // ESQUERDA
                regiaoxPerso = 1*larguraPerso;
                regiaoyPerso = 1*alturaPerso;
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
                al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                al_draw_bitmap(plata, 455, 300, 0);
                al_draw_bitmap(plata, 50, 400, 0);
                if(inverte==0){
                regiaoxPerso = 2*larguraPerso;
                regiaoyPerso = 1*alturaPerso;
                al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso,alturaPerso, posxPerso,posyPerso,0);
                }else{
                regiaoxPerso = 2*larguraPerso;
                regiaoyPerso = 1*alturaPerso;
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
            }else if(noAr==0) { // FICA PARADO
                al_draw_bitmap_region(mapa, 0, 0, al_get_bitmap_width(mapa), al_get_bitmap_height(mapa), 0, 0, 0);
                al_draw_bitmap(plata, 455, 300, 0);
                al_draw_bitmap(plata, 50, 400, 0);
                if(inverte==0){
                regiaoxPerso = 0*larguraPerso;
                regiaoyPerso = 0*alturaPerso;
                al_draw_bitmap_region(spritePortal, regiaoxPortal2, regiaoyPortal2, larguraPortal,alturaPortal, posxPortal2,posyPortal2,0);
                al_draw_bitmap_region(spritePortal, regiaoxPortal1, regiaoyPortal1, larguraPortal,alturaPortal, posxPortal1,posyPortal1,0);
                al_draw_bitmap_region(spritePersonagem, regiaoxPerso,regiaoyPerso, larguraPerso, alturaPerso, posxPerso,posyPerso,0);
                }else{
                regiaoxPerso = 0*larguraPerso;
                regiaoyPerso = 1*alturaPerso;
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
    return 0;

}
