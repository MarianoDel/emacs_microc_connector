//---------------------------------------------
// ##
// ## @Author: Med
// ## @Editor: Emacs - ggtags
// ## @TAGS:   Global
// ## @CPU:    STM32F103
// ##
// #### HARD.H #################################
//---------------------------------------------

#ifndef HARD_H_
#define HARD_H_


//----------- Defines For Configuration -------------

//----- Board Configuration -------------------//
//--- Hardware ------------------//
#define HARDWARE_VERSION_1_0    // first prototype


//--- Software ------------------//
#define FIRMWARE_VERSION_1_0    // init version


//-------- Type of Program (depending on software version) ----------------


//--- Serial Number / Device Id Bytes length ----------
#define USE_DEVICE_ID_4BYTES
// #define USE_DEVICE_ID_12BYTES



//-------- Oscillator and Crystal selection (Freq in startup_clocks.h) ---
#define HSI_INTERNAL_RC
// #define HSE_CRYSTAL_OSC

#ifdef HSE_CRYSTAL_OSC
// #define CRYSTAL_8MHZ
#define CRYSTAL_12MHZ
#endif

#ifdef HSE_CRYSTAL_OSC
// #define SYSCLK_FREQ_72MHz
#define SYSCLK_FREQ_8MHz
#endif

#ifdef HSI_INTERNAL_RC
#define SYSCLK_FREQ_64MHz
// #define SYSCLK_FREQ_8MHz
#endif

//-------- End Of Defines For Configuration ------




//--- Hardware & Software Messages ------------------//
// #ifdef HARDWARE_VERSION_2_0
// #define HARD "Hardware Version: 2.0"
// #endif
// #ifdef HARDWARE_VERSION_1_0
// #define HARD "Hardware Version: 1.0"
// #endif
// #ifdef FIRMWARE_VERSION_1_0
// #define SOFT "Firmware Version: 1.0"
// #endif
//--- End of Hardware & Software Messages ------------------//



// Exported Types --------------------------------------------------------------
// PA defines ----
// PA0 
// PA1 NC

// PA2
#define S1_NEG    ((GPIOA->IDR & 0x0004) == 0)

// PA3
#define S1_PLUS    ((GPIOA->IDR & 0x0008) == 0)

// PA4 
// PA5 
// PA6 NC

// PA7 Alternative TIM3_CH2

// PA8
// PA9 NC

// PA10
#define PROBE_ACT    ((GPIOA->ODR & 0x0400) != 0)
#define PROBE_ACT_ON    (GPIOA->BSRR = 0x00000400)
#define PROBE_ACT_OFF    (GPIOA->BSRR = 0x04000000)

// PA11
// PA12 NC
// PA13 PA14 PA15 NC jtag

// PB defines ----
// PB0 
// PB1
// PB2
// PB3 PB4 NC jtag
// PB5 NC

// PB6 
#define IS_PLUS    ((GPIOB->IDR & 0x0040) == 0)

// PB7
// PB8
// PB9
// PB10
// PB11 NC

// PB12
#define S3_PLUS    ((GPIOB->IDR & 0x1000) == 0)

// PB13
#define S3_NEG    ((GPIOB->IDR & 0x2000) == 0)

// PB14
// PB15 NC

// PC defines ----
// PC0
// PC1 NC

// PC2
#define S2_NEG    ((GPIOC->IDR & 0x0004) == 0)

// PC3
#define S2_PLUS    ((GPIOC->IDR & 0x0008) == 0)

// PC4
// PC5 NC

// PC6
#define S4_NEG    ((GPIOC->IDR & 0x0040) == 0)

// PC7
#define S4_PLUS    ((GPIOC->IDR & 0x0080) == 0)

// PC8
// PC9

// PC10 Alternative Uart4 Tx
// PC11 Alternative Uart4 Rx

// PC12
// PC13
// PC14
// PC15 NC

// PD defines ----
// PD0
// PD1
// PD2 NC 



//--- Exported Module Functions ------------------------------------------------
unsigned char S1_Plus_Is_On (void);
unsigned char S2_Plus_Is_On (void);
unsigned char S3_Plus_Is_On (void);
unsigned char S4_Plus_Is_On (void);
unsigned char S1_Neg_Is_On (void);
unsigned char S2_Neg_Is_On (void);
unsigned char S3_Neg_Is_On (void);
unsigned char S4_Neg_Is_On (void);
unsigned char IS_Plus_Is_On (void);
unsigned char Probe_Act_Is_On (void);
void Probe_Act_On (void);
void Probe_Act_Off (void);

#endif    /* HARD_H_ */
