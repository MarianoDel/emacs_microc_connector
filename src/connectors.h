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


// Module Exported Functions ---------------------------------------------------
void Connectors_Update (void);
void Connectors_Timeouts (void);
unsigned char Connectors_Rpi_Get (void);
void Connectors_Rpi_Set (unsigned char new_rpi_state);


#endif    /* _CONNECTORS_H_ */

//--- end of file ---//

