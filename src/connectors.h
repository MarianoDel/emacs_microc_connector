//------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### CONNECTORS.H ###############################
//------------------------------------------------

// Prevent recursive inclusion -------------------------------------------------
#ifndef _CONNECTORS_H_
#define _CONNECTORS_H_

// #include "neopixel.h"

// Module Exported Types Constants and Macros ----------------------------------
typedef enum {
    CONN_POLARITY_UNKNOW,
    CONN_POLARITY_POS,
    CONN_POLARITY_NEG,
    CONN_POLARITY_ALT

} conn_polarity_e;


// Module Exported Functions ---------------------------------------------------
void Connectors_Update (void);
void Connectors_Timeouts (void);
unsigned char Connectors_Rpi_Get (void);
void Connectors_Rpi_Set (unsigned char new_rpi_state);
conn_polarity_e Connectors_Polarity_Get (void);
void Connectors_Polarity_Set (conn_polarity_e new_polarity);
void Connectors_Send_Present (void);


#endif    /* _CONNECTORS_H_ */

//--- end of file ---//

