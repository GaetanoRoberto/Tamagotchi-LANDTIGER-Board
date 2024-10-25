#include "LPC17xx.h"

extern unsigned int animazione;
extern unsigned int frame  ;
extern unsigned int sazieta,felicita  ;
extern unsigned int morto;
extern uint8_t h,m,s;
extern unsigned int disable_joystick ;

void drawBactery1(int liv,uint16_t color);
void drawBactery2(int liv,uint16_t color);
void calculateAge(uint8_t h,uint8_t m,uint8_t s);
void disegna(uint16_t color);
void disegnaMorto(uint16_t color,int xShift);
void disegna2(uint16_t color);
void cancellaTutto(void);

void caramella(uint16_t color);
void caramella2(uint16_t color);

void disegnaSX(uint16_t color);
void disegnaDX(uint16_t color);
