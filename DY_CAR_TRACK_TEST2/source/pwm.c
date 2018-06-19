/* DriverLib Includes */
#include <ti/devices/msp432e4/driverlib/driverlib.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

float pwm_val_l;
float pwm_val_r;

void PWM_init(float pwm_pro_l0,float pwm_pro_l1,float pwm_pro_r0,float pwm_pro_r1)//分别控制正反
{
    pwm_val_l = pwm_pro_l0;
    pwm_val_r = pwm_pro_r0;
 /* The PWM peripheral must be enabled for use. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0)));

    /* Set the PWM clock to the system clock. */
    MAP_PWMClockSet(PWM0_BASE,PWM_SYSCLK_DIV_1);

    /* Enable the clock to the GPIO Port F for PWM pins */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    MAP_GPIOPinConfigure(GPIO_PF2_M0PWM2);
    MAP_GPIOPinConfigure(GPIO_PF3_M0PWM3);
    
    MAP_GPIOPinConfigure(GPIO_PF0_M0PWM0);
    MAP_GPIOPinConfigure(GPIO_PF1_M0PWM1);
    
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_2 | GPIO_PIN_3));
    MAP_GPIOPinTypePWM(GPIO_PORTF_BASE, (GPIO_PIN_0 | GPIO_PIN_1));

    /* Configure the PWM0 to count up/down without synchronization. */
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_UP_DOWN |
                        PWM_GEN_MODE_NO_SYNC);
    
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN |
                        PWM_GEN_MODE_NO_SYNC);

    /* Set the PWM period to 400Hz.  To calculate the appropriate parameter
     * use the following equation: N = (1 / f) * SysClk.  Where N is the
     * function parameter, f is the desired frequency, and SysClk is the
     * system clock frequency.
     * In this case you get: (1 / 400HZ) * 16MHZ = 40000 cycles.  Note that
     * the maximum period you can set is 2^16 - 1. */
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, 40000);
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, 40000);

    /* Set PWM0 PF2 to a duty cycle of 25%.  You set the duty cycle as a
     * function of the period.  Since the period was set above, you can use the
     * PWMGenPeriodGet() function.  For this example the PWM will be high for
     * 25% of the time or 10000 clock cycles (40000 / 4). */
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,
                     pwm_pro_l0*MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1));//正转
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                     pwm_pro_r0*MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1));

    /* Set PWM0 PF3 to a duty cycle of 75%.  You set the duty cycle as a
     * function of the period.  Since the period was set above, you can use the
     * PWMGenPeriodGet() function.  For this example the PWM will be high for
     * 7% of the time or 30000 clock cycles 3*(40000 / 4). */
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,
                     pwm_pro_l1 * MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1));//反转
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                     pwm_pro_r1 * MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1));

    MAP_IntMasterEnable();

    /* This timer is in up-down mode.  Interrupts will occur when the
     * counter for this PWM counts to the load value (64000), when the
     * counter counts up to 64000/4 (PWM A Up), counts down to 64000/4
     * (PWM A Down), and counts to 0. */
    MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_1,
                            PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                            PWM_INT_CNT_AU | PWM_INT_CNT_AD);
    MAP_PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_0,
                            PWM_INT_CNT_ZERO | PWM_INT_CNT_LOAD |
                            PWM_INT_CNT_AU | PWM_INT_CNT_AD);
    MAP_IntEnable(INT_PWM0_1);//使能PWM中断
    MAP_IntEnable(INT_PWM0_0);//使能PWM中断
    
    MAP_PWMIntEnable(PWM0_BASE, PWM_INT_GEN_1);//使能PWM
    MAP_PWMIntEnable(PWM0_BASE, PWM_INT_GEN_0);//使能PWM
    

    /* Enable the PWM0 Bit 0 (PF0) and Bit 1 (PF1) output signals. */
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);

    /* Enables the counter for a PWM generator block. */
    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);

    /* Loop forever while the PWM signals are generated. */
}

/* PWM ISR */
void PWM0_1_IRQHandler(void)
{
    uint32_t getIntStatus;

    getIntStatus = MAP_PWMGenIntStatus(PWM0_BASE, PWM_GEN_1, true);

    MAP_PWMGenIntClear(PWM0_BASE, PWM_GEN_1, getIntStatus);
    

}

void PWM0_0_IRQHandler(void)
{
    uint32_t getIntStatus;

    getIntStatus = MAP_PWMGenIntStatus(PWM0_BASE, PWM_GEN_0, true);

    MAP_PWMGenIntClear(PWM0_BASE, PWM_GEN_0, getIntStatus);
    

}