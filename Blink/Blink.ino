/*
  Blink

  Developer: Ty Robicheaux
  Date: 2.13.26

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://docs.arduino.cc/hardware/

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/basics/Blink/
*/

// the setup function runs once when you press reset or power the board
// ------------------------------------
// Generic Police Siren
// Flashing Lights + PWM Fade LED
// ------------------------------------

int redLED = 10;
int blueLED = 9;
int speaker = 11;
int fadeLED = 6;   // NEW PWM Fade LED

// -------- Flashing Lights --------
unsigned long previousFlash = 0;
int flashInterval = 100;
bool lightState = false;

// -------- Fade LED --------
unsigned long previousFade = 0;
int fadeInterval = 20;   // Smaller = faster fade
int brightness = 0;
int fadeAmount = 5;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(fadeLED, OUTPUT);
}

// ----------------------------
// Handle Alternating Lights
// ----------------------------
void handleLights() {
  unsigned long currentTime = millis();

  if (currentTime - previousFlash >= flashInterval) {
    previousFlash = currentTime;

    lightState = !lightState;

    digitalWrite(redLED, lightState);
    digitalWrite(blueLED, !lightState);
  }
}

// ----------------------------
// Handle PWM Fade LED
// ----------------------------
void handleFade() {
  unsigned long currentTime = millis();

  if (currentTime - previousFade >= fadeInterval) {
    previousFade = currentTime;

    analogWrite(fadeLED, brightness);

    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;  // Reverse fade direction
    }
  }
}

void loop() {

  // =========================
  // WAIL MODE
  // =========================
  for (int freq = 600; freq <= 1400; freq += 3) {
    tone(speaker, freq);
    handleLights();
    handleFade();
    delay(5);
  }

  for (int freq = 1400; freq >= 600; freq -= 3) {
    tone(speaker, freq);
    handleLights();
    handleFade();
    delay(5);
  }

  // =========================
  // YELP MODE
  // =========================
  for (int i = 0; i < 3; i++) {

    for (int freq = 900; freq <= 1500; freq += 15) {
      tone(speaker, freq);
      handleLights();
      handleFade();
      delay(3);
    }

    for (int freq = 1500; freq >= 900; freq -= 15) {
      tone(speaker, freq);
      handleLights();
      handleFade();
      delay(3);
    }
  }

}

