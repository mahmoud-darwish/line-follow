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
#define Speed 80
float SD;
//#define S5 A1      
int last_seen = 1; // right -->  1 || left --> 0
int middle =0  ;
int flag =1;  // not on black
int still_on_white = 1;
int last_flag =1;
int lastflag_error;
int Lspeed;
int Rspeed;
int lasterror =0;
int turnl= 100;
int turnr= -100;
int turn = 0;
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
float left = !(digitalRead(S1))*1 + !(digitalRead(S2))*0.5 ;
float right = !(digitalRead(S3))*0.5 + !(digitalRead(S4))*1 ;
float error = left - right;
Serial.print("  ");
Serial.print("Err: ");
Serial.print(error);

if (flag){lasterror = error;lastflag_error = error; flag=0;}





if(!(digitalRead(S1) ||digitalRead(S2) ||digitalRead(S3) ||digitalRead(S4)|| digitalRead(S5) || digitalRead(S6))){
        if (still_on_white){
            Move_Tank(0,0);
            delay(100);
            still_on_white = 0;
        }
       
        else  if (turn == 0){
              Lspeed = turnl;//(turnl<=60)?turnl:60;
              Rspeed = turnr;//(turnr>=-60)?turnr:-60;
              //Move_Tank(Lspeed,Rspeed);
              //delay(100);
              //turnl+=5;
              //turnr-=5;
        }
        else {
              Lspeed = turnr;//(turnr>=-60)?turnr :-60;
              Rspeed = turnl;//(turnl<=60)?turnl:60;
              //Move_Tank(Lspeed,Rspeed);
              //delay(100);
              //turnl+=5;
              //turnr-=5;
        }
        Serial.print("all white");
        
}

else {
  turnl = 70;
  turnr = -70;
still_on_white = 1;
Serial.print(" not all white");
        

    if(!(digitalRead(S1) ||digitalRead(S2) ||digitalRead(S3) ||digitalRead(S4) ) ){
      SD = error * kp;
    }
    if (digitalRead(S1) || digitalRead(S2)){
      turn = 1;
    }
    else if (digitalRead(S3) || digitalRead(S4)){
      turn = 0;
    }

    else{
    SD = error * kp + (error - lasterror) * kd;
    }
    //lasterror = error;
    if (last_flag){
      lasterror = error;
      last_flag = 0;
    }
    else {
      lastflag_error = lasterror;
      lasterror = error;
    }

     Lspeed =  Speed +constrain(SD,-10,10);
     Rspeed =  Speed -constrain(SD,-10,10);



}
Serial.print(" ");
Serial.print(Lspeed);
Serial.print(" ");
Serial.print(Rspeed);

Serial.println();
Move_Tank(Lspeed,Rspeed);












        


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

