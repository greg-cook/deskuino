/*
Desk controller using Seeed Xiao
https://wiki.seeedstudio.com/Seeeduino-XIAO/
*/

// Pins attached to the motor controller
const int IN1_PIN = 9;
const int IN2_PIN = 10;
const int PWM_PIN = 8;

// Set upper and lower bound for movement speed
const int MINPWM = 128;
const int MAXPWM = 255;

// The pin number attached to the button.
const int UPBUTTON_PIN = 5;
const int DOWNBUTTON_PIN = 6;

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
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(PWM_PIN, OUTPUT);

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
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(PWM_PIN, Speed);
}

void deskDown(int Speed) {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(PWM_PIN, Speed);
}

void deskStop() {
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
}


