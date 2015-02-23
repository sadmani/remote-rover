#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Vector3.h>

int motorLB = 3;
int motorLA = 5;
int motorRB = 6;
int motorRA = 10;

ros::NodeHandle  nh;

std_msgs::String str_msg;
geometry_msgs::Twist twist_msg;

ros::Publisher chatter("move_state", &twist_msg);

void moveWheels( const geometry_msgs::Twist&msg){
  float vel_x = msg.linear.x;
  float vel_y = msg.linear.y;
  float ang_z = msg.angular.z;
  
  float adj_vel_x = 120*vel_x + 120;
  float adj_vel_y = 120*vel_y + 120;
  
  analogWrite(motorRA, 255);
  analogWrite(motorRB, 255);
  analogWrite(motorLA, 255);
  analogWrite(motorLB, 255);
  delay(500);
  
  twist_msg = msg;
  chatter.publish(&twist_msg);
  
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

ros::Subscriber<geometry_msgs::Twist>sub4("twist_rover",&moveWheels);

void setup(){
  pinMode(motorLB, OUTPUT);
  pinMode(motorRB, OUTPUT);
  pinMode(motorLA, OUTPUT);
  pinMode(motorRA, OUTPUT);
  
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub4);
}

void loop(){
  nh.spinOnce();
  delay(1000);
}
