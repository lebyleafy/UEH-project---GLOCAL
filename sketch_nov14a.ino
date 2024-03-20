#include <Servo.h>

Servo myservo; //define servo 

//motor define 
int IN1 = 10; 
int IN2 = 12;

//bumper define 
int IN3 = 11;
int IN4 = 13;

//cup input
int trig_a = A0;
int echo_a = A1;

//servo start moving by censor
int trig_b = 7;     
int echo_b = 8;     
int pos = 0;

//move servo
void servoMove() {
      for (pos = 0; pos <= 180; pos += 1) { 
        myservo.write(pos);              
        delay(5);
      }
      for (pos = 180; pos >= 0; pos -= 1) { 
        myservo.write(pos);              
        delay(3);                       
      }
}

//stop motor
void Stop() {
	analogWrite(IN1, 0);
	digitalWrite(IN2, LOW);
}

//motor run foward
void Foward() { 

	analogWrite(IN1, 255);
	digitalWrite(IN2, HIGH);

}

// motor run in reverse
void Reverse() {
	analogWrite(IN1, 255);
	digitalWrite(IN2, LOW);
}

//bumper
void Bump(){
  analogWrite(IN3, 255);
  digitalWrite(IN4, HIGH);
}

void StopBump(){
  analogWrite(IN3, 0);
  digitalWrite(IN4, LOW);
}

void setup()
{
    Serial.begin(9600);     // baurate 9600

    //motor 
    pinMode(IN1, OUTPUT); //speed
	  pinMode(IN2, OUTPUT); //direction

    //bumper
    pinMode(IN3, OUTPUT); //energy
	  pinMode(IN4, OUTPUT); // bump

    // user input censor 
    pinMode(trig_a,OUTPUT);   // trig for send signal
    pinMode(echo_a,INPUT);   // echo for receive signal

    // servo censor 
    pinMode(trig_b,OUTPUT);   // trig for send signal
    pinMode(echo_b,INPUT);   // echo for receive signal

    myservo.attach(9); //attach servo to pin 9     
}
 
void loop()
{
    unsigned long duration_a; // time variable for user input censor 
    unsigned long duration_b; // time variable for servo censor 

    int distance_a;           // distance variable for user input censor
    int distance_b;           // distance varible for servo censor 
    
    // user input censor
    digitalWrite(trig_a,0);  
    delayMicroseconds(2);
    digitalWrite(trig_a,1);   
    delayMicroseconds(5);   
    digitalWrite(trig_a,0);

    duration_a = pulseIn(echo_a,HIGH);
    distance_a = int(duration_a/2/29.412);


    // servo censor 
    digitalWrite(trig_b,0);   
    delayMicroseconds(2);
    digitalWrite(trig_b,1);   
    delayMicroseconds(5);  
    digitalWrite(trig_b,0);   

    duration_b = pulseIn(echo_b,HIGH);  
    distance_b = int(duration_b/2/29.412);

    // start moving if see user put the cup in 
    if (distance_a <= 5){
      Serial.println("ok");
      delay(1000);

      Foward();
      delay(1000);
      Stop();
    }
    // if servo censor detect object that close or equal 5cm, start the action 
    if (distance_b <= 5){
      delay(1000);

      servoMove();
      delay(100);

      Bump();
      delay(700);
      StopBump();

      Stop();
      delay(1000);

      Reverse();
      delay(1000);   
      Stop();                    
    }        
    //test
    Serial.print(distance_a);
    Serial.println("cm");
    delay(200);
}
