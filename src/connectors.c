//------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### CONNECTORS.C ###############################
//------------------------------------------------

// Includes --------------------------------------------------------------------
#include "connectors.h"
#include "effects.h"
#include "hard.h"
#include "usart.h"

// #include "neopixel_driver.h"
#include <stdio.h>


// Module Private Types Constants & Macros -------------------------------------
typedef enum {
    NO_CONN,
    ONE_CONN_FADING,
    TWO_CONN_FIXED,
    BAD_CONN_BLINKING

} conn_states;


typedef enum {
    LIGHT_NONE,
    LIGHT_FADING,
    LIGHT_FIXED,
    LIGHT_BLINKING_0,
    LIGHT_BLINKING_1

} light_values;


typedef enum {
    CONN_INIT,
    CONN_RPI_DISCONNECT,
    CONN_RPI_OK

} conn_rpi_state_e;



// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
volatile unsigned short connectors_timeout = 0;


// Module Private Functions ----------------------------------------------------
void Connectors_Light (unsigned char ch,
		       unsigned char * conn_ch_light);

unsigned char Connectors_IS_Get (void);
void Connectors_IS_Set (unsigned char new_is_state);


// Module Functions ------------------------------------------------------------
void Connectors_Timeouts (void)
{
    if (connectors_timeout)
	connectors_timeout--;
}


unsigned char last_connectors = 0;
void Connectors_Comms_Update (void)
{
    unsigned char send = 0;
    char buff[40];
    unsigned char current_connectors = 0;

    current_connectors |= S1_Plus_Is_On();
    current_connectors <<= 1;
    current_connectors |= S1_Neg_Is_On ();
    current_connectors <<= 1;

    current_connectors |= S2_Plus_Is_On();
    current_connectors <<= 1;
    current_connectors |= S2_Neg_Is_On ();
    current_connectors <<= 1;

    current_connectors |= S3_Plus_Is_On();
    current_connectors <<= 1;
    current_connectors |= S3_Neg_Is_On ();
    current_connectors <<= 1;

    current_connectors |= S4_Plus_Is_On();
    current_connectors <<= 1;
    current_connectors |= S4_Neg_Is_On ();

    if (current_connectors != last_connectors)
    {
	last_connectors = current_connectors;
	send = 1;
    }
    else if (!connectors_timeout)
	send = 1;
    
    if (send)
    {
	sprintf(buff, "conn 0x%02x 0x%02x\r\n", current_connectors, IS_Plus_Is_On ());
	Uart4Send(buff);
	connectors_timeout = 6000;
    }
}


void Connectors_Logic (unsigned char ch,
		       unsigned char * conn_ch_st,
		       unsigned char * conn_ch_light,
		       char * fading_ch)
{
    unsigned char conn_0 = 0;
    unsigned char conn_1 = 0;
    char who_fade = '\0';
    
    switch (ch)
    {
    case 0:
	if (IS_Plus_Is_On())
	    conn_0 = 1;
	else
	    conn_0 = S1_Plus_Is_On();

	// conn_0 = S1_Plus_Is_On();	
	conn_1 = S1_Neg_Is_On();
	who_fade = 'a';
	break;

    case 1:
	conn_0 = S2_Plus_Is_On();
	conn_1 = S2_Neg_Is_On();
	who_fade = 'b';	
	break;

    case 2:
	conn_0 = S3_Plus_Is_On();
	conn_1 = S3_Neg_Is_On();
	who_fade = 'c';	
	break;

    case 3:
	conn_0 = S4_Plus_Is_On();
	conn_1 = S4_Neg_Is_On();
	who_fade = 'd';	
	break;
    }
    
    switch (*conn_ch_st)
    {
    case NO_CONN:
	if (conn_0 || conn_1)
	{
	    // go forward if no fading on other channels
	    if (*fading_ch == '\0')
	    {
		*conn_ch_st = ONE_CONN_FADING;
		*conn_ch_light = LIGHT_FADING;
		*fading_ch = who_fade;
	    }
	    else if (conn_0)
	    {
		*conn_ch_st = BAD_CONN_BLINKING;
		*conn_ch_light = LIGHT_BLINKING_0;
	    }
	    else if (conn_1)
	    {
		*conn_ch_st = BAD_CONN_BLINKING;
		*conn_ch_light = LIGHT_BLINKING_1;
	    }
	}
	break;

    case ONE_CONN_FADING:
	if (conn_0 && conn_1)
	{
	    *conn_ch_st = TWO_CONN_FIXED;
	    *conn_ch_light = LIGHT_FIXED;
	    *fading_ch = '\0';		
	}

	if (!conn_0 && !conn_1)
	{
	    *conn_ch_st = NO_CONN;
	    *conn_ch_light = LIGHT_NONE;
	    if (*fading_ch == who_fade)
		*fading_ch = '\0';
	}
	break;

    case TWO_CONN_FIXED:
	if (!conn_0 || !conn_1)
	{
	    // if no other channel fading go fading, else blink error
	    if (*fading_ch == '\0')
	    {
		*conn_ch_st = ONE_CONN_FADING;
		*conn_ch_light = LIGHT_FADING;
		*fading_ch = who_fade;
	    }
	    else
	    {
		if (conn_0)
		{
		    *conn_ch_st = BAD_CONN_BLINKING;
		    *conn_ch_light = LIGHT_BLINKING_0;
		}
		else if (conn_1)
		{
		    *conn_ch_st = BAD_CONN_BLINKING;
		    *conn_ch_light = LIGHT_BLINKING_1;
		}
	    }
	}
	break;

    case BAD_CONN_BLINKING:
	if (!conn_0 && !conn_1)
	{
	    *conn_ch_st = NO_CONN;
	    *conn_ch_light = LIGHT_NONE;
	}
	break;

    default:
	*conn_ch_st = NO_CONN;
	break;
    }
}


void Connectors_Light (unsigned char ch,
		       unsigned char * conn_ch_light)
{
    pixel_t my_pixel;
    unsigned char c_pos = 0;
    unsigned char c_neg = 0;

    switch (ch)
    {
    case 0:
	if (IS_Plus_Is_On())
	{
	    c_pos = 0;
	    // c_null = 8;
	    my_pixel.R = 0;
	    my_pixel.G = 0;
	    my_pixel.B = 0;
	    Effects_Connectors_Colors (8, my_pixel, MODE_FIXT);
	}
	else
	{
	    c_pos = 8;
	    // c_null = 0;
	    my_pixel.R = 0;
	    my_pixel.G = 0;
	    my_pixel.B = 0;
	    Effects_Connectors_Colors (0, my_pixel, MODE_FIXT);
	}
	c_neg = 1;
	break;

    case 1:
	c_pos = 7;
	c_neg = 2;
	break;

    case 2:
	c_pos = 6;
	c_neg = 3;
	break;

    case 3:
	c_pos = 5;
	c_neg = 4;
	break;
    }
    
    switch(*conn_ch_light)
    {
    case LIGHT_NONE:
	my_pixel.R = 0;
	my_pixel.G = 0;
	my_pixel.B = 0;
	Effects_Connectors_Colors (c_pos, my_pixel, MODE_FIXT);
	Effects_Connectors_Colors (c_neg, my_pixel, MODE_FIXT);	
	break;

    case LIGHT_FADING:
	my_pixel.R = 0;
	my_pixel.G = 0;
	my_pixel.B = 255;
	Effects_Connectors_Colors (c_pos, my_pixel, MODE_DIMMER);
	Effects_Connectors_Colors (c_neg, my_pixel, MODE_DIMMER);	
	break;

    case LIGHT_FIXED:
	if (Connectors_Polarity_Get() == CONN_POLARITY_POS)
	{
	    my_pixel.R = 243;
	    my_pixel.G = 58;
	    my_pixel.B = 106;
	    Effects_Connectors_Colors (c_pos, my_pixel, MODE_FIXT);
	    my_pixel.R = 137;
	    my_pixel.G = 207;
	    my_pixel.B = 240;
	    Effects_Connectors_Colors (c_neg, my_pixel, MODE_FIXT);
	    break;
	}
	else if (Connectors_Polarity_Get() == CONN_POLARITY_NEG)
	{
	    my_pixel.R = 137;
	    my_pixel.G = 207;
	    my_pixel.B = 240;
	    Effects_Connectors_Colors (c_pos, my_pixel, MODE_FIXT);
	    my_pixel.R = 243;
	    my_pixel.G = 58;
	    my_pixel.B = 106;
	    Effects_Connectors_Colors (c_neg, my_pixel, MODE_FIXT);
	    break;
	    
	}
	
	my_pixel.R = 0;
	my_pixel.G = 255;
	my_pixel.B = 0;
	Effects_Connectors_Colors (c_pos, my_pixel, MODE_FIXT);
	Effects_Connectors_Colors (c_neg, my_pixel, MODE_FIXT);
	break;

    case LIGHT_BLINKING_0:
	my_pixel.R = 255;
	my_pixel.G = 0;
	my_pixel.B = 0;
	Effects_Connectors_Colors (c_pos, my_pixel, MODE_BLINK);
	break;

    case LIGHT_BLINKING_1:
	my_pixel.R = 255;
	my_pixel.G = 0;
	my_pixel.B = 0;
	Effects_Connectors_Colors (c_neg, my_pixel, MODE_BLINK);
	break;
    }
}


unsigned char connector_a = NO_CONN;
unsigned char connector_b = NO_CONN;
unsigned char connector_c = NO_CONN;
unsigned char connector_d = NO_CONN;

unsigned char connector_light_a = LIGHT_NONE;
unsigned char connector_light_b = LIGHT_NONE;
unsigned char connector_light_c = LIGHT_NONE;
unsigned char connector_light_d = LIGHT_NONE;

char fading_ch = '\0';
conn_rpi_state_e conn_rpi = CONN_INIT;
void Connectors_Update (void)
{
    switch (conn_rpi)
    {
    case CONN_INIT:
	conn_rpi++;
	connectors_timeout = 20000;
	Effects_White_No_Conn_Reset();
	break;

    case CONN_RPI_DISCONNECT:
	// if (connectors_timeout)
	//     break;

	// if (Connectors_Rpi_Is_Up())
	// {
	//     connectors_state++;
	// }
	
	Effects_White_No_Conn();

	if (!connectors_timeout)
	{
	    pixel_t my_pixel;
	    my_pixel.R = 0;
	    my_pixel.G = 0;
	    my_pixel.B = 0;
	    Effects_Connectors_Colors (0, my_pixel, MODE_FIXT);
	    conn_rpi++;
	}
	break;
	
    case CONN_RPI_OK:
	Connectors_Logic(0, &connector_a, &connector_light_a, &fading_ch);
	Connectors_Logic(1, &connector_b, &connector_light_b, &fading_ch);
	Connectors_Logic(2, &connector_c, &connector_light_c, &fading_ch);
	Connectors_Logic(3, &connector_d, &connector_light_d, &fading_ch);

	// update connectors pixels
	Connectors_Light(0, &connector_light_a);
	Connectors_Light(1, &connector_light_b);
	Connectors_Light(2, &connector_light_c);
	Connectors_Light(3, &connector_light_d);	

	Effects_Update_All ();

	Connectors_Comms_Update();

	if (IS_Plus_Is_On ())
	{
	    if (!Connectors_IS_Get())
	    {
		Connectors_IS_Set(1);
		Probe_Change_With_Delay();
	    }
	}
	else
	{
	    if (Connectors_IS_Get())
	    {
		Connectors_IS_Set(0);
		Probe_Change_With_Delay();
	    }
	}

	// if (!Connectors_Rpi_Get())
	// {
	//     conn_rpi = CONN_INIT;
	// }
	break;
    }
}


unsigned char connectors_rpi_is_up = 0;
unsigned char Connectors_Rpi_Get (void)
{
    return connectors_rpi_is_up;
}


void Connectors_Rpi_Set (unsigned char new_rpi_state)
{
    connectors_rpi_is_up = new_rpi_state;
}


conn_polarity_e conn_pol = CONN_POLARITY_UNKNOW;
conn_polarity_e Connectors_Polarity_Get (void)
{
    return conn_pol;
}


void Connectors_Polarity_Set (conn_polarity_e new_polarity)
{
    conn_pol = new_polarity;
}


unsigned char connectors_is_set = 0;
unsigned char Connectors_IS_Get (void)
{
    return connectors_is_set;
}


void Connectors_IS_Set (unsigned char new_is_state)
{
    connectors_is_set = new_is_state;
}


void Connectors_Send_Present (void)
{
    char buff[40];
    sprintf(buff, "conn 0x%02x 0x%02x\r\n", last_connectors, IS_Plus_Is_On ());
    Uart4Send(buff);
}

//--- end of file ---//
