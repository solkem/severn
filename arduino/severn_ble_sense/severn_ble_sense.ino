/*
  Severn LS Edge AI - Arduino BLE Sense Firmware

  This sketch reads accelerometer and proximity sensor data from the
  Arduino BLE Sense board and exposes it via Bluetooth Low Energy (BLE).

  Required Libraries (install via Arduino Library Manager):
  - ArduinoBLE
  - Arduino_LSM9DS1
  - Arduino_APDS9960

  Board: Arduino Nano 33 BLE Sense
*/

#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>
#include <Arduino_APDS9960.h>

// BLE Service and Characteristic UUIDs (must match web page)
#define ACCELEROMETER_SERVICE_UUID "00001101-0000-1000-8000-00805f9b34fb"
#define ACCEL_CHARACTERISTIC_UUID  "00002101-0000-1000-8000-00805f9b34fb"

#define PROXIMITY_SERVICE_UUID     "00001102-0000-1000-8000-00805f9b34fb"
#define PROXIMITY_CHARACTERISTIC_UUID "00002102-0000-1000-8000-00805f9b34fb"

// BLE Services
BLEService accelerometerService(ACCELEROMETER_SERVICE_UUID);
BLEService proximityService(PROXIMITY_SERVICE_UUID);

// BLE Characteristics
// Accelerometer: 3 floats (x, y, z) = 12 bytes
BLECharacteristic accelCharacteristic(ACCEL_CHARACTERISTIC_UUID, BLERead | BLENotify, 12);

// Proximity: 1 int (0-255) = 1 byte
BLECharacteristic proximityCharacteristic(PROXIMITY_CHARACTERISTIC_UUID, BLERead | BLENotify, 1);

// Sensor data variables
float accelX, accelY, accelZ;
int proximityValue;

// Timing variables for sampling rate
unsigned long lastAccelUpdate = 0;
unsigned long lastProximityUpdate = 0;
const int ACCEL_INTERVAL = 20;      // 50Hz (1000ms / 50 = 20ms)
const int PROXIMITY_INTERVAL = 100;  // 10Hz (proximity sensor is slower)

// Store unique device name
String deviceName;

void setup() {
  Serial.begin(9600);

  // Wait for serial connection (optional, comment out for standalone operation)
  // while (!Serial);

  Serial.println("Severn LS Edge AI - Arduino BLE Sense");
  Serial.println("Initializing sensors...");

  // Initialize IMU (accelerometer, gyroscope, magnetometer)
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("✓ IMU initialized");

  // Initialize Proximity sensor
  if (!APDS.begin()) {
    Serial.println("Failed to initialize APDS9960 sensor!");
    while (1);
  }
  Serial.println("✓ APDS9960 initialized");

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }
  Serial.println("✓ BLE initialized");

  // Generate unique device name from MAC address
  String macAddress = BLE.address();
  // Extract last 4 characters of MAC (without colons)
  String shortID = "";
  int colonCount = 0;
  for (int i = macAddress.length() - 1; i >= 0 && shortID.length() < 4; i--) {
    char c = macAddress.charAt(i);
    if (c != ':') {
      shortID = c + shortID;
    }
  }

  // Create device name: "Arduino-XXXX"
  deviceName = "Arduino-" + shortID;

  // Set BLE device name (this will appear in the web page device picker)
  BLE.setLocalName(deviceName.c_str());
  BLE.setDeviceName(deviceName.c_str());

  // Display the unique name prominently
  Serial.println("========================================");
  Serial.print("   DEVICE NAME: ");
  Serial.println(deviceName);
  Serial.println("   (Write this on a label for the device)");
  Serial.println("========================================");

  // Set up Accelerometer Service
  BLE.setAdvertisedService(accelerometerService);
  accelerometerService.addCharacteristic(accelCharacteristic);
  BLE.addService(accelerometerService);

  // Set up Proximity Service
  proximityService.addCharacteristic(proximityCharacteristic);
  BLE.addService(proximityService);

  // Initialize characteristic values
  byte accelData[12] = {0};
  accelCharacteristic.writeValue(accelData, 12);

  byte proxData[1] = {0};
  proximityCharacteristic.writeValue(proxData, 1);

  // Start advertising
  BLE.advertise();

  Serial.println();
  Serial.println("BLE device active, waiting for connections...");
}

void loop() {
  // Wait for a BLE central device to connect
  BLEDevice central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    // While the central is connected, read and send sensor data
    while (central.connected()) {
      unsigned long currentTime = millis();

      // Update accelerometer data at 50Hz
      if (currentTime - lastAccelUpdate >= ACCEL_INTERVAL) {
        lastAccelUpdate = currentTime;
        updateAccelerometer();
      }

      // Update proximity data at 10Hz
      if (currentTime - lastProximityUpdate >= PROXIMITY_INTERVAL) {
        lastProximityUpdate = currentTime;
        updateProximity();
      }
    }

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}

void updateAccelerometer() {
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(accelX, accelY, accelZ);

    // Pack float values into byte array
    byte accelData[12];
    memcpy(accelData, &accelX, 4);
    memcpy(accelData + 4, &accelY, 4);
    memcpy(accelData + 8, &accelZ, 4);

    // Update BLE characteristic
    accelCharacteristic.writeValue(accelData, 12);

    // Debug output
    Serial.print("Accel - X: ");
    Serial.print(accelX);
    Serial.print(" Y: ");
    Serial.print(accelY);
    Serial.print(" Z: ");
    Serial.println(accelZ);
  }
}

void updateProximity() {
  if (APDS.proximityAvailable()) {
    proximityValue = APDS.readProximity();

    // Pack proximity value (0-255) into byte
    byte proxData[1];
    proxData[0] = (byte)proximityValue;

    // Update BLE characteristic
    proximityCharacteristic.writeValue(proxData, 1);

    // Debug output
    Serial.print("Proximity: ");
    Serial.println(proximityValue);
  }
}
