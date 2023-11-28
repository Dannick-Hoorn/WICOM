#include <Arduino.h>

/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleServer.cpp
    Ported to Arduino ESP32 by Evandro Copercini
    updates by chegewara
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "9350ea95-9152-47f1-be81-1c3182011d4b"
#define CHARACTERISTIC_UUID "799b207f-a661-4121-86a5-795dc039acb3"
#define ledPin 10

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;

class MyCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic)
    {
      Serial.println("Characteristic just written!");
      std::string rxValue = pCharacteristic->getValue();
      Serial.print("Characteristic value = ");
      Serial.println(rxValue.c_str());
      if(rxValue == "led"){
        digitalWrite(ledPin, HIGH);
      }
      else{
        digitalWrite(ledPin, LOW);
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode(ledPin, OUTPUT);

  BLEDevice::init("ESP32 Dannick");
  pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Dannick");
  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}