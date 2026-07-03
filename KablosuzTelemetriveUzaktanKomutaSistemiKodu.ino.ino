#include "BluetoothSerial.h"
#include <ESP32Servo.h>

BluetoothSerial SerialBT;
Servo hedefServo;

// Hedef HC-05 MAC Adresi
uint8_t thalesTargetAddress[6] = {0x00, 0x23, 0x09, 0x01, 0x2F, 0x6E}; 

// Donanım Pinleri
const int servoPin = 13;
const int rolePin = 12;

// Değişkenler
char gelenKarakter;
String veriTamponu = "";
bool paketBasladi = false;
int gelenPotDegeri = 0;
int servoAcisi = 0;

void setup() {
  Serial.begin(115200); 
  
  // --- AKTÜATÖR KURULUMLARI ---
  hedefServo.attach(servoPin); 
  pinMode(rolePin, OUTPUT);
  digitalWrite(rolePin, LOW); 
  
  // --- BLUETOOTH KURULUMU ---
  SerialBT.setPin("1234", 4);
  SerialBT.begin("ESP32_Receiver_Station", true); 
  
  Serial.println("Sistem Baslatiliyor (LCD Iptal Edildi)...");
  
  if (SerialBT.connect(thalesTargetAddress)) {
    Serial.println("BAGLANTI BASARILI! Aktuatorler devrede.");
  } else {
    Serial.println("Baglanti basarisiz. Sifreyi veya mesafeyi kontrol edin.");
  }
}

void loop() {
  while (SerialBT.available()) {
    gelenKarakter = SerialBT.read(); 
    
    if (gelenKarakter == '<') {
      paketBasladi = true;   
      veriTamponu = "";      
    } 
    else if (gelenKarakter == '>') {
      paketBasladi = false;  
      gelenPotDegeri = veriTamponu.toInt();
      
      // Motor Yon/Hiz Haritalamasi
      servoAcisi = map(gelenPotDegeri, 0, 1023, 0, 180);
      hedefServo.write(servoAcisi);
      
      // Kritik Alan Kontrolu (Role)
      if (gelenPotDegeri > 900) {
        digitalWrite(rolePin, HIGH); 
      } else {
        digitalWrite(rolePin, LOW);  
      }
      
      // Verileri yine de bilgisayar ekranindan (Serial Monitor) gorebilmen icin:
      Serial.print("Ham Veri: ");
      Serial.print(gelenPotDegeri);
      Serial.print("\t --> \tMotor Komutu: ");
      Serial.println(servoAcisi);
    } 
    else {
      if (paketBasladi) {
        veriTamponu += gelenKarakter;
      }
    }
  }
}