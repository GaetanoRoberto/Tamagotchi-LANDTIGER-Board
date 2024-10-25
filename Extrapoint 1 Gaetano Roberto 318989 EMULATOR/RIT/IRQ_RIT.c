/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "GLCD.h" 
#include "../timer/timer.h"
#include "../funzioni/funzioni.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/




void riquadro(int sx,uint16_t color){
		if(sx==1){
		LCD_DrawLine(0,260,120,260,color); //linea superiore 
		LCD_DrawLine(0,319,120,319,color);//inf
	  LCD_DrawLine(0,260,0,320,color);// sx

		}else{
		LCD_DrawLine(121,260,240,260,color); //linea superiore 
		LCD_DrawLine(121,319,240,319,color);//inf
		LCD_DrawLine(239,260,239,320,color);// dx


		}
		LCD_DrawLine(120,260,120,320,color); //linea centrale

};



void RIT_IRQHandler (void)
{					
	static int select=0;
	static int left = 2;  //27
	disable_RIT();
	
  
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 ){	//left
		
		if(disable_joystick == 0)
		{
			left = 1;
		riquadro(!left,Black);
		riquadro(left,Red);
		}
	}
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 ){//right
				if(disable_joystick == 0)
		{
		left = 0;
		riquadro(!left,Black);
		riquadro(left,Red);
		}
	}

	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed p1.25*/
		/* Joytick Down pressed p1.26 --> using J_DOWN due to emulator issues*/
		
		select++;


		switch(select){
			case 1:

		if(left==1){
					animazione = 1;
					riquadro(left,Black);
					left=2;

		}
		if(left==0){
			animazione = 2;
			riquadro(left,Black);
			left=2;

			
			

		}
		if(morto==1){



			
			LCD_DrawCircle(120,160,78,White);
			GUI_Text(60, 145, (uint8_t *) "Il tuo tamagotchi", White, White);
			GUI_Text(85, 165, (uint8_t *) "e' scappato", White, White);
			
			reset_timer(0);
			reset_timer(1);
			sazieta=5;
			felicita=5;


			
			
			
			drawBactery1(felicita,Red);
			drawBactery2(sazieta,Blue);
			
			GUI_Text(100, 280, (uint8_t *) "Reset", White, White);
			animazione = 0;
			h=0;m=0;s=0;

		GUI_Text(35, 280, (uint8_t *) " Meal  ", Black, White);
		GUI_Text(155, 280, (uint8_t *) " Snack  ", Black, White);
		LCD_DrawLine(120,260,120,320,Black); // linea centrale verticale
		LCD_DrawLine(0,260,240,260,Black); //linea superiore 
		LCD_DrawLine(0,319,240,319,Black);//inf
	  LCD_DrawLine(0,260,0,320,Black);// sx
		LCD_DrawLine(239,260,239,320,Black);// dx


			enable_timer(0);
			enable_timer(1);
			morto=0;
			disable_joystick=0;
		}
				break;
			default:
				break;
		}
	}
	else{
			select=0;
	}

	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	enable_RIT();
  return;
}


///******************************************************************************
//**                            End Of File
//******************************************************************************/
