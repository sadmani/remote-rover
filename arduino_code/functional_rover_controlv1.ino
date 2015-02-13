#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

int servo1_pin = 12;
int servo2_pin = 4;
int motorLA = 8;
int motorLB = 9;
int motorRA = 10;
int motorRB = 11;

//Servo servo1;
//Servo servo2;

ros::NodeHandle  nh;

std_msgs::String str_msg;

int led_dig;
int move_LR;
int move_UD;
int move_msg;
//char move_LR

int led_control = 0;
int value1 = 0;
int value2 = 0;
int value3 = 0;

int led1 = 5;
int led2 = 7;
int pos = 0;

//ros::Publisher chatter("servo_state", &str_msg);


void headlightsCb( const std_msgs::Float64&msg){
  led_dig = msg.data;
  led_control = led_dig;
  if(led_control == 7.0){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else{
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}

void servoLR( const std_msgs::Float64&msg){
  int val = servo1.read();
  Serial.print(val);
  move_LR = msg.data;
  value1 = move_LR;
//  servo1.write(180);
  if (value1 == 1.0){
    val = val + 15;
    servo1.write(val);
  }
  else if(value1 == 3.0){
    val = val - 15;
    servo1.write(val);
  }
  else{
    servo1.write(170);
  }
}

void servoUD( const std_msgs::Float64&msg){
  int val = servo2.read();
  Serial.print(val);
  move_UD = msg.data;
  value2 = move_UD;
  if (value2 == 2.0){
    val = val + 15;
    servo2.write(val);
  }
  else if(value2 == 0.0){
    val = val - 15;
    servo2.write(val);
  }
  else{
    servo2.write(170);
  }
}

void moveWheels( const std_msgs::Float64&msg){
  move_msg = msg.data;
  value3 = move_msg;
  digitalWrite(motorRA, HIGH);
  digitalWrite(motorRB, HIGH);
  digitalWrite(motorLA, HIGH);
  digitalWrite(motorLB, HIGH);
  delay(500);
//  digitalWrite(motorRA, HIGH);
//  digitalWrite(motorRB, LOW);
//  digitalWrite(motorLA, HIGH);
//  digitalWrite(motorLB, LOW);
//  delay(500);
  
  if (value3 == 4.0){
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, LOW);
    delay(500);
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, HIGH);    
  }
  else if(value3 == 6.0){
    digitalWrite(motorRA, LOW);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, LOW);
    delay(500);
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, HIGH);
  }
  else if(value3 == 8.0){
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, LOW);
    delay(500);
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, HIGH);
  }
  else if(value3 == 5.0){
    digitalWrite(motorRA, LOW);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, HIGH);
    delay(500);
    digitalWrite(motorRA, HIGH);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLA, HIGH);
    digitalWrite(motorLB, HIGH);  
  }  
  else{
    digitalWrite(motorRA, LOW);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLA, LOW);
    digitalWrite(motorLB, LOW);
  }
}


ros::Subscriber<std_msgs::Float64>sub("led_chat",&headlightsCb);
ros::Subscriber<std_msgs::Float64>sub2("servoLR_chat",&servoLR);
ros::Subscriber<std_msgs::Float64>sub3("servoUD_chat",&servoUD);
ros::Subscriber<std_msgs::Float64>sub4("move_chat",&moveWheels);

//ros::Subscriber<std_msgs::String>sub("led_chat",&headlightsCb);

void setup(){
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorRA, OUTPUT);
  pinMode(motorRA, OUTPUT);
  servo1.attach(12);
  servo2.attach(4);
  servo1.write(90);
  servo2.write(90);
  nh.getHardware()->setBaud(9600);
  nh.initNode();
//  nh.advertise(chatter);
  nh.subscribe(sub);  
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
}

void loop(){
  nh.spinOnce();
  delay(1000);
}
