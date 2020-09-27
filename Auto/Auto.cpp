#include "Auto.h"

//varijable:
          //desni1  , desni2   , lijevi1  , lijevi2  , trigerpin, echopin  , desniBrz , lijeviBrz.
Auto::Auto(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f, uint8_t g, uint8_t h):
           BluetoothModul(), MjeracBrzine(g, h), UltraSenzor(e, f) {
    pinDesniMotor1 = a;
    pinDesniMotor2 = b;
    pinLijeviMotor1 = c;
    pinLijeviMotor2 = d;
    pinMode(pinDesniMotor1, OUTPUT);            
    pinMode(pinDesniMotor2, OUTPUT);
    
    pinMode(pinLijeviMotor1, OUTPUT);
    pinMode(pinLijeviMotor2, OUTPUT);

    ugasenAuto = true;
    ideNaprijed = false;
    ideNazad = false;
    pamtiPutanju = true;
}

void Auto::Naprijed() {
    ideNaprijed = true;
    ideNazad = false;
  
    digitalWrite(pinDesniMotor1, HIGH);
    digitalWrite(pinDesniMotor2, LOW);

    digitalWrite(pinLijeviMotor1, HIGH);
    digitalWrite(pinLijeviMotor2, LOW);
    Serial.println("Krenuo naprijed.");
}

void Auto::Nazad() {
    ideNaprijed = false;
    ideNazad = true;

    digitalWrite(pinDesniMotor1, LOW);
    digitalWrite(pinDesniMotor2, HIGH);

    digitalWrite(pinLijeviMotor1, LOW);
    digitalWrite(pinLijeviMotor2, HIGH);
    Serial.println(F("Krenuo nazad."));
}

void Auto::NaprijedDesno() {
    digitalWrite(pinDesniMotor1, LOW);
    digitalWrite(pinDesniMotor2, LOW);           

    analogWrite(this->pinLijeviBrzina, this->brzinaSkretanja);
    analogWrite(this->pinDesniBrzina, this->brzinaSkretanja - this->razlikaBrzina);

    Serial.println(F("Skrenuo naprijed desno."));
    digitalWrite(pinLijeviMotor1, HIGH);
    digitalWrite(pinLijeviMotor2, LOW);

    delay(this->vrijemeSkretanja);

    analogWrite(this->pinLijeviBrzina, this->trenutnaBrzina);
    analogWrite(this->pinDesniBrzina, this->trenutnaBrzina - this->razlikaBrzina);

    if (ideNaprijed == true) {
        this->Naprijed();
    } else if (ideNazad == true) {
        this->Nazad();
    } else {
        this->ZaustaviAuto();
    }
}

void Auto::NaprijedLijevo() {
    digitalWrite(pinLijeviMotor1, LOW);
    digitalWrite(pinLijeviMotor2, LOW);           

    analogWrite(this->pinLijeviBrzina, this->brzinaSkretanja);
    analogWrite(this->pinDesniBrzina, this->brzinaSkretanja - this->razlikaBrzina);

    Serial.println(F("Skrenuo naprijed lijevo."));
    digitalWrite(pinDesniMotor1, HIGH);
    digitalWrite(pinDesniMotor2, LOW);

    delay(this->vrijemeSkretanja);

    analogWrite(this->pinLijeviBrzina, this->trenutnaBrzina);
    analogWrite(this->pinDesniBrzina, this->trenutnaBrzina - this->razlikaBrzina);

    if (ideNaprijed == true) {
        this->Naprijed();
    } else if (ideNazad == true) {
        this->Nazad();
    } else {
        this->ZaustaviAuto();
    }  
}

void Auto::NazadDesno() {
    digitalWrite(pinDesniMotor1, LOW);
    digitalWrite(pinDesniMotor2, LOW);           

    analogWrite(this->pinLijeviBrzina, this->brzinaSkretanja);
    analogWrite(this->pinDesniBrzina, this->brzinaSkretanja - this->razlikaBrzina);

    Serial.println(F("Skrenuo nazad desno."));
    digitalWrite(pinLijeviMotor1, LOW);
    digitalWrite(pinLijeviMotor2, HIGH);

    delay(this->vrijemeSkretanja);

    analogWrite(this->pinLijeviBrzina, this->trenutnaBrzina);
    analogWrite(this->pinDesniBrzina, this->trenutnaBrzina - this->razlikaBrzina);

    if (ideNaprijed == true) {
        this->Naprijed();
    } else if (ideNazad == true) {
        this->Nazad();
    } else {
        this->ZaustaviAuto();
    }  
}

void Auto::NazadLijevo() {
    digitalWrite(pinLijeviMotor1, LOW);
    digitalWrite(pinLijeviMotor2, LOW);           

    analogWrite(this->pinLijeviBrzina, this->brzinaSkretanja);
    analogWrite(this->pinDesniBrzina, this->brzinaSkretanja - this->razlikaBrzina);

    Serial.println(F("Skrenuo nazad lijevo."));
    digitalWrite(pinDesniMotor1, LOW);
    digitalWrite(pinDesniMotor2, HIGH);

    delay(this->vrijemeSkretanja);

    analogWrite(this->pinLijeviBrzina, this->trenutnaBrzina);
    analogWrite(this->pinDesniBrzina, this->trenutnaBrzina - this->razlikaBrzina);

    if (ideNaprijed == true) {
        this->Naprijed();
    } else if (ideNazad == true) {
        this->Nazad();
    } else {
        this->ZaustaviAuto();
    }      
}

void Auto::ZaustaviAuto() {
    ideNaprijed = false;
    ideNazad = false;
    digitalWrite(pinDesniMotor1, LOW);
    digitalWrite(pinDesniMotor2, LOW);
    digitalWrite(pinLijeviMotor1, LOW);
    digitalWrite(pinLijeviMotor2, LOW);
    Serial.println(F("Auto zaustavljen."));
}

unsigned long Auto::VrijemeZastoja() {
    unsigned long pocetnoVrijeme = millis();
    if (this->PostojiPrepreka() == true) {
        boolean isaoNaprijed = ideNaprijed;
        boolean isaoNazad = ideNazad;
        this->ZaustaviAuto();
        Serial.println(F("Auto zaustavljen zbog opasnosti od sudara."));
        while(this->PostojiPrepreka() == true) {
            delay(100);
        }
        if (isaoNaprijed == true) {
            this->Naprijed();
        } else if (isaoNazad == true) {
            this->Nazad();
        }
        return millis() - pocetnoVrijeme;
    }
    return 0;

    
}

void Auto::UgasiAuto() {
   
	ugasenAuto = true;
	ideNaprijed = false;
	ideNazad = false;
	this->trenutnaBrzina = 0;
	this->prethodnaBrzina = 0;
	digitalWrite(pinDesniMotor1, LOW);
	digitalWrite(pinDesniMotor2, LOW);

	digitalWrite(pinLijeviMotor1, LOW);
	digitalWrite(pinLijeviMotor2, LOW);

	
   
    
    Serial.println(F("Auto ugasen."));
    if (pamtiPutanju == true) {

		if (this->brojacOsnovneNaredbe > 20) {
			Serial.println(F("Nema dovoljno prostora za pamcenje ove rute..."));
			return;
		}
		else if (brojacRouta >= 1) {
			Serial.println(F("Prekoracen dozvoljen broj zapamcenih routa, odbacujem routu."));
			return;
		}

        Serial.println(F("Da li zelite pospremiti ovu putanju u \"bazu podataka?\"(DA - da, ostali odgovori - ne"));
        while(!this->PostojiKomanda()) delay(100);
        if (!strcmp(this->trenutnaNaredba, "da")) {
            Serial.println(F("Unesi ime route : (maximalno devet znakova)"));
            while(!this->PostojiKomanda()) delay(100);
            strcpy(this->imenaRouti[brojacRouta], this->trenutnaNaredba);
            Serial.println(F("Putanja zapamcena."));  
            this->brojNaredbiPoRouti[brojacRouta] = this->brojacOsnovneNaredbe;
            this->brojacRouta++;
        } else {
            Serial.println(F("Putanja odbacena."));
        }
    }
    

    
    this->brojacOsnovneNaredbe = 0;
	if (brojacRouta >= 1) {
		pamtiPutanju = false;
	}
	else {
		pamtiPutanju = true;
	}
    return;
}

void Auto::UpaliAuto() {
    ugasenAuto = false;
    ideNaprijed = false;
    ideNazad = false;
    Serial.println(F("Auto upaljen."));
  
    startTime = millis();
    return;
}



void Auto::OsnovnaNaredba() {
    if (ugasenAuto == true && strcmp(this->trenutnaNaredba, "upali") != 0) {
        Serial.println(F("Ne mozete nista raditi dok ne pokrenete auto."));
        return;
	}
	else if (ugasenAuto == false && strcmp(this->trenutnaNaredba, "upali") == 0) {
		Serial.println(F("Auto vec upaljen, naredba odbacena."));
		return;
	}
	else if (this->ideNaprijed && strcmp(this->trenutnaNaredba, "napred") == 0) {
		Serial.println(F("Auto vec ide naprijed, naredba odbacena."));
		return;
	}
	else if (this->ideNazad && strcmp(this->trenutnaNaredba, "nazad") == 0) {
		Serial.println(F("Auto vec ide nazad, naredba odbacena."));
		return;
	}
	else if (!this->ideNazad && !this->ideNaprijed && strcmp(this->trenutnaNaredba, "zaustavi") == 0) {
		Serial.println(F("Auto vec zaustavljeno, naredba odbacena."));
		return;
	}
	if (pamtiPutanju == true && strcmp(this->trenutnaNaredba, "upali") == 0) {
		this->vremenaNaredbi[brojacRouta][brojacOsnovneNaredbe] = 0;
		strcpy(this->imenaNaredbi[brojacRouta][brojacOsnovneNaredbe], this->trenutnaNaredba);
		this->brojacOsnovneNaredbe++;
	}
	else if (pamtiPutanju == true) {
        this->vremenaNaredbi[brojacRouta][brojacOsnovneNaredbe] = millis() - startTime;
        strcpy(this->imenaNaredbi[brojacRouta][brojacOsnovneNaredbe], this->trenutnaNaredba);
        this->brojacOsnovneNaredbe++;
    }
    
    if (!strcmp(this->trenutnaNaredba, "napred")) {
        this->Naprijed();
    } else if (!strcmp(this->trenutnaNaredba, "nazad")) {
        this->Nazad();
    } else if (!strcmp(this->trenutnaNaredba, "napredd")) {
        this->NaprijedDesno();
    } else if (!strcmp(this->trenutnaNaredba, "nazadd")) {
        this->NazadDesno();
    } else if (!strcmp(this->trenutnaNaredba, "napredl")) {
        this->NaprijedLijevo();
    } else if (!strcmp(this->trenutnaNaredba, "nazadl")) {
        this->NazadLijevo();
    } else if (!strcmp(this->trenutnaNaredba, "ugasi")) {
        this->UgasiAuto();
    } else if (!strcmp(this->trenutnaNaredba, "upali")) {
        this->UpaliAuto();
    } else if (!strcmp(this->trenutnaNaredba, "zaustavi")) {
        this->ZaustaviAuto();
    } else if (!strcmp(this->trenutnaNaredba, "ubrzaj")) {
        this->PovecajBrzinu();
    } else if (!strcmp(this->trenutnaNaredba, "uspori")) {
        this->SmanjiBrzinu();
    }
    return;
}

void Auto::ZapamcenaNaredba() {
    for (uint8_t i = 0;i < 1;i++) {
        if (!strcmp(imenaRouti[i], this->trenutnaNaredba)) {
            Serial.println(F("Rekonstrukcija puta pocinje..."));
            this->pamtiPutanju = false;
            unsigned long zastoji = 0;
            unsigned long pocetnoVrijeme = millis();
			signed long preostaloVrijeme = 0;

            for (uint8_t indeksNaredbe = 0; indeksNaredbe < this->brojNaredbiPoRouti[i]; indeksNaredbe++ ) {

                strcpy(this->trenutnaNaredba, imenaNaredbi[i][indeksNaredbe]);
                zastoji += this->VrijemeZastoja();
				
				preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                while(preostaloVrijeme >= 100) {
                    delay(100);
                    zastoji += this->VrijemeZastoja();
					preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                }
				preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                while(preostaloVrijeme >= 10) {
                    delay(10);
					preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                }
				preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                while(preostaloVrijeme >= 1) {
                    delay(1);
					preostaloVrijeme = vremenaNaredbi[i][indeksNaredbe] - millis() + pocetnoVrijeme + zastoji;
                }

				this->OsnovnaNaredba();
				Serial.print("trebalo proci : ");
				Serial.println(vremenaNaredbi[i][indeksNaredbe]);
				Serial.print("plus zastoji :");
				Serial.println(zastoji);
				Serial.print("Ukupno proslo :");
				Serial.println(millis() - pocetnoVrijeme);
			
            }
            break;
        }
    }
}




