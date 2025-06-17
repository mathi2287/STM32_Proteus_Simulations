#define ledPin 3
void setup() {
  Serial.begin(9600); // UART0 at 9600 baud
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read();  // Read a character
    digitalWrite(ledPin, HIGH); 
  }else{
  digitalWrite(ledPin, LOW);
  }
}