const int buttonPin = 2;
int buttonStatus = 0;
int lastButtonStatus = HIGH;
bool blinkingEnabled = false;
int currentCharIndex = 0;

char inputName[100];
int inputNameIndex = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void shortBlink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void longBlink() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void encodeCharacterToMorse(char character) {
  switch (character) {
    case 'a': shortBlink(); longBlink(); break;
    case 'b': longBlink(); shortBlink(); shortBlink(); shortBlink(); break;
    case 'c': longBlink(); shortBlink(); longBlink(); shortBlink(); break;
    case 'd': longBlink(); shortBlink(); shortBlink(); break;
    case 'e': shortBlink(); break;
    case 'f': shortBlink(); shortBlink(); longBlink(); shortBlink(); break;
    case 'g': longBlink(); longBlink(); shortBlink(); break;
    case 'h': shortBlink(); shortBlink(); shortBlink(); shortBlink(); break;
    case 'i': shortBlink(); shortBlink(); break;
    case 'j': shortBlink(); longBlink(); longBlink(); longBlink(); break;
    case 'k': longBlink(); shortBlink(); longBlink(); break;
    case 'l': shortBlink(); longBlink(); shortBlink(); shortBlink(); break;
    case 'm': longBlink(); longBlink(); break;
    case 'n': longBlink(); shortBlink(); break;
    case 'o': longBlink(); longBlink(); longBlink(); break;
    case 'p': shortBlink(); longBlink(); longBlink(); shortBlink(); break;
    case 'q': longBlink(); longBlink(); shortBlink(); longBlink(); break;
    case 'r': shortBlink(); longBlink(); shortBlink(); break;
    case 's': shortBlink(); shortBlink(); shortBlink(); break;
    case 't': longBlink(); break;
    case 'u': shortBlink(); shortBlink(); longBlink(); break;
    case 'v': shortBlink(); shortBlink(); shortBlink(); longBlink(); break;
    case 'w': shortBlink(); longBlink(); longBlink(); break;
    case 'x': longBlink(); shortBlink(); shortBlink(); longBlink(); break;
    case 'y': longBlink(); shortBlink(); longBlink(); longBlink(); break;
    case 'z': longBlink(); longBlink(); shortBlink(); shortBlink(); break;

    default: break;
  }
}

void loop() {
  buttonStatus = digitalRead(buttonPin);

  if (buttonStatus == LOW && lastButtonStatus == HIGH) {
    blinkingEnabled = !blinkingEnabled;
    currentCharIndex = 0;
  }

  lastButtonStatus = buttonStatus;

  if (blinkingEnabled) {
    if (inputName[currentCharIndex] != '\0') {
      char currentChar = inputName[currentCharIndex];
      encodeCharacterToMorse(currentChar);
      delay(1000);
      currentCharIndex++;
    } else {
      blinkingEnabled = false;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar == '\n' || inputNameIndex >= sizeof(inputName) - 1) {
      inputName[inputNameIndex] = '\0';
      inputNameIndex = 0;
      Serial.print("Blinking -  ");
      Serial.print(inputName);
      blinkingEnabled = true;
    } else {
      inputName[inputNameIndex] = incomingChar;
      inputNameIndex++;
    }
  }
}
