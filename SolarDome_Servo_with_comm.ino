/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
#include <XBee.h>
 
Servo myservo1;  //servo object
Servo myservo2;  // "      "
XBee xbee = XBee();  // create the XBee object

uint8_t payload[36] = { 0 };

// SH + SL Address of receiving XBee
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x403e0f30);
ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
ZBTxStatusResponse txStatus = ZBTxStatusResponse();

int pos1 = 0;    // variable to store the servo position 
int pos2 = 0;
int sensor = 0;
int byte_pos=0;
 
void setup() 
{ 
  myservo1.attach(9);  // use pin 9 for servo 
  myservo2.attach(10);
  
  myservo1.write(90);
  myservo2.write(90);
  Serial.begin(115200);      //changed the baud rate
  xbee.setSerial(Serial);
  delay(2000);
  
} 
 
void loop() 
{ 
  for(pos1 = 10; pos1 <= 170; pos1 += 10) // Half circle in 10 degree increments
  {   
    myservo1.write(pos1); // tell servo to go to position in variable 'pos' 
    //delay(200);       // waitfor the servo to reach the position 
    
    byte_pos=0;
    for(pos2 = 170; pos2>=0; pos2-=10)     // goes from 180 degrees to 0 degrees 
      {                                
        myservo2.write(pos2);  
        sensor = analogRead(A5);      //reading the sensor data
        payload[2*byte_pos] = sensor >> 8 & 0xff;
        payload[(2*byte_pos)+1] = sensor & 0xff;
        //Serial.println(sensor);
        
        /*
        Serial.print("Pos1: ");
        Serial.print(pos1);
        Serial.print("\t");
        Serial.print("Pos2: ");
         Serial.print(pos2);
         Serial.print("\t");
        Serial.print("Sensor Reading: ");
        Serial.print(sensor);
        Serial.print("\n"); 
          // tell servo to go to position in variable 'pos' 
          */
        delay(200);   // wait for the servo to reach the position 
        
        byte_pos+=1;
      } 
      delay(200);
       xbee.send(zbTx);
      
      
    } 
  
  
   
  
} 
