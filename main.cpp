#include <Arduino.h>
#define LED_1 10
#define LED_2 9
#define LED_3 8
#define LED_4 7
#define LED_RGB_RED 6
#define LED_RGB_GREEN 5
#define LED_RGB_BLUE 4
#define BUTTON_1 3
#define BUTTON_2 2

// put function declarations here:
void isFree(int x);
void batteryState(int x);
void loader();
void chargingFinished();

int buttonState1 = 0;
int buttonState2 = 0;
int state = 1; // state = 0 => ocupata, state = 1 => libera
int percentage = 0;

void setup() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_RGB_BLUE, OUTPUT);
  pinMode(LED_RGB_GREEN, OUTPUT);
  pinMode(LED_RGB_RED, OUTPUT);
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(LED_RGB_BLUE, HIGH);
  // digitalWrite(LED_RGB_GREEN, HIGH);
  // loader(once);
  isFree(state);
  buttonState1 = digitalRead(BUTTON_1);
  buttonState2 = digitalRead(BUTTON_2);
  if(buttonState1 == LOW)
  {
    state = 0;
  }
  isFree(state);
  if(state == 0)
    batteryState(percentage);
  if(buttonState2 == LOW)
  {
    delay(1000);
    if(buttonState2 == LOW && state == 0)
    {
      chargingFinished();
      percentage = 0;
    }
  }
}

// put function definitions here:
void isFree(int state)
{
  if(state == 1)
  {
    digitalWrite(LED_RGB_GREEN, HIGH);
    digitalWrite(LED_RGB_RED, LOW);
    digitalWrite(LED_RGB_BLUE, LOW);
  }
  else
  {
    digitalWrite(LED_RGB_RED, HIGH);
    digitalWrite(LED_RGB_GREEN, LOW);
    digitalWrite(LED_RGB_BLUE, LOW);
  }
}

void batteryState(int x)
{
  if(percentage >= 0 && percentage < 25)
  {
    digitalWrite(LED_1, HIGH);
    delay(300);
    digitalWrite(LED_1, LOW);
    delay(300);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    percentage += 5;
  }
  if(percentage >= 25 && percentage < 50)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    delay(300);
    digitalWrite(LED_2, LOW);
    delay(300);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    percentage += 5;
  }
  if(percentage >= 50 && percentage < 75)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    delay(300);
    digitalWrite(LED_3, LOW);
    delay(300);
    digitalWrite(LED_4, LOW);
    percentage += 5;
  }
  if(percentage >= 75 && percentage < 100)
  {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    delay(300);
    digitalWrite(LED_4, LOW);
    delay(300);
    percentage += 5;
  }
  if(percentage == 100)
  {
      chargingFinished();
  }
}

void chargingFinished()
{
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);
    delay(300);
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);
    delay(300);
  }
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
  state = 1;
  isFree(state);
  percentage = 0;
}