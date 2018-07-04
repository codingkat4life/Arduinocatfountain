int vcc = 2; //attach pin 2 to vcc
int trig = 3; // attach pin 3 to Trig
int echo = 4; //attach pin 4 to Echo
int gnd = 5; //attach pin 5 to GND
int Relay = 6;
     
void setup() {

// Sets pins to output or input
pinMode (vcc,OUTPUT); 
pinMode (gnd,OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo,INPUT);
pinMode(Relay, OUTPUT); 

// Initialize serial communication:
Serial.begin(9600);
digitalWrite(vcc, HIGH);
}

void loop()
{

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


/*
Serial.print(cm);
Serial.print("cm");
Serial.println();
*/

//variables offtime and ontime
int ontime = 20000;
int offtime = 1000;

if (cm < 35) {
   
   // If cat is close enough, turn off relay for 20s, then turn on and wait 1s
   digitalWrite(Relay, LOW);  
   delay(ontime);
   digitalWrite(Relay, HIGH);   // turn on relay
   delay(offtime);
}

//wait 100ms before next loop
delay(100);
}



long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}


