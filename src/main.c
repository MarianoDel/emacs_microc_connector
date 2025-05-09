//---------------------------------------------------------------
// #### PROJECT MICRO-CURRENTS SUPPLY-BRD F103 - Custom Board ###
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### MAIN.C ##################################################
//---------------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "stm32f10x.h"
#include "hard.h"

#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"

#include "comms.h"
#include "effects.h"
#include "test_functions.h"
#include "connectors.h"

#include <stdio.h>
#include <string.h>


// Private Types Constants and Macros ------------------------------------------


// Externals -------------------------------------------------------------------
//--- Externals from timers
volatile unsigned short timer_standby = 0;
volatile unsigned short wait_ms_var = 0;



// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TimingDelay_Decrement(void);
void SysTickError (void);


// Module Functions ------------------------------------------------------------
int main (void)
{
    // Gpio Configuration.
    GpioInit();
    
    // Systick Timer Activation
    if (SysTick_Config(64000))
        SysTickError();

    // Hardware Tests
    // TF_Hardware_Tests ();

    // --- main program inits. ---
    // Init Uart4
    Uart4Config();

    // Init Tim3 for neopixel
    TIM3_Init();

//     // Init Tim1 Tim8 for Boost
//     // TIM1_Init_Master_Output_Disable ();
//     // TIM8_Init_Slave_Output_Disable ();
    
//     // --- start supply manager
//     Usart3Send("\r\n -- Supply Board ver 2.0 init --\r\n");
//     Supply_Status_Reset ();

    Effects_White_No_Conn_Reset();
    unsigned char cnt = 0;
    unsigned char white_effect = 1;
    timer_standby = 20000;

    // while (1)
    // 	Effects_White_No_Conn();
    
    while (1)
    {
	// Comms_Update ();
	Connectors_Update ();
	// switch (cnt)
	// {
	// case 0:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 255;
	// 	my_pixel.G = 0;
	// 	my_pixel.B = 0;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_DIMMER);
		
	// 	cnt++;
	// 	white_effect = 0;
	//     }
	//     else
	// 	Effects_White_No_Conn();
	    
	//     break;

	// case 1:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 82;
	// 	my_pixel.G = 82;
	// 	my_pixel.B = 82;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_DIMMER);
		
	// 	cnt++;
	//     }
	//     break;

	// case 2:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 0;
	// 	my_pixel.G = 255;
	// 	my_pixel.B = 0;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_DIMMER);
		
	// 	cnt++;
	//     }
	//     break;

	// case 3:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 0;
	// 	my_pixel.G = 0;
	// 	my_pixel.B = 255;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_DIMMER);
		
	// 	cnt++;
	//     }
	//     break;

	// case 4:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 255;
	// 	my_pixel.G = 0;
	// 	my_pixel.B = 0;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_BLINK);
		
	// 	cnt++;
	//     }
	//     break;

	// case 5:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 0;
	// 	my_pixel.G = 255;
	// 	my_pixel.B = 0;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_BLINK);
		
	// 	cnt++;
	//     }
	//     break;

	// case 6:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel;
	// 	my_pixel.R = 0;
	// 	my_pixel.G = 0;
	// 	my_pixel.B = 255;
		
	// 	timer_standby = 10000;
	// 	for (int i = 0; i < 9; i++)
	// 	    Effects_Connectors_Colors (i, my_pixel, MODE_BLINK);
		
	// 	cnt++;
	//     }
	//     break;

	// case 7:
	//     if (!timer_standby)
	//     {
	// 	pixel_t my_pixel1;
	// 	pixel_t my_pixel2;
	// 	pixel_t my_pixel3;		
	// 	my_pixel1.R = 0;
	// 	my_pixel1.G = 0;
	// 	my_pixel1.B = 255;

	// 	my_pixel2.R = 255;
	// 	my_pixel2.G = 0;
	// 	my_pixel2.B = 0;

	// 	my_pixel3.R = 0;
	// 	my_pixel3.G = 255;
	// 	my_pixel3.B = 0;
		
	// 	timer_standby = 10000;
	// 	Effects_Connectors_Colors (0, my_pixel1, MODE_BLINK);
	// 	Effects_Connectors_Colors (1, my_pixel1, MODE_DIMMER);
	// 	Effects_Connectors_Colors (2, my_pixel1, MODE_BLINK);
	// 	Effects_Connectors_Colors (3, my_pixel1, MODE_DIMMER);
	// 	Effects_Connectors_Colors (4, my_pixel2, MODE_BLINK);
	// 	Effects_Connectors_Colors (5, my_pixel2, MODE_FIXT);
	// 	Effects_Connectors_Colors (6, my_pixel2, MODE_DIMMER);
	// 	Effects_Connectors_Colors (7, my_pixel2, MODE_FIXT);
	// 	Effects_Connectors_Colors (8, my_pixel3, MODE_DIMMER);

		
	// 	cnt++;
	//     }
	//     break;
	    
	// case 8:
	//     if (!timer_standby)
	//     {
	// 	cnt = 0;
	// 	Effects_White_No_Conn_Reset();
	// 	white_effect = 1;
	//     }
	//     break;
	// }

	// if (!white_effect)
	//     Effects_Update_All ();
    }
}

//--- End of Main ---//


// Other Module Functions ------------------------------------------------------

void TimingDelay_Decrement(void)
{
    if (wait_ms_var)
        wait_ms_var--;

    if (timer_standby)
        timer_standby--;

    Hard_Timeouts ();
    
    Effects_Timeouts();

    Connectors_Timeouts();
}


void SysTickError (void)
{
    //Capture systick error...
    while (1)
    {
        // if (LED)
        //     LED_OFF;
        // else
        //     LED_ON;

        for (unsigned char i = 0; i < 255; i++)
        {
            asm ("nop \n\t"
                 "nop \n\t"
                 "nop \n\t" );
        }
    }
}

//--- end of file ---//

