/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"


unsigned int animazione ;
unsigned int sazieta=5,felicita=5 ;
unsigned int frame = 0;
unsigned int morto = 0;
uint8_t h = 0,m = 0,s= 0;
unsigned int disable_joystick = 0;

int matrice1[20][16]={
{0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0},
{0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0},
{1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1},
{1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0},
{0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0}
};
int matrice2[20][16]={
{0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0},
{0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0},
{1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1},
{1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0}
};

int matriceMorto[20][16]={
{0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,0,0,0,1,1,1,0,0},
{0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0},
{1,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1},
{1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0},
{0,0,0,1,1,0,1,1,1,1,0,1,1,0,0,0},
{0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0},
{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
{0,0,0,1,1,1,0,0,0,1,1,1,0,0,0,0}
};




void drawBactery1(int liv,uint16_t color){
	int i;
	for(i=0;i<liv;i++)
		LCD_DrawRectangle(36+(i*10)+1,57,9,20,color);
}
void drawBactery2(int liv,uint16_t color){
	int i;
	for(i=0;i<liv;i++)
		LCD_DrawRectangle(156+(i*10)+1,57,9,20,color);
}

void  calculateAge(uint8_t h,uint8_t m,uint8_t s){
	char time_char[14];
	time_char[13]= '\0';
	sprintf(time_char,"AGE: %02d:%02d:%02d",h,m,s);
	GUI_Text(60, 10, (uint8_t *) time_char , Black, White);

}

void disegna(uint16_t color){
	
		int row,col;
		int x0=75,y0=110;
		for(row=0;row<20;row++){
			for(col=0;col<16;col++){
				if(matrice1[row][col]==1){
			//LCD_SetPoint(y+y0,x+x0,Black);
				LCD_DrawRectangle(col+x0,row+y0,6,6,color);
				}

				x0=x0+5;


				}
			y0=y0+5;
			x0=75;

			}
		}

		void disegnaMorto(uint16_t color,int xShift){
	
		int row,col;
		int x0=xShift,y0=110;
		for(row=0;row<20;row++){
			for(col=0;col<16;col++){
				if(matriceMorto[row][col]==1){
			//LCD_SetPoint(y+y0,x+x0,Black);
				LCD_DrawRectangle(col+x0,row+y0,6,6,color);
				}

				x0=x0+5;


				}
			y0=y0+5;
			x0=xShift;

			}
		}
		

void disegna2(uint16_t color){
	
		int row,col;
		int x0=75,y0=110;
		for(row=0;row<20;row++){
			for(col=0;col<16;col++){
				if(matrice2[row][col]==1){
			//LCD_SetPoint(y+y0,x+x0,Black);
				LCD_DrawRectangle(col+x0,row+y0,6,6,color);
				}

				x0=x0+5;


				}
			y0=y0+5;
			x0=75;

			}
		}
 
void caramella(uint16_t color){
	LCD_DrawCircle(15,180,10,color);
};
void caramella2(uint16_t color){
	LCD_DrawRectangle(215,180,20,20,color);
};


void disegnaSX(uint16_t color){
	
		int row,col;
		int x0=30,y0=110;
		for(row=0;row<20;row++){
			for(col=0;col<16;col++){
				if(matrice2[row][col]==1){
				LCD_DrawRectangle(col+x0,row+y0,6,6,color);
				}

				x0=x0+5;


				}
			y0=y0+5;
			x0=30;

			}
		}
void disegnaDX(uint16_t color){
	
		int row,col;
		int x0=130,y0=110;
		for(row=0;row<20;row++){
			for(col=0;col<16;col++){
				if(matrice2[row][col]==1){
				LCD_DrawRectangle(col+x0,row+y0,6,6,color);
				}

				x0=x0+5;


				}
			y0=y0+5;
			x0=130;

			}
		}
//void cancellaTutto(void){
//				LCD_DrawRectangle(1,82,238,170,White);
//}
