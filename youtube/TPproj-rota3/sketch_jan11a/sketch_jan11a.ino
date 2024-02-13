#include <Arduino.h>
#include <U8g2lib.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define MAX_MESSAGES 2  // Nombre maximum de messages à afficher

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High-speed I2C

EthernetUDP udp;

byte mac[] = {0xA8, 0x61, 0x0A, 0xAE, 0xA9, 0xB1};  // Replace with your own MAC address A8:61:0A:AE:A9:B1
IPAddress fixedIP(192, 168, 64, 10);

char receivedMessages[MAX_MESSAGES][UDP_TX_PACKET_MAX_SIZE];
int currentMessageIndex = 0;

void setup(void) {
  u8g2.begin();

  // Set up Ethernet with MAC address and fixed IP address
  Ethernet.begin(mac, fixedIP);
  udp.begin(12345); // UDP port to listen on

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Arduino IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop(void) {
  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
  u8g2.drawStr(0, 10, "Compteur Youtube :)!");  // write something to the internal memory

  // Check for UDP messages
  int packetSize = udp.parsePacket();
  if (packetSize) {
    udp.read(receivedMessages[currentMessageIndex], UDP_TX_PACKET_MAX_SIZE);
    currentMessageIndex = (currentMessageIndex + 1) % MAX_MESSAGES;
  }

  // Display the received UDP messages on the screen
  for (int i = 0; i < MAX_MESSAGES; i++) {
    int displayIndex = (currentMessageIndex + i) % MAX_MESSAGES;
    int yPosition = 30 + i * 10;
    u8g2.drawStr(0, yPosition, receivedMessages[displayIndex]);
  }

  u8g2.setDrawColor(1); // Couleur rose (RVB 255, 0, 255)
  u8g2.setFont(u8g2_font_ncenB08_tr);   // Choisissez une police adaptée
  u8g2.sendBuffer();

  delay(500);
}
