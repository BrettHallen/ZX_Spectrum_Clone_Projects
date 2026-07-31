# LUT216 by [Z.A.N.](https://sblive.narod.ru/index.htm)
My attempt at some English translation for Z.A.N.'s BMC-based Sinclair ZX Spectrum clone.<br>

WORK IN PROGRESS!<br>

Here's a comparison of the LUT216 board (a Spectrum clone) with a ZX81:<br>

![Comparison of LUT216 with ZX81](/LUT216/ZX81_vs_ULA216.jpg)

The name "LUT216" comes from (I believe):
- "ЛУТ" (LUT) = Laser-UV Technology (Лазерно-Ультрафиолетовая Технология), the Russian term for the Toner Transfer + UV exposure/photoresist method of DIY PCB production
- "216" = the КА1515ХМ1-216 [Базового Матричного Кристалла](https://ru.wikipedia.org/wiki/1515ХМ1) (Basic Matrix Crystal) that is the heart of this computer

[Original Page (RU)](https://sblive.narod.ru/ZX-Spectrum/LUT216/LUT216.htm)

## КА1515ХМ1-216 Basic Matrix Crystal
The BMC is the heart of this design - I think this chip is the pinnacle of Soviet Speccy engineering!<br>

The transliteration of the part ID is "KA1515HM1".  The "-216" indicates the customised version for implementing in ZX Spectrum clones to replace the ULA (and more).  There were [others for the ZX Spectrum](https://martin.hinner.info/iccmap/ru/info/ka1515xm1.html) but the -216 is the only one I've ever come across:
- КА1515ХМ1-171
- КА1515ХМ1-433
- КА1515ХМ1-6004
- КА1515ХМ1-6006
- КА1515ХМ1-6008

You can find some detailed information in Russian [here](https://zxbyte.org/t34vg1.htm).

I also have an English pinout diagram [here](/LUT216/KA1515XM1-216_pinout.pdf).

## [Original Information](/LUT216/Originals)
A copy of the original files from Z.A.N.'s page for reference:
- LUT216.rar: Gerbers
- LUT216SCH.GIF: schematic
- LUT216MontMono.png: board layout

## Notes in Russian
- The first DRAM pins are connected together to simplify upgrading.
- ROM_LOCK = ROM lock
- PORT_LOCK = Kempston port lock (required for connecting a TR-DOS controller)
- /WRPO = relevant only when connecting the 580ВВ55 (8255)
- The default ROM pin combination is designed for installing 27128 or 27512 ROM chips with the Pentagon layout (ROM 27128/27512 pins 1, 27, and 28 are connected to +5V)

## Western Parts List
See also [here](https://elcomps.com/en/a72) for a general list of Soviet - Western 74-series ID conversion.<br>

Note! Soviet parts are generally 2.5mm pitch and not 2.54mm - this doesn't matter much for smaller ICs but it can cause a problem with larger ICs and with pin headers!<br>

All mistakes are mine - I couldn't find a BOM so have generated this from the schematic.<br>

| Part ID | Soviet Part    | Western Part| Part Type                    |
|---------|----------------|-------------|------------------------------|
| D1      | К555ЛН1        | 74LS04      | Hex inverter                 |
| D2      | К555АП3        | 74LS240     | Octal inverter line driver   |
| D3      | КА1515ХМ1-216  |             | Basic matrix crystal (= ULA) |
| D4      | К561ЛН2        | CD4049      | CMOS hex inverter            |
| D5      | КР1858ВМ1      | Z80         | CPU                          |
| D6      | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D7      | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D8      | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D9      | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D10     | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D11     | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D12     | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D13     | КР565РУ5 [0]   | 4164        | 64Kbit DRAM                  |
| D14     |                | 27128       | 16KByte EPROM [1]            |
| Q1      |                | 8MHz        | Crystal                      |
| T1-T5   | КТ315          | BC547 [2]   | NPN transistor (B-C-E)       |
| VD1-15  |                | 1N4148      | Diode                        |
| R1      |                | 510Ω        | Green/Brown/Brown            |
| R2      |                | 510Ω        | Green/Brown/Brown            |
| R3      |                | 10KΩ        | Brown/Black/Orange           |
| R4      |                | 10KΩ        | Brown/Black/Orange           |
| R5      |                | 10KΩ        | Brown/Black/Orange           |
| R6      |                | 10KΩ        | Brown/Black/Orange           |
| R7      |                | 10KΩ        | Brown/Black/Orange           |
| R8      |                | 10KΩ        | Brown/Black/Orange           |
| R9      |                | 10KΩ        | Brown/Black/Orange           |
| R10     |                | 10KΩ        | Brown/Black/Orange           |
| R11     |                | 1KΩ         | Brown/Black/Red              |
| R12     |                | 1KΩ         | Brown/Black/Red              |
| R13     |                | 5.1KΩ       | Green/Brown/Red              |
| R14     |                | 2KΩ         | Red/Black/Red                |
| R15     |                | 430Ω        | Yellow/Orange/Brow           |
| R16     |                | 10KΩ        | Brown/Black/Orange           |
| R17     |                | 3MΩ         | Orange/Black/Green           |
| R18     |                | 10KΩ        | Brown/Black/Orange           |
| R19     |                | 10KΩ        | Brown/Black/Orange           |
| R20     |                | 10KΩ        | Brown/Black/Orange           |
| R21     |                | 10KΩ        | Brown/Black/Orange           |
| R22     |                | 10KΩ        | Brown/Black/Orange           |
| R23     |                | 300Ω        | Orange/Black/Brown           |
| R24     |                | 10KΩ        | Brown/Black/Orange           |
| R25     |                | 510Ω        | Green/Brown/Brown            |
| R26     |                | 10KΩ        | Brown/Black/Orange           |
| R27     |                | 10KΩ        | Brown/Black/Orange           |
| R28     |                | 1KΩ         | Brown/Black/Red              |
| R29     |                | 510Ω        | Green/Brown/Brown            |
| R30     |                | 510Ω        | Green/Brown/Brown            |
| R31     |                | 510Ω        | Green/Brown/Brown            |
| R32     |                | 510Ω        | Green/Brown/Brown            |
| R33     |                | 510Ω        | Green/Brown/Brown            |
| R34     |                | 510Ω        | Green/Brown/Brown            |
| R35     |                | 510Ω        | Green/Brown/Brown            |
| R36     |                | 510Ω        | Green/Brown/Brown            |
| R37     |                | 3.3KΩ       | Orange/Orange/Red            |
| R38     |                | 3.3KΩ       | Orange/Orange/Red            |
| R39     |                | 3.3KΩ       | Orange/Orange/Red            |
| R40     |                | 6.2KΩ       | Blue/Red/Red                 |
| R41     |                | 3.3KΩ       | Orange/Orange/Red            |
| R42     |                | 3.3KΩ       | Orange/Orange/Red            |
| R43     |                | 3.3KΩ       | Orange/Orange/Red            |
| R44     |                | 3.3KΩ       | Orange/Orange/Red            |
| R45     |                | 100Ω        | Brown/Black/Brown            |
| R46     |                | 3.3KΩ       | Orange/Orange/Red            |
| R47     |                | 100Ω        | Brown/Black/Brown            |
| R48     |                | 3.3KΩ       | Orange/Orange/Red            |
| R49     |                | 100Ω        | Brown/Black/Brown            |
| R50     |                | 6.2KΩ       | Blue/Red/Red                 |
| R51     |                | 3.3KΩ       | Orange/Orange/Red            |
| R52     |                | 10KΩ        | Brown/Black/Orange           |
| R53     |                | 1.5KΩ       | Brown/Green/Red              |
| R54     |                | 2KΩ         | Red/Black/Red                |
| R55     |                | 100Ω        | Brown/Black/Brown            |
| R65 [3] |                | 1KΩ         | Brown/Black/Red              |
| L1      | ДМ-0.2-200 [4] | 200µH       | Axial inductor               |
| C1      |                | (?) [5]     | Ceramic                      |
| C3      |                | 33nF        | Ceramic (333)                |
| C4      |                | 100nF       | Ceramic (104)                |
| C5      |                | 300pF       | Ceramic (301)                |
| C6      |                | 1µF (?) [6] | Electrolytic Capacitor       |
| C7      |                | 100µF       | Electrolytic Capacitor       |
| C8      |                | 100nF       | Ceramic (104)                |
| C9      |                | 68nF [7]    | Ceramic (683)                |
| C15     |                | 100µF       | Electrolytic Capacitor       |
| C16     |                | 68nF [7]    | Ceramic (683)                |
| C17     |                | 68nF [7]    | Ceramic (683)                |
| C18     |                | 68nF [7]    | Ceramic (683)                |
| C19     |                | 68nF [7]    | Ceramic (683)                |
| C20     |                | 68nF [7]    | Ceramic (683)                |
| C21     |                | 68nF [7]    | Ceramic (683)                |
| C22     |                | 68nF [7]    | Ceramic (683)                |
| C23     |                | 68nF [7]    | Ceramic (683)                |
| C24     |                | 68nF [7]    | Ceramic (683)                |
| C25     |                | 68nF [7]    | Ceramic (683)                |
| C26     |                | 68nF [7]    | Ceramic (683)                |
| C27     |                | 68nF [7]    | Ceramic (683)                |
| X1      |                | MAB5SH      | 5-pin DIN for joystick       |
| X2      |                | MAB5SH      | 5-pin DIN for RGB video      |
| X3      |                | MAB5SH      | 5-pin DIN for tape           |
| POWER   |                |             | 1x4 pin header               |
| SPKR    |                |             | 1x2 pin header               |
| RESET   |                |             | 1x2 pin header               |
| SV2     |                |             | 2x8 DIP ribbon connector [8] |


- Note 0: Original Soviet parts *might* be available on ebay: try searching for "kr565ru5"
- Note 1: D14 has space for a 28 or 32 pin EPROM and it configured for a 27128 or 27512.  Address lines above A13 are not used.
- Note 2: The KT-13 (flat plastic) package has pin order B-C-E, if you are using a Western equivalent (i.e. BC337, BC547 or 2N3904) be sure to check the pin order!  However the Soviet parts seem to be easily available on ebay so I'd just source them.
- Note 3: I suspect this should be R56
- Note 4: I guessed at the Soviet inductor (choke) part ID - these should be available on ebay: try searching for "200uh soviet choke"
- Note 5: Unspecified on schematic, I assume you match the capacitor value to your particular particular crystal (i.e. 22pF, 220)
- Note 6: Unspecified on schematic, used in reset circuit so assuming 1µF electrolytic
- Note 7: You could use standard 100nF (104) instead of 68nF for these decoupling capacitors
- Note 8: This is for the keyboard connector, I think Harting 09170169622 or similar

| Resistor  | Count  |
|-----------|--------|
| 100Ω      | 4      |
| 300Ω      | 1      |
| 430Ω      | 1      |
| 510Ω      | 11     |
| 1KΩ       | 4      |
| 1.5KΩ     | 1      |
| 2KΩ       | 2      |
| 3.3KΩ     | 10     |
| 5.1KΩ     | 1      |
| 6.2KΩ     | 2      |
| 10KΩ      | 18     |
| 3MΩ       | 1      |
| **Total** | **56** |

![LUT216 schematic](/LUT216/Originals/LUT216SCH.gif)

![LUT216 board layout](/LUT216/Originals/LUT216MontMono.png)
