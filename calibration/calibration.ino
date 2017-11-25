/*
 * Kalibráló program forráskódja egy HX711 AD konverterhez
 * erősen a SparkFun példakódján alapszik: https://github.com/sparkfun/HX711-Load-Cell-Amplifier
 *
 * A kód bogde GitHub felhasználó libraryját használja: https://github.com/bogde/HX711
 * Bogde libraryja a GNU GENERAL PUBLIC LICENSE alatt van kiadva.
 */

#include "HX711.h"

/*
 * Az órajelet biztosító és a kimeneti tűk száma
 */
#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

float calibration_factor = -10990;
float reading = 0;

/*
 * Inicializálási kód
 */
void setup() {
  Serial.begin(9600);
  /*
   * Az elején le kell venni a súlyt a mérlegcelláról
   * a mérleg nullázása.
   * Ezután ráhelyezünk egy ismert súlyt.
   */

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

}

/*
 * Ismétlődő kód
 */

void loop() {

  /*
   * Miután ráhelyeztünk egy ismert súlyt a korrekciós tényezőt addig kell
   * állítani amíg nem kapunk megfelelő értékekek.
   */
  scale.set_scale(calibration_factor);

  Serial.print("Reading: ");
  reading = scale.get_units();
  if (reading > 0) { Serial.print(" "); }
  Serial.print(reading, 3);
  Serial.print(" g");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  /*
   * + számítógép felőli bemenet esetén a korrekciós tényezőt növeli
   * - számítógép felőli bemenet esetén a korrekciós tényezőt csökkenti
   */
  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
  }
}
