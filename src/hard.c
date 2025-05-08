//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.C #################################
//---------------------------------------------
#include "hard.h"
#include "stm32f10x.h"

// #include <stdio.h>


// Module Private Types Constants and Macros -----------------------------------
#define SWITCHES_ROOF    60
#define SWITCHES_THRESHOLD    50


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
volatile unsigned char s1p_cnt = 0;
volatile unsigned char s2p_cnt = 0;
volatile unsigned char s3p_cnt = 0;
volatile unsigned char s4p_cnt = 0;
volatile unsigned char s1n_cnt = 0;
volatile unsigned char s2n_cnt = 0;
volatile unsigned char s3n_cnt = 0;
volatile unsigned char s4n_cnt = 0;
volatile unsigned char isp_cnt = 0;


// Module Private Functions ----------------------------------------------------
void Hard_Update_Counter (unsigned char value,
			  volatile unsigned char * counter);


// Module Functions ------------------------------------------------------------
void Hard_Timeouts (void)
{
    Hard_Update_Counter (S1_PLUS, &s1p_cnt);
    Hard_Update_Counter (S2_PLUS, &s2p_cnt);
    Hard_Update_Counter (S3_PLUS, &s3p_cnt);
    Hard_Update_Counter (S4_PLUS, &s4p_cnt);
    Hard_Update_Counter (S1_NEG, &s1n_cnt);
    Hard_Update_Counter (S2_NEG, &s2n_cnt);
    Hard_Update_Counter (S3_NEG, &s3n_cnt);
    Hard_Update_Counter (S4_NEG, &s4n_cnt);
    Hard_Update_Counter (IS_PLUS, &isp_cnt);
}


void Hard_Update_Counter (unsigned char value,
			  volatile unsigned char * counter)
{
    if (value)
    {
	if (*counter < SWITCHES_ROOF)
	    *counter +=1;
    }
    else
    {
	if (*counter)
	    *counter -=1;
    }
}


unsigned char S1_Plus_Is_On (void)
{
    if (s1p_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S2_Plus_Is_On (void)
{
    if (s2p_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S3_Plus_Is_On (void)
{
    if (s3p_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S4_Plus_Is_On (void)
{
    if (s4p_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S1_Neg_Is_On (void)
{
    if (s1n_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S2_Neg_Is_On (void)
{
    if (s2n_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S3_Neg_Is_On (void)
{
    if (s3n_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char S4_Neg_Is_On (void)
{
    if (s4n_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char IS_Plus_Is_On (void)
{
    if (isp_cnt >= SWITCHES_THRESHOLD)
	return 1;
    
    return 0;
}

unsigned char Probe_Act_Is_On (void)
{
    return PROBE_ACT;
}


void Probe_Act_On (void)
{
    PROBE_ACT_ON;
}


void Probe_Act_Off (void)
{
    PROBE_ACT_OFF;
}

//--- end of file ---//
