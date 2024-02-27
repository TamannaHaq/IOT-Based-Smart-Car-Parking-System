#define BLYNK_TEMPLATE_ID "TMPL6px0nYxhr"
#define BLYNK_TEMPLATE_NAME "Smart Car parking"
#define BLYNK_AUTH_TOKEN "5nR3Gepmbi8r1njHGIe9VEFmn8Ys7N6t"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>  
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

#include <LiquidCrystal_I2C.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OPPO RENO 2";
char pass[] = "12345678";

LiquidCrystal_I2C lcd (0x3F, 20,4);

Servo myservo;

#define ir_enter 25
#define ir_exit  26

#define slot1 4
#define slot2 18
#define slot3 19
#define slot4 23
#define slot5 32
#define slot6 33


int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int servoPin = 27;

   

void setup(){
Serial.begin(9600);
WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

pinMode(slot1, INPUT);
pinMode(slot2, INPUT);
pinMode(slot3, INPUT);
pinMode(slot4, INPUT);
pinMode(slot5, INPUT);
pinMode(slot6, INPUT);




pinMode(ir_enter, INPUT);
pinMode(ir_exit, INPUT);
  
myservo.attach(servoPin);
myservo.write(0);

Blynk.begin(auth, ssid, pass);
lcd.begin ();
lcd.backlight ();
 

delay (1000);   

Read_Sensor();


}

void loop(){

Blynk.run();
Read_Sensor();

  

lcd.setCursor (0,1);
if(S1==1){lcd.print("S1:Full ");
          
          Blynk.virtualWrite(V1, 255);}
     else{lcd.print("S1:Empty");
          
          Blynk.virtualWrite(V1, 0);}

lcd.setCursor (11,1);
if(S2==1){lcd.print("S2:Full ");
          
          Blynk.virtualWrite(V2, 255);}
     else{lcd.print("S2:Empty");
          
          Blynk.virtualWrite(V2, 0);}
     

lcd.setCursor (0,2);
if(S3==1){lcd.print("S3:Full "); 
          
          Blynk.virtualWrite(V3, 255);}
     else{lcd.print("S3:Empty");
          
          Blynk.virtualWrite(V3, 0);}

lcd.setCursor (11,2);
if(S4==1){lcd.print("S4:Full ");
         
          Blynk.virtualWrite(V4, 255);}
     else{lcd.print("S4:Empty");
          
          Blynk.virtualWrite(V4, 0);}

lcd.setCursor (0,3);
if(S5==1){lcd.print("S5:Full ");
         
          Blynk.virtualWrite(V5, 255);}
     else{lcd.print("S5:Empty");
          
          Blynk.virtualWrite(V5, 0);}

lcd.setCursor (11,3);
if(S6==1){lcd.print("S6:Full ");
         
          Blynk.virtualWrite(V6, 255);}
     else{lcd.print("S6:Empty");
          
          Blynk.virtualWrite(V6, 0);}                  
   

if ((digitalRead (ir_enter) == LOW) && ((digitalRead (slot1) == HIGH) || (digitalRead (slot2) == HIGH) || (digitalRead (slot3) == HIGH) || (digitalRead (slot4) == HIGH) || (digitalRead (slot5) == HIGH)  || (digitalRead (slot6) == HIGH)  ))
  {
    myservo.write(90);
    delay(3000);
    myservo.write(0);
  }

if(digitalRead (ir_exit) == LOW) {
   myservo.write(90);
    delay(3000);
    myservo.write(0);
}

Read_Sensor();
int total = S1+S2+S3+S4+S5+S6;
int slot = 6-total;

lcd.setCursor (3,0);
lcd.print("slot Left: ");
lcd.print(slot);


delay(100);
}

void Read_Sensor(){
S1=0, S2=0, S3=0, S4=0, S5=0, S6=0; 

if(digitalRead(slot1) == 0){S1=1;}
if(digitalRead(slot2) == 0){S2=1;}
if(digitalRead(slot3) == 0){S3=1;}
if(digitalRead(slot4) == 0){S4=1;} 
if(digitalRead(slot5) == 0){S5=1;}
if(digitalRead(slot6)==0){S6=1;}
}
