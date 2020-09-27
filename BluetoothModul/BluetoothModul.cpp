#include "BluetoothModul.h"

BluetoothModul::BluetoothModul() {
    brojacRouta = 0;
    brojacOsnovneNaredbe = 0;
}

boolean BluetoothModul::PostojiKomanda() {
    uint8_t brojac = 0;
    for (uint8_t i = 0; i < 10; i++) {
        trenutnaNaredba[i]  = 0; //ciscenje da ne bi ostala prethodna naredba.
    }
    if (Serial.available()) {
        //strcpy(prethodnaNaredba, trenutnaNaredba);
		delay(100);
        while(Serial.available() != 0 && brojac < 9) {
            trenutnaNaredba[brojac] = Serial.read();
            brojac++;
        }
        trenutnaNaredba[brojac] = '\0';
		Serial.print("Unesena naredba :");
		Serial.println(trenutnaNaredba);
        return true;
    } else 
        return false;
}

boolean BluetoothModul::JeLiOsnovna() {
    for (uint8_t i = 0; i < 11; i++) {
        if (!strcmp(this->trenutnaNaredba, this->osnovneNaredbe[i]))
            return true;
    }
    return false;
}

boolean BluetoothModul::JeLiNapredna() {
    for (uint8_t i = 0; i < 1; i++) {
       if (!strcmp(this->imenaRouti[i], this->trenutnaNaredba)) {
          return true; 
       }
    }
    return false;
}

void BluetoothModul::SetRxAndTx(uint8_t rx, uint8_t tx)
{
	pinRx = rx;
	pinTx = tx;
	pinMode(pinRx, INPUT);
	pinMode(pinTx, OUTPUT);
}
