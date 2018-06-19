#ifndef _TURN_CTRL
#define _TURN_CTRL

#include <stdint.h>

extern void Turn_Spin_Right(void);
extern void Turn_Spin_Left(void);
extern void Delay_ms(uint8_t n);
extern void Forward(void);
extern void Turn_Right(void);
extern void Turn_Left(void);
extern void Back(void);
extern void Stop(void);
extern void ControlCar(unsigned char ConType);

#endif