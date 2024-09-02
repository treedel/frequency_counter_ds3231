# FrequencyCounterEref
 A high accuracy frequency counter implementation that uses hardware counter and external reference signal for measurement.
 This allows more accurate measurement even with higher frequencies as the output is not dependent on crystal provided on
 the board.

 ## Components used
 1) Arduino Mega
 2) DS3231 (Or any 1Hz external oscillator)

 ## Instructions
 Configure the SQW pin of DS3231 to output signal of frequency 1Hz but this is not necessary and any other external
 reference signal could be used as long as its accurate. The same sketch could be adapted to uno and other boards just by
 adjusting the timer number. For arduino uno, use timer 1 and also use appropriate counter pin for providing input signal.

 Connect the pins according to the layout provided below and upload the sketch.

 Pin layout:
 - External 1Hz reference signal    - D18
 - Test input signal                - D47