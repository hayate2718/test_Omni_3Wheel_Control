/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

/*
 spi2 test
 |pin_num|func|
 |---|---|
 |ra7|sck2|
 |rc2|ss2|
 |ra8|sdi2|
 |rb4|sdo2|
 */

#include <string.h>

#define LED_R PORTDbits.RD8
#define LED_G PORTCbits.RC10

volatile static uint8_t SPI2_Rxdata[8] = {0};

typedef union{
    struct{
        uint8_t bit_0 : 1; //right
        uint8_t bit_1 : 1; //down
        uint8_t bit_2 : 1; //up
        uint8_t bit_3 : 1; //left
        uint8_t bit_4 : 1; //square
        uint8_t bit_5 : 1; //Cross
        uint8_t bit_6 : 1; //Circle
        uint8_t bit_7 : 1; //Triangle
        uint8_t bit_8 : 1; //L1
        uint8_t bit_9 : 1; //R1
        uint8_t bit_A : 1; //L3
        uint8_t bit_B : 1; //R3
        uint8_t bit_C : 1; //Share
        uint8_t bit_D : 1; //Options
        uint8_t bit_E : 1; //none
        uint8_t bit_F : 1; //none
        uint8_t L2value;
        uint8_t R2value;
        int8_t LstickX;
        int8_t LstickY;
        int8_t RstickX;
        int8_t RstickY;
    };
    uint64_t alldata;
}DS4_Data_Pack;


void delay_ms(unsigned int msec){
    unsigned int cnt = msec;
    TMR1_Start();
    while(cnt){
        while(IFS0bits.T1IF){
            IFS0CLR = _IFS0_T1IF_MASK;
            cnt--;
        }
    }
    TMR1_Stop();
}

void SPI2_User_Handler(uintptr_t context){
    //uint8_t SPI2_Rxdata_buf[8] = {0};
    static uint8_t cnt = 0;
    
    cnt++;
    
    if(cnt > 50){
        GPIO_PortToggle(GPIO_PORT_C, 1<<10);
        cnt = 0;
    }
    
    SPI2_Read((void*)SPI2_Rxdata,sizeof(SPI2_Rxdata));
    
    //memcpy((void*)SPI2_Rxdata,SPI2_Rxdata_buf,sizeof(SPI2_Rxdata));
    
    
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    SPI2_CallbackRegister(SPI2_User_Handler, (uintptr_t)NULL );
    
    DS4_Data_Pack ds4_data;
    ds4_data.alldata = 0;

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        
        memcpy(&ds4_data,(void*)SPI2_Rxdata,sizeof(ds4_data));
        
        if(ds4_data.bit_8){
            LED_R = 1;
        }else if(ds4_data.bit_3){
            LED_R = 0;
        }
        
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

