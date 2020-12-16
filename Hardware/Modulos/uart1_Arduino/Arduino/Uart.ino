char Income[1]; // for incoming serial data
const int LEDMov=13;
const int LEDNoMov=4;

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  pinMode(LEDMov,OUTPUT);
  pinMode(LEDNoMov,OUTPUT);
}

void loop() {
  // send data only when you receive data:
 Serial.readBytes(Income,1);
 Serial.println(Income);
 if(Income[0]=='N'){
  digitalWrite(LEDMov,LOW);
  digitalWrite(LEDNoMov,HIGH);
 }else if(Income[0]=='Y'){
  digitalWrite(LEDMov,HIGH);
  digitalWrite(LEDNoMov,LOW);
 }
 
    // say what you got:
  }
