/*
 * Beolvasó program forráskódja egy HX711 AD konverterhez
 * erősen a SparkFun példakódján alapszik: https://github.com/sparkfun/HX711-Load-Cell-Amplifier
 *
 * A kód bogde GitHub felhasználó libraryját használja: https://github.com/bogde/HX711
 * Bogde libraryja a GNU GENERAL PUBLIC LICENSE alatt van kiadva.
 */
#include "HX711.h"

/*
 * A kalibrálásból megkapott korrekciós tényező,
 * és az órajelet biztosító és a kimeneti tűk sorszáma
 */

#define calibration_factor -10990.0

#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);

/*
 * Inicializálási kód
 */
void setup() {
  Serial.begin(38400);

  /*
   * Nullázás, inicializálás a korrekciós tényezővel
   */
  scale.set_scale(calibration_factor); 
  scale.tare(); 

}

/*
 * Ismétlődő kód
 */
 
void loop() {
  /*
   * Mért adatok kiírása
   */
  Serial.print(scale.get_units(), 10); 
  Serial.print(" g"); 
  Serial.println();
}
