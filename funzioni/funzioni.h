#include "LPC17xx.h"

extern  uint8_t animazione;
extern  uint8_t morto;
extern uint8_t  h,m ,s;
extern uint8_t sazieta,felicita ;
extern uint8_t disable_joystick;
extern uint8_t frame;
extern uint8_t suono;
extern int volume;

void drawBactery1(int liv,uint16_t color);
void drawBactery2(int liv,uint16_t color);
void calculateAge(uint8_t h,uint8_t m,uint8_t s);
void disegna(uint16_t color);
void disegnaMorto(uint16_t color,int xShift);
void disegna2(uint16_t color);
void disegnaInterazione(uint16_t color);
void disegnaSound(uint16_t icona,uint16_t color);

void caramella(uint16_t color);
void caramella2(uint16_t color);

void disegnaSX(uint16_t color);
void disegnaDX(uint16_t color);


