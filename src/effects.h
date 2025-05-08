//------------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ##
// #### EFFECTS.H ###############################
//------------------------------------------------

// Prevent recursive inclusion -------------------------------------------------
#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include "neopixel.h"

// Module Exported Types Constants and Macros ----------------------------------
typedef enum {
    MODE_DIMMER,
    MODE_FIXT,
    MODE_BLINK

} conn_mode_e;


// Module Exported Functions ---------------------------------------------------
void Effects_Timeouts (void);
void Effects_White_No_Conn_Reset (void);
void Effects_White_No_Conn (void);
void Effects_Connectors_Colors (unsigned char conn,
				pixel_t new_pixel,
				conn_mode_e mode);


#endif    /* _EFFECTS_H_ */

//--- end of file ---//

