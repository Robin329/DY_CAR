#ifndef _TURN_CTRL
#define _TURN_CTRL

#include <stdint.h>

//extern void Delay_ms(uint8_t n);
extern void Forward();
extern void Turn_Right();
extern void Turn_Left();
extern void Back();
extern void Stop();
extern void ControlCar(unsigned char ConType);

#endif