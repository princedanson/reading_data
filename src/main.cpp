
#include "headers/headers.h"
MFRC522 mfrc522(SS_PIN,RST);
ESP8266WiFiMulti WiFiMulti;
WiFiManager wifi;
MFRC522::MIFARE_Key key;
HTTPClient https;
WiFiClient client;

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
      for (byte i = 0; i < 6; i++)key.keyByte[i]= 0xFF;
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
      status = mfrc522.MIFARE_Read(block,fname,&len);
      memcpy(person->fname,fname,sizeof(fname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
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
      status = mfrc522.MIFARE_Read(block,sname,&len);
      memcpy(person->sname,sname,sizeof(sname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
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
      status = mfrc522.MIFARE_Read(block,lname,&len);
      memcpy(person->lname,lname,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
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
      status = mfrc522.MIFARE_Read(block,acct,&len);
      memcpy(person->account,acct,sizeof(lname));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
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
      status = mfrc522.MIFARE_Read(block,sec,&len);
      memcpy(person->security,sec,sizeof(sec));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
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
      status = mfrc522.MIFARE_Read(block,month,&len);
      memcpy(person->exp_month,month,sizeof(month));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
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
        return;
      }
      status = mfrc522.MIFARE_Read(block,year,&len);
      memcpy(person->exp_year,year,sizeof(year));
      if (status != MFRC522::STATUS_OK)
      {
        Serial.print("Can't Read Card: ");
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
      }
    memcpy(person->uid,mfrc522.uid.uidByte,mfrc522.uid.size);
    array_to_string(mfrc522.uid.uidByte,mfrc522.uid.size,person->uid);
      
    Serial.println(person->uid);
    printHex(mfrc522.uid.uidByte,mfrc522.uid.size);
         
    delay(250);
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    Serial.println("*****************************************************************");
    Serial.printf(" User name: %s %s %s\n",person->sname,person->fname,person->lname);
    Serial.printf(" Account no: %s\n",person->account);
    Serial.printf(" Secutity Code: %s\n",person->security);
    Serial.println();
    Serial.printf("UID %s\n",person->uid);
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

    //Stringlization 
    StaticJsonDocument<200> into;
    into["email"].set(person->sname);
    into["userName"].set(person->uid);
    into["password"].set("Daniel@o14o");
    into["confirmPassword"].set("Daniel@o14o");
    //into["year"].set(person->exp_year);
    //into["month"].set(person->exp_month);
    //into["security"].set(person->security);
    String output2;
    serializeJsonPretty(into,output2);
    Serial.print(output2);
    int lenh = measureJsonPretty(into);
    Serial.println();
    Serial.println(lenh);
    
    //WIfi
    //std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    //client->setFingerprint(fingerprint_sni_cloudflaressl_com);
    //client->setInsecure();  
   
    Serial.print("[HTTPS] begin...\n");
    String keyi ="emmanuel";
    keyi = "Bearer "+ keyi;
    if (https.begin(client, address)) {
      https.addHeader("Content-Type", "application/json");
      https.addHeader("Authorization","12345abcdef");
      https.addHeader("server","Microsoft-IIS/10.0");
      https.addHeader("Content-Length",String(lenh));
      https.addHeader("Connection","keep-alive");
      https.addHeader(" transfer-encoding","chunked");
      https.addHeader(" x-powered-by","ASP.NET");
      // HTTPS
      Serial.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.sendRequest("POST",output2);
      // httpCode will be negative on error
      if (httpCode > 0) {
        
        while(httpCode == HTTP_CODE_PROCESSING) Serial.print(".");
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode==HTTP_CODE_ACCEPTED) {
          String payload = https.getString();
          Serial.println(payload);
        }
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        Serial.println(https.errorToString(httpCode));
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
        String payload = https.getString();
        Serial.println(payload);
        
      }
      

      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
      delay(1000);
        delete person;
  }
}
