#include <Adafruit_NeoPixel.h>

const int buttonPin1 = 2;      // Anslut den första knappen till pin 2
const int buttonPin2 = 3;      // Anslut den andra knappen till pin 3
const int buttonPin3 = 4;      // Anslut den tredje knappen till pin 4
const int buttonPin4 = 5;      // Anslut den fjärde knappen till pin 5
const int buzzerPin = 9;       // Anslut summer till pin 9
const int potPin = A0;         // Anslut potentiometer till A0
const int neoPixelPin = 8;     // Anslut NeoPixel-ringen till pin 8

Adafruit_NeoPixel neopixelRing = Adafruit_NeoPixel(24, neoPixelPin, NEO_GRB + NEO_KHZ800);

int lastButtonState1 = LOW;
int lastButtonState2 = LOW;
int lastButtonState3 = LOW;
int lastButtonState4 = LOW;
int canPlay = 1;

void setup() { 
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(potPin, INPUT);
  Serial.begin(9600);

  neopixelRing.begin();
  neopixelRing.show(); // Initialisera NeoPixel-ringen
}

void loop() {
  int sensorValue = analogRead(potPin);
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);
  int buttonState3 = digitalRead(buttonPin3);
  int buttonState4 = digitalRead(buttonPin4);  

  // Mappa potentiometerns värde till en oktavändring mellan -2 och 2
  int octaveChange = map(sensorValue, 0, 1023, -2, 2);

  if (buttonState1 == HIGH && lastButtonState1 == LOW && canPlay == 1) {
    Serial.println(sensorValue);
    playTone(262 * pow(2, octaveChange), 250); // Spela upp tonen C för 500 millisekunder
    setColor(25, 95, 95); // Röd färg för knapp 1
  }
  else if (buttonState2 == HIGH && lastButtonState2 == LOW && canPlay == 1) {
    playTone(330 * pow(2, octaveChange), 250); // Spela upp tonen E för 500 millisekunder
    setColor(139, 69, 19); // Grön färg för knapp 2
  }
  else if (buttonState3 == HIGH && lastButtonState3 == LOW && canPlay == 1) {
    playTone(392 * pow(2, octaveChange), 250); // Spela upp tonen G för 500 millisekunder
    setColor(128, 128, 0); // Blå färg för knapp 3
  }
  else if (buttonState4 == HIGH && lastButtonState4 == LOW && canPlay == 1) {
    playTone(440 * pow(2, octaveChange), 250); // Spela upp tonen A för 500 millisekunder
    setColor(100,149,237); // blå färg för knapp 4
  }
  noTone(buzzerPin);

  lastButtonState1 = buttonState1;
  lastButtonState2 = buttonState2;
  lastButtonState3 = buttonState3;
  lastButtonState4 = buttonState4;  
}

void playTone(int frequency, int duration) {
  tone(buzzerPin, frequency, duration);
  delay(duration); // Låt tonen spela utan att vänta
  noTone(buzzerPin);
}

void setColor(int red, int green, int blue, int purple) {
  for (int i = 0; i < neopixelRing.numPixels(); i++) {
    neopixelRing.setPixelColor(i, neopixelRing.Color(red, green, blue, purple));
  }
  neopixelRing.show();
}
