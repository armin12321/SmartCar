#include "MjeracBrzine.h"

MjeracBrzine::MjeracBrzine (uint8_t desni, uint8_t lijevi) { 
    trenutnaBrzina = 0;
    prethodnaBrzina = 0;
    pinLijeviBrzina = lijevi;
    pinDesniBrzina = desni;
    pinMode(pinDesniBrzina, OUTPUT);
    pinMode(pinLijeviBrzina, OUTPUT);
}

void MjeracBrzine::SetVrijemeSkretanja(int vrijeme) {
    vrijemeSkretanja = vrijeme;
}

void MjeracBrzine::SetRazlikaBrzina (uint8_t razlika) {
    razlikaBrzina = razlika;
}

void MjeracBrzine::SetBrzinaSkretanja(uint8_t brzina) {
    brzinaSkretanja = brzina;
}

void MjeracBrzine::SetPromjenaBrzine(uint8_t promjena) {
    promjenaBrzine = promjena;
}

void MjeracBrzine::PovecajBrzinu() {
    if (trenutnaBrzina + promjenaBrzine < 255) {
        prethodnaBrzina = trenutnaBrzina;
        trenutnaBrzina += promjenaBrzine;
        analogWrite(pinLijeviBrzina, trenutnaBrzina); 
        analogWrite(pinDesniBrzina, trenutnaBrzina - razlikaBrzina);        
    } else if (trenutnaBrzina + 1 < 255) {
        prethodnaBrzina = trenutnaBrzina;
        trenutnaBrzina += 1;
        analogWrite(pinLijeviBrzina, trenutnaBrzina); 
        analogWrite(pinDesniBrzina, trenutnaBrzina - razlikaBrzina);        
    } else {
        Serial.println("Brzina dostigla svoj maksimum.");
        return;
    }
    Serial.print("Brzina povecana sa ");
    Serial.print(prethodnaBrzina);
    Serial.print(" na ");
    Serial.println(trenutnaBrzina);
    return;
}

void MjeracBrzine::SmanjiBrzinu() {
    if (trenutnaBrzina - promjenaBrzine >= razlikaBrzina) {
        prethodnaBrzina = trenutnaBrzina;
        trenutnaBrzina -= promjenaBrzine;
        analogWrite(pinLijeviBrzina, trenutnaBrzina);
        analogWrite(pinDesniBrzina, trenutnaBrzina - razlikaBrzina);
    } else if (trenutnaBrzina - 1 >= razlikaBrzina) {
        prethodnaBrzina = trenutnaBrzina;
        trenutnaBrzina -= 1;
        analogWrite(pinLijeviBrzina, trenutnaBrzina);
        analogWrite(pinDesniBrzina, trenutnaBrzina - razlikaBrzina);
    } else {
        Serial.println("Brzina dostigla svoj minimum.");
        return;
    }
    Serial.print("Brzina umanjena sa ");
    Serial.print(prethodnaBrzina);
    Serial.print(" na ");
    Serial.println(trenutnaBrzina);
}
