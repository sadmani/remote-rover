/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
//std_msgs::String led_msg;
//std_msgs::String led_dig;

float led_dig;

int led_control = 0;

void messageCb( const std_msgs::Float64&msg){
  led_dig = msg.data;
  led_control = led_dig;
  digitalWrite(13, HIGH);
  if(led_control== 123.0){
    digitalWrite(7, HIGH);
  }
  else{
    digitalWrite(7, LOW);
  }
}

ros::Publisher chatter("chatter", &str_msg);
//ros::Publisher led_chat("led_chat", &led_msg);

char hello[13] = "hello world!";
//char led[5] = "123";

ros::Subscriber<std_msgs::Float64>sub("led_chat",&messageCb);

void setup()
{
  pinMode(7, OUTPUT);
  pinMode(13, OUTPUT);
  nh.getHardware()->setBaud(9600);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  str_msg.data = hello;
//  led_msg.data = led;
  chatter.publish( &str_msg );
//  led_chat.publish( &led_msg);
  nh.spinOnce();
  delay(1000);
}
