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


int sair = 0, tecla = 0, teclaPulo = 0, inverte = 0, lado = 0, i=0, noAr = 0, contador = 0;
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