void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop(){
  while(Serial.available()){
    char getData = Serial.read();
    Serial.write(getData);
  
    if(getData == 'a'){
      digitalWrite(13, HIGH);
    }
    else if(getData == 'b'){
      digitalWrite(13, LOW);
    }
  }
}
