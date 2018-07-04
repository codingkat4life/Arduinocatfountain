/* This program sets up an ultrasonic sensor to turn on and off a water pump for a cats water fountain. 
If the cat comes within a certain distance of the pump, a relay is used to turn the pump on for a certain duration,
then it is turned off. */

int vcc = 2; // Attach pin 2 to vcc
int trig = 3; // Attach pin 3 to Trig
int echo = 4; // Attach pin 4 to Echo
int gnd = 5; // Attach pin 5 to GND
int Relay = 6; // Attach relay to pin 6
boolean switchIsOn = false;

void setup() {

  // Sets pins to output or input
  pinMode (vcc, OUTPUT); 
  pinMode (gnd, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Relay, OUTPUT); 
  
  // Initialize serial communication:
  Serial.begin(9600);
  digitalWrite(vcc, HIGH);
}

void loop() {
  
  int cm = getdistance();
  // Log debugging
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();  
  
  //variables offtime and ontime
 
  int triggerdist = 35;
  if (cm < triggerdist) {
    if (!switchIsOn) {
        digitalWrite(Relay, LOW);
        switchIsOn = true;
        delay(20000);
       }  
  }
  else {     
    if (switchIsOn) { // switch is on, turn it off
      digitalWrite(Relay, HIGH);   // turn on relay
      switchIsOn = false;
    } // else, nothing needed, switch is already off
  }
  
  // Wait 100ms before next loop
  delay(100);
  
}


long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

int getdistance() {
   // Initialize duration variable
  long duration, inches, cm;
  
  // Sets pin trig off and on
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);
  
  // Gets duration from ultrasonic sensor
  duration = pulseIn(echo, HIGH);
  
  // Converts duration into a distance
  cm = microsecondsToCentimeters(duration);
  
  return cm;
}


