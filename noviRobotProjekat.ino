#include <Auto.h>
#define promjenaBrzine 20
#define brzinaOkretanja 200
#define vremeOkretanja 500
#define desni1 2
#define desni2 4
#define lijevi1 7
#define lijevi2 8
#define echo 5
#define triger 6
#define maxUd 200
#define minUd 14
#define enA 9
#define enB 3
#define razlikaBrzina 6
#define rx 0
#define tx 1

Auto mojAuto (desni1, desni2, lijevi1, lijevi2, triger, echo, enA, enB);

void setup() {
    // put your setup code here, to run once:
    mojAuto.SetMaxUdaljenost(maxUd);
    mojAuto.SetMinUdaljenost(minUd);
    mojAuto.SetBrzinaSkretanja(brzinaOkretanja);
    mojAuto.SetRazlikaBrzina(razlikaBrzina);
    mojAuto.SetPromjenaBrzine(promjenaBrzine);
    mojAuto.SetVrijemeSkretanja(vremeOkretanja);
    mojAuto.SetRxAndTx(rx, tx);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (mojAuto.PostojiKomanda()) {
        if (mojAuto.JeLiOsnovna() == true) {
            mojAuto.OsnovnaNaredba();
            mojAuto.startTime = mojAuto.startTime + mojAuto.VrijemeZastoja();
        } else if (mojAuto.JeLiNapredna() == true && mojAuto.ugasenAuto == true) {
            mojAuto.ZapamcenaNaredba();
        } else if (mojAuto.JeLiNapredna() == true && mojAuto.ugasenAuto == false) {
            Serial.println(F("Kretanje traje, sada nije moguce rekonstruirati put."));
        }
        else {
            Serial.println(F("Nepoznata naredba."));
        }
    }
    
    mojAuto.startTime = mojAuto.startTime + mojAuto.VrijemeZastoja();
}
