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
#include <ctype.h>
#include  <string>


//Header Constants
#define RST D1          //Reset pin
#define SS_PIN D2       //Select_PIn
#define SIZE 15         
#define PORT 80         //client connectivity Port


//Userdefine variable
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

//Function prototypes
void strclean (unsigned char* src);
void printHex(byte *buffer, byte bufferSize);
void array_to_string(byte array[], unsigned int len, char buffer[]);
