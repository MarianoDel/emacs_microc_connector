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
    
    // // --- start supply manager
    Uart4Send("\r\n -- Connectors Board ver 1.0 init --\r\n");
    
    while (1)
    {

	Comms_Update ();

	Connectors_Update ();

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

