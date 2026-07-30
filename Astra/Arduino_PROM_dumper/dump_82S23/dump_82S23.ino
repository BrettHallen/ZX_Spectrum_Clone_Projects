/*
 * dump_82S23.ino  --  dump a 82S23 / К155РЕ3 bipolar PROM (32 x 8)
 *
 * Open-collector part: data lines use the Arduino's INTERNAL pull-ups,
 * so no external resistors are strictly required for a static read.
 * (If reads look flaky, add ~4.7k external pull-ups from each O pin to 5V.)
 *
 * Chip Vcc -> Arduino 5V,  chip GND -> Arduino GND.
 * CE (pin 6) is active LOW.
 *
 *  --- Wiring (chip pin -> Arduino pin) ---
 *   A0(1)->D2  A1(2)->D3  A2(3)->D4  A3(4)->D5  A4(5)->D6
 *   CE(6)->D7
 *   O1(15)->D8  O2(14)->D9  O3(13)->D10 O4(12)->D11
 *   O5(11)->D12 O6(10)->D13 O7(7)->A0   O8(9)->A1
 */

const uint8_t ADDR[5] = {2, 3, 4, 5, 6};        // A0..A4
const uint8_t CE      = 7;                        // active LOW
// data pins in order O1..O8  (O1 = bit 0 of the byte we print)
const uint8_t DATA[8] = {8, 9, 10, 11, 12, 13, A0, A1};

void setup() {
  Serial.begin(115200);
  for (uint8_t i = 0; i < 5; i++) pinMode(ADDR[i], OUTPUT);
  pinMode(CE, OUTPUT);
  digitalWrite(CE, HIGH);                         // start disabled
  for (uint8_t i = 0; i < 8; i++) pinMode(DATA[i], INPUT_PULLUP);

  Serial.println(F("82S23 / K155RE3 dump (32 bytes)"));

  for (uint16_t a = 0; a < 32; a++) {
    for (uint8_t b = 0; b < 5; b++) digitalWrite(ADDR[b], (a >> b) & 1);
    digitalWrite(CE, LOW);                        // enable
    delayMicroseconds(5);                         // settle (far longer than needed)
    uint8_t v = 0;
    for (uint8_t b = 0; b < 8; b++)
      if (digitalRead(DATA[b])) v |= (1 << b);    // DATA[0]=O1 -> bit0
    digitalWrite(CE, HIGH);                        // disable

    char line[24];
    sprintf(line, "%02X: %02X", a, v);
    Serial.println(line);
  }
  Serial.println(F("done."));
}

void loop() {}
