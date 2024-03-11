# DMM external display

Those who don't grow up still grow old. This is especially true for my eyes. I need reading glasses to distinguish parts from each other. However, with those, I cannot see well in the distance. So, when taking measurements, I am busier putting on and taking off my glasses than with the actual measurement taking.
This little project was created to get myself some bigger digits so that I can still read the values from a distance, at least from my multimeter.

Initially, I bought the Owon XDM2041 because it is cheap and it has a HY3131 based main board and I wanted to build my own device around. But that was easier said than done. It has an RS232 connection though, which gives access to the meter's SCPI interface and gues what? It is very easy to use it for my purpose, using only a microcontroller some LED displays and some periferal components.

To reach my goal I used:
- ATmega 32U4 based dev board (Arduino Pro Micro)
- TTL UART to RS232 converter (MAX232 + 4 C 1µF/25V)
- 6 7-segment LED display (one of 'em is only used for '-')
- 5 xx595 shift registers + decoup. C
- 3  8x8 dot matrix LED display
- 3 MAX2719 dot matrix display driver
- Rob Tillaart's MATRIX7219 Arduino library present in the Arduino IDE


I used an Arduino Pro Micro board (which has an Atmel ATmega32U4). I could have used any popular Arduino boards, but this controller has both USB and UART, so I could use the USB serial for programming and debugging while keeping connection with the multimeter. The code will run on ATmega's with small modifications (you'll figure it out).

The XDM2041 does not accept TTL level serial, so a TTL to serial line level converter is required. I used a through-hole MAX232 IC for this which I wired up on a small piece of prototyping board. You can also find ready-to-use adapter boards on variuous online shops.

Big (46mm/1.8") LED 7-segment diplays are used to display the numbers, 3 dot-matrix LED displays are used for the letters. The leftmost digit is only used for displaying the '-'-sign, so if you feel it's a waste of a display, you can use one or two LEDs instead. Initially, I wanted to use one MAX2719 to drive the 6 7-segment displays but that did not work properly because my displays have two LEDs in series per segment, which made the burn too dim and flickery. Good old x595 IC to the rescue... Works very well but (remember to use a higher value for the decimal point because that only had one LED instead).

I'm sure most people with some experience in electronics can deduct the wiring from the code but I will post a schematic (when I have time to create one) as well as some pictures.
