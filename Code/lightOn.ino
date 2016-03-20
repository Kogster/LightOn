#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int inter = 5;
int echoPin=2; //ECHO pin 
int trigPin=4; //TRIG pin 
int lamp = 8;
enum State {ON, TO_OFF, OFF, TO_ON };
State state;
int trigdist = 20;
int press_length = 1000;
int after_servo_delay = 400; //This was needed because otherwise ghost detections occured.
int zeroed = 97;
int trav_dist = 57;


void setup() {
   state = OFF;
   myservo.attach(3);
   Serial.begin(9600); 
   myservo.write(zeroed);
   pinMode(echoPin, INPUT); 
   pinMode(trigPin, OUTPUT);
   pinMode(lamp, OUTPUT);
}

void loop() {

   switch(state){
     case ON:
       if(dist() <= trigdist){
         state = TO_OFF;
         lamp_off();
       }
       break;
     case TO_OFF:
       if(dist() > trigdist){
         state = OFF;
       }
       break;
     case OFF:
       if(dist() <= trigdist){
         state = TO_ON;
         lamp_on();
       }
       break;
     case TO_ON:
       if(dist() > trigdist){
         state = ON;
       }
       break;
   }
   delay(inter);
}

int dist(){
   digitalWrite(trigPin, HIGH); //Trigger ultrasonic detection 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW); 
   int distance = pulseIn(echoPin, HIGH); //Read ultrasonic reflection
   distance = distance/58; //Calculate distance 
   Serial.println(distance); //Print distance
   return distance;
}

void lamp_on(){
   digitalWrite(lamp, HIGH);
   myservo.write(zeroed + trav_dist);
   delay(press_length);
   myservo.write(zeroed);
   delay(after_servo_delay);
}

void lamp_off(){
  digitalWrite(lamp, LOW);
  myservo.write(zeroed - trav_dist);
  delay(press_length);
  myservo.write(zeroed);
  delay(after_servo_delay);
}

