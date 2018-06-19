/******************************************************************************
 * MSP432E401Y
 * Description:串口初始化 
 * 引脚：PA0->TX
 *       PA1->RX
 * Author: Robin.J
***************************************************************************/
#include <common.h>
#include "ti/devices/msp432e4/driverlib/driverlib.h"

uint8_t Text_Count = 0;
uint8_t Count_Char = 0;
char Buffer[3]; //待发送字符
char Buffer_Out[3] = {'\0'};//速度值转换为字符
float Line_speed;
float Angular_speed;

unsigned char ch;
//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UART0_IRQHandler(void)
{
    uint32_t ui32Status;

    Count_Char = 0;
    Text_Count = 0; 
    /*Get the interrrupt status.*/
    ui32Status = MAP_UARTIntStatus(UART0_BASE, true);

      UARTSend((uint8_t *)"Input:", 8);
    /*Clear the asserted interrupts.*/
    MAP_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(MAP_UARTCharsAvail(UART0_BASE))
    {
        
        /* Read the next character from the UART and write it back to the UART.*/
        
//        MAP_UARTCharPutNonBlocking(UART0_BASE,
//                                   MAP_UARTCharGetNonBlocking(UART0_BASE));
   
        Buffer[Text_Count++] = MAP_UARTCharGetNonBlocking(UART0_BASE);
        MAP_UARTCharPutNonBlocking(UART0_BASE,
                                 Buffer[Count_Char++]);

        /*Blink the LED to show a character transfer is occuring.*/
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);

        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
       // SysCtlDelay(g_ui32SysClock / (1000 * 3));
    }
    
//      Line_speed = (float)atoi(Buffer);//发送线速度
//    if(Line_speed >= 17){
//      ch = 130;
//    }else {
//      ch = 7.64 * Line_speed;
//    }
    
//    Angular_speed = (float)atoi(Buffer);//发送角速度
//    if(Angular_speed > 13.6){
//      ch = 130;
//    }else{
//      ch = 9.55 * Angular_speed;
//    }
    
      ch = (unsigned char)atoi(Buffer);
    
      UARTSend((uint8_t *)"Current:", 10);
      sprintf(Buffer_Out,"%d",(int)s_r);
//      sprintf(Buffer_Out,"%d",(int)s_l);
      UARTSend((uint8_t *)Buffer_Out, 10);
 
      memset(Buffer_Out,0,sizeof(Buffer_Out));
      
}
//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}
//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
void uart_init(void)
{
    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);

    //
    // Enable the GPIO pins for the LED (PN0).
    //
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);

    //
    // Enable the peripherals used by this example.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Enable processor interrupts.
    //
    MAP_IntMasterEnable();

    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    MAP_UARTConfigSetExpClk(UART0_BASE, g_ui32SysClock, 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Enable the UART interrupt.
    //
    MAP_IntEnable(INT_UART0);
    MAP_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //
    // Prompt for text to be entered.
    //
//    UARTSend((uint8_t *)"Input Speed: ", 16);
    
}

/******************* (C) COPYRIGHT 2018 DY EleTe *****END OF FILE************/

