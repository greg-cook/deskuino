/*
Desk controller using Seeed Xiao
https://wiki.seeedstudio.com/Seeeduino-XIAO/
*/

// Pins attached to the motor controller
const int DESKSPEED_PIN = 8;
const int DESKUP_PIN = 10;
const int DESKDOWN_PIN = 9;

// Set upper and lower bound for movement speed
const int MINPWM = 128;
const int MAXPWM = 255;

// The pins for the buttons
const int UPBUTTON_PIN = 6;
const int DOWNBUTTON_PIN = 5;

int buttonPressed = 0;

void setup() {
  // delay(1000); // some microcontrollers reboot twice
  Serial.begin(115200);
  while (! Serial); // Wait until Serial is ready - Leonardo/Micro
  Serial.println(F("setup(): begin"));

  // Buttons use the built-in pull up register.
  Serial.println(F("setup(): initializing buttons"));
  pinMode(UPBUTTON_PIN, INPUT);
  digitalWrite(UPBUTTON_PIN, HIGH);
  pinMode(DOWNBUTTON_PIN, INPUT);
  digitalWrite(DOWNBUTTON_PIN, HIGH);

  // Initialize the motor controller
  Serial.println(F("setup(): initializing outputs"));
  pinMode(DESKUP_PIN, OUTPUT);
  pinMode(DESKDOWN_PIN, OUTPUT);
  pinMode(DESKSPEED_PIN, OUTPUT);

  Serial.println(F("setup(): ensuring desk is stopped"));
  deskStop();

  Serial.println(F("setup(): ready"));
}

void loop() {
  checkUpButton();
  checkDownButton();
}

void checkUpButton() {
  buttonPressed = digitalRead(UPBUTTON_PIN);
  if (buttonPressed == HIGH) {
    deskUp(MAXPWM);
  } else {
    deskStop();
  }
}

void checkDownButton() {
  buttonPressed = digitalRead(DOWNBUTTON_PIN);
  if (buttonPressed == HIGH) {
    deskDown(MAXPWM);
  } else {
    deskStop();
  }
}

void deskUp(int Speed) {
  digitalWrite(DESKUP_PIN, HIGH);
  digitalWrite(DESKDOWN_PIN, LOW);
  analogWrite(DESKSPEED_PIN, Speed);
}

void deskDown(int Speed) {
  digitalWrite(DESKUP_PIN, LOW);
  digitalWrite(DESKDOWN_PIN, HIGH);
  analogWrite(DESKSPEED_PIN, Speed);
}

void deskStop() {
  digitalWrite(DESKUP_PIN, LOW);
  digitalWrite(DESKDOWN_PIN, LOW);
}
