#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String emotions[] = {"happy", "sad", "surprised", "angry", "blink"};
int currentEmotionIndex = 0;
unsigned long previousMillis = 0;
const long interval = 2000; // 2 giây
int animationSteps = 5;    
int currentStep = 0;
bool isAnimating = false;
String previousEmotion = "";

void drawVectorEyes(String emotion, int step) {
  int eyeX1 = 10;
  int eyeY = 15;
  int eyeSize = 50;
  int pupilSize = 20;
  int eyeX2 = 75;

  display.clearDisplay();

  if (emotion == "happy") {
    display.fillRoundRect(eyeX1, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    display.fillRoundRect(eyeX2, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    int pupilOffsetY = map(step, 0, animationSteps, 0, -5);
    display.fillCircle(eyeX1 + eyeSize / 2, eyeY + eyeSize / 2 + pupilOffsetY, pupilSize / 2, SSD1306_BLACK);
    display.fillCircle(eyeX2 + eyeSize / 2, eyeY + eyeSize / 2 + pupilOffsetY, pupilSize / 2, SSD1306_BLACK);
    display.drawLine(eyeX1 + 5, eyeY + 5, eyeX1 + eyeSize - 5, eyeY + 5, SSD1306_BLACK);
    display.drawLine(eyeX2 + 5, eyeY + 5, eyeX2 + eyeSize - 5, eyeY + 5, SSD1306_BLACK);
  } else if (emotion == "sad") {
    display.fillRoundRect(eyeX1, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    display.fillRoundRect(eyeX2, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    int pupilOffsetY = map(step, 0, animationSteps, 0, 5);
    display.fillRect(eyeX1 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY, pupilSize, pupilSize, SSD1306_BLACK);
    display.fillRect(eyeX2 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY, pupilSize, pupilSize, SSD1306_BLACK);
    display.drawLine(eyeX1 + 5, eyeY + eyeSize - 5, eyeX1 + eyeSize - 5, eyeY + eyeSize - 5, SSD1306_BLACK);
    display.drawLine(eyeX2 + 5, eyeY + eyeSize - 5, eyeX2 + eyeSize - 5, eyeY + eyeSize - 5, SSD1306_BLACK);
  } else if (emotion == "surprised") {
    display.fillRoundRect(eyeX1, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    display.drawRoundRect(eyeX2, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    int pupilOffsetY = map(step, 0, animationSteps, 0, 0);
    display.fillTriangle(
      eyeX1 + eyeSize / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY,
      eyeX1 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize + pupilSize) / 2 + pupilOffsetY,
      eyeX1 + (eyeSize + pupilSize) / 2, eyeY + (eyeSize + pupilSize) / 2 + pupilOffsetY,
      SSD1306_BLACK
    );
    display.fillTriangle(
      eyeX2 + eyeSize / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY,
      eyeX2 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize + pupilSize) / 2 + pupilOffsetY,
      eyeX2 + (eyeSize + pupilSize) / 2, eyeY + (eyeSize + pupilSize) / 2 + pupilOffsetY,
      SSD1306_BLACK
    );
    display.drawCircle(eyeX1 + eyeSize / 2, eyeY + eyeSize / 2, (eyeSize / 2) + 3, SSD1306_WHITE);
    display.drawRoundRect(eyeX2 - 3, eyeY - 3, eyeSize + 6, eyeSize + 6, 8, SSD1306_WHITE);
  } else if (emotion == "angry") {
    display.fillRoundRect(eyeX1, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    display.fillRoundRect(eyeX2, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    int pupilOffsetY = map(step, 0, animationSteps, 0, 0);
    display.fillRect(eyeX1 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY, pupilSize, pupilSize, SSD1306_BLACK);
    display.fillRect(eyeX2 + (eyeSize - pupilSize) / 2, eyeY + (eyeSize - pupilSize) / 2 + pupilOffsetY, pupilSize, pupilSize, SSD1306_BLACK);
    int eyebrowOffsetY = map(step, 0, animationSteps, 0, 0);
    display.drawLine(eyeX1, eyeY + eyeSize / 2 + eyebrowOffsetY, eyeX1 + eyeSize, eyeY + eyeSize / 2, SSD1306_BLACK);
    display.drawLine(eyeX2, eyeY + eyeSize / 2 + eyebrowOffsetY, eyeX2 + eyeSize, eyeY + eyeSize / 2, SSD1306_BLACK);
  } else if (emotion == "blink") {
    unsigned long blinkDuration = 600; 
    unsigned long blinkStartTime = millis() % blinkDuration;
    unsigned long blinkEndTime = blinkDuration - blinkStartTime;
    bool blinkState = (blinkStartTime < (blinkDuration / 2));

    if (blinkState) {
      display.drawLine(eyeX1, eyeY + eyeSize / 2, eyeX1 + eyeSize, eyeY + eyeSize / 2, SSD1306_WHITE);
      display.drawLine(eyeX2, eyeY + eyeSize / 2, eyeX2 + eyeSize, eyeY + eyeSize / 2, SSD1306_WHITE);
    } else {
      display.fillRoundRect(eyeX1, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
      display.fillRoundRect(eyeX2, eyeY, eyeSize, eyeSize, 8, SSD1306_WHITE);
    }
  }

  display.display();
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  drawVectorEyes(emotions[currentEmotionIndex], 0);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    isAnimating = true;
    currentStep = 0;
    previousEmotion = emotions[currentEmotionIndex];

    currentEmotionIndex++;
    if (currentEmotionIndex >= sizeof(emotions) / sizeof(emotions[0])) {
      currentEmotionIndex = 0;
    }
  }

  if (isAnimating) {
    drawVectorEyes(emotions[currentEmotionIndex], currentStep);

    currentStep++;
    if (currentStep >= animationSteps) {
      isAnimating = false;
    }
  }
}
