#define hallReadpin A0
#define ampReadpin A3
#define LEDpin 7
#define threshold 7
float lastread;
bool state;
bool laststate;
int value;

void setup() {
  // put your setup code here, to run once
  Serial.begin(115200);
  pinMode(LEDpin, OUTPUT);
  //pinMode(ampReadpin, INPUT);

  digitalWrite(LEDpin, HIGH);
  //Serial.println("Program Running!");
}

void loop() {
  // put your main code here, to run repeatedly:
value = analogRead(ampReadpin);

delay(100);
Serial.println(value);
//AmIOn();
// HallRead();
}

bool AmIOn() {
  int myThreshold = 3;
  int numAboveThreshold = 0;
  int value = analogRead(ampReadpin);
  for(int i=0; i<15; i++){
    
    if(value > myThreshold) {
      //Serial.println("ampReadpin=");
      Serial.println(value);
      numAboveThreshold++;
    }
    delay(100);
    //Serial.println(numAboveThreshold);
  }
  if (numAboveThreshold > threshold){
  Serial.println("I'm ON");
  //Serial.println(numAboveThreshold);
  digitalWrite(LEDpin, HIGH);
  }
  else {
    Serial.println("i'm off");
    digitalWrite(LEDpin, LOW);
  }
  return numAboveThreshold > threshold;
}
// void HallRead(){
 
//   int currentread = analogRead(ampReadpin);
//   // Serial.println("Current reading:");
//   // Serial.println(currentread);
//   //if(currentread >= 520){
//   if(AmIOn){
//     state = true;
//     if (state != laststate) {
//     digitalWrite(LEDpin, HIGH);
//     //Serial.println("currentread");
//     laststate = state;
//     }
//   }
//  // else if (currentread <= 490) {
//    else {
//     state = false;
//     if (state != laststate) {
//       digitalWrite(LEDpin, LOW);
//       laststate = state;
//     }
//   }
  
  // if(currentread != lastread){
  //   int difference = currentread-lastread;
  //   if(difference >= 2 || difference <= -2){
      
  //     digitalWrite(LEDpin, HIGH);
  //     Serial.println("Hall pin reads:");
  //     Serial.println(difference);
  //     Serial.println(lastread);
    
  //   }
  //   lastread = currentread;
     
  // }
  // else{
  //   digitalWrite(LEDpin, LOW);
  //   //Serial.println(currentread);
  //   //lastread = currentread;
  // }
//}
