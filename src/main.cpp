<<<<<<< HEAD
#include "headers/headers.h"
=======
#include <Arduino.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include  <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiManager.h>
#include <WiFiClientSecure.h>


#define  RST D1
#define SS_PIN D2
#define SIZE 15  
#define PORT 80

>>>>>>> reading_data/reading_data1.0


const char address[]="http://paywave-dev.eba-ypxxxpkf.us-east-1.elasticbeanstalk.com/signUp";   //HOST_URL
const char* ssid = "Aitel 4G MiFi_65DB";
const char* password ="51377932";
//Object definition
MFRC522 mfrc522(SS_PIN,RST);
ESP8266WiFiMulti WiFiMulti;
WiFiManager wifi;
<<<<<<< HEAD
MFRC522::MIFARE_Key key;
HTTPClient https;
WiFiClient client;
=======
void strclean (unsigned char* src);
void printHex(byte *buffer, byte bufferSize);
void array_to_string(byte array[], unsigned int len, char buffer[]);

void printHex(byte *buffer, byte bufferSize);
void array_to_string(byte array[], unsigned int len, char buffer[]);



typedef unsigned char byte;
typedef struct {
  byte fname[SIZE];
  byte sname[SIZE];
  byte lname[SIZE];
  byte account[SIZE];
  byte security[SIZE];
  byte exp_month[3];
  byte exp_year[SIZE];
  char uid[32];
  long int price;


}id;
char address[]="http://paywave-dev.eba-ypxxxpkf.us-east-1.elasticbeanstalk.com/signUp";

  char uid[32];
  long int price;

}id;
char address[]="http://paywave-dev.eba-ypxxxpkf.us-east-1.elasticbeanstalk.com/signUp";
>>>>>>> reading_data/reading_data1.0


//Setup
void setup() {
  Serial.begin(115200);
  SPI.begin();              //Initializing SPI
  mfrc522.PCD_Init();       // Initializing MMFRC55
    for (byte i = 0; i < 6; i++)key.keyByte[i]= 0xFF;
      
  // Wifi Connectivity Settings
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid,password);
  Serial.println("Connecting");
    if ((WiFiMulti.run() != WL_CONNECTED))
    {
      Serial.print("*");
    }
    else
     Serial.println("\nConnected");
}

void loop() {

    if ((WiFiMulti.run() == WL_CONNECTED)) { //Checking if Wifi is Connected 

      if(!mfrc522.PICC_IsNewCardPresent())  //Checking if a Card is present 
      {
        return;
      }
      if(!mfrc522.PICC_ReadCardSerial())    //Selecting on Card
      {
        return;
      }

      Serial.println("Card Detected");
      // Authentecating block 1

      //block variables 
      byte block =1 ;
      byte len =18;
      id *person = new id;
      byte fname[20];
      MFRC522::StatusCode status;

      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      //  Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,fname,&len);
      memcpy(person->fname,fname,sizeof(fname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
       // Serial.printf("Card Read %s\n\n",person->fname);
      
      //block 2 fname

      block++;
      byte sname[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      //else
    // Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,sname,&len);
      memcpy(person->sname,sname,sizeof(sname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block=1;
        return;
      }
      //else
      //Serial.printf("Card Read %s\n\n",person->sname);
      //Read last name
       block=4;
      byte lname[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      //else
        //Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,lname,&len);
      memcpy(person->lname,lname,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      //else
      //Serial.printf("Card Read %s\n\n",person->lname);

      
      //Account No
      //Read last name
      block++;
      byte acct[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
     // else
     //  Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,acct,&len);
      memcpy(person->account,acct,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      //else
      //Serial.printf("Card Read %s\n\n",person->account);


      //Security Pin
      //Read last name
        block=8;
      byte sec[19];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      else
        {Serial.printf("Authentication for block %d Successfull\n",block);}
    
      status = mfrc522.MIFARE_Read(block,sec,&len);
      memcpy(person->security,sec,sizeof(sec));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
      //else
      //  Serial.printf("Card Read %s\n\n",person->security);


      //expiration date
      block=10;
      byte month[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block = 1;
        return;
      }


      status = mfrc522.MIFARE_Read(block,month,&len);
      memcpy(person->exp_month,month,sizeof(month));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block = 1;
        return;
      }

      //Read year
      block=12;
      byte year[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d: ",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        block = 1;
        return;
      }
      
      status = mfrc522.MIFARE_Read(block,year,&len);
      memcpy(person->exp_year,year,sizeof(year));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        block =1;
        return;
      }
     

      memcpy(person->uid,mfrc522.uid.uidByte,mfrc522.uid.size);
      array_to_string(mfrc522.uid.uidByte,mfrc522.uid.size,person->uid);
      
      //Serial.println(person->uid);
      //printHex(mfrc522.uid.uidByte,mfrc522.uid.size);
      


   
      

    delay(250);
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();



    Serial.println("*****************************************************************");
    Serial.printf(" User name: %s %s %s\n",person->sname,person->fname,person->lname);
    Serial.printf(" Account no: %s\n",person->account);
    Serial.printf(" Secutity Code: %s\n",person->security);
<<<<<<< HEAD
    Serial.println();
    Serial.printf("UID %s\n",person->uid);
=======

>>>>>>> reading_data/reading_data1.0
    Serial.printf(" Expiration Date: %s\\%s \n",person->exp_month,person->exp_year);
    Serial.println("*****************************************************************");
   
   
    strclean(person->sname);
    strclean(person->fname);
    strclean(person->lname);
    strclean(person->account);
    strclean(person->security);
    strclean(person->exp_month);
    strclean(person->exp_year);
    strclean(person->exp_month);
    //Serial.print((const __FlashStringHelper*)person->fname);

    Serial.println("*****************************************************************");
    Serial.printf(" User name: %s %s %s\n",person->sname,person->fname,person->lname);
    Serial.printf(" Account no: %s\n",person->account);
    Serial.printf(" Secutity Code: %s\n",person->security);
    Serial.printf(" Expiration Date: %s\\%s \n",person->exp_month,person->exp_year);
    Serial.println("*****************************************************************");

    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("Serialization");
    Serial.println("****************************************");
    
    //Json Objectification and Stringlization
    StaticJsonDocument<200> into;
<<<<<<< HEAD
    into["email"].set("Samuel@dd");
    into["userName"].set("james");
    into["password"].set("Daniel@o14o");
    into["confirmPassword"].set("Daniel@o14o");
    //into["year"].set(person->exp_year);
    //into["month"].set(person->exp_month);
    //into["security"].set(person->security);
    String output2;

    serializeJsonPretty(into,output2);
    Serial.print(output2);
=======
    //sonObject obj = into.as<char>();
>>>>>>> reading_data/reading_data1.0
    int lenh = measureJsonPretty(into);
    Serial.println();
    Serial.println(lenh);
    
    //WIfi
 
    //std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    //client->setFingerprint(fingerprint_sni_cloudflaressl_com);
    //client->setInsecure();  
   
    Serial.print("[HTTPS] begin...\n");
<<<<<<< HEAD
    String keyi ="emmanuel";    //Authentication key
=======
    if (https.begin(client, address)) {
      https.addHeader("Content-Type", "application/json");
      https.addHeader("Authorization","12345abcdef");
      //https.addHeader("server","Microsoft-IIS/10.0");
      //https.addHeader("Content-Length",String(lenh));
      //https.addHeader("Connection","keep-alive");
      //https.addHeader(" transfer-encoding","chunked");
      //https.addHeader(" x-powered-by","ASP.NET");
        // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.POST(output2);

    String keyi ="emmanuel";
>>>>>>> reading_data/reading_data1.0
      keyi = "Bearer "+ keyi;
    if (https.begin(client, address)) {
      https.addHeader("Content-Type", "application/json");
      https.addHeader("Authorization","12345abcdef");
<<<<<<< HEAD
      https.addHeader("server","Microsoft-IIS/10.0");
      https.addHeader("Content-Length",String(lenh));
      https.addHeader("Connection","keep-alive");
      https.addHeader(" transfer-encoding","chunked");
      https.addHeader(" x-powered-by","ASP.NET");

        // HTTPS
        
      Serial.print("[HTTPS] POST...\n");
      // start connection and send HTTP header
      int httpCode = https.sendRequest("POST",output2);
    
      Serial.println(httpCode);

      // httpCode will be negative on error
      if (httpCode > 0) {

          
        // file found at server
        if(httpCode== HTTP_CODE_PROCESSING)
            {
              Serial.print("Processing");
              while(httpCode==HTTP_CODE_PROCESSING)
              {
                Serial.print(".");
              }
              return;
            }
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == HTTP_CODE_CREATED) {
=======
        // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
>>>>>>> reading_data/reading_data1.0
          String payload = https.getString();
          Serial.println(payload);
          Serial.printf("Playload: %d",httpCode);
        } 
         // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] PUT... code: %d\n", httpCode);
        String payload = https.getString();
        Serial.println(payload);
      } else {
<<<<<<< HEAD
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
=======
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());

>>>>>>> reading_data/reading_data1.0
        String payload = https.getString();
        Serial.println(payload);
        
      }
<<<<<<< HEAD
      

=======
>>>>>>> reading_data/reading_data1.0
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
      delay(1000);
        delete person;
  }
<<<<<<< HEAD
}
=======
}
void strclean (unsigned char * src) {
    // Run two pointers in parallel.

    

    // Process every source character.
    
      unsigned char *dst = src;

    while (*src) {
        // Only copy (and update destination pointer) if suitable.
        // Update source pointer always.

        if (isalpha(*src)){ *dst++ = *src;}else if(isdigit(*src)){*dst++ = *src;}
        src++;
        
    }

    // Finalise destination string.

    *dst = '\0';
}
      void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i],HEX);
  }
      }

std::string byteToString(const unsigned char* byteArray, size_t len) {
    char* str = new char[len + 1];
    memcpy(str, byteArray, len);
    str[len] = '\0';
    std::string result(str);
    delete[] str;
    return result;
}
void array_to_string(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';

}
>>>>>>> reading_data/reading_data1.0
