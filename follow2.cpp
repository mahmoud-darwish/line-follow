#define enAPin 9
#define enBPin 11
#define in1Pin 8
#define in2Pin 10
#define in3Pin 13
#define in4Pin 12
#define S1 A1
#define S2 A2      // Middle Sensor

#define S3  A3    // Right sensor
#define S4  2
#define S5  A0
#define S6  7
#define kp  7    //40 10 10
#define kd  10
#define Speed 100
int SD;
//#define S5 A1      
int last_seen = 1; // right -->  1 || left --> 0
int middle =0  ;
int flag =1;  // not on black
int still_on_white = 1;
int Lspeed;
int Rspeed;
int lasterror =0;
void setup() {
  Serial.begin(9600);
// put your setup code here, to run once:
pinMode(enAPin, OUTPUT);
pinMode(enBPin, OUTPUT);
pinMode(in1Pin, OUTPUT);
pinMode(in2Pin, OUTPUT);
pinMode(in3Pin, OUTPUT);
pinMode(in4Pin, OUTPUT);

}

void loop() {
// put your main code here, to run repeatedly:
Serial.print(digitalRead(S1));
Serial.print("  ");
Serial.print(digitalRead(S2));
Serial.print("  ");
Serial.print(digitalRead(S5));
Serial.print("  ");
Serial.print(digitalRead(S6)); 
Serial.print("  ");
Serial.print(digitalRead(S3));
Serial.print("  ");
Serial.print(digitalRead(S4));
Serial.print("  ");

/*Serial.print(digitalRead(S5));
Serial.println();*/
int left = !(digitalRead(S1))*2 + !(digitalRead(S2))*1 ;
int right = !(digitalRead(S3))*1 + !(digitalRead(S4))*2 ;
int error = left - right;
Serial.print("  ");
Serial.print("Err: ");
Serial.print(error);

if (flag){lasterror = error;flag=0;}





if(!(digitalRead(S1) ||digitalRead(S2) ||digitalRead(S3) ||digitalRead(S4)|| digitalRead(S5) || digitalRead(S6))){
        if (still_on_white){
            Move_Tank(0,0);
            delay(100);
            still_on_white = 0;
        }
        if (lasterror > 0){
          Lspeed = 60;
          Rspeed = 0;

        }
        else {
          Lspeed = 0;
          Rspeed = 60;
        }
        Serial.print("all white");
        
}

else {
still_on_white = 1;
Serial.print(" not all white");
        

    if(!(digitalRead(S1) ||digitalRead(S2) ||digitalRead(S3) ||digitalRead(S4) ) ){
      SD = error * kp;
    }

    else{
    SD = error * kp + (error - lasterror) * kd;
    }
    lasterror = error;
     Lspeed =  Speed +SD;
     Rspeed =  Speed -SD;



}
Serial.print(" ");
Serial.print(Lspeed);
Serial.print(" ");
Serial.print(Rspeed);

Serial.println();
Move_Tank(Lspeed,Rspeed);












        
  delay(10);

}
void Motor(char port,int speed){
switch(port){
  case 'a':
  case 'A':
      if (speed>=0){
        digitalWrite(in1Pin, HIGH);
        digitalWrite(in2Pin, LOW);
        analogWrite(enAPin, speed);
        }
      else{
        digitalWrite(in1Pin, LOW);
        digitalWrite(in2Pin, HIGH);
        analogWrite(enAPin, speed*-1);
      }
    
      
    break;
  case 'b':
  case 'B':
      if (speed>=0){
        digitalWrite(in3Pin, 1);
        digitalWrite(in4Pin, 0);
        analogWrite(enBPin, speed);
        }
      else{
        digitalWrite(in3Pin, 0);
        digitalWrite(in4Pin, 1);
        analogWrite(enBPin, speed*-1);
      }
    
    break;

}
}

void Move_Tank(int motor1,int motor2){
    Motor('a',motor1);
    Motor('b',motor2);
}

