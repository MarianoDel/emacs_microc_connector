//----------------------------------------------------------
// #### MAGNET PROJECT - Custom Board ####
// ## Internal Test Functions Module
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### TEST_FUNCTIONS.C ###################################
//----------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "test_functions.h"
#include "hard.h"
#include "stm32f10x.h"
#include "gpio.h"
#include "usart.h"
#include "dma.h"
#include "tim.h"

#include "neopixel.h"
#include "neopixel_driver.h"

#include <stdio.h>
#include <string.h>


// Externals -------------------------------------------------------------------
extern volatile unsigned short wait_ms_var;
extern volatile unsigned short timer_standby;


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------
void TF_Probe_Act (void);
void TF_Tim3_Ch2_NeoPixel_1_Enable (void);
void TF_Tim3_Ch2_NeoPixel_72_Enable (void);


// Module Functions ------------------------------------------------------------
void TF_Hardware_Tests (void)
{
    // TF_Probe_Act ();

    // TF_Tim3_Ch2_NeoPixel_1_Enable ();

    TF_Tim3_Ch2_NeoPixel_72_Enable ();
    
}


void TF_Probe_Act (void)
{
    while (1)
    {
	if (Probe_Act_Is_On())
	    Probe_Act_Off();
	else
	    Probe_Act_On();

	Wait_ms (5000);
    }
}




// place a shortcut on IC4 2 & IC3 4
void TF_Uart4_Loop (void)
{
    char buff [100];
    
    Uart4Config();
    
    while (1)
    {
        if (!timer_standby)
        {
            Uart4Send("Mariano\n");
            timer_standby = 2000;
            // if (Led_Is_On())
            //     Led_Off();
        }

        if (Uart4HaveData())
        {
            Uart4HaveDataReset();
            Uart4ReadBuffer(buff, 100);
            if (strncmp(buff, "Mariano", sizeof("Mariano") - 1) == 0);
                // Led_On();
        }
    }
}



void TF_Tim3_Ch2_NeoPixel_1_Enable (void)
{
    unsigned char cnt = 0;
    pixel_t my_pixel;

    TIM3_Init();

    my_pixel.R = 0;
    my_pixel.G = 0;
    my_pixel.B = 0;

    // start entire buffer with null color
    Neo_Set_Pixel(0, &my_pixel);

    while (1)
    {
	// Led_On();
	switch (cnt)
	{
	case 0:
	    cnt++;
	    my_pixel.R = 255;
	    my_pixel.G = 0;
	    my_pixel.B = 0;
	    break;
	    
	case 1:
	    cnt++;
	    my_pixel.R = 0;
	    my_pixel.G = 255;
	    my_pixel.B = 0;
	    break;

	case 2:
	    cnt = 0;
	    my_pixel.R = 0;
	    my_pixel.G = 0;
	    my_pixel.B = 255;
	    break;
	}
	
	Neo_Set_Pixel(0, &my_pixel);
	Neo_Driver_Send_Pixel_Data();
	Wait_ms(100);
	// Led_Off();
	Wait_ms(1900);	
    }
}


void TF_Tim3_Ch2_NeoPixel_72_Enable (void)
{
    unsigned char cnt = 0;
    pixel_t my_pixel;

    TIM3_Init();

    my_pixel.R = 0;
    my_pixel.G = 0;
    my_pixel.B = 0;

    // start entire buffer with null color
    for (int i = 0; i < 72; i++)
	Neo_Set_Pixel(i, &my_pixel);

    while (1)
    {

	switch (cnt)
	{
	case 0:
	    cnt++;
	    my_pixel.R = 255;
	    my_pixel.G = 0;
	    my_pixel.B = 0;
	    break;
	    
	case 1:
	    cnt++;
	    my_pixel.R = 0;
	    my_pixel.G = 255;
	    my_pixel.B = 0;
	    break;

	case 2:
	    cnt++;
	    my_pixel.R = 0;
	    my_pixel.G = 0;
	    my_pixel.B = 255;
	    break;

	case 3:
	    cnt = 0;
	    my_pixel.R = 85;
	    my_pixel.G = 85;
	    my_pixel.B = 85;
	    break;
	}

	my_pixel.R = my_pixel.R >> 1;
	my_pixel.G = my_pixel.G >> 1;
	my_pixel.B = my_pixel.B >> 1;
	
	for (int i = 0; i < 72; i++)
	    Neo_Set_Pixel(i, &my_pixel);
	
	Neo_Driver_Send_Pixel_Data();
	Wait_ms(2000);	
    }
}


// void TF_Tim3_Ch2_NeoPixel_64_Enable (void)
// {
//     pixel_t my_pixel;

//     TIM3_Init();

//     my_pixel.R = 0;
//     my_pixel.G = 0;
//     my_pixel.B = 0;

//     // start entire buffer with null color
//     for (int i = 0; i < 64; i++)
// 	Neo_Set_Pixel(i, &my_pixel);

//     unsigned char connector_a = NO_CONN;
//     unsigned char connector_b = NO_CONN;
//     unsigned char connector_c = NO_CONN;
//     unsigned char connector_d = NO_CONN;

//     unsigned char connector_light_a = LIGHT_NONE;
//     unsigned char connector_light_b = LIGHT_NONE;
//     unsigned char connector_light_c = LIGHT_NONE;
//     unsigned char connector_light_d = LIGHT_NONE;

//     char fading_ch = '\0';
//     unsigned char blink_value = 0;
//     unsigned short blink_cnt = 0;

//     while (1)
//     {
// 	TF_Connector_Logic(0, &connector_a, &connector_light_a, &fading_ch);
// 	TF_Connector_Logic(1, &connector_b, &connector_light_b, &fading_ch);
// 	TF_Connector_Logic(2, &connector_c, &connector_light_c, &fading_ch);
// 	TF_Connector_Logic(3, &connector_d, &connector_light_d, &fading_ch);

// 	if (!timer_led)
// 	{
// 	    timer_led = 3;

// 	    // update dimmer value
// 	    TF_Dimmer_Counter_Update();
// 	}
	
// 	if (!timer_standby)
// 	{
// 	    timer_standby = 10;

// 	    // get dimmer value
// 	    unsigned char dim = 0;
// 	    dim = TF_Dimmer_Get_Counter();

// 	    // update blink value
// 	    if (blink_cnt)
// 		blink_cnt--;
// 	    else
// 	    {
// 		blink_cnt = 50;
// 		if (blink_value)
// 		    blink_value = 0;
// 		else
// 		    blink_value = 255;
// 	    }

// 	    // update pixel memory
// 	    TF_Connector_Light(0,
// 			       &connector_light_a,
// 			       dim,
// 			       blink_value);

// 	    TF_Connector_Light(1,
// 			       &connector_light_b,
// 			       dim,
// 			       blink_value);

// 	    TF_Connector_Light(2,
// 			       &connector_light_c,
// 			       dim,
// 			       blink_value);

// 	    TF_Connector_Light(3,
// 			       &connector_light_d,
// 			       dim,
// 			       blink_value);

// 	    //send pixel data
// 	    TF_Send_Pixel_Data();
// 	}

// 	// send connection data every 6 secs. or on a change
// 	TF_Send_Connection_Data ();

// 	// update comms with mainbrd
// 	TF_Comms_Update ();
//     }
// }


// void TF_Connector_Light (unsigned char ch,
// 			 unsigned char * conn_ch_light,
// 			 unsigned char dimmer_cnt,
// 			 unsigned char blink_value)			 
// {
//     pixel_t my_pixel;
//     unsigned char posi_0 = 0;
//     unsigned char posi_1 = 0;    
    
//     switch (ch)
//     {
//     case 0:
// 	posi_0 = 24;
// 	posi_1 = 32;
// 	break;

//     case 1:
// 	posi_0 = 23;
// 	posi_1 = 40;
// 	break;

//     case 2:
// 	posi_0 = 15;
// 	posi_1 = 48;
// 	break;

//     case 3:
// 	posi_0 = 7;
// 	posi_1 = 63;
// 	break;
//     }

//     switch(*conn_ch_light)
//     {
//     case LIGHT_NONE:
// 	my_pixel.R = 0;
// 	my_pixel.G = 0;
// 	my_pixel.B = 0;
// 	Neo_Set_Pixel(posi_0, &my_pixel);
// 	Neo_Set_Pixel(posi_1, &my_pixel);	
// 	break;

//     case LIGHT_FADING:
// 	// my_pixel.R = 0;
// 	// my_pixel.G = dimmer_cnt;
// 	// my_pixel.B = 0;
// 	my_pixel.R = 0;
// 	my_pixel.G = 0;
// 	my_pixel.B = dimmer_cnt;
// 	Neo_Set_Pixel(posi_0, &my_pixel);
// 	Neo_Set_Pixel(posi_1, &my_pixel);	
// 	break;

//     case LIGHT_FIXED:
// 	my_pixel.R = 0;
// 	my_pixel.G = 255;
// 	my_pixel.B = 0;
// 	Neo_Set_Pixel(posi_0, &my_pixel);
// 	Neo_Set_Pixel(posi_1, &my_pixel);	
// 	break;

//     case LIGHT_BLINKING_0:
// 	my_pixel.R = blink_value;
// 	my_pixel.G = 0;
// 	my_pixel.B = 0;

// 	Neo_Set_Pixel(posi_0, &my_pixel);
// 	break;

//     case LIGHT_BLINKING_1:
// 	my_pixel.R = blink_value;
// 	my_pixel.G = 0;
// 	my_pixel.B = 0;

// 	Neo_Set_Pixel(posi_1, &my_pixel);	
// 	break;
//     }
// }


// unsigned char last_connectors = 0;
// void TF_Send_Connection_Data (void)
// {
//     unsigned char send = 0;
//     char buff[40];
//     unsigned char current_connectors = 0;

//     current_connectors |= Conn_D1();
//     current_connectors <<= 1;
//     current_connectors |= Conn_D0();
//     current_connectors <<= 1;
//     current_connectors |= Conn_C1();
//     current_connectors <<= 1;
//     current_connectors |= Conn_C0();
//     current_connectors <<= 1;
//     current_connectors |= Conn_B1();
//     current_connectors <<= 1;
//     current_connectors |= Conn_B0();
//     current_connectors <<= 1;
//     current_connectors |= Conn_A1();
//     current_connectors <<= 1;
//     current_connectors |= Conn_A0();

//     if (current_connectors != last_connectors)
//     {
// 	last_connectors = current_connectors;
// 	send = 1;
//     }
//     else if (!timer_connectors)
// 	send = 1;
    
//     if (send)
//     {
// 	sprintf(buff, "conn 0x%02x 0x%02x\r\n", current_connectors, Conn_D1());
// 	Usart3Send(buff);
// 	timer_connectors = 6000;
//     }
// }


// void TF_Connector_Logic (unsigned char ch,
// 			 unsigned char * conn_ch_st,
// 			 unsigned char * conn_ch_light,
// 			 char * fading_ch)
// {
//     unsigned char conn_0 = 0;
//     unsigned char conn_1 = 0;
//     char who_fade = '\0';
    
//     switch (ch)
//     {
//     case 0:
// 	conn_0 = Conn_A0();
// 	conn_1 = Conn_A1();
// 	who_fade = 'a';
// 	break;

//     case 1:
// 	conn_0 = Conn_B0();
// 	conn_1 = Conn_B1();
// 	who_fade = 'b';	
// 	break;

//     case 2:
// 	conn_0 = Conn_C0();
// 	conn_1 = Conn_C1();
// 	who_fade = 'c';	
// 	break;

//     case 3:
// 	conn_0 = Conn_D0();
// 	conn_1 = Conn_D1();
// 	who_fade = 'd';	
// 	break;
//     }
    
//     switch (*conn_ch_st)
//     {
//     case NO_CONN:
// 	if (conn_0 || conn_1)
// 	{
// 	    // go forward if no fading on other channels
// 	    if (*fading_ch == '\0')
// 	    {
// 		*conn_ch_st = ONE_CONN_FADING;
// 		*conn_ch_light = LIGHT_FADING;
// 		*fading_ch = who_fade;
// 	    }
// 	    else if (conn_0)
// 	    {
// 		*conn_ch_st = BAD_CONN_BLINKING;
// 		*conn_ch_light = LIGHT_BLINKING_0;
// 	    }
// 	    else if (conn_1)
// 	    {
// 		*conn_ch_st = BAD_CONN_BLINKING;
// 		*conn_ch_light = LIGHT_BLINKING_1;
// 	    }
// 	}
// 	break;

//     case ONE_CONN_FADING:
// 	if (conn_0 && conn_1)
// 	{
// 	    *conn_ch_st = TWO_CONN_FIXED;
// 	    *conn_ch_light = LIGHT_FIXED;
// 	    *fading_ch = '\0';		
// 	}

// 	if (!conn_0 && !conn_1)
// 	{
// 	    *conn_ch_st = NO_CONN;
// 	    *conn_ch_light = LIGHT_NONE;
// 	    if (*fading_ch == who_fade)
// 		*fading_ch = '\0';
// 	}
// 	break;

//     case TWO_CONN_FIXED:
// 	if (!conn_0 || !conn_1)
// 	{
// 	    // if no other channel fading go fading, else blink error
// 	    if (*fading_ch == '\0')
// 	    {
// 		*conn_ch_st = ONE_CONN_FADING;
// 		*conn_ch_light = LIGHT_FADING;
// 		*fading_ch = who_fade;
// 	    }
// 	    else
// 	    {
// 		if (conn_0)
// 		{
// 		    *conn_ch_st = BAD_CONN_BLINKING;
// 		    *conn_ch_light = LIGHT_BLINKING_0;
// 		}
// 		else if (conn_1)
// 		{
// 		    *conn_ch_st = BAD_CONN_BLINKING;
// 		    *conn_ch_light = LIGHT_BLINKING_1;
// 		}
// 	    }
// 	}
// 	break;

//     case BAD_CONN_BLINKING:
// 	if (!conn_0 && !conn_1)
// 	{
// 	    *conn_ch_st = NO_CONN;
// 	    *conn_ch_light = LIGHT_NONE;
// 	}
// 	break;

//     default:
// 	*conn_ch_st = NO_CONN;
// 	break;
//     }
// }




//--- end of file ---//
