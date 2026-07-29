# Astra/Астра Information
A Soviet-era Sinclair ZX Spectrum clone from Minsk in the Byelorussian SSR.<br>

Its full name is "Универсальная Телеигровая Приставка Астра", or "Universal Television Game Console Astra".<br>

The files found here are from [ZXBYTE's site](https://zxbyte.org), translated to English where required and with my own additional information added.<br>

## [Schematics](/Astra/Schematics)
Schematics and board layout with Western-equivalent part IDs added.<br>

IMPORTANT - several of the interface pinouts have conflicting pin assignments when comparing the schematic with the manual.  The manual pinout matches my machine.<br>

## Cassette Pinout (X1)
The cassette interface uses a 5-pin DIN labelled "МАГ" (Магнетофон).<br>

IMPORTANT NOTE!  The [schematic pinout](/Astra/Schematics/X1_Pinout_RU.jpg) disagrees with the [manual pinout](/Astra/Schematics/Astra_Manual_Pinout.jpeg)!  For my machine I have used the manual's pinout.<br>

Note that the schematic lists IN FL (signal 33) and OUT FL (signal 34) but I can't see where they are used.<br>

| Pin | Signal         |
|-----|----------------|
| 1   | EAR (Вх. Маг)  |
| 2   | Ground (0V)    |
| 3   | MIC (Вых. Маг) |
| 4   | IN FL (?)      |
| 5   | OUT FL (?)     |

Now if we look at the manual's pinout:<br>

| Pin | Signal      |
|-----|-------------|
| 1   | MIC (Выход) |
| 2   | Ground (0V) |
| 3   | EAR (Вход)  |
| 4   |             |
| 5   |             |

## Video Pinout (X3)
The audio and video are output via a 2x4 РГ1Н-1 connector labelled "ТВ".  On the [schematic](/Astra/Schematics/X3_Pinout_RU.jpg) it is interface "X3".<br>

| Pin | Signal                   |
|-----|--------------------------|
| 1   | Brightness (8/16)        |
| 2   | Blue                     |
| 3   | Green                    |
| 4   | Red                      |
| 5   | Video (Видео)            |
| 6   | Audio (УНЧ)              |
| 7   | Inverted sync (Инверсия) |
| 8   | Ground (Общий)           |

The manual pinout lists pin 1 as "Полутон" or half-tone which seems to match.<br>

## Power Pinout (X4)
The power input is a 5-pin DIN labelled "БП" (Блок Питания).  On the schematic is it interface "X4", but in the [manual pinout](/Astra/Schematics/Astra_Manual_Pinout.jpeg) it is interface "X2".<br>

Note that the schematic lists ±12V but I don't see it actually used - signals 31 & 32 on the schematic - follow the manual pinout.<br>

| Pin | Signal   |
|-----|----------|
| 1   | +5V      |
| 2   |          |
| 3   | 0V       |
| 4   | -12V (?) |
| 5   | +12V (?) |

## Useful Links
- [ZXBYTE](https://zxbyte.org/astra.htm)

## Youtube Videos
- [Part 1](https://youtu.be/gDP2ERXGaYo)
- [Part 2](https://youtu.be/xESQuC1y398)
- [Part 3](https://youtu.be/SmFEAmI-PiA)
- [Part 4](https://youtu.be/jdW-dMJSBxg)
- 

  

