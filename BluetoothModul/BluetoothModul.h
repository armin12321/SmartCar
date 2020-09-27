#ifndef BluetoothModul_h
#define BluetoothModul_h

#include "Arduino.h"

class BluetoothModul {
	public:
        char osnovneNaredbe[11][10] = {
          {'n','a','p','r','e','d','\0','\0','\0','\0'} ,
          {'n','a','z','a','d','\0','\0','\0','\0','\0'} ,
          {'n','a','p','r','e','d','d','\0','\0','\0'} ,
          {'n','a','z','a','d','d','\0','\0','\0','\0'} ,
          {'n','a','p','r','e','d','l','\0','\0','\0'} ,
          {'n','a','z','a','d','l','\0','\0','\0','\0'} ,
          {'z','a','u','s','t','a','v','i','\0','\0'} ,
          {'u','g','a','s','i','\0','\0','\0','\0','\0'} ,
          {'u','p','a','l','i','\0','\0','\0','\0','\0'} ,
          {'u','b','r','z','a','j','\0','\0','\0','\0'} ,
          {'u','s','p','o','r','i','\0','\0','\0','\0'} ,
        };
        uint8_t brojNaredbiPoRouti[1];
        uint8_t brojacRouta, brojacOsnovneNaredbe, pinRx, pinTx;
        char trenutnaNaredba[10]; // u stvari devet, jedan je za null terminator.
        //char prethodnaNaredba[10];
        unsigned long vremenaNaredbi[1][20];
        char imenaNaredbi[1][20][10]; // 5 ruti, 50 naredbi u svakoj ruti, svaka naredba 10 znakova.
        char imenaRouti[1][10]; // pet ruti svaka moze imati ime do deset znakova - null terminator
        BluetoothModul();
        boolean PostojiKomanda();        
        boolean JeLiOsnovna();
        boolean JeLiNapredna();
		void SetRxAndTx(uint8_t, uint8_t);
};

#endif
