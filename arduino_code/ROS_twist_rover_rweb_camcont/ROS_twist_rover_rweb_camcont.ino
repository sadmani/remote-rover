#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int8.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>
#include <Servo.h>
#include <Servo.h>
Servo servo1;
Servo servo2;

int trig_pin = 12; //green wire
int echo_pin = 11; //yellow wire

int motorLB = 3;
int motorLA = 5;
int motorRB = 6;
int motorRA = 10;

float prev_vel_x = 0;
float prev_vel_y = 0;

ros::NodeHandle  nh;

std_msgs::String str_msg;
std_msgs::Float64 blah_msg;
std_msgs::Float64 dist_msg;
std_msgs::Int8 servo_msg;
geometry_msgs::Twist twist_msg;

ros::Publisher pubUS("ultrasound", &dist_msg);
ros::Publisher chatter("move_state", &blah_msg);
int distance = 53.0;

void moveWheels( const geometry_msgs::Twist&msg){
  float vel_x = msg.linear.x;
  float vel_y = msg.linear.y;
  float ang_z = msg.angular.z;
  
  float adj_vel_x = 255*vel_x;
  float adj_vel_y = 255*vel_y;
  
//  analogWrite(motorRA, 255);
//  analogWrite(motorRB, 0);
//  analogWrite(motorLA, 255);
//  analogWrite(motorLB, 0);
  //delay(500);
  blah_msg.data = vel_x;
  chatter.publish(&blah_msg);
  
  if (ang_z == 0.0){
    if (adj_vel_x == 0.0){
      //Move forward or backward
      if (vel_y > 0){
        //Move forward
        analogWrite(motorRA, adj_vel_y);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, adj_vel_y);
        analogWrite(motorLB, 0);
      }
      else if(vel_y < 0){
        //Move backward
        analogWrite(motorRA, 0);
        analogWrite(motorRB, -adj_vel_y);
        analogWrite(motorLA, 0);
        analogWrite(motorLB, -adj_vel_y);
      }
      else{
        analogWrite(motorRA, 255);
        analogWrite(motorRB, 255);
        analogWrite(motorLA, 255);
        analogWrite(motorLB, 255);
      }
    }
    else if(adj_vel_y == 0){
      //Turn left or right
      if(vel_x < 0){
        //Turn right
        analogWrite(motorRA, 0);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, -adj_vel_x);
        analogWrite(motorLB, 0);
      }
      else if(vel_x > 0){
        //Turn left 
        analogWrite(motorRA, adj_vel_x);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, 0);
        analogWrite(motorLB, 0);
      }
    }
  }
} 

void moveWebWheels( const geometry_msgs::Twist&msg){
  float vel_x = msg.linear.x;
  float vel_y = msg.linear.y;
  float ang_z = msg.angular.z;
  
  float adj_vel_x = 255*vel_x;
  float adj_vel_y = 255*vel_y;
  
  if((vel_x == prev_vel_x) & (vel_y == prev_vel_y)){
    adj_vel_x = 0;
    adj_vel_y = 0;
  }
  blah_msg.data = vel_x;
  chatter.publish(&blah_msg);
  
  if (ang_z == 0.0){
    if (adj_vel_x == 0.0){
      //Move forward or backward
      if (vel_y > 0){
        //Move forward
        analogWrite(motorRA, adj_vel_y);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, adj_vel_y);
        analogWrite(motorLB, 0);
      }
      else if(vel_y < 0){
        //Move backward
        analogWrite(motorRA, 0);
        analogWrite(motorRB, -adj_vel_y);
        analogWrite(motorLA, 0);
        analogWrite(motorLB, -adj_vel_y);
      }
      else{
        analogWrite(motorRA, 255);
        analogWrite(motorRB, 255);
        analogWrite(motorLA, 255);
        analogWrite(motorLB, 255);
      }
    }
    else if(adj_vel_y == 0){
      //Turn left or right
      if(vel_x < 0){
        //Turn right
        analogWrite(motorRA, 0);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, -adj_vel_x);
        analogWrite(motorLB, 0);
      }
      else if(vel_x > 0){
        //Turn left 
        analogWrite(motorRA, adj_vel_x);
        analogWrite(motorRB, 0);
        analogWrite(motorLA, 0);
        analogWrite(motorLB, 0);
      }
    }
  }
  
  prev_vel_x = vel_x;
  prev_vel_y = vel_y;
}

void servoMove( const geometry_msgs::Twist&msg){
//  int val = servo1.read();
//  Serial.print(val);

  float down_msg = msg.linear.x;
  float up_msg = msg.linear.y;
  float left_msg = msg.angular.x;
  float right_msg = msg.angular.y;

  int val1 = servo1.read();
  if (up_msg == 1.0){
    val1 = val1 + 15;
    servo1.write(val1);
  }
  else if(up_msg == 1.0){
    val1 = val1 - 15;
    servo1.write(val1);
  }
  else{
    servo1.write(170);
  }
  
  int val2 = servo2.read();
  if (right_msg == 1.0){
    val2 = val2 + 15;
    servo2.write(val2);
  }
  else if(left_msg == 1.0){
    val2 = val2 - 15;
    servo2.write(val2);
  }
  else{
    servo2.write(170);
  }
}


ros::Subscriber<geometry_msgs::Twist>sub3("webtools_twist",&moveWebWheels);
ros::Subscriber<geometry_msgs::Twist>sub4("buffered_twist",&moveWheels);
ros::Subscriber<geometry_msgs::Twist>sub5("cam_cont",&servoMove);

void setup(){
  pinMode(motorLB, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorLA, OUTPUT);
  pinMode(motorRA, OUTPUT);
  
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  servo1.attach(12);
  servo2.attach(4);
  servo1.write(90);
  servo2.write(90);
  
  nh.getHardware()->setBaud(57600);
  nh.initNode();
  
  nh.advertise(pubUS);
  nh.advertise(chatter);
  nh.subscribe(sub3);
  nh.subscribe(sub4);
  nh.subscribe(sub5);
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
  
  dist_msg.data = distance;  
  pubUS.publish(&dist_msg);  
  nh.spinOnce();
  delay(50);
}
