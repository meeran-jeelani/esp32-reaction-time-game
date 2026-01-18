#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define BUTTON_PIN 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

enum GameState {
  WAITING,
  READY,
  SHOW_RESULT
};

GameState state = WAITING;

unsigned long startTime = 0;
unsigned long reactionTime = 0;
unsigned long waitStart = 0;
unsigned long randomDelayTime = 0;

bool lastButtonState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  randomSeed(analogRead(0));

  showWaitScreen();
  waitStart = millis();
  randomDelayTime = random(2000, 5000);
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);

  switch (state) {

    case WAITING:
      // Ignore button during waiting
      if (millis() - waitStart >= randomDelayTime) {
        showPressScreen();
        startTime = millis();
        state = READY;
      }
      break;

    case READY:
      // Detect NEW button press only
      if (lastButtonState == HIGH && currentButtonState == LOW) {
        reactionTime = millis() - startTime;
        showResult();
        state = SHOW_RESULT;
      }
      break;

    case SHOW_RESULT:
      delay(3000);
      resetGame();
      break;
  }

  lastButtonState = currentButtonState;
}

void showWaitScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  display.println("WAIT...");
  display.display();
}

void showPressScreen() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(15, 20);
  display.println("PRESS!");
  display.display();
}

void showResult() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println("Reaction Time:");
  display.setTextSize(2);
  display.setCursor(10, 30);
  display.print(reactionTime);
  display.println(" ms");
  display.display();
}

void resetGame() {
  state = WAITING;
  showWaitScreen();
  waitStart = millis();
  randomDelayTime = random(2000, 5000);
}
