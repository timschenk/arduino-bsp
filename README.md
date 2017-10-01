BSP Eurorack Breakout
=====================

Eurorack breakout box for Beatstep Pro. It takes one midi in and has 14 CV outs (8+3+3). This is the first use case.
As it takes MIDI in you can use it with any midi device.

On the other hand you can see this as a general development board, to test ideas.
It uses 6 analog channels and 9 digital channels (4 pwm channels).
All channels can be set as input or output by software.

As far as I understood, its possible to set 2 pwm channels to 16 bit by software (http://playground.arduino.cc/Code/Timer1).
You could have a higher bit depth (default is 10 Bit) on analog inputs with oversampling.

Thoughts
========

There is still enough free memory on the arduino to hold code. There could be with MIDI CC selectable functions.
One could be a humanize function to delay messages for a random time or to randomize velocity.
An other could be a chord function, whenever there comes a note on SEQ1/SEQ2 in, it sends a chord for this note. And so on...

Requirements:
=============

https://github.com/wizard97/ArduinoRingBuffer
https://github.com/FortySevenEffects/arduino_midi_library.git



this is just a sketch / work in progress by http://tim-schenk.de
Thanks to Philip Wise aka Pusherman for making board layouts