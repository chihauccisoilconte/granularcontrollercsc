
//this is the code for the "granular controller"
//made in 2021 by Nicolò Merendino aka "Chi ha ucciso Il Conte?" - https://chihauccisoilconte.eu/
//this project was developed as part of the computer music course at University of Padua

//libraries required:
// MIDI library - https://github.com/FortySevenEffects/arduino_midi_library
// Neopixel library - https://github.com/adafruit/Adafruit_NeoPixel

#include <MIDI.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN        3
#define NUMPIXELS 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

const int DEFAULT_MIDI_CHANNEL = 1;
MIDI_CREATE_DEFAULT_INSTANCE();
const int button1Pin = 2;
int note1 = 0;


void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);

  Serial.begin(38400);

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif

  pinMode(button1Pin, INPUT);

  pixels.begin();

}

void loop() {

  int sensorValue0 = analogRead(A0);
  int sensorValue1 = analogRead(A1);
  int sensorValue2 = analogRead(A2);
  int sensorValue3 = analogRead(A3);
  int button1State = digitalRead(button1Pin);




  int cc0 = map(sensorValue0, 125, 918, 0, 127);
  if (cc0 > 1) {
    MIDI.sendControlChange(1, cc0, DEFAULT_MIDI_CHANNEL);
  }
  int cc1 = map(sensorValue1, 125, 918, 0, 127);
  if (cc1 > 1) {
    MIDI.sendControlChange(2, cc1, DEFAULT_MIDI_CHANNEL);
  }

  int cc2 = map(sensorValue2, 125, 918, 0, 127);
  if (cc2 > 1) {
    MIDI.sendControlChange(2, cc2, DEFAULT_MIDI_CHANNEL);
  }

  int cc3 = map(sensorValue3, 143, 1015, 0, 127);
  if (cc3 > 10) {
    MIDI.sendControlChange(4, cc3, DEFAULT_MIDI_CHANNEL);

  }
  int ledon = map(cc2, 0, 127, 0, 6);




  for (int i = 0; i < ledon; i++) {

    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();


    pixels.clear();


    if (note1 == 0) {


      MIDI.sendNoteOn(43, 127, DEFAULT_MIDI_CHANNEL);
      note1 = 1;
    }
  } else {


    if (note1 == 1) {

      MIDI.sendNoteOff(43, 0, DEFAULT_MIDI_CHANNEL);
    }
    note1 = 0;

  }

}
}

//this machine kills fascists
