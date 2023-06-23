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



MFRC522 mfrc522(SS_PIN,RST);
ESP8266WiFiMulti WiFiMulti;
WiFiManager wifi;
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


void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();

   for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Aitel 4G MiFi_65DB", "51377932");
  Serial.println("Reading Data from Card");
 

}

void loop() {

    if ((WiFiMulti.run() == WL_CONNECTED)) {
    

      
      MFRC522::MIFARE_Key key;
    
      HTTPClient https;


      for (byte i = 0; i < 6; i++)
      {
        key.keyByte[i]= 0xFF;
      
      }

      if(!mfrc522.PICC_IsNewCardPresent())
      {
        return;
      }
      if(!mfrc522.PICC_ReadCardSerial())
      {
        return;
      }
      Serial.println("Card Detected");
      // Authentecating block 1

      //block 1
      byte block ;
      byte len =18;
      block = 1;
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
        Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,fname,&len);
      memcpy(person->fname,fname,sizeof(fname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
        Serial.printf("Card Read %s\n\n",person->fname);
      
      //block 2 fname

      block=2;
      byte sname[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      {
        Serial.printf("Authentication for block %d Successfull\n",block);
      }
      status = mfrc522.MIFARE_Read(block,sname,&len);
      memcpy(person->sname,sname,sizeof(sname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      Serial.printf("Card Read %s\n\n",person->sname);

      //Read last name
        block=4;
      byte lname[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
        Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,lname,&len);
      memcpy(person->lname,lname,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      Serial.printf("Card Read %s\n\n",person->lname);

      
      //Account No
      //Read last name
      block=5;
      byte acct[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
        Serial.printf("Authentication for block %d Successfull\n",block);
      
      status = mfrc522.MIFARE_Read(block,acct,&len);
      memcpy(person->account,acct,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      Serial.printf("Card Read %s\n\n",person->account);


      //Security Pin
      //Read last name
        block=8;
      byte sec[19];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
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
        return;
      }
      else
        Serial.printf("Card Read %s\n\n",person->security);


      //expiration date
      block=10;
      byte month[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      {
        Serial.printf("Authentication for block %d Successfull\n",block);
      }
      status = mfrc522.MIFARE_Read(block,month,&len);
      memcpy(person->exp_month,month,sizeof(month));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      Serial.printf("Card Read %s\n\n",person->exp_month);


      //Read year
      block=12;
      byte year[20];
      status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
      if(status != MFRC522::STATUS_OK)
      {
        Serial.printf("Cant Authenticate Block,%d: ",block);
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      {
        Serial.printf("Authentication for block %d Successfull\n",block);
      }
      status = mfrc522.MIFARE_Read(block,year,&len);
      memcpy(person->exp_year,year,sizeof(year));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
      else
      {
        Serial.printf("Card Read %s\n\n",person->exp_year);
      }


      memcpy(person->uid,mfrc522.uid.uidByte,mfrc522.uid.size);
      array_to_string(mfrc522.uid.uidByte,mfrc522.uid.size,person->uid);
      
      Serial.println(person->uid);
      printHex(mfrc522.uid.uidByte,mfrc522.uid.size);
      


   
      


    delay(1000);
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    Serial.println("*****************************************************************");
    Serial.printf(" User name: %s %s %s\n",person->sname,person->fname,person->lname);
    Serial.printf(" Account no: %s\n",person->account);
    Serial.printf(" Secutity Code: %s\n",person->security);

    Serial.printf(" Expiration Date: %s\\%s \n",person->exp_month,person->exp_year);
    Serial.println("*****************************************************************");
    String  name[30];
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
    //Serial.print( input);
    StaticJsonDocument<200> into;
    //sonObject obj = into.as<char>();
    int lenh = measureJsonPretty(into);
    Serial.println();
    Serial.println(lenh);
    
    //WIfi
 
    //std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
WiFiClient client;
    //client->setFingerprint(fingerprint_sni_cloudflaressl_com);
     //client->setInsecure();  
   
    Serial.print("[HTTPS] begin...\n");
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
      keyi = "Bearer "+ keyi;
    if (https.begin(client, address)) {
      https.addHeader("Content-Type", "application/json");
      https.addHeader("Authorization","12345abcdef");
        // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());

        String payload = https.getString();
        Serial.println(payload);
        
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
      delay(10000);
        delete person;
  }
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
