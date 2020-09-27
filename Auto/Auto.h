#ifndef Auto_h
#define Auto_h
#include "BluetoothModul.h"
#include "MjeracBrzine.h"
#include "UltraSenzor.h"

class Auto:public BluetoothModul, public MjeracBrzine, public UltraSenzor {
	public:
        uint8_t pinLijeviMotor1, pinLijeviMotor2, pinDesniMotor1, pinDesniMotor2;
        boolean ugasenAuto, ideNaprijed, ideNazad, pamtiPutanju;
        unsigned long startTime = 0;
        Auto(uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);
        void Naprijed();
        void Nazad();
        void NaprijedDesno();
        void NaprijedLijevo();
        void NazadDesno();
        void NazadLijevo();
        void UgasiAuto();
        void UpaliAuto();
        void ZaustaviAuto();
        unsigned long VrijemeZastoja();
        void OsnovnaNaredba();
        void ZapamcenaNaredba();
}; 

#endif
