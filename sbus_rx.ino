#include <SBUS.h>
#include <Servo.h>
Servo elerons;
Servo alt;
Servo motor;
SBUS sbusx(Serial);
uint16_t channels[16];
bool failSafe;
bool lostFrame;
bool armed;
void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  elerons.attach(4);
  motor.attach(5);
  alt.attach(3);
  motor.writeMicroseconds(2300);
  delay(2000);
  motor.writeMicroseconds(800);
  delay(6000);
  sbusx.begin();
}

void loop() {
    if(sbusx.read(&channels[0], &failSafe, &lostFrame)){
      //sbusx.write(&channels[0]);
      armed = map(channels[7], 172, 1811, 0, 1);
      elerons.writeMicroseconds(map(channels[0], 172, 1811, 700, 2300));
      alt.writeMicroseconds(map(channels[1], 172, 1811, 700, 2300));
      if(armed){
        motor.writeMicroseconds(map(channels[2], 172, 1811, 800, 2300));
        digitalWrite(13,HIGH);
      }
      else{        
        motor.writeMicroseconds(800);
        digitalWrite(13,LOW);
      }
    }
    if(failSafe){
      elerons.writeMicroseconds(1500);
      alt.writeMicroseconds(1500);
      motor.writeMicroseconds(800);
      digitalWrite(13,HIGH);
      delay(1000);
      digitalWrite(13,LOW);
      delay(1000);
    }
}
