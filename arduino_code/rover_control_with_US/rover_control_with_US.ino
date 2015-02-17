#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
//#include <std_msgs/Float64.h>
#include <Servo.h>

int trig_pin = 3;
int echo_pin = 2;

Servo servo1;
Servo servo2;

int servo1_pin = 12;
int servo2_pin = 4;

int motorLA = 11;
int motorLB = 10;
int motorRA = 9;
//int motorRB = 8;
int motorRB = 5;

ros::NodeHandle  nh;

std_msgs::String chat_msg;
std_msgs::Float64 dist_msg;

ros::Publisher chatter("chatter", &chat_msg);
ros::Publisher pubUS("ultrasound", &dist_msg);

char hello[13] = "hello world!";
int distance = 53.0;


//const int adc_pin = 0;

//char frameid[] = "/ultrasound";

int led_dig;
int move_LR;
int move_UD;
int move_msg;
//char move_LR

int led_control = 0;
int value1 = 0;
int value2 = 0;
int value3 = 0;

//int led1 = 5;
int led1 = 8;
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


void setup(){
  //Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(motorLB, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorRA, OUTPUT);
  pinMode(motorRA, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  
  servo1.attach(12);
  servo2.attach(4);
  servo1.write(90);
  servo2.write(90);
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(pubUS);
  nh.advertise(chatter);
  nh.subscribe(sub);  
  nh.subscribe(sub2);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
}

void loop(){
  long duration, distance;
  digitalWrite(trig_pin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line

  digitalWrite(trig_pin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trig_pin, LOW);
  duration = pulseIn(echo_pin, HIGH);
  distance = (duration/2) / 29.1;
  dist_msg.data = distance;
  if (distance >= 200 || distance <= 0){
    pubUS.publish(&dist_msg);
  }
  else {
    pubUS.publish(&dist_msg);
  }
  delay(500);
  dist_msg.data = distance;
  chat_msg.data = hello;
  chatter.publish(&chat_msg);
  pubUS.publish(&dist_msg);
  nh.spinOnce();
  delay(1000);
}
