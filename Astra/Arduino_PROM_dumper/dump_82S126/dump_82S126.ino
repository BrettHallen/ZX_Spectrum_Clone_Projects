/*
 * dump_82S126.ino  --  dump a 82S126 / КР556РТ4 bipolar PROM (256 x 4)
 *
 * Open-collector part: data lines use the Arduino's INTERNAL pull-ups,
 * so no external resistors are strictly required for a static read.
 * (If reads look flaky, add ~4.7k external pull-ups from each O pin to 5V.)
 *
 * Chip Vcc -> Arduino 5V,  chip GND -> Arduino GND.
 * CS1 (pin 13) and CS2 (pin 14) are BOTH active LOW -- tie both low to enable.
 *
 *  --- Wiring (chip pin -> Arduino pin) ---
 *   A0(5)->D2  A1(6)->D3  A2(7)->D4  A3(4)->D5
 *   A4(3)->D6  A5(2)->D7  A6(1)->D8  A7(15)->D9
 *   CS1(13)->D10  CS2(14)->D11
 *   O0(12)->D12  O1(11)->D13  O2(10)->A0  O3(9)->A1
 */

const uint8_t ADDR[8] = {2, 3, 4, 5, 6, 7, 8, 9};   // A0..A7
const uint8_t CS1 = 10, CS2 = 11;                    // both active LOW
// data pins in order O0..O3  (O0 = bit 0 of the nibble we print)
const uint8_t DATA[4] = {12, 13, A0, A1};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 8; i++) pinMode(ADDR[i], OUTPUT);
  pinMode(CS1, OUTPUT); pinMode(CS2, OUTPUT);
  digitalWrite(CS1, HIGH); digitalWrite(CS2, HIGH);   // start disabled
  for (uint8_t i = 0; i < 4; i++) pinMode(DATA[i], INPUT_PULLUP);

  Serial.println(F("82S126 / KR556RT4 dump (256 nibbles, low 4 bits used)"));

  for (uint16_t a = 0; a < 256; a++) {
    for (uint8_t b = 0; b < 8; b++) digitalWrite(ADDR[b], (a >> b) & 1);
    digitalWrite(CS1, LOW); digitalWrite(CS2, LOW);   // enable
    delayMicroseconds(5);                             // settle
    uint8_t v = 0;
    for (uint8_t b = 0; b < 4; b++)
      if (digitalRead(DATA[b])) v |= (1 << b);        // DATA[0]=O0 -> bit0
    digitalWrite(CS1, HIGH); digitalWrite(CS2, HIGH); // disable

    char line[24];
    sprintf(line, "%02X: %X", a, v & 0x0F);
    Serial.println(line);
  }
  Serial.println(F("done."));
}

void loop() {}
