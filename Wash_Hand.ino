#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define triggerPin 11
#define echoPin 10

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int pinIRSabun = 9;
const int RelaySabun = 2;
const int pinIRAir = 8;
const int RelayAir = 4;
String arrData [2];

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin();

  // Pin Mode untuk pembacaan Air Sabun
  pinMode(pinIRSabun, INPUT);
  pinMode(RelaySabun, OUTPUT);

  // Pin Mode untuk pembacaan Air Bersih
  pinMode(pinIRAir, INPUT);
  pinMode(RelayAir, OUTPUT);

  // Menampilkan ke layar LCD
  lcd.setCursor(0,1);
  lcd.print("By Bobby Rinaldo");
  delay(5000);
  lcd.clear();
}

void loop() {
  String dataValue, dataMinAir; 
  String data = "";
  while(Serial.available()>0) {
    data += char(Serial.read());
  }
  data.trim();
  if(data != "") {
    int index = 0;
    for(int i=0; i<= data.length(); i++) {
      char delimiter = '#';
      if(data[i] != delimiter) {
        arrData[index] += data[i];
      } else {
        index++;
      }
        dataValue = arrData[0];
        dataMinAir = arrData[1];
        dataValue.toInt();
        dataMinAir.toInt();
        Serial.println(dataValue);
        Serial.println(dataMinAir);
    }
    arrData[0] = "";
    arrData[1] = "";
  }

  lcd.setCursor(0,0);
  lcd.print("Level Air " + dataValue);
// Pembacaan Sensor Sabun dan menyalakan Relay
if(dataValue > dataMinAir){
  int sensorsabun = digitalRead(pinIRSabun);
  if(sensorsabun == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(RelaySabun, HIGH);
    delay(80);
  }else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(RelaySabun, LOW);
  }
// end
// Pembacaan Sensor Air dan menyalakan Relay
  int sensorair = digitalRead(pinIRAir);
  if(sensorair == LOW) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(RelayAir, HIGH);
    delay(10000);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(RelayAir, LOW);
  }
 } else if(dataValue < dataMinAir) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(RelayAir, LOW);
    digitalWrite(RelaySabun, LOW);
    
    lcd.setCursor(0,1);
    lcd.print("Maaf Air Habis");
    delay(5000);
    lcd.clear();
 }
}
