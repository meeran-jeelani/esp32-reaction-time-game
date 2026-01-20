#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUTTON_PIN 4

// ---------------- STATES ----------------
enum GameState {
  IDLE,
  WAITING,
  READY,
  RESULT
};

GameState state = IDLE;

// ---------------- INPUT ----------------
bool lastButtonState = HIGH;
bool buttonLocked = false;

// ---------------- TIMING ----------------
unsigned long waitStart = 0;
unsigned long randomDelay = 0;
unsigned long reactionStart = 0;
unsigned long reactionTime = 0;
unsigned long bestTime = 0;

// ---------------- UI ----------------
unsigned long animTimer = 0;
int dots = 0;

// ---------------- UI FUNCTIONS ----------------

void drawFrame() {
  display.drawRect(0, 0, 128, 64, WHITE);
}

void showIdle() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  drawFrame();
  display.setTextSize(1);
  display.setCursor(22, 18);
  display.println("REACTION GAME");
  display.setCursor(20, 40);
  display.println("Press Button");
  display.display();
}

void showWait() {
  if (millis() - animTimer > 400) {
    animTimer = millis();
    dots = (dots + 1) % 4;

    display.clearDisplay();
    display.setTextColor(WHITE);
    drawFrame();
    display.setTextSize(2);
    display.setCursor(30, 22);
    display.print("WAIT");
    for (int i = 0; i < dots; i++) display.print(".");
    display.display();
  }
}

void showPress() {
  display.clearDisplay();
  display.fillRect(0, 0, 128, 64, WHITE);
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(2);
  display.setCursor(20, 22);
  display.println("PRESS!");
  display.display();
}

void showResult() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  drawFrame();
  display.setTextSize(1);

  display.setCursor(10, 12);
  display.print("Time: ");
  display.print(reactionTime);
  display.println(" ms");

  display.setCursor(10, 30);
  display.print("Best: ");
  display.print(bestTime);
  display.println(" ms");

  display.setCursor(10, 50);
  display.println("Press to Restart");

  display.display();
}

// ---------------- SETUP ----------------

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  randomSeed(micros());
  showIdle();
}

// ---------------- LOOP ----------------

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  bool pressed = (lastButtonState == HIGH && buttonState == LOW);
  bool released = (lastButtonState == LOW && buttonState == HIGH);
  lastButtonState = buttonState;

  // Unlock button only after release
  if (released) buttonLocked = false;

  // -------- IDLE --------
  if (state == IDLE) {
    if (pressed && !buttonLocked) {
      buttonLocked = true;

      randomDelay = random(2000, 5000);
      waitStart = millis();
      animTimer = millis();
      dots = 0;

      state = WAITING;
    }
  }

  // -------- WAITING --------
  else if (state == WAITING) {
    showWait();

    if (millis() - waitStart >= randomDelay) {
      showPress();

      // RESET button logic for clean reaction press
      lastButtonState = HIGH;
      buttonLocked = false;

      reactionStart = millis();
      state = READY;
    }
  }

  // -------- READY --------
  else if (state == READY) {
    if (pressed && !buttonLocked) {
      buttonLocked = true;

      reactionTime = millis() - reactionStart;
      if (bestTime == 0 || reactionTime < bestTime) {
        bestTime = reactionTime;
      }

      showResult();
      state = RESULT;
    }
  }

  // -------- RESULT --------
  else if (state == RESULT) {
    if (pressed && !buttonLocked) {
      buttonLocked = true;
      showIdle();
      state = IDLE;
    }
  }
}
