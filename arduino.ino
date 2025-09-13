#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// --- LED Strip ---
#define LED_PIN 6
#define NUM_LEDS 8
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- OLED ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// --- EMG ---
#define EMG_PIN A0
float smoothed = 0;
float alpha = 0.05;
float baseline = 0;

void setup() {
  Serial.begin(9600);      // Send to NodeMCU
  strip.begin();
  strip.show();
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { for(;;); }
  display.clearDisplay();
  display.display();
  
  // Calibrate baseline
  long sum=0; int count=0;
  unsigned long start=millis();
  while(millis()-start<3000) { sum+=analogRead(EMG_PIN); count++; delay(5); }
  baseline = sum/(float)count;
}

void loop() {
  int raw = analogRead(EMG_PIN);
  smoothed = alpha*raw + (1-alpha)*smoothed;
  float activity = smoothed - baseline;
  if(activity<0) activity=0;

  // Map activity to LEDs
  int leds_on = map(min((int)activity,500),0,500,0,NUM_LEDS);
  uint8_t r=0,g=0,b=0;
  if(activity<150) g=200;
  else if(activity<300) { r=200; g=200; }
  else if(activity<400) { r=255; g=100; }
  else r=255;
  
  strip.clear();
  for(int i=0;i<leds_on;i++) strip.setPixelColor(i, strip.Color(r,g,b));
  strip.show();

  // OLED display
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  if(activity<50) display.println("RELAX");
  else if(activity<150) display.println("LIGHT");
  else if(activity<300) display.println("MEDIUM");
  else if(activity<400) display.println("STRONG");
  else display.println("MAX!");
  
  int barWidth = map(min((int)activity,500),0,500,0,SCREEN_WIDTH-2);
  display.fillRect(0,50,barWidth,10,SSD1306_WHITE);
  display.drawRect(0,50,SCREEN_WIDTH-2,10,SSD1306_WHITE);
  display.display();

  // --- SEND EMG TO NODEMCU ---
  Serial.print("EMG:");
  Serial.println((int)activity);

  delay(50);
}
