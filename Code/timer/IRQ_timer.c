/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../funzioni/funzioni.h"
#include "../RIT/RIT.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
uint16_t SinTable[45] =                                      
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};


 
void TIMER0_IRQHandler (void)
{	static int sec=0;

					s++;

					

						if(s == 60){//1 min
						m++;
						s=0;
						if(m==60){
							h++;
							m=0;
						}
					}
							calculateAge(h,m,s);

					if(s%5==0){
							sazieta--;
							felicita--;
							drawBactery1(5,White);
							drawBactery2(5,White);
							if(felicita>0){
							drawBactery1(felicita,Red);
							}
							if(felicita>0){
								drawBactery2(sazieta,Blue);
							}

					}
					
	// reset 
	if ((sazieta == 0 || felicita == 0) && (animazione == 0 || animazione == 5)) {
		animazione = 5;//morto
		disable_joystick = 1;
		disable_timer(2);

 

		GUI_Text(50, 110, (uint8_t *) "Addio!", Black, White);
		
		if(frame == 0 || frame == 1){
		GUI_Text(35, 280, (uint8_t *) " Meal  ", White, White);
		GUI_Text(155, 280, (uint8_t *) " Snack  ", White, White);


		
			
		disegna2(White);
		disegna(White);
		disegnaMorto(Red,102);
			frame = 2;
		}else if (frame == 2){
		disegnaMorto(White,102);
	  disegnaDX(Red);
		frame = 3;
		}else{
		
		disegnaDX(White);
		GUI_Text(50, 110, (uint8_t *) "Addio!", White, White);
	
		LCD_DrawCircle(120,160,78,Black);
		
		GUI_Text(60, 145, (uint8_t *) "Il tuo tamagotchi", Black, White);
		GUI_Text(85, 165, (uint8_t *) "e' scappato", Black, White);
		LCD_DrawLine(120,260,120,320,White); // linea centrale verticale
	
		GUI_Text(100, 280, (uint8_t *) "Reset", Red, White);
		suono = 4;
		enable_timer(3);
		enable_timer(1);
			
		LCD_DrawLine(0,260,240,260,Red); //linea superiore 
		LCD_DrawLine(0,319,240,319,Red);//inf
	  LCD_DrawLine(0,260,0,320,Red);// sx
		LCD_DrawLine(239,260,239,320,Red);// dx

				morto=1;
		disable_timer(0);

		}

	}
	
	//animazione == 0 => base
	if(animazione == 0){
		if(frame == 0){
				disegna2(White);
				disegna(Black);
				frame = 1;
		}else 
		if(frame == 1 ){
				disegna(White);
				disegna2(Black);
				frame = 0;
		}		

	}

		
		//animazione == 1 => mangiare SX
	if(animazione == 1){
		disable_joystick = 1;
		if(sec==0){

			disegna2(White);
		disegna(White);

		disable_timer(2);
		caramella(Red);
		disegnaSX(Black);	
		suono = 2;
		enable_timer(3);
		enable_timer(1);
		}
		sec++;
	}
	if ( animazione == 1 & sec == 2){
		caramella(White);
		disegnaSX(White);
		
		if(sazieta < 5)
			sazieta++;
		drawBactery2(sazieta,Blue);
		animazione = 0;
		sec = 0;
		enable_timer(2);
		disable_joystick = 0;

	}
	//animazione ==2 => mangiare DX
		if(animazione == 2){

		if(sec==0){
		disable_joystick = 1;

			disegna2(White);
		disegna(White);
		disable_timer(2);
		caramella2(Blue);
		disegnaDX(Black);	
		suono = 2;
		enable_timer(3);
		enable_timer(1);
		}
		sec++;
	} 
	if ( animazione == 2 & sec == 2)
	{
	 
		caramella2(White);
		disegnaDX(White);
		
		if (felicita <5)
			felicita++;
		
		drawBactery1(felicita,Red);
		animazione = 0;
		sec = 0;
		enable_timer(2);
		disable_joystick = 0;

	}
	if( animazione == 4){
		
		if(sec==0){
		disable_joystick = 1;

		disegna2(White);
		disegna(White);
		
		disegnaInterazione(Black);	
		suono = 3;
		enable_timer(3);
		enable_timer(1);
		}
		sec++;
	} 
	if ( animazione == 4 & sec == 3)
	//sec = 3 perchè la prima volta esco dal ciclo con sec = 1 
	{
	 		disegnaInterazione(White);
			if (felicita <5){
							felicita++;
							drawBactery1(felicita,Red);
			}
		animazione = 0;
		sec = 0;
		disable_joystick = 0;

	}
				

  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


//const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};
extern int freqs[8];

void riproduci (uint8_t note) {

		disable_timer(3);
		reset_timer(3);
		init_timer(3,freqs[note]);
		enable_timer(3);

}

void TIMER1_IRQHandler (void)
{
	static int note = 0;
	
	switch(suono) {
		case 1:
				note++;
			if (note == 1) {
				disable_timer(3);
				disable_timer(1);
				note = 0;
				suono  = 0;
			} else {
				riproduci(note);
			}
			
			break;
		case 2:
			
			note++;
			if (note == 3) {
				disable_timer(3);
				disable_timer(1);
				note = 0;
				suono  = 0;
			} else {
				riproduci(note);
			}

			
			break;
		case 3:
		
			note++;
			if (note == 5) {
				disable_timer(3);
				disable_timer(1);
				note = 0;
				suono  = 0;
			} else {
				riproduci(note);
			}

			
			break;
		case 4:
			
			note++;
			if (note == 7) {
				disable_timer(3);
				disable_timer(1);
				note = 0;
				suono  = 0;
			} else {
				riproduci(note);
			}

			
			break;
			default:
			break;
		}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER2_IRQHandler (void)
{
	
   if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.y > 100 & display.y < 220){
			if(display.x > 60 & display.x < 160){
				if(animazione == 0){
					animazione = 4;	
				}
			}
		} 
	}
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
	 




void TIMER3_IRQHandler (void){	
	
		static int ticks=0;


	/* DAC management */	
	LPC_DAC->DACR = ((SinTable[ticks]*volume)/819)<<6;

	ticks++;
	if(ticks==45) ticks=0;
	
	
	//819 valore piu' grande della sinusoide

	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
