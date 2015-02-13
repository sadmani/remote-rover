#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Char.h>


ros::NodeHandle nh;

char getData;

void messageCb( const std_msgs::Char& msg){
  getData = msg.data;
  
//  while(Serial.available()){
//    char getData = Serial.read();
//    char getData = msg.data;
//   Serial.write(getData);
  
//    if(getData == '1'){
//      digitalWrite(13, HIGH);
//    }
//    else if(getData == '2'){
//      digitalWrite(13, LOW);
//    }
//  }

  if(getData == '1'){
    digitalWrite(13, HIGH);
  }
  else if(getData == '2'){
    digitalWrite(13, LOW);
  }
}

ros::Subscriber<std_msgs::Char> lc("led_control", &messageCb);

void setup(){
  nh.getHardware()->setBaud(9600);
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(lc);
}

void loop(){
  nh.spinOnce();
  delay(20);
}
