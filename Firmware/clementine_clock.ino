#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

#define PIN_BIG_BUTTON 26
#define PIN_SMALL_BUTTON 27
#define PIN_ENCODER_A 28
#define PIN_ENCODER_B 29
#define PIN_ENCODER_BTN 2
#define PIN_SPEAKER 1

LiquidCrystal_I2C lcd(0x27, 16, 2);

RTC_Millis rtc;

int currentHour = 12;
int currentMinute = 0;
int currentSecond = 0;
unsigned long lastMinuteUpdate = 0;
unsigned long lastSecondUpdate = 0;
unsigned long last5MinuteSound = 0;

volatile int encoderPosition = 0;
int lastEncoderPosition = 0;
int lastEncoderA = 0;
int lastEncoderB = 0;
bool encoderPressed = false;
bool lastEncoderPressed = false;
bool timeAdjustMode = false;
int adjustField = 0;
unsigned long encoderButtonPressTime = 0;

bool bigButtonPressed = false;
bool lastBigButtonPressed = false;

bool displayNeedsUpdate = true;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Clementine Clock Starting...");

  Wire.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clementine");
  lcd.setCursor(0, 1);
  lcd.print("Clock");
  delay(2000);
  lcd.clear();

  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  DateTime now = rtc.now();
  currentHour = now.hour();
  currentMinute = now.minute();
  currentSecond = now.second();

  pinMode(PIN_BIG_BUTTON, INPUT_PULLUP);
  pinMode(PIN_SMALL_BUTTON, INPUT_PULLUP);
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
  pinMode(PIN_ENCODER_BTN, INPUT_PULLUP);
  pinMode(PIN_SPEAKER, OUTPUT);

  lastEncoderA = digitalRead(PIN_ENCODER_A);
  lastEncoderB = digitalRead(PIN_ENCODER_B);

  updateDisplay();
  
  Serial.println("Clock initialized!");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSecondUpdate >= 1000) {
    lastSecondUpdate = currentMillis;
    currentSecond++;
    if (currentSecond >= 60) {
      currentSecond = 0;
      currentMinute++;
      if (currentMinute >= 60) {
        currentMinute = 0;
        currentHour++;
        if (currentHour >= 24) {
          currentHour = 0;
        }
      }
    }
  }

  if (currentMillis - lastMinuteUpdate >= 60000) {
    lastMinuteUpdate = currentMillis;
    displayNeedsUpdate = true;
    
    if (currentMinute % 5 == 0 && currentSecond == 0) {
      if (currentMillis - last5MinuteSound >= 60000) {
        last5MinuteSound = currentMillis;
        playSound();
      }
    }
  }

  readRotaryEncoder();
  
  readButtons();

  if (timeAdjustMode) {
    handleTimeAdjustment();
  }

  if (displayNeedsUpdate) {
    updateDisplay();
    displayNeedsUpdate = false;
  }

  delay(10);
}

void readRotaryEncoder() {
    encoderPressed = !digitalRead(PIN_ENCODER_BTN);
  
  if (encoderPressed && !lastEncoderPressed) {
    timeAdjustMode = true;
    adjustField = 0;
    encoderButtonPressTime = millis();
    encoderPosition = 0;
    lastEncoderPosition = 0;
    Serial.println("Entering time adjustment mode - adjust hour");
    displayNeedsUpdate = true;
  }
  
  if (!encoderPressed && lastEncoderPressed) {
    if (timeAdjustMode) {
      if (adjustField == 0) {
        adjustField = 1;
        encoderPosition = 0;
        lastEncoderPosition = 0;
        Serial.println("Switching to minute adjustment");
        displayNeedsUpdate = true;
      } else {
        timeAdjustMode = false;
        Serial.println("Exiting time adjustment mode");
        displayNeedsUpdate = true;
      }
    }
  }
  
  lastEncoderPressed = encoderPressed;

  if (encoderPressed && timeAdjustMode) {
    int encoderA = digitalRead(PIN_ENCODER_A);
    int encoderB = digitalRead(PIN_ENCODER_B);
    
    if (encoderA != lastEncoderA || encoderB != lastEncoderB) {
      if (lastEncoderA == LOW && encoderA == HIGH) {
        if (encoderB == LOW) {
          encoderPosition++;
        } else {
          encoderPosition--;
        }
      } else if (lastEncoderB == LOW && encoderB == HIGH) {
        if (encoderA == LOW) {
          encoderPosition--;
        } else {
          encoderPosition++;
        }
      }
      
      lastEncoderA = encoderA;
      lastEncoderB = encoderB;
    }
    
    if (encoderPosition != lastEncoderPosition) {
      int change = encoderPosition - lastEncoderPosition;
      
      if (adjustField == 0) {
        currentHour += change;
        if (currentHour < 0) currentHour = 23;
        if (currentHour >= 24) currentHour = 0;
        Serial.print("Hour adjusted to: ");
        Serial.println(currentHour);
      } else {
        currentMinute += change;
        if (currentMinute < 0) {
          currentMinute = 59;
          currentHour--;
          if (currentHour < 0) currentHour = 23;
        }
        if (currentMinute >= 60) {
          currentMinute = 0;
          currentHour++;
          if (currentHour >= 24) currentHour = 0;
        }
        Serial.print("Minute adjusted to: ");
        Serial.println(currentMinute);
      }
      
      lastEncoderPosition = encoderPosition;
      displayNeedsUpdate = true;
      currentSecond = 0;
    }
  } else if (!encoderPressed) {
    lastEncoderA = digitalRead(PIN_ENCODER_A);
    lastEncoderB = digitalRead(PIN_ENCODER_B);
    encoderPosition = 0;
    lastEncoderPosition = 0;
  }
}

void readButtons() {
  bigButtonPressed = !digitalRead(PIN_BIG_BUTTON);
  
  if (bigButtonPressed && !lastBigButtonPressed) {
    Serial.println("Big button pressed");
  }
  
  lastBigButtonPressed = bigButtonPressed;
}

void handleTimeAdjustment() {
}

void updateDisplay() {
  lcd.clear();
  
  if (timeAdjustMode) {
    lcd.setCursor(0, 0);
    if (adjustField == 0) {
      lcd.print("Adjust Hour:");
    } else {
      lcd.print("Adjust Minute:");
    }
    lcd.setCursor(0, 1);
  } else {
    lcd.setCursor(0, 0);
  }
  
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", currentHour, currentMinute);
  lcd.print(timeStr);
  
  if (timeAdjustMode) {
    lcd.setCursor(5, 1);
    if (adjustField == 0) {
      lcd.print("^");
    } else {
      lcd.setCursor(3, 1);
      lcd.print("^");
    }
  }
}

void playSound() {
  
  unsigned long toneStart = millis();
  unsigned long toneDuration = 200;
  
  while (millis() - toneStart < toneDuration) {
    digitalWrite(PIN_SPEAKER, HIGH);
    delayMicroseconds(500);
    digitalWrite(PIN_SPEAKER, LOW);
    delayMicroseconds(500);
  }
  
  delay(50);
  
  toneStart = millis();
  while (millis() - toneStart < toneDuration) {
    digitalWrite(PIN_SPEAKER, HIGH);
    delayMicroseconds(416);
    digitalWrite(PIN_SPEAKER, LOW);
    delayMicroseconds(416);
  }
  
  digitalWrite(PIN_SPEAKER, LOW);
  
  Serial.println("5-minute sound played");
}

