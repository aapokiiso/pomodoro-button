const int PIN_RED = 3;
const int PIN_GREEN = 6;
const int PIN_BLUE = 9;

const int PIN_BUTTON_OUT = 7;
const int PIN_BUTTON_IN = 8;

const int POMODORO_MINUTES = 25;
const unsigned long MINUTE_MILLIS = 60000; // avoid int overflow
const unsigned long POMODORO_MILLIS = POMODORO_MINUTES * MINUTE_MILLIS;

const unsigned long BUTTON_DEBOUNCE_MILLIS = 50;

unsigned long pomodoroStartMillis = 0;

int realButtonState = LOW;
unsigned long lastButtonDebounceMillis = 0;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(PIN_BUTTON_OUT, OUTPUT);
  pinMode(PIN_BUTTON_IN, INPUT);
}

void loop() {
  if (isPomodoroOngoing()) {
    emitColor(255, 0, 0);
  } else {
    if (isButtonPressed()) {
      startPomodoro();
    }  
  }
}

bool isButtonPressed() {
  int buttonReading = digitalRead(PIN_BUTTON_IN);

  if (buttonReading != realButtonState) {
    lastButtonDebounceMillis = millis();
  }

  unsigned long millisSinceLastDebounce = millis() - lastButtonDebounceMillis;

  if (millisSinceLastDebounce > BUTTON_DEBOUNCE_MILLIS) {
    realButtonState = buttonReading;
  }

  return realButtonState;
}

bool isPomodoroOngoing() {
  unsigned long currentMillis = millis();
  unsigned long pomodoroEndMillis = pomodoroStartMillis + POMODORO_MILLIS;
  
  return pomodoroStartMillis > 0 && currentMillis < pomodoroEndMillis;
}

void startPomodoro() {
  pomodoroStartMillis = millis();
}

void emitColor(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}

