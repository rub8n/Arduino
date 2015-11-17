const int buttonsLEDPin = 10;
const int firstButtonPin = A2; //20 A2
//const int secondButtonPin = A2; //19
//const int thirdButtonPin = A1; //18

//Let's say you have your push button on pin 2
int switchState = 0; // actual read value from pin2
int oldSwitchState = 0; // last read value from pin2

int lightsOn = 0; // is the switch on = 1 or off = 0

void setup() {
  analogWrite(buttonsLEDPin,0);
  pinMode(firstButtonPin, INPUT);
  Serial.begin(9600);
  digitalWrite(firstButtonPin, HIGH);
}

void loop() {
  
  switchState = digitalRead(firstButtonPin); // read the pushButton State

 if (switchState == HIGH) {     
    Serial.println("Button off"); 
  } else { 
    Serial.println("ON!!!!");
  }
  delay(100);
  
//  if (switchState != oldSwitchState) // catch change
//  {
//    oldSwitchState = switchState;
//    
//    if (switchState == HIGH)
//    {
//      // toggle
//      lightsOn = !lightsOn;
//    }
//    
//  }
//
//  if(lightsOn)
//  {
//    //digitalWrite(3, HIGH);   // set the LED on
//    Serial.println("LED on");
//  } else {
//    //digitalWrite(3, LOW);   // set the LED off
//    Serial.println("LED off");
//  }
 
  Serial.println("*");

  //delay(200);
    
}
