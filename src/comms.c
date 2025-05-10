//---------------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### COMMS.C ###########################################
//---------------------------------------------------------

// Includes --------------------------------------------------------------------
#include "comms.h"
// #include "hard.h"
#include "usart.h"
#include "connectors.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Module Private Types Constants and Macros -----------------------------------
char s_ans_ok [] = {"ok\n"};
char s_ans_nok [] = {"nok\n"};
#define SIZEOF_COMMS_BUFF    128
#define COMMS_TT_RELOAD    3000


// Externals -------------------------------------------------------------------


// Globals ---------------------------------------------------------------------
char comms_buff [SIZEOF_COMMS_BUFF];
    

// Module Private Functions ----------------------------------------------------
static void Comms_Messages (char * msg_str);


// Module Functions ------------------------------------------------------------
void Comms_Update (void)
{
    if (Uart4HaveData())
    {
        Uart4HaveDataReset();
        Uart4ReadBuffer(comms_buff, SIZEOF_COMMS_BUFF);
        Comms_Messages(comms_buff);
    }
}


static void Comms_Messages (char * msg_str)
{
    // char buff [128];    
    
    if (strncmp (msg_str, "polarity pos", sizeof("polarity pos") - 1) == 0)
    {
	Connectors_Polarity_Set(CONN_POLARITY_POS);
    }

    else if (strncmp (msg_str, "polarity neg", sizeof("polarity neg") - 1) == 0)
    {
	Connectors_Polarity_Set(CONN_POLARITY_NEG);
    }

    else if (strncmp (msg_str, "polarity alt", sizeof("polarity alt") - 1) == 0)
    {
	Connectors_Polarity_Set(CONN_POLARITY_ALT);
    }
    
    else if (strncmp (msg_str, "rpi is up", sizeof("rpi is up") - 1) == 0)
    {
	Connectors_Rpi_Set(1);
    }
    else if (strncmp (msg_str, "rpi is down", sizeof("rpi is down") - 1) == 0)
    {
	Connectors_Rpi_Set(0);
    }
    // else
    //     Uart4Send(s_ans_nok);

}


//---- End of File ----//
