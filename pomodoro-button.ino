const int PIN_RED = 3;
const int PIN_GREEN = 6;
const int PIN_BLUE = 9;

const int PIN_BUTTON_OUT = 7;
const int PIN_BUTTON_IN = 8;

const unsigned long BUTTON_DEBOUNCE_MILLIS = 100;

int lastButtonState = LOW;
int realButtonState = LOW;
unsigned long lastButtonDebounceMillis = 0;

bool doNotDisturbActive = false;
bool buttonPressHandled = false;

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  pinMode(PIN_BUTTON_OUT, OUTPUT);
  pinMode(PIN_BUTTON_IN, INPUT);

  digitalWrite(PIN_BUTTON_OUT, HIGH);
}

void loop() {
  if (isButtonPressed()) {
    if (!buttonPressHandled) {
      doNotDisturbActive = !doNotDisturbActive;
      buttonPressHandled = true;
    }
  } else {
    buttonPressHandled = false;  
  }

  if (doNotDisturbActive) {
    // Red
    emitColor(255, 0, 0);
  } else {
    // Green
    emitColor(0, 255, 0);
  }
}

bool isButtonPressed() {
  int buttonReading = digitalRead(PIN_BUTTON_IN);

  if (buttonReading != lastButtonState) {
    lastButtonDebounceMillis = millis();
  }

  unsigned long millisSinceLastDebounce = millis() - lastButtonDebounceMillis;

  if (millisSinceLastDebounce > BUTTON_DEBOUNCE_MILLIS) {
    realButtonState = buttonReading;
    lastButtonState = LOW;
  } else {
    realButtonState = LOW;
    lastButtonState = buttonReading;  
  }

  return realButtonState;
}

void emitColor(int r, int g, int b) {
  analogWrite(PIN_RED, r);
  analogWrite(PIN_GREEN, g);
  analogWrite(PIN_BLUE, b);
}
