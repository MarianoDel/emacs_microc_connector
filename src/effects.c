//------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### EFFECTS.C ###############################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "effects.h"
#include "neopixel.h"
#include "neopixel_driver.h"


// Module Private Types Constants & Macros -------------------------------------
typedef enum {
    EFFECT_L0,
    EFFECT_L1,
    EFFECT_L2,
    EFFECT_L3,
    EFFECT_L4,
    EFFECT_L5,
    EFFECT_L6,
    EFFECT_L7

} effects_state_e;

// flags for connectors effects
#define dimmer_flag    0x01
#define update_flag    0x80
#define fixt_flag    0x02
#define blink_flag    0x04


typedef struct {
    unsigned char mode_flag;
    pixel_t pixel;
} connect_st;


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
volatile unsigned short effects_timer = 0;
volatile unsigned short effects_blink_timer = 0;
volatile unsigned short effects_dimmer_timer = 0;
volatile unsigned char dimmer_cnt = 0;
volatile unsigned char dimmer_dir = 0;
volatile unsigned char blink_value = 0;
volatile unsigned char effects_update_dimmer = 0;
volatile unsigned char effects_update_blink = 0;
effects_state_e effects_state = EFFECT_L0;

connect_st connectors_array [9];


// Module Private Functions ----------------------------------------------------
void Effects_Change_Connectors_Colors (unsigned char conn, pixel_t new_pixel);



// Module Functions ------------------------------------------------------------
void Effects_Timeouts (void)
{
    if (effects_timer)
	effects_timer--;

    if (effects_blink_timer)
	effects_blink_timer--;
    else
    {
	effects_blink_timer = 500;
	effects_update_blink = 1;
	if (blink_value)
	    blink_value = 0;
	else
	    blink_value = 1;
	
    }

    if (effects_dimmer_timer)
	effects_dimmer_timer--;
    else
    {
	effects_update_dimmer = 1;
	effects_dimmer_timer = 3;
	if (dimmer_dir)
	{
	    if (dimmer_cnt < 255)
		dimmer_cnt++;
	    else
		dimmer_dir = 0;
	}
	else
	{
	    if (dimmer_cnt)
		dimmer_cnt--;
	    else
		dimmer_dir = 1;
	}
    }
}


void Effects_White_No_Conn_Reset (void)
{
    pixel_t my_pixel;
    
    effects_state = EFFECT_L0;

    my_pixel.R = 0;
    my_pixel.G = 0;
    my_pixel.B = 0;

    // start entire buffer with null color
    for (int i = 0; i < 72; i++)
	Neo_Set_Pixel(i, &my_pixel);
    
}


void Effects_White_No_Conn (void)
{
    pixel_t my_pixel;

    if (effects_timer)
	return;

    effects_timer = 1500;

    my_pixel.R = 0;
    my_pixel.G = 0;
    my_pixel.B = 0;

    // start entire buffer with null color
    for (int i = 0; i < 72; i++)
	Neo_Set_Pixel(i, &my_pixel);
    
    my_pixel.R = 42;
    my_pixel.G = 42;
    my_pixel.B = 42;

    switch(effects_state)
    {
    case EFFECT_L0:
	for (int i = 0; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L1:
	for (int i = 1; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);

	effects_state++;
	break;

    case EFFECT_L2:
	for (int i = 2; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L3:
	for (int i = 3; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L4:
	for (int i = 4; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L5:
	for (int i = 5; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L6:
	for (int i = 6; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state++;
	break;

    case EFFECT_L7:
	for (int i = 7; i < 72; i+=8)
	    Neo_Set_Pixel(i, &my_pixel);
	
	effects_state = EFFECT_L0;
	break;
	
    }
    
    Neo_Driver_Send_Pixel_Data();

}


void Effects_Connectors_Colors (unsigned char conn,
				pixel_t new_pixel,
				conn_mode_e mode)
{
    connectors_array[conn].pixel.R = new_pixel.R;
    connectors_array[conn].pixel.G = new_pixel.G;
    connectors_array[conn].pixel.B = new_pixel.B;

    switch (mode)
    {
    case MODE_DIMMER:
	connectors_array[conn].mode_flag = dimmer_flag;
	break;

    case MODE_FIXT:
	connectors_array[conn].mode_flag = fixt_flag | update_flag;	
	break;

    case MODE_BLINK:
	connectors_array[conn].mode_flag = blink_flag;
	break;

    default:
	connectors_array[conn].mode_flag = fixt_flag | update_flag;
	break;
    }
}


void Effects_Change_Connectors_Colors (unsigned char conn, pixel_t new_pixel)
{
    unsigned char pix_base = conn * 8;
    for (int i = pix_base; i < (pix_base + 8); i++)
	Neo_Set_Pixel(i, &new_pixel);

}


void Effects_Update_All (void)
{
    unsigned char update_done = 0;
    
    if (!effects_update_dimmer)
	return;
    
    effects_update_dimmer = 0;

    // check dimmer or update on all connectors
    for (int i = 0; i < 9; i++)
    {
	unsigned char mode;
	unsigned short calc;
	pixel_t new_pixel;
	
	mode = connectors_array[i].mode_flag;

	if (mode & update_flag)
	{
	    connectors_array[i].mode_flag &= ~(update_flag);
	    Effects_Change_Connectors_Colors (i, connectors_array[i].pixel);
	    update_done = 1;
	}
	else if (mode & dimmer_flag)
	{
	    calc = connectors_array[i].pixel.R * dimmer_cnt;
	    new_pixel.R = calc >> 8;
	    calc = connectors_array[i].pixel.G * dimmer_cnt;
	    new_pixel.G = calc >> 8;
	    calc = connectors_array[i].pixel.B * dimmer_cnt;
	    new_pixel.B = calc >> 8;

	    Effects_Change_Connectors_Colors (i, new_pixel);
	    update_done = 1;	    
	}
	else if (mode & blink_flag)
	{
	    if (effects_update_blink)
	    {
		if (blink_value)
		    Effects_Change_Connectors_Colors (i, connectors_array[i].pixel);
		else
		{
		    new_pixel.R = 0;
		    new_pixel.G = 0;
		    new_pixel.B = 0;

		    Effects_Change_Connectors_Colors (i, new_pixel);
		}
		update_done = 1;
	    }
	}
    }

    // all blinks update done
    if (effects_update_blink)
	effects_update_blink = 0;

    if (update_done)
	Neo_Driver_Send_Pixel_Data();

}






// void Effects_All_Connectors (unsigned char conn,
// 				pixel_t new_pixel,
// 				unsigned char mode)
// {
//     unsigned short calc;
//     switch (mode)
//     {
//     case MODE_DIMMER:
// 	calc = new_pixel.R * dimmer_cnt;
// 	new_pixel.R = calc >> 8;
// 	calc = new_pixel.G * dimmer_cnt;
// 	new_pixel.G = calc >> 8;
// 	calc = new_pixel.B * dimmer_cnt;
// 	new_pixel.B = calc >> 8;
// 	break;

//     case MODE_FIXT:
// 	break;

//     case MODE_BLINK:
// 	if (!blink_value)
// 	{
// 	    new_pixel.R = 0;
// 	    new_pixel.G = 0;
// 	    new_pixel.B = 0;
// 	}
// 	break;
//     }

//     unsigned char pix_base = conn * 8;
//     for (int i = pix_base; i < (pix_base + 8); i++)
// 	Neo_Set_Pixel(i, &new_pixel);

// }

//--- end of file ---//
