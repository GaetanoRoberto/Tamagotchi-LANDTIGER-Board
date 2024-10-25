/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "funzioni/funzioni.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif 

/* EMULATOR*/

int main(void)

{

  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	enable_RIT();													/* RIT enabled												*/
	
	LCD_Clear(White);

	GUI_Text(20, 30, (uint8_t *) " Happiness  ", Black, White);
	GUI_Text(150, 30, (uint8_t *) " Satiety  ", Black, White);

	LCD_DrawLine(0,260,240,260,Black);
	LCD_DrawLine(120,260,120,320,Black); //linea centrale
/*bordi*/
	LCD_DrawLine(0,0,239,0,Black);//bordo top
	LCD_DrawLine(239,0,239,319,Black);//bordo dx
	LCD_DrawLine(0,0,0,319,Black);//bordo sx
	LCD_DrawLine(0,319,239,319,Black);//bordo bot

	LCD_DrawRectangle(35,55,55,25,Black);//bordo batteria1
	LCD_DrawRectangle(155,55,55,25,Black);//bordo batteria2
	
	LCD_DrawRectangle(37,57,49,20,White);//background batteria1
	LCD_DrawRectangle(157,57,49,20,White);//background batteria2
	
	LCD_DrawRectangle(91,62,3,10,Black);//decorazione batteria
	LCD_DrawRectangle(211,62,3,10,Black);//decorazione batteria
	
	
	drawBactery1(5,Red);
	drawBactery2(5,Blue);


	GUI_Text(35, 280, (uint8_t *) " Meal  ", Black, White);
	GUI_Text(155, 280, (uint8_t *) " Snack  ", Black, White);
	


	//TIMER
		init_timer(0, 0x17D7840 ); 			/*17D7840 1s*/

	/* 50ms * 25MHz *20 = 1.25*10^6 = 0x1312D0 */

		enable_timer(0);
						
		init_timer(1, 0x17D7840 ); 			/*1s*/

		enable_timer(1);
		


	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
   while (1)	
  {

		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
