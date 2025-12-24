# CLAUDE.md — Project Context for AI Assistants

This file provides essential context about the Severn LS Edge AI project for AI assistants (like Claude) working with this codebase.

---

## Project Overview

**Severn LS Edge AI** is an educational platform designed to teach 4th and 5th grade students (ages 9-11) about Edge AI, machine learning, and data privacy using hands-on hardware.

### Mission
Democratize AI education by creating an open-source, privacy-first alternative to cloud-based ML tools like Google's Teachable Machine — but running entirely on local hardware that students can own, understand, and modify.

### Why This Matters
- **Privacy by Design**: Unlike cloud-based AI tools that send student data to external servers, all processing happens locally on the Arduino device or in the browser
- **Demystifying AI**: Students see the actual code, sensors, and data — not a black box
- **Real Hardware Skills**: Working with physical Arduino devices teaches tangible IoT concepts
- **Classroom-Ready**: Unique device naming system supports 20+ devices without conflicts

---

## Technical Architecture

### Hardware
- **Board**: Arduino Nano 33 BLE Sense Rev2
- **Sensors**:
  - BMI270 + BMM150 IMU (accelerometer/gyroscope/magnetometer)
  - APDS9960 (proximity/gesture/color sensor)
- **Communication**: Bluetooth Low Energy (BLE)

### Software Stack

```
┌─────────────────────────────────────────────────────────────┐
│  Web Interface (index.html)                                 │
│  - Pure HTML/CSS/JavaScript (no frameworks)                 │
│  - Web Bluetooth API for device communication               │
│  - Real-time sensor data visualization                      │
│  - Works offline, no server required                        │
└──────────────────────────┬──────────────────────────────────┘
                           │ BLE (Bluetooth Low Energy)
┌──────────────────────────▼──────────────────────────────────┐
│  Arduino Firmware (severn_ble_sense.ino)                    │
│  - Reads sensors at configurable rates                      │
│  - Exposes data via BLE GATT services                       │
│  - Unique device names from MAC address                     │
│  - C++ running on ARM Cortex-M4                             │
└─────────────────────────────────────────────────────────────┘
```

### Key File Locations

| File | Purpose |
|------|---------|
| `index.html` | Complete web interface (HTML + CSS + JS in single file) |
| `arduino/severn_ble_sense/severn_ble_sense.ino` | Arduino firmware for sensor reading and BLE |
| `arduino/README.md` | Firmware setup and classroom deployment guide |
| `README.md` | Main project documentation |

---

## BLE Protocol Specification

### Device Naming
- Format: `Arduino-XXXX` where XXXX is derived from MAC address
- Example: `Arduino-A1B2`, `Arduino-C3D4`
- Critical for classroom management with multiple devices

### Services and Characteristics

**Accelerometer Service**
- Service UUID: `00001101-0000-1000-8000-00805f9b34fb`
- Characteristic UUID: `00002101-0000-1000-8000-00805f9b34fb`
- Data: 12 bytes (3 × float32, little-endian: X, Y, Z)
- Update rate: 50Hz (every 20ms)

**Proximity Service**
- Service UUID: `00001102-0000-1000-8000-00805f9b34fb`
- Characteristic UUID: `00002102-0000-1000-8000-00805f9b34fb`
- Data: 1 byte (uint8, 0=far, 255=near)
- Update rate: 10Hz (every 100ms)

---

## Development Guidelines

### When Modifying the Web Interface (`index.html`)

1. **Keep it single-file**: No build process, no npm, no bundling. Teachers need to just open the file.
2. **Browser support**: Target Chrome, Edge, Opera only (Web Bluetooth requirement)
3. **Offline-first**: Never add features that require internet connectivity
4. **Student-friendly UI**: Large buttons, clear feedback, mobile-responsive
5. **Accessibility**: Consider color contrast and readability for young users

### When Modifying the Firmware (`severn_ble_sense.ino`)

1. **Rev2 compatibility**: Use `Arduino_BMI270_BMM150` library, not `Arduino_LSM9DS1`
2. **Unique names matter**: The MAC-based naming is essential for classrooms
3. **Serial output**: Keep the device name banner for teacher setup
4. **Stable rates**: Maintain 50Hz accel, 10Hz proximity unless there's a good reason
5. **BLE UUIDs**: Don't change existing UUIDs; web interface depends on them

### Adding New Sensors

To add a new sensor:
1. Add a new BLE service with unique UUID (0x1103, 0x1104, etc.)
2. Add corresponding characteristic
3. Update `index.html` with matching UUIDs
4. Add UI elements to display the data
5. Update documentation

### Privacy Requirements

**Never add features that**:
- Send data to external servers
- Require user accounts or login
- Store data in cloud services
- Track usage analytics
- Phone home for any reason

This is a core project principle, not a preference.

---

## Educational Context

### Target Audience
- **Primary**: 4th and 5th grade students (ages 9-11)
- **Secondary**: Teachers, parents, after-school programs, maker spaces

### Learning Objectives

Students should be able to:
1. Explain what a sensor is and how it measures the physical world
2. Connect a Bluetooth device to a computer
3. Read and interpret real-time sensor data
4. Understand that AI can run on small, local devices
5. Articulate why data privacy matters
6. Recognize that they can build and modify technology, not just consume it

### Classroom Deployment

The project is designed for classrooms with 20+ students:
- Each Arduino gets a unique name (no conflicts)
- Names are printed to Serial Monitor for labeling
- Web interface shows all nearby devices
- Students select their own device from the list
- No account creation or internet required

---

## Planned Features (Roadmap)

### Next Priority
1. **Data recording**: Capture sensor data to CSV/JSON for ML training
2. **Edge Impulse integration**: Export data → train model → deploy back to Arduino
3. **On-device inference**: Run trained TinyML models locally

### Future Ideas
- Activity recognition (walking, running, jumping)
- Gesture recognition (wave, circle, shake)
- Teacher dashboard for monitoring all student devices
- Lesson plan materials and curriculum guide
- Localization (Spanish, French, etc.)

---

## Common Tasks

### Testing the Web Interface
1. Upload firmware to Arduino
2. Open `index.html` in Chrome/Edge/Opera
3. Click "Connect to Arduino"
4. Select your device from the list
5. Verify sensor values update in real-time

### Testing the Firmware
1. Open Arduino IDE
2. Open `arduino/severn_ble_sense/severn_ble_sense.ino`
3. Select board: Arduino Nano 33 BLE
4. Upload and open Serial Monitor (9600 baud)
5. Verify sensors initialize and BLE starts advertising

### Adding a New Feature
1. Check if it violates privacy principles (see above)
2. Keep the single-file architecture for web
3. Test on actual Arduino hardware
4. Update README.md and this file
5. Keep the target audience (elementary students) in mind

---

## Troubleshooting Reference

### Arduino Won't Upload
- Double-press reset button for bootloader mode
- Check USB cable (some are power-only)
- Verify board selection in Arduino IDE

### Web Bluetooth Not Working
- Must use Chrome, Edge, or Opera
- Check `chrome://flags` if issues persist
- HTTPS or localhost required (security restriction)

### Sensors Not Reading
- Check Serial Monitor for initialization errors
- Verify using Rev2 libraries (BMI270, not LSM9DS1)
- Check I2C connections (unlikely issue with integrated sensors)

### BLE Connection Drops
- Check for interference (USB 3.0 hubs are common culprits)
- Ensure stable power to Arduino
- Stay within ~10 meter range

---

## Code Style

### JavaScript (index.html)
- Vanilla JS only (no frameworks)
- Use `const`/`let`, not `var`
- Descriptive variable names
- Comments for non-obvious logic

### C++ (Arduino)
- Follow Arduino conventions
- Use `#define` for constants
- Comment BLE UUID purposes
- Keep main loop clean (delegate to functions)

### Documentation
- Markdown for all docs
- Keep language accessible to non-technical readers (teachers, parents)
- Include both "simple" and "technical" explanations where helpful

---

## Project Principles

1. **Privacy First**: No data leaves the device. Ever.
2. **Simplicity**: One HTML file. One Arduino sketch. No complexity.
3. **Accessibility**: A 10-year-old should be able to use it.
4. **Transparency**: All code is visible and understandable.
5. **Offline**: Works without internet completely.
6. **Open Source**: Anyone can learn from and modify this.

---

## Contact & Contribution

This project was built for Severn Lower School students. Contributions are welcome from educators, developers, and students alike.

When contributing:
- Keep the target audience in mind
- Maintain privacy principles
- Test on actual hardware when possible
- Update documentation with any changes
