/*
  
*/

int up_pin = 12;
int down_pin = 11;
unsigned long last_heartbeat = 0;
const unsigned long WAIT_BEFORE_RAISE = 15000L; //15s
const unsigned long RAISE_TIME = 15000L; //15s
const unsigned long LOWER_TIME = 2500L; //2.5s
bool raised = true;


// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  last_heartbeat = millis();
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(up_pin, OUTPUT);
  pinMode(down_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  delay(1000);  
  raise();
}

void raise() {
    digitalWrite(up_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(RAISE_TIME);
    digitalWrite(up_pin, LOW);
    delay(1000);
    digitalWrite(down_pin, HIGH);   // turn the LED on (HIGH is the voltage level)      
    delay(LOWER_TIME);
    digitalWrite(down_pin, LOW);      
    raised = true;
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
    raised = false;
    delay(300);
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    if(raised == false && millis() - last_heartbeat > WAIT_BEFORE_RAISE) {
      raise();
    }
    delay(300);
  }
}
