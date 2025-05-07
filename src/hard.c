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


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------


// Module Private Functions ----------------------------------------------------


// Module Functions ------------------------------------------------------------
unsigned char S1_Plus_Is_On (void)
{
    return S1_PLUS;
}

unsigned char S2_Plus_Is_On (void)
{
    return S2_PLUS;
}

unsigned char S3_Plus_Is_On (void)
{
    return S3_PLUS;
}

unsigned char S4_Plus_Is_On (void)
{
    return S4_PLUS;
}

unsigned char S1_Neg_Is_On (void)
{
    return S1_NEG;
}

unsigned char S2_Neg_Is_On (void)
{
    return S2_NEG;
}

unsigned char S3_Neg_Is_On (void)
{
    return S3_NEG;
}

unsigned char S4_Neg_Is_On (void)
{
    return S4_NEG;
}

unsigned char IS_Plus_Is_On (void)
{
    return IS_PLUS;
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
