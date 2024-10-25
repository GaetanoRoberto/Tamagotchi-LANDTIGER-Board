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

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/




 
void TIMER0_IRQHandler (void)
{
					s++;

					
//					if(s%(60) ==0){//1 min
//						m++;
//						s=0;
//						if(m%(60)==0){
//							h++;
//							m=0;
//						}
//					}
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
	if (sazieta == 0 || felicita == 0) {
		animazione = 5;//morto
		disable_joystick = 1;
		
		disable_timer(1);
		disable_timer(0);

		GUI_Text(50, 110, (uint8_t *) "Addio!", Black, White);

		disegna2(White);
		disegna(White);
		disegnaMorto(Red,102);
		disegnaMorto(White,102);
		

	  disegnaDX(Red);
		disegnaDX(White);
		
		GUI_Text(35, 280, (uint8_t *) " Meal  ", White, White);
	GUI_Text(155, 280, (uint8_t *) " Snack  ", White, White);

		GUI_Text(155, 280, (uint8_t *) "Snack", White, White);
				GUI_Text(50, 110, (uint8_t *) "Addio!", White, White);

		LCD_DrawCircle(120,160,78,Black);
		GUI_Text(60, 145, (uint8_t *) "Il tuo tamagotchi", Black, White);
		GUI_Text(85, 165, (uint8_t *) "e' scappato", Black, White);
		LCD_DrawLine(120,260,120,320,White); // linea centrale verticale
	
		GUI_Text(100, 280, (uint8_t *) "Reset", Red, White);
		
		LCD_DrawLine(0,260,240,260,Red); //linea superiore 
		LCD_DrawLine(0,319,240,319,Red);//inf
	  LCD_DrawLine(0,260,0,320,Red);// sx
		LCD_DrawLine(239,260,239,320,Red);// dx

		morto=1;
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



void TIMER1_IRQHandler (void)
{
	static int s=0;
	
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
		if(s==0){
		disegna2(White);
		disegna(White);

		disable_timer(0);
		caramella(Red);
		disegnaSX(Black);	
		}
		s++;
	}
	if ( animazione == 1 & s == 2){
		caramella(White);
		disegnaSX(White);
		
		if(felicita < 5)
			felicita++;
		drawBactery1(felicita,Red);
		animazione = 0;
		s = 0;
		enable_timer(0);
		disable_joystick = 0;

	}
	//animazione ==2 => mangiare DX
		if(animazione == 2){

		if(s==0){
		disable_joystick = 1;
		disegna2(White);
		disegna(White);
		disable_timer(0);
		caramella2(Blue);
		disegnaDX(Black);	
		}
		s++;
	}
	if ( animazione == 2 & s == 2){
		caramella2(White);
		disegnaDX(White);
		
		if (sazieta <5)
			sazieta++;
		
		drawBactery2(sazieta,Blue);
		animazione = 0;
		s = 0;
		enable_timer(0);
		disable_joystick = 0;

	}

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
