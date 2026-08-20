# Wii Nunchuck → QWIIC adapter — design notes

Target: plug a Wii Nunchuck into the **QWIIC2** connector of an ESP32 Rainbow, where the
`esp32-zxspectrum` firmware already exposes it as a Kempston joystick (port 31).

All geometry below is derived from the open-source
[Adafruit Wii Nunchuck Breakout Adapter](https://github.com/adafruit/Adafruit-Wii-Nunchuck-Breakout-Adapter-PCB)
EagleCAD files (PID 4836, CC-BY-SA) — read out of the board file rather than measured, so the
contact mapping and outline are exact. Attribution belongs to Limor Fried / Adafruit.

---

## 1. Contact map

Origin = centre of the contact field. X is measured from the tongue centreline, viewed from the
**front** (the face the plug's notch sits against — Adafruit silkscreens this "Notch Up!").

| Face | X = −2.0 mm | X = 0 | X = +2.0 mm |
|---|---|---|---|
| **Front** (notch side) | **SCL** | *no pad* — the "N.C." position | **GND** |
| **Back** | **3V3** | attach-detect — **leave floating** | **SDA** |

Notes:

- The attach-detect contact is pulled high inside the Nunchuck so a *Wiimote* can sense that
  something is plugged in. Your adapter is not a Wiimote. Bring it to a test pad if you like, but
  do not connect it to anything.
- The N.C. position has no pad on the Adafruit design at all, and some Nunchuck plugs have no
  contact there. Leave it empty.
- Published pin *numbering* for this connector is inconsistent between references (they disagree
  on which pin is GND and which is SCL). Trust the physical map above, not pin numbers, and never
  trust the wire colours on a third-party extension cable.

## 2. Tongue geometry

| Feature | Dimension |
|---|---|
| PCB thickness | **2.0 mm** ±10% |
| Tongue width | 6.35 mm (±3.175 from centreline) |
| Tongue protrusion above slot floor | 7.36 mm |
| Contact size | 1.3 mm wide × 7.6 mm long |
| Contact pitch | 2.0 mm |
| Contact position | centred on the tongue; 0.26 mm of bare laminate at the tip; runs 0.5 mm past the shoulder into the body |
| Slots either side of tongue | inner edge ±3.175, outer edge ±6.223 (3.05 mm wide), floor 3.30 mm below the contact centreline |
| Grabber-latch recesses | extra 1.016 mm outward at ±6.223 → ±7.239, 2.54 mm tall, centred on the contact centreline |
| Body top edge (outside the slots) | 5.207 mm above the contact centreline |

**2.0 mm is the single most important number here.** A standard 1.6 mm board rattles in the plug
and makes intermittent contact. JLCPCB, PCBWay and Aisler all offer 2.0 mm FR4 as a stock option.
Adafruit's own README calls them "extra thicc 2.0mm PCBs" for exactly this reason.

The supplied footprint `Wii_Nunchuck_Edge_Connector.kicad_mod` carries the pads *and* the
Edge.Cuts geometry for the tongue, slots and latch recesses, so dropping it on a board draws the
whole connector end for you — just join it to the rest of your outline.

## 3. Schematic

Net list (J1 and J2 are the two QWIIC connectors, wired pin-for-pin in parallel):

| Net | Connections |
|---|---|
| `GND` | J1.1, J2.1, J1/J2 shell tabs, tongue front X=+2, C1.2, C2.2, D1 cathode |
| `3V3` | J1.2, J2.2, tongue back X=−2, C1.1, C2.1, R1→JP1, R2→JP2, R3 |
| `SDA` | J1.3, J2.3, tongue back X=+2, JP1 |
| `SCL` | J1.4, J2.4, tongue front X=−2, JP2 |
| *(none)* | tongue back X=0 — attach-detect, no connect |

where `R1 10k` sits between `3V3` and `JP1`, `JP1` between `R1` and `SDA` (likewise `R2`/`JP2` for
`SCL`), and `R3 2k2` between `3V3` and `D1` anode.

Four nets, that is the whole design. No level shifter and no regulator: QWIIC is 3.3 V and the
Nunchuck is a 3.3 V part, so the BSS138 and AP2112K on the Adafruit board are there only to
support 5 V Arduino hosts and are pure cost for you.

### Pull-ups

I checked the Rainbow's schematic (`esp32-s3-spectrum.kicad_sch`): **neither QWIIC connector has
pull-up resistors** — the pins go straight to the ESP32-S3, and the firmware relies on the
internal ~45 kΩ pull-ups. That is marginal at 100 kHz once you add cable capacitance, so put the
pull-ups on your adapter. 10 kΩ matches the Qwiic peripheral convention; 4.7 kΩ gives crisper
edges if you are only ever running this one device.

Put each pull-up behind a normally-closed solder jumper (JP1/JP2) so the board plays nicely when
daisy-chained with other Qwiic boards that also carry pull-ups.

### LED

R3 = 2.2 kΩ with a green LED gives ~0.6 mA — visible, negligible load. (Adafruit used 10 kΩ,
which is very dim.) Consider a cuttable jumper if you ever want it off.

## 4. BOM

| Ref | Part | Package | Notes |
|---|---|---|---|
| J1, J2 | JST **SM04B-SRSS-TB(LF)(SN)** | SMD, side-entry | The exact part the Rainbow uses. Two = pass-through/daisy-chain |
| J3 | — | PCB edge | The tongue; footprint supplied |
| R1, R2 | 10 kΩ ±1% | 0603 | I²C pull-ups |
| R3 | 2.2 kΩ | 0603 | LED series |
| C1 | 100 nF X7R 16 V | 0603 | Decoupling, place near the tongue |
| C2 | 1 µF X7R 16 V | 0603 | Bulk, near the connectors |
| D1 | Green LED | 0603 | Power indicator |
| JP1, JP2 | Solder jumpers | — | Normally closed, in series with R1/R2 |

## 5. Fab and assembly

- **Thickness 2.0 mm.** Say it twice on the fab drawing.
- **ENIG** surface finish minimum — HASL leaves an uneven, easily-worn contact surface.
  Hard/electroplated gold ("gold fingers") is better if you can afford it, though for an adapter
  that gets plugged in a handful of times ENIG is fine. Gold-finger service usually also demands a
  45°/30° edge bevel, which you do **not** want here — the plug expects a flat 2.0 mm tongue.
- **No soldermask** over the contacts on either face (the footprint opens the mask), and keep the
  mask boundary at least 0.2 mm back from the shoulder so it does not foul the plug's contacts.
- **No vias, no traces, no silkscreen** inside the tongue area. Route to the contacts from the
  body side only, and drop layer changes below the shoulder.
- Copper: 1 oz is fine. Trace width is irrelevant electrically here — 0.3 mm is comfortable.
- Put all components, connectors, silkscreen and the orientation marking on the **body**, clear of
  the tongue and the two slots. The plug's shroud walls occupy the slot region for the full
  8.5 mm depth.
- Mark the front face clearly — the tongue is symmetric left-to-right, so nothing mechanically
  stops the plug going on upside down, and reversed insertion puts 3.3 V onto SCL. A big
  "NOTCH THIS SIDE ↑" on the front silkscreen is the whole protection mechanism. If you want real
  protection, add series 33 Ω resistors in SDA/SCL, or a small dual-Schottky clamp.
- Deburr/inspect the routed edge of the tongue; a burr on a 2.0 mm board makes insertion feel
  wrong and can scrape the plug's contacts.

## 6. Bring-up

1. Before plugging in the Nunchuck, power the adapter from the Rainbow and check 3.3 V and GND on
   the tongue with a meter, and confirm SDA/SCL are on the faces the table above says.
2. Plug into **QWIIC2** (SDA = GPIO 44, SCL = GPIO 43). QWIIC1 (GPIO 5/6) is wired on the board
   but unused by the firmware.
3. Watch the serial monitor at 115200 — the firmware prints `-> nunchuk detected` at boot if the
   ident read at address 0x52 succeeds. Note it only probes **once at startup**, so the Nunchuck
   must be attached before power-on.
4. From 48K BASIC: `10 PRINT IN 31: GO TO 10` — expect 1 right, 2 left, 4 down, 8 up, 16 fire
   (C and Z both map to fire). The stick thresholds are ±50 counts from centre.
5. If you get "no ident": that is almost always a clone controller. The firmware does only the
   modern unencrypted handshake (`0xF0 0x55`, `0xFB 0x00`) and reads the ident immediately after
   writing `0xFA`, with no settling delay — some clones need a short delay or the old encrypted
   init.

## 7. Sources

- Adafruit Wii Nunchuck Breakout Adapter PCB — <https://github.com/adafruit/Adafruit-Wii-Nunchuck-Breakout-Adapter-PCB> (CC-BY-SA, Limor Fried / Adafruit)
- Adafruit product page and learn guide — <https://www.adafruit.com/product/4836>, <https://learn.adafruit.com/adafruit-wii-nunchuck-breakout-adapter/pinouts>
- ESP32 Rainbow hardware — <https://github.com/atomic14/esp32-zxspectrum-hardware>
- ESP32 Rainbow firmware (`Nunchuck.cpp`, `wii_i2c`, `platformio.ini`, `spectrum.cpp`) — <https://github.com/atomic14/esp32-zxspectrum>
- QWIIC connector pinout discussion — <https://github.com/atomic14/esp32-zxspectrum/discussions/7>
