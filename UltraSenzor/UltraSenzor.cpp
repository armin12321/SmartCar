#include "UltraSenzor.h"

UltraSenzor::UltraSenzor(uint8_t triger, uint8_t echo) {
    pinTriger = triger;
    pinEcho = echo;
}

void UltraSenzor::SetMaxUdaljenost(uint8_t ud) {
    maxUdaljenost = ud;
}

void UltraSenzor::SetMinUdaljenost(double ud) {
    minUdaljenost = ud;
}

boolean UltraSenzor::PostojiPrepreka() {
    NewPing senzor(pinTriger, pinEcho, maxUdaljenost);
    if (senzor.ping_cm() < minUdaljenost) {
        delay(100); 
        if (senzor.ping_cm() < minUdaljenost) {
            return true;
        }
    }
    return false;
}
