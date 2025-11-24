# Arduino BLE Sense Firmware

This folder contains the Arduino sketch for the Arduino Nano 33 BLE Sense board.

## Hardware Required
- Arduino Nano 33 BLE Sense

## Required Libraries

Install these libraries using the Arduino IDE Library Manager (Sketch → Include Library → Manage Libraries):

1. **ArduinoBLE** (by Arduino)
2. **Arduino_LSM9DS1** (by Arduino) - for accelerometer/gyroscope/magnetometer
3. **Arduino_APDS9960** (by Arduino) - for proximity/gesture sensor

## Installation Steps

1. Open Arduino IDE
2. Install the required libraries listed above
3. Select board: **Tools → Board → Arduino Nano 33 BLE**
4. Select port: **Tools → Port → [your Arduino port]**
5. Open the sketch: **arduino/severn_ble_sense/severn_ble_sense.ino**
6. Upload to your Arduino BLE Sense board

## How It Works

The sketch:
- Reads accelerometer data at 50Hz (every 20ms)
- Reads proximity sensor data at 10Hz (every 100ms)
- Exposes data via two BLE services:
  - **Accelerometer Service** (UUID: 00001101-0000-1000-8000-00805f9b34fb)
    - Sends X, Y, Z acceleration values as 3 floats (12 bytes)
  - **Proximity Service** (UUID: 00001102-0000-1000-8000-00805f9b34fb)
    - Sends proximity value as 1 byte (0-255, where higher = closer)

## Unique Device Names (Important for Classrooms!)

Each Arduino automatically generates a **unique device name** based on its MAC address. The name format is: **Arduino-XXXX** (e.g., "Arduino-A1B2", "Arduino-C3D4").

### Setting Up Multiple Devices (for teachers):

**One-Time Setup Process:**
1. Upload the sketch to the first Arduino
2. Open **Serial Monitor** (Tools → Serial Monitor, set to 9600 baud)
3. Look for the device name display:
   ```
   ========================================
      DEVICE NAME: Arduino-A1B2
      (Write this on a label for the device)
   ========================================
   ```
4. Write this name on a physical label and attach it to the Arduino
5. Repeat for all 20 devices

**For Students:**
- Each student's Arduino will have a unique label (e.g., "Arduino-A1B2")
- When they connect from the web page, they select the matching name
- No two devices will have the same name!

## Troubleshooting

**Problem: Libraries won't install**
- Make sure you have the latest Arduino IDE (1.8.19+ or 2.x)
- The Arduino Nano 33 BLE Sense libraries require the board to be installed first
- Go to Tools → Board → Boards Manager → Search for "Arduino Mbed OS Nano Boards" and install

**Problem: Upload fails**
- Press the reset button on the Arduino twice quickly to enter bootloader mode
- Try a different USB cable (some cables are power-only)

**Problem: Can't find device in web page**
- Make sure the Arduino is powered on (LED should be lit)
- Check Serial Monitor to confirm BLE is advertising
- The device name must start with "Arduino" to be detected

## Serial Monitor

Open the Serial Monitor (Tools → Serial Monitor) at 9600 baud to see debug output:
- Sensor initialization status
- Connection/disconnection events
- Real-time sensor readings
