#ifndef UltraSenzor_h
#define UltraSenzor_h

#include "Arduino.h"
#include <NewPing.h>

class UltraSenzor {
	public:
        uint8_t maxUdaljenost, pinTriger, pinEcho;
        double minUdaljenost;
        UltraSenzor(uint8_t, uint8_t);
        void SetMaxUdaljenost(uint8_t);
        void SetMinUdaljenost(double);
        boolean PostojiPrepreka();
}; 

#endif
