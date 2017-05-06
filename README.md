# HCS12 - Muzik Kutusu

-> Control PTH and get the value from PTH.

->Play 3 different songs for 15 seconds according to what is selected at
the two least significant DIP switches (00, 01, 10, 11).

-> Light PORTB LEDs according to the music. (It is up to you but at least
you can get use of the frequencies, i.e. notes.)

-> Show the number of the song on 7-segment LEDs.

-> If 00 is selected, play all three songs and each for 5 seconds.

-> 10s and 5s delay will be implemented by using Timer Overflow
Property of Timer Module.

-> The different frequencies will be generated using Output Compare
Property of Timer Module.
