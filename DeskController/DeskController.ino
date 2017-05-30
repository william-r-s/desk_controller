/*
  
*/

int up_pin = 12;
int down_pin = 11;
unsigned long last_heartbeat = 0;
const unsigned long WAIT_BEFORE_RAISE = 30000L; //30s
const unsigned long RAISE_TIME = 15000L; //15s
const unsigned long LOWER_TIME = 2500L; //2.5s
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(up_pin, OUTPUT);
  pinMode(down_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT);  
  
  delay(1000);  
  digitalWrite(LED_BUILTIN, HIGH);
  raise();
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  last_heartbeat = millis();
  while (Serial.available() > 0 && millis() - last_heartbeat < 1000) {
    Serial.read();  // read and discard any input
  }
  
}

boolean raised() {
  return analogRead(sensorPin) < 100;
}

void raise() {
    if(raised()) {
      return;
    }
    digitalWrite(up_pin, HIGH);
    delay(RAISE_TIME);
    digitalWrite(up_pin, LOW);
    delay(1000);
    digitalWrite(down_pin, HIGH);
    delay(LOWER_TIME);
    digitalWrite(down_pin, LOW);      

}

// the loop function runs over and over again forever
void loop() {
  int inByte = 0;
  if (Serial.available() > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    // get incoming byte:
    inByte = Serial.read();
    unsigned long now = millis ();
    while (Serial.available() > 0 && millis() - now < 1000) {
      Serial.read();  // read and discard any input
    }
    last_heartbeat = millis();
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    if(raised() == false && millis() - last_heartbeat > WAIT_BEFORE_RAISE) {
      raise();
    }
    delay(300);
  }
}
