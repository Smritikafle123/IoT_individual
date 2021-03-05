#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <MFRC522.h>

BlynkTimer timer;
char auth[] = "Cku0jBLLna51nEQOr1R2ftQuo5FsavWm";
char ssid[] = "vaak";
char pass[] = "123456789";
constexpr uint8_t RST_PIN = D3;  
constexpr uint8_t SS_PIN = D4; 

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
String tag;
void setup() {
 Serial.begin(9600);
 Blynk.begin(auth, "vaak", "123456789"); 
 SPI.begin(); // Init SPI bus
 rfid.PCD_Init(); // Init MFRC522
 pinMode(D8, OUTPUT);
 pinMode(16,OUTPUT);
 pinMode(5,OUTPUT);
}

void loop() {

 Blynk.run();
 if ( ! rfid.PICC_IsNewCardPresent())
 return;
 if (rfid.PICC_ReadCardSerial()) {
   for (byte i = 0; i < 4; i++) {
     tag += rfid.uid.uidByte[i];
   }

  Serial.println(tag);
 if (tag == "73159133152") {
  Serial.println("Access Granted!");
  digitalWrite(D8, HIGH);
  delay(100);
  digitalWrite(D8, LOW);
  delay(100);
  digitalWrite(D8, HIGH);
  delay(100);
  digitalWrite(D8, LOW);
  delay(100);
  digitalWrite(D8, HIGH);
  delay(100);
  digitalWrite(D8, LOW);
  delay(100);
  digitalWrite(16,LOW);
  digitalWrite(5,HIGH); 
  Blynk.notify("Person has entered");
  } 
else {

  Serial.println("Access Denied!");
  digitalWrite(D8, HIGH);
  delay(2000);
  Blynk.notify("Someone is trying to open the door");
  digitalWrite(D8, LOW);
  digitalWrite(16,HIGH);
  digitalWrite(5,LOW);
 }

 tag = "";
 rfid.PICC_HaltA();
 rfid.PCD_StopCrypto1();
 }
}
