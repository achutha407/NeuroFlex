# ⚡ NeuroFlex  

NeuroFlex is an **IoT + Embedded Systems project** built for hackathons and real-world applications.  
It integrates **Arduino**, **NodeMCU**, **EMG sensors**, **OLED displays**, and **RGB lighting** to create an **interactive neuro-muscular signal visualization system**.  

The project combines **hardware control, live signal monitoring, and cloud integration** with a **website frontend** for data display and interaction.  

---

## 🚀 Features
- 🎛 **Arduino Integration** – Collects EMG (Electromyography) signals and processes data.  
- 🌐 **NodeMCU (ESP8266)** – Handles IoT communication and cloud sync.  
- 🖥 **Website** – Displays real-time data, results, and visualizations.  
- 💡 **RGB + OLED Display** – Provides live feedback on muscle activity.  
- ☁️ **Cloud Storage** – Sends processed data to the cloud for logging & analysis.  

---

## 📂 Project Structure
│── arduino/ # Arduino sketches (EMG, OLED, RGB control)
│── nodemcu/ # NodeMCU (ESP8266) code for IoT + cloud sync
│── website/ # Frontend website code (HTML, CSS, JS)

---

## 🔧 Hardware Requirements
- Arduino UNO / Nano  
- NodeMCU ESP8266  
- EMG Sensor Module  
- WS2812B RGB LED strip  
- 0.96" OLED Display (I2C/SPI)  
- Jumper wires, breadboard, micro-USB cable  

---

## 🛠 Software Requirements
- Arduino IDE (with required libraries: `Adafruit_NeoPixel`, `Wire`, `Adafruit_GFX`, `Adafruit_SSD1306`)  
- NodeMCU drivers + ESP8266 board support  
- Web browser (for frontend site)  
- Cloud platform (Firebase / Thingspeak / MQTT – depending on setup)  
