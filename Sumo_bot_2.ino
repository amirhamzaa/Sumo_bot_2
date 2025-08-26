// === Motor Pins ===
const int LM1 = 10;
const int LM2 = 11;
const int RM1 = 5;
const int RM2 = 6;

// === IR Sensors ===
const int FL = A2;
const int FR = A5;
const int BL = A1;
const int BR = A4;

// === Ultrasonic ===
const int trigPin = 2;
const int echoPin = 3;

// === Constants ===
unsigned long previousTime = 0;
int SenseFL, SenseFR, SenseBL, SenseBR, distance, black_th=350;
long duration;

void setup() {
  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  previousTime = millis();
}




void loop() {
  while((millis()-previousTime)<1000){
    moveForward(90); 
     ribbon() ;
  }
  while((millis()-previousTime)>=1000 && (millis()-previousTime)<1500){
    turnLeft(80); 
     ribbon() ;
  }
  while((millis()-previousTime)>=1500 && (millis()-previousTime)<2200){
    turnRight(80); 
     ribbon() ;
  }
  while((millis()-previousTime)>=2200 && (millis()-previousTime)<2700){
    turnLeft(80); 
     ribbon() ;
  }
  previousTime = millis();
 /* read_sensor();
  print_sensor();*/
  //test_motor();
}
void ribbon() {
    read_sensor();
   while(SenseFL>black_th && SenseFR<black_th && SenseBL<black_th && SenseBR<black_th && distance>30){
       turnRight(100); 
    read_sensor();
   }
   while(SenseFL<black_th && SenseFR>black_th && SenseBL<black_th && SenseBR<black_th && distance>30){
       turnLeft(100); 
    read_sensor();
   }
   while(SenseFL<black_th && SenseFR<black_th && SenseBL>black_th && SenseBR>black_th && distance>30){
       moveForward(100);
    read_sensor();
   }
   while(SenseFL>black_th && SenseFR>black_th && SenseBL<black_th && SenseBR<black_th && distance>30){
       moveBackward(100);  
    read_sensor();
   }
   while(distance<=30){
    moveForward(255);
    read_sensor();
   }
}


// === Movement Functions ===

void moveForward(int speed) {
  analogWrite(LM1, 0); analogWrite(LM2, speed);
  analogWrite(RM1, 0); analogWrite(RM2, speed);
}

void moveBackward(int speed) {
  analogWrite(LM1, speed); analogWrite(LM2, 0);
  analogWrite(RM1, speed); analogWrite(RM2, 0);
}

void turnLeft(int speed) {
  analogWrite(LM1, speed); analogWrite(LM2, 0);
  analogWrite(RM1, 0);     analogWrite(RM2, speed);
}

void turnRight(int speed) {
  analogWrite(LM1, 0);     analogWrite(LM2, speed);
  analogWrite(RM1, speed); analogWrite(RM2, 0);
}

void stopMotors() {
  analogWrite(LM1, 0); analogWrite(LM2, 0);
  analogWrite(RM1, 0); analogWrite(RM2, 0);
}
void print_sensor() {
  Serial.print( SenseFL);
  Serial.print("   ");
  Serial.print( SenseFR);
  Serial.print("   ");
  Serial.print( SenseBL);
  Serial.print("   ");
  Serial.print( SenseBR);
  Serial.print("   ");
  Serial.println(distance);
  delay(100);
}

void read_sensor() {
  SenseFL= analogRead(FL);
  SenseFR= analogRead(FR);
  SenseBL= analogRead(BL);
  SenseBR=analogRead(BR);
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 20000); // 20 ms timeout
  if (duration == 0) return -1;
  distance=duration * 0.034 / 2;
}

void test_motor(){//=====Test Motor
 moveForward(200);
 delay(2000);
 moveBackward(200) ;
 delay(2000);
 turnLeft(200);
 delay(2000);
 turnRight(200);
delay(2000);
 stopMotors();
delay(2000);
  
}
