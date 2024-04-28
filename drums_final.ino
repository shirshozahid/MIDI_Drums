//library initialisation
#include <MIDI.h>
#define snareDrum analogRead(A0)
#define bassDrum analogRead(A1)
#define openHat analogRead(A2)
#define closeHat analogRead(A3)
MIDI_CREATE_DEFAULT_INSTANCE();

//Variables
int pressure;
int threshold = 300;
int outputVolume;
unsigned long previousTime = 0;
const long interval = 10;
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);  // Launch MIDI and listen to channel 4
}

void loop() {
  snare();
  bass();
  open();
  close();
}

void snare() {
  unsigned long currentTime = millis();
  int hitVal = snareDrum;
  outputVolume = map(hitVal, 0, 1023, 0, 127);
  if (currentTime - previousTime >= interval) {
    if (snareDrum > threshold)  // If we have received a message
    {
      digitalWrite(LED_BUILTIN, HIGH);
      MIDI.sendNoteOn(38, outputVolume, 1);  // Send a Note 
    }
  } else {
    MIDI.sendNoteOff(38, 0, 1);  // Stop the note
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void bass() {
  unsigned long currentTime = millis();
  int hitVal = bassDrum;
  outputVolume = map(hitVal, 0, 1023, 0, 127);
  if (currentTime - previousTime >= interval) {
    if (bassDrum > threshold)  // If we have received a message
    {
      digitalWrite(LED_BUILTIN, HIGH);
      MIDI.sendNoteOn(36, outputVolume, 1);  // Send a Note 
    }
  } else {
    MIDI.sendNoteOff(36, 0, 1);  // Stop the note
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void open() {
  unsigned long currentTime = millis();
  int hitVal = openHat;
  outputVolume = map(hitVal, 0, 1023, 0, 127);
  if (currentTime - previousTime >= interval) {
    if (openHat > threshold)  // If we have received a message
    {
      digitalWrite(LED_BUILTIN, HIGH);
      MIDI.sendNoteOn(56, outputVolume, 1);  // Send a Note 
    }
  } else {
    MIDI.sendNoteOff(56, 0, 1);  // Stop the note
    digitalWrite(LED_BUILTIN, LOW);
  }
}
void close() {
  unsigned long currentTime = millis();
  int hitVal = closeHat;
  outputVolume = map(hitVal, 0, 1023, 0, 127);
  if (currentTime - previousTime >= interval) {
    if (closeHat > threshold)  // If we have received a message
    {
      digitalWrite(LED_BUILTIN, HIGH);
      MIDI.sendNoteOn(50, outputVolume, 1);  // Send a Note 
    }
  } else {
    MIDI.sendNoteOff(50, 0, 1);  // Stop the note
    digitalWrite(LED_BUILTIN, LOW);
  }
}