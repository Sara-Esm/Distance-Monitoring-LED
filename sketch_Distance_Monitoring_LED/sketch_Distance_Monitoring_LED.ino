#include <LiquidCrystal.h>

const int trigPin = 9;
const int echoPin = 10;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int numLEDs = 4;
const int ledPins[numLEDs] = {6, 7, 8, 13};
const int animationDelay = 200;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Distance: ");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  lcd.setCursor(10, 0);
  lcd.print("     ");
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print(" cm");

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  updateLEDs(distance);

  delay(500);
}

void updateLEDs(int distance) {
  // Clear all LEDs
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // Update LED patterns based on distance
  if (distance <= 2) {
    // Turn off all LEDs
    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  } else if (distance < 5) {
    blinkLED(ledPins[0], 2); // Blink the first LED twice
  } else if (distance < 10) {
    blinkLED(ledPins[0], 2); // Blink the first LED twice
    blinkLED(ledPins[1], 2); // Blink the second LED twice
  } else if (distance < 15) {
    blinkLED(ledPins[0], 3); // Blink the first LED three times
    blinkLED(ledPins[1], 3); // Blink the second LED three times
    blinkLED(ledPins[2], 3); // Blink the third LED three times
  } else if (distance < 20) {
    blinkLED(ledPins[0], 4); // Blink the first LED four times
    blinkLED(ledPins[1], 4); // Blink the second LED four times
    blinkLED(ledPins[2], 4); // Blink the third LED four times
    blinkLED(ledPins[3], 4); // Blink the fourth LED four times
  } else if (distance < 25) {
    // Chasing effect: LEDs light up one after the other
    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(animationDelay);
      digitalWrite(ledPins[i], LOW);
    }
  } else if (distance < 30) {
    // Alternate blinking: Odd-numbered LEDs blink together, even-numbered LEDs blink together
    for (int i = 0; i < numLEDs; i++) {
      if (i % 2 == 0) {
        blinkLED(ledPins[i], 2); // Blink even-numbered LEDs twice
      } else {
        blinkLED(ledPins[i], 3); // Blink odd-numbered LEDs three times
      }
    }
  } else {
    // Default pattern: Blink all LEDs together
    blinkAllLEDs(3); // Blink all LEDs three times
  }
}

void blinkLED(int pin, int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pin, HIGH);
    delay(animationDelay);
    digitalWrite(pin, LOW);
    delay(animationDelay);
  }
}

void blinkAllLEDs(int count) {
  for (int i = 0; i < count; i++) {
    for (int j = 0; j < numLEDs; j++) {
      digitalWrite(ledPins[j], HIGH);
    }
    delay(animationDelay);
    for (int j = 0; j < numLEDs; j++) {
      digitalWrite(ledPins[j], LOW);
    }
    delay(animationDelay);
  }
}

