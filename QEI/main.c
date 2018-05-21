/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432E4 Empty Project
 *
 * Description: An empty project that uses DriverLib
 *
 *                MSP432E401Y
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
*******************************************************************************/
/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

unsigned long  COUNT = 0;
unsigned long  POS = 0;
int  s;
int d;



//********************************************************************
//QEI0初始化

int
QEIInit (void)
{
    QEIConfigure(QEI0_BASE,(QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET|
    QEI_CONFIG_QUADRATURE|QEI_CONFIG_NO_SWAP),10000000);//使用A,B通道共4个边沿计算位置
    
   /* GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_1,
    GPIO_STRENGTH_4MA,
    GPIO_PIN_TYPE_STD);
    
    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_2,
    GPIO_STRENGTH_4MA,
    GPIO_PIN_TYPE_STD);
    
    GPIOPadConfigSet(GPIO_PORTL_BASE, GPIO_PIN_3,
    GPIO_STRENGTH_4MA,
    GPIO_PIN_TYPE_STD);
  */
    GPIOPinTypeQEI(GPIO_PORTL_BASE,GPIO_PIN_1|GPIO_PIN_2);//配置PL1，PL2为PhA1，PhB1
    QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, 120000000/100);//10ms
    
    //使能速度计算，使能QEI
    QEIVelocityEnable(QEI0_BASE);
    QEIEnable(QEI0_BASE);

    //速度计时器计时完成时触发中断
    QEIIntEnable(QEI0_BASE,QEI_INTTIMER);
    IntEnable(INT_QEI0);
    
    
    return(0); 
}

void QEI0_IRQHandler(void)
{
    
    
  QEIIntClear(QEI0_BASE, QEI_INTTIMER);
  POS = QEIPositionGet(QEI0_BASE);
  d = QEIDirectionGet(QEI0_BASE);
  
    COUNT = QEIVelocityGet(QEI0_BASE);
    s = (COUNT*6000)/2024;
    printf("The Speed is %d .Velocity is %d.Direction is %d.\n",s,COUNT /4,d);
    COUNT = 0;
 
  


}

 int main(void)
{

    /* Configure the system clock for 120 MHz */
    MAP_SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN |
                                          SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480),
                                          120000000);
    
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);//使能QEI0外设
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);/*enable L port*/
    MAP_IntEnable(INT_GPIOL);
    
    GPIOPinConfigure(GPIO_PL1_PHA0);
    GPIOPinConfigure(GPIO_PL2_PHB0);


        
    QEIEnable(QEI0_BASE);//使能正交编码器QEI0

    QEIInit();
    while(1)
    {
        
    }
}
