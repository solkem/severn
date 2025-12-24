# Severn LS Edge AI

**Teaching the Next Generation of AI — One Sensor at a Time**

> An open-source, privacy-first platform that empowers 4th and 5th grade students to build their own AI systems using real hardware — no cloud required, no data leaves the classroom.

---

## The Big Idea: AI That Stays With You

Imagine teaching a 10-year-old that they can create their own "smart" device — one that recognizes gestures, detects movement, or knows when someone is nearby — and **all of it happens right on a tiny computer they can hold in their hand**.

That's what Severn LS Edge AI does.

We're building an open, accessible alternative to tools like Google's Teachable Machine, but with a critical difference: **your data never leaves your device**. Students learn that artificial intelligence doesn't require sending information to faraway servers. It can happen right here, right now, on the "edge" — on the device itself.

---

## Why This Matters for Young Learners

### The Privacy Problem with Traditional AI Tools

Most AI educational tools work like this:
1. Collect data (photos, sounds, movement) from students
2. Send it to cloud servers owned by large companies
3. Process it somewhere far away
4. Send results back

**Students never see where their data goes. They don't understand who has access to it. They become comfortable with surveillance as the default.**

### Our Approach: Edge AI

Edge AI flips this model:
1. Collect data from sensors on the Arduino
2. Process it **right on the device** (or locally in the browser)
3. Train and run AI models **without internet**
4. **Your data never leaves your control**

**This teaches students that privacy and intelligence can coexist.**

---

## What Students Learn

### Technical Concepts (Made Accessible)

| Concept | How We Teach It |
|---------|-----------------|
| **Sensors** | "Your Arduino can feel movement and know when things are close — just like you can!" |
| **Data** | "Every time you move, your Arduino measures it with numbers. Let's see them change!" |
| **Bluetooth** | "Your Arduino talks to your computer using invisible radio waves — no wires needed!" |
| **Machine Learning** | "We're going to teach your Arduino to recognize patterns, just like you learned to recognize letters." |
| **Edge AI** | "Your Arduino is so smart, it doesn't need to ask the internet for help. It figures things out by itself!" |
| **Privacy** | "Unlike some apps that send your information to computers far away, your Arduino keeps everything right here with you." |

### Real-World Skills

- **Computational Thinking**: Breaking problems into sensor inputs and outputs
- **Data Literacy**: Understanding what sensors measure and why
- **Critical Thinking About Technology**: Asking "where does my data go?"
- **Hardware Fundamentals**: Connecting physical devices to software
- **Scientific Method**: Collecting data, making predictions, testing hypotheses

---

## How It Works

### The Simple Version (For Students)

```
┌─────────────────────┐      Bluetooth      ┌─────────────────────┐
│                     │    ~~~~~~~~~~~~>    │                     │
│  Arduino BLE Sense  │                     │   Your Computer's   │
│                     │    <~~~~~~~~~~~~    │      Web Browser    │
│  - Motion sensor    │                     │                     │
│  - Proximity sensor │                     │   Shows live data!  │
│                     │                     │   Trains AI models! │
└─────────────────────┘                     └─────────────────────┘
         ^                                           ^
         │                                           │
    Feels motion                                Runs locally
    Detects closeness                           No internet needed
    Runs AI models                              Your data stays here
```

### The Technical Version (For Teachers & Developers)

**Hardware Layer:**
- Arduino Nano 33 BLE Sense Rev2
- BMI270 IMU (accelerometer/gyroscope) + BMM150 (magnetometer)
- APDS9960 (proximity/gesture/color sensor)
- Onboard BLE radio for wireless communication

**Firmware Layer** (`arduino/severn_ble_sense/severn_ble_sense.ino`):
- Reads accelerometer at 50Hz (every 20ms)
- Reads proximity sensor at 10Hz (every 100ms)
- Exposes data via two BLE GATT services:
  - **Accelerometer Service** (UUID: `00001101-...`): 3 floats (X/Y/Z) = 12 bytes
  - **Proximity Service** (UUID: `00001102-...`): 1 byte (0-255)
- Generates unique device names from MAC address (critical for classrooms)

**Web Layer** (`index.html`):
- Pure HTML/CSS/JavaScript (no frameworks, no build step)
- Uses Web Bluetooth API for device discovery and connection
- Real-time sensor visualization
- Works offline — just open the file in Chrome/Edge/Opera

**ML Layer** (Integration with Edge Impulse):
- Export sensor data for model training
- Deploy trained TinyML models back to Arduino
- Run inference entirely on-device

---

## Quick Start

### For Teachers: Setting Up the Classroom

**What You Need:**
- Arduino Nano 33 BLE Sense Rev2 boards (one per student or pair)
- USB cables for initial programming
- Computers with Chrome, Edge, or Opera browsers
- Labels/stickers for device identification

**One-Time Setup (per device):**

1. **Install Arduino IDE** (version 2.x recommended)

2. **Install the board package:**
   - Tools → Board → Boards Manager
   - Search "Arduino Mbed OS Nano Boards"
   - Install

3. **Install required libraries** (Sketch → Include Library → Manage Libraries):
   - `ArduinoBLE`
   - `Arduino_BMI270_BMM150` (for Rev2 boards)
   - `Arduino_APDS9960`

4. **Upload the firmware:**
   - Open `arduino/severn_ble_sense/severn_ble_sense.ino`
   - Select board: Tools → Board → Arduino Nano 33 BLE
   - Select port: Tools → Port → [your Arduino]
   - Click Upload

5. **Label your device:**
   - Open Serial Monitor (9600 baud)
   - Note the unique device name (e.g., "Arduino-A1B2")
   - Write this on a physical label and attach to the Arduino

6. **Repeat for all devices**

### For Students: Connecting Your Arduino

1. Make sure your Arduino is powered (via USB or battery)
2. Open the web page in Chrome, Edge, or Opera
3. Click **"Connect to Arduino"**
4. Find YOUR device in the list (look for the name on your label!)
5. Click Pair
6. Watch your sensor data appear in real-time!

---

## Privacy: A Core Principle, Not an Afterthought

### What Makes This Different

| Traditional Cloud AI | Severn LS Edge AI |
|---------------------|-------------------|
| Data uploaded to company servers | Data stays on your device |
| Requires internet connection | Works completely offline |
| Company stores and may use your data | No external parties involved |
| Privacy policy you never read | Privacy by design |
| You trust the company | You trust yourself |

### What This Teaches Students

**Critical Questions We Encourage:**
- "When I use an app, where does my information go?"
- "Who can see what I'm doing?"
- "Can I make something smart without sharing my data?"
- "Why do some companies want my data?"

**The Answer Edge AI Provides:**
- Intelligence doesn't require surveillance
- You can build powerful AI systems that respect privacy
- The future of technology can be different

---

## Why We Built Our Own (Instead of Using Teachable Machine)

Google's Teachable Machine is fantastic for quick demos. But for **real education**, we need more:

| Feature | Teachable Machine | Severn LS Edge AI |
|---------|-------------------|-------------------|
| Runs on hardware students own | No | Yes |
| Works offline | Partially | Fully |
| Data stays local | Requires internet | Always local |
| Students see the code | No | Yes, open source |
| Teaches real IoT skills | No | Yes |
| Works with physical sensors | Camera/mic only | Any sensor |
| Classroom-ready (multi-device) | Tricky | Built-in |
| Free and open source | No | Yes |

**We want students to be creators, not just consumers.**

---

## Architecture Deep Dive

### BLE Communication Protocol

```
Arduino Nano 33 BLE Sense
├── BLE Peripheral Role
│   ├── Device Name: "Arduino-XXXX" (unique per device)
│   │
│   ├── Accelerometer Service (0x1101)
│   │   └── Accelerometer Characteristic (0x2101)
│   │       ├── Properties: READ, NOTIFY
│   │       └── Value: [float32 X][float32 Y][float32 Z] (12 bytes, little-endian)
│   │
│   └── Proximity Service (0x1102)
│       └── Proximity Characteristic (0x2102)
│           ├── Properties: READ, NOTIFY
│           └── Value: [uint8] (1 byte, 0=far, 255=near)

Web Browser (Central Role)
├── Web Bluetooth API
│   ├── Scans for devices with name prefix "Arduino"
│   ├── Connects to GATT server
│   ├── Subscribes to characteristic notifications
│   └── Parses binary data and updates UI
```

### Sampling Rates

| Sensor | Rate | Interval | Rationale |
|--------|------|----------|-----------|
| Accelerometer | 50 Hz | 20 ms | Sufficient for gesture recognition |
| Proximity | 10 Hz | 100 ms | Appropriate for presence detection |

### Binary Data Encoding

**Accelerometer packet (12 bytes):**
```
Byte 0-3:   Float32 X (little-endian)
Byte 4-7:   Float32 Y (little-endian)
Byte 8-11:  Float32 Z (little-endian)
```

**Proximity packet (1 byte):**
```
Byte 0:     Uint8 (0-255)
```

---

## Roadmap

### Current Features (v1.0)
- [x] Arduino firmware with accelerometer and proximity
- [x] Unique device naming for classroom management
- [x] Web Bluetooth connection and real-time display
- [x] Cross-browser support (Chrome, Edge, Opera)
- [x] Mobile-responsive design

### Planned Features
- [ ] Data recording and export (CSV, JSON)
- [ ] Edge Impulse integration for ML model training
- [ ] On-device inference deployment
- [ ] Activity recognition demo (walking, running, jumping)
- [ ] Gesture recognition demo (wave, circle, shake)
- [ ] Classroom dashboard for teachers
- [ ] Lesson plans and curriculum materials
- [ ] Multi-language support

---

## Technical Requirements

### Hardware
- Arduino Nano 33 BLE Sense **Rev2** (recommended)
- USB-C cable for programming
- Optional: Battery pack for wireless operation

### Software
- Arduino IDE 2.x
- Modern web browser with Web Bluetooth support:
  - Chrome 56+
  - Edge 79+
  - Opera 43+
  - **Note:** Firefox and Safari do not support Web Bluetooth

### Libraries
- ArduinoBLE (by Arduino)
- Arduino_BMI270_BMM150 (by Arduino) — for Rev2
- Arduino_APDS9960 (by Arduino)

---

## Troubleshooting

### Arduino Issues

**Libraries won't install:**
- Install the board package first (Arduino Mbed OS Nano Boards)
- Use Arduino IDE 2.x for best compatibility

**Upload fails:**
- Double-press the reset button to enter bootloader mode
- Try a different USB cable (some are power-only)
- Check that the correct board and port are selected

**Sensors not initializing:**
- Check Serial Monitor at 9600 baud for error messages
- Ensure you're using the correct libraries for Rev2 (BMI270, not LSM9DS1)

### Web Browser Issues

**"Web Bluetooth not supported":**
- Use Chrome, Edge, or Opera
- On Chrome, check `chrome://flags` for Bluetooth settings

**Can't find device:**
- Make sure Arduino is powered on (LED visible)
- Check Serial Monitor to confirm "BLE advertising started"
- Move closer to the device (within 10 meters)

**Connection drops frequently:**
- Check for BLE interference (other devices, USB 3.0 hubs)
- Ensure Arduino has stable power

---

## Project Structure

```
severn/
├── README.md                    # This file
├── CLAUDE.md                    # Context for AI assistants
├── index.html                   # Web interface (single file, no build)
└── arduino/
    ├── README.md               # Firmware setup guide
    └── severn_ble_sense/
        └── severn_ble_sense.ino # Arduino firmware
```

---

## Contributing

We welcome contributions from educators, developers, and students!

### Ways to Help
- **Educators:** Test in your classroom and share feedback
- **Developers:** Improve the web interface or firmware
- **Students:** Report bugs and suggest features
- **Everyone:** Help translate materials for other languages

### Development Setup
1. Clone the repository
2. Upload firmware to your Arduino
3. Open `index.html` in a supported browser
4. That's it! No build process, no dependencies

---

## Philosophy

### Why Edge AI for Kids?

We believe the next generation deserves to understand AI, not just consume it. They should know:

1. **AI is not magic.** It's math, sensors, and code — things they can learn.
2. **AI doesn't require big companies.** You can build intelligent systems yourself.
3. **Privacy matters.** Smart technology can respect your data.
4. **Hardware is accessible.** A $30 Arduino can do amazing things.
5. **Open source empowers.** When you can see the code, you can change the code.

### The Teachable Machine Gap

Google's Teachable Machine democratized ML demos. But it's still:
- A black box (students can't see how it works)
- Cloud-dependent (data leaves your device)
- Limited to camera/microphone (no hardware sensors)
- Not deployable (you can't put it on your own device)

Severn LS Edge AI fills this gap by giving students **real hardware, real code, real privacy, and real understanding**.

---

## License

This project is open source. See LICENSE file for details.

---

## Acknowledgments

Built for the students of Severn Lower School, inspired by educators everywhere who believe kids deserve to understand the technology shaping their world.

---

<p align="center">
  <strong>Teaching Edge AI. Protecting Privacy. Empowering the Next Generation.</strong>
</p>
