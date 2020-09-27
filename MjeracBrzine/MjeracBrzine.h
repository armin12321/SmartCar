#ifndef MjeracBrzine_h
#define MjeracBrzine_h

#include "Arduino.h"

class MjeracBrzine {
	public:
        uint8_t trenutnaBrzina, prethodnaBrzina;
        uint8_t pinLijeviBrzina, pinDesniBrzina;
        uint8_t brzinaSkretanja, razlikaBrzina;
        uint8_t promjenaBrzine;
        int vrijemeSkretanja;
        MjeracBrzine(uint8_t, uint8_t);
        void SetBrzinaSkretanja(uint8_t);
        void SetRazlikaBrzina(uint8_t);
        void SetPromjenaBrzine(uint8_t);
        void PovecajBrzinu();
        void SmanjiBrzinu();
        void SetVrijemeSkretanja(int);
};

#endif
