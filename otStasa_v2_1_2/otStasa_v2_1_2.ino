
   uint32_t current = rtc.getUnix(0);

 
    if (current >= time + 30){ //Iicializaciy gsm moduly 
      gsmRestart();
      Serial.println("GSM tester v1.0");
      mySerial.println("AT+CLIP=1");  //включаем АОН
      delay(100);
      mySerial.println("AT+CMGF=1");  //режим кодировки СМС - обычный (для англ.)
      delay(100);
      mySerial.println("AT+CSCS=\"GSM\"");  //режим кодировки текста
      delay(100);
      time = current;
    }
   char temObchay[100];
char temp0 [100];
    int val = analogRead(sensePin0); 
            if(val == 95) {
                      lcd.setCursor(0,0);
                      lcd.print("menu");
                      delay(1000);
                      Serial.println("menu");
                      sprintf(temObchay , "%.0dT1, %.0dT2, %.0dT3, %.0dT4 :: ", getTemp(sensor1), getTemp(sensor2), getTemp(sensor3), getTemp(sensor4));
                      handleRing(temObchay);
                      }
   int val2 = analogRead(sensePin1);
      switch (val2){
             case 90 ... 100:
                      lcd.setCursor(10,0);
                      lcd.print("vverh");
                      delay(1000);
                           displayTemperature();
                      break;
             case 465 ... 485:
                      lcd.setCursor(10,0);
                      lcd.print("vniz");
                      delay(1000);
                      break;
             case 690 ... 715:
                      lcd.setCursor(10,0);
                      lcd.print("vlevo");
                      delay(1000);
                      break;
             case 895 ... 915:
                      lcd.setCursor(10,0);
                      lcd.print("vpravo");
                      delay(1000);
                      break;
}


  

   if (mySerial.available()) {  //если GSM модуль что-то послал нам, то
    while (mySerial.available()) {  //сохраняем входную строку в переменную val
      ch = mySerial.read();
      val1 += char(ch);
      delay(10);
    }
    if (val1.indexOf("RING") > -1) {  //если звонок обнаружен, то проверяем номер
      if (val1.indexOf("79809483376") > -1) {  //если номер звонящего наш. Укажите свой номер без "+"
        Serial.println("--- MASTER RING DETECTED ---");
        mySerial.println("ATA");  //vkl связь
        digitalWrite(led, HIGH);  //включаем светодиод на 3 сек
        delay(1000);
        mySerial.println("ATH0");  //разрываем связь
        digitalWrite(led, LOW);  //выключаем реле
        sms(String(temp0), String("+79611269315"));  //отправляем СМС на номер +71234567890
      }
    } else
      Serial.println(val1);  //печатаем в монитор порта пришедшую строку
    val1 = "";
  }
  if (Serial.available()) {  //если в мониторе порта ввели что-то
    while (Serial.available()) {  //сохраняем строку в переменную val
      ch = Serial.read();
      val1 += char(ch);
      delay(10);
    }
     if (val1.indexOf("dels") > -1) {
     mySerial.println("AT+CMGDA=\"DEL SENT\"");
    //delay(100);
   // mySerial.println("AT+CMGD=4");
    delay(100);
     }
    //mySerial.println("AT+CMGDA=\"DEL INBOX\"");
   // delay(10);
    if (val1.indexOf("rid") > -1) {
    //  mySerial.println("AT+CMGDA=\"DEL ALL\"");
    //delay(100);
    mySerial.println("AT+CMGD=1,4");
    delay(100);
    }
    //mySerial.println(val);  //передача всех команд, набранных в мониторе порта в GSM модуль
    if (val1.indexOf("sms1") > -1) {  //если увидели команду отправки СМС
     sms(String("hello 300"), String("+79611269315"));  //отправляем СМС на номер +71234567890
    }
    if (val1.indexOf("res") > -1) {   //jdem s monitora porta i sbrasivaem gsm
    mySerial.println("AT+CFUN=1,1");
    }
    val1 = "";  //очищаем
  }
   int buttonSignal = analogRead(sensePin0);
  if(buttonSignal == 95) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURA");
    delay(1000);
  }

  // Фунция джойстка
  buttonSignal = analogRead(sensePin1);
  handleJoy(buttonSignal);
    

}

if (vrt == 1) {              //zapros 1 datchik
 
       oneWire.reset();//sbros linii datchikov
       oneWire.select(sensor1); //obracshenie k datchiky po nomery
       oneWire.write(0x44); //otpravka na datchik kod - izmer temper
      
       oneWire.reset();//sbros linii datchikov
       oneWire.select(sensor2); //obracshenie k datchiky po nomery
       oneWire.write(0x44); //otpravka na datchik kod - izmer temper
      
       oneWire.reset();//sbros linii datchikov
       oneWire.select(sensor3); //obracshenie k datchiky po nomery
       oneWire.write(0x44); //otpravka na datchik kod - izmer temper
      
       oneWire.reset();//sbros linii datchikov
       oneWire.select(sensor4); //obracshenie k datchiky po nomery
       oneWire.write(0x44); //otpravka na datchik kod - izmer temper
          }

     //  if (vrt == 5) {          
             //} 
       if (vrt == 5) {            
               lcd.setCursor(0,1);     
               lcd.print("1");
             }

       if (vrt == 7) {   

              lcd.setCursor(20,1);
              lcd.print(t1);
              lcd.print(" ");
              lcd.print(t2);
              lcd.print(" ");
              lcd.print(t3);
              lcd.print(" ");
              lcd.print(t4);
   }
   if (vrt == 10) {             
               lcd.setCursor(0,1);
               lcd.print("3");
  }
if (vrt == 15) {             
               lcd.setCursor(0,1);
               lcd.print("4");
      }
if (vrt == 20) {           
         //chtenie 1 datchik
            
          oneWire.reset();  //sbros linii
          oneWire.select(sensor1); //opredelenie datchika
          oneWire.write(0xBE); // команда на начало чтения измеренной температуры
             byte data[2]; // Место для значения температуры
                data[0] = oneWire.read();  //chtenie mladshego razrjda
                data[1] = oneWire.read();   //chtenie starshego
                tempC1 = ((data[1] << 8) | data[0]) * 0.0625;
                t1 = tempC1;

          
            

          oneWire.reset();  //sbros linii
          oneWire.select(sensor2); //opredelenie datchikamo
          oneWire.write(0xBE); // команда на начало чтения измеренной температуры        
                 data[0] = oneWire.read();  //chtenie mladshego razrjda
                 data[1] = oneWire.read();   //chtenie starshego
                 tempC2 = ((data[1] << 8) | data[0]) * 0.0625;
                 t2 = tempC2;

          
          oneWire.reset();  //sbros linii
          oneWire.select(sensor3); //opredelenie datchika
          oneWire.write(0xBE); // команда на начало чтения измеренной температуры           
                data[0] = oneWire.read();  //chtenie mladshego razrjda
                data[1] = oneWire.read();   //chtenie starshego
                tempC3 = ((data[1] << 8) | data[0]) * 0.0625;
                t3 = tempC3;
            

          oneWire.reset();  //sbros linii
          oneWire.select(sensor4); //opredelenie datchika
          oneWire.write(0xBE); // команда на начало чтения измеренной температуры
                 data[0] = oneWire.read();  //chtenie mladshego razrjda
                 data[1] = oneWire.read();   //chtenie starshego
                 tempC4 = ((data[1] << 8) | data[0]) * 0.0625;
                 t4 = tempC4;
           
              lcd.clear(); 
              lcd.setCursor(0,0);
              lcd.print("1M");
              lcd.print(tempC1);
              lcd.setCursor(8,0);
              lcd.print("2t");
              lcd.print(tempC2);    
              lcd.setCursor(16,0);
              lcd.print("3t");
              lcd.print(tempC3);
              lcd.setCursor(24,0);
              lcd.print("4t");
              lcd.print(tempC4);

              sprintf (temp0 , "%dT1, %dT2, %dT3, %dT4 :: ", t1, t2, t3, t4);
              char tt [8];
              rtc.getTimeChar(tt);
              strcat(temp0, tt);
              //       Serial.println(temp0);  //печатаем в монитор порта пришедшую строку
              //       Serial.println(time);
               lcd.setCursor(0,1);
               lcd.print("5");
     }
    if (vrt == 25) {vrt = 0;     //konec, obnulenie VRT
               lcd.setCursor(0,1);
               lcd.print("6");
               } 

 vrt++;



#include <buildTime.h>
#include <microDS3231.h>

#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#include <SoftwareSerial.h>
MicroDS3231 rtc;
SoftwareSerial gsmSerial(9, 10); // RX, TX
int incomingByte = 0;
int led = 13;
String incomingString = "";

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DS_PIN 2
OneWire oneWire(DS_PIN);

DallasTemperature sensors(&oneWire);

uint8_t sensor1[8] = { 0x28, 0xFF, 0x4E, 0xF3, 0x67, 0x18, 0x01, 0xE1 };
uint8_t sensor2[8] = { 0x28, 0xFF, 0xD9, 0xF4, 0x67, 0x18, 0x01, 0x81 };
uint8_t sensor3[8] = { 0x28, 0xFF, 0x96, 0x5F, 0x68, 0x18, 0x01, 0x65 };
uint8_t sensor4[8] = { 0x28, 0xFF, 0x61, 0xC0, 0x67, 0x18, 0x01, 0xB6 };
uint32_t time = 0;
uint32_t current = 0;

int vrt = 0;

int sensePin0 = A0; // ЦЕНТРАЛЬНАЯ КНОПКА
int sensePin1 = A1; // ДЖОЙСТИК

void setup() {
  lcd.begin(40, 2);
  lcd.print("zapusk");

  delay(2000); //время на инициализацию модуля

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(9600); //скорость порта  
  gsmSerial.begin(9600);
  uint32_t current = rtc.getUnix(3);
  time = current;
}

void loop() {
  uint32_t current = rtc.getUnix(0);
 
  if (current >= time + 300) {
    gsmRestart();

    time = current;
  }
  
  char temObchay[100];

  int buttonSignal = analogRead(sensePin0);
  
  if(buttonSignal == 95) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMPERATURA");
    delay(1000);
  }

  // Фунция джойстка
  buttonSignal = analogRead(sensePin1);
  handleJoy(buttonSignal);

  switch (vrt) {
    case 1:
          tempSensors(); // zapros na datchik
      break;
    case 5:
      break;
    case 10:
      break;
    case 15:
      break;
    case 200:
      displayTemperature();
      Serial.println("LCDprint");
      sprintf(temObchay , "%.0dT1, %.0dT2, %.0dT3, %.0dT4 :: ", getTemp(sensor1), getTemp(sensor2), getTemp(sensor3), getTemp(sensor4));
      char time[8];
      rtc.getTimeChar(time);
      strcat(temObchay, time);
      break;
    case 250:
      vrt = 0;     //konec, obnulenie VRT
      break;
  }
delay (10);
  vrt++;

  handleRing(temObchay);
}

void handleJoy(int signal) {
  switch (signal) {
    case 90 ... 100:
      lcd.setCursor(10,0);
      lcd.print("vverh");
      delay(1000);
      break;
    case 465 ... 485:
      lcd.setCursor(10,0);
      lcd.print("vniz");
      delay(1000);
      break;
    case 690 ... 715:
      lcd.setCursor(10,0);
      lcd.print("vlevo");
      delay(1000);
      break;
    case 895 ... 915:
      lcd.setCursor(10,0);
      lcd.print("vpravo");
      delay(1000);
      break;
  }
}

void handleRing(char msg[100]) {
  if (gsmSerial.available()) {  //если GSM модуль что-то послал нам, то
    while (gsmSerial.available()) {  //сохраняем входную строку в переменную val
      incomingByte = gsmSerial.read();
      incomingString += char(incomingByte);
      delay(10);
    }
    
    if (incomingString.indexOf("RING") > -1) {  //если звонок обнаружен, то проверяем номер
      if (incomingString.indexOf("79809483376") > -1) {  //если номер звонящего наш. Укажите свой номер без "+"
        // Serial.println("--- MASTER RING DETECTED ---");
        gsmSerial.println("ATA"); // vkl связь
        digitalWrite(led, HIGH); //включаем светодиод на 3 сек
        delay(1000);
        gsmSerial.println("ATH0"); //разрываем связь
        digitalWrite(led, LOW); //выключаем реле
        sms(String(msg), String("+79611269315"));  //отправляем СМС на номер +71234567890
      } else {
        gsmSerial.println("ATH0");  //разрываем связь
        incomingString = "";
      }
    } 
  }
}

void sms(String text, String phone) { //процедура отправки
  // Serial.println("SMS send started");
  gsmSerial.println("AT+CMGS=\"" + phone + "\"");
  delay(5000);
  gsmSerial.print(text);
  delay(500);
  gsmSerial.print((char)26);
  // delay(500);
  // Serial.println("SMS send complete");
  delay(2000);
}

void setTemp(uint8_t sensor[8]) {
  oneWire.reset();//sbros linii datchikov
  oneWire.select(sensor); //obracshenie k datchiky po nomery
  oneWire.write(0x44); //otpravka na datchik kod - izmer temper
}

float getTemp(uint8_t sensor[8]) {
  oneWire.reset();  //sbros linii
  oneWire.select(sensor); //opredelenie datchika
  oneWire.write(0xBE); // команда на начало чтения измеренной температуры
  byte data[2]; // Место для значения температуры
  data[0] = oneWire.read();  //chtenie mladshego razrjda
  data[1] = oneWire.read();   //chtenie starshego
  
  return ((data[1] << 8) | data[0]) * 0.0625;
}

void gsmRestart() {
  Serial.println("GSM tester v1.0");
  gsmSerial.println("AT+CLIP=1"); //включаем АОН
  delay(100);

  gsmSerial.println("AT+CMGF=1"); //режим кодировки СМС - обычный (для англ.)
  delay(100);

  gsmSerial.println("AT+CSCS=\"GSM\""); //режим кодировки текста
  delay(100);
}

void tempSensors() {
  setTemp(sensor1);
  setTemp(sensor2);
  setTemp(sensor3);
  setTemp(sensor4);
}

void displayTemperature() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(getTemp(sensor1));
  lcd.print("/");

  lcd.setCursor(6, 0);
  lcd.print(getTemp(sensor2));
  lcd.print("/");

  lcd.setCursor(12, 0);
  lcd.print(getTemp(sensor3));

  lcd.setCursor(0, 1);
  lcd.print(getTemp(sensor4));
  lcd.print("/");
 
  lcd.setCursor(6, 1);
  lcd.print(rtc.getHours());
  lcd.print(":");
  lcd.print(rtc.getMinutes());
  lcd.print("/");
  lcd.print(rtc.getDate());
  lcd.print(rtc.getMonth());
}