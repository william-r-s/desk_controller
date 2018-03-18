
int up_pin = 12;
int down_pin = 11;
unsigned long last_heartbeat = 0;
const unsigned long WAIT_BEFORE_RAISE = 0L; //0s
const unsigned long RAISE_TIME = 15000L; //15s
const unsigned long LOWER_TIME = 1000L; //1s

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(up_pin, OUTPUT);
  pinMode(down_pin, OUTPUT);
  digitalWrite(up_pin, LOW);  
  digitalWrite(down_pin, LOW);      
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);    
  Serial.write(42);
  digitalWrite(LED_BUILTIN, HIGH);  
  
//  delay(1000);
//  digitalWrite(LED_BUILTIN, LOW);   

}

void raise() { 
    digitalWrite(LED_BUILTIN, LOW);
    delay(WAIT_BEFORE_RAISE);
    digitalWrite(up_pin, HIGH);
    delay(RAISE_TIME);
    digitalWrite(up_pin, LOW);
    delay(1000);
    digitalWrite(down_pin, HIGH);
    delay(LOWER_TIME);
    digitalWrite(down_pin, LOW);
    digitalWrite(LED_BUILTIN, HIGH);       
}

// the loop function runs over and over again forever
void loop() {
  int inByte = 0;
  if (Serial.available() > 0) {
    unsigned long now = millis ();
    while (Serial.available() > 0 && millis() - now < 1000) {
      Serial.read();  // read and discard any input
    }
    raise();
  }
}
