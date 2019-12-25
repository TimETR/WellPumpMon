#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet2.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp2.h>
#include <Twitter.h>
#include <util.h>

/*
 UDPSendReceiveString:
 This sketch receives UDP message strings, prints them to the serial port
 and sends an "acknowledge" string back to the sender

 A Processing sketch is included at the end of file that can be used to send
 and received messages for testing with a computer.

 created 21 Aug 2010
 by Michael Margolis

 This code is in the public domain.
 */


#include <Ethernet2.h>

#define hallReadpin A0
#define LEDpin 7
#define LED2pin 5
#define pumpId "House"
float lastread;
String state;
String laststate;
//char pumpId = "House";
const char WEBSITE[] = "api.pushingbox.com"; //pushingbox API server
const String devid = "v228ADEDF705EAC2"; //Custom device ID

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
IPAddress ip(192, 168, 1, 111);
byte MAC[] = {0x2C, 0xF7, 0xF1, 0x08, 0x10, 0xF4};


void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  digitalWrite(LED2pin, HIGH);
 digitalWrite(LEDpin, LOW);

  // start the Ethernet
  Ethernet.begin(MAC);
  
  // // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

 
}

void loop() {
  
  delay(10);
  
  hallEffectTriggered();
}

void hallEffectTriggered() {
  float currentread = analogRead(hallReadpin);
  //Serial.println("Current reading:");
  Serial.println(currentread);
  if(currentread >= 520){
    state = "On";
    if (state != laststate) {
    digitalWrite(LEDpin, HIGH);
    //Serial.println(currentread);
    laststate = state;
    sendData(state);
    }
  }
  else if (currentread <= 490) {
    state = "Off";
    if (state != laststate) {
      digitalWrite(LEDpin, LOW);
      laststate = state;
      sendData(state);
    }
  }
}
void sendData(String state){
  //Print to Serial monitor or Terminal of your chocice at 115200 Baud
  Serial.println("On:"+ state);
  
    
  EthernetClient client;  //Instantiate WiFi object

    //Start or API service using our WiFi Client through PushingBox
    if (client.connect(WEBSITE, 80))
      { 
        digitalWrite(LED2pin, HIGH);
         client.print("GET /pushingbox?devid=" + devid
       + "&pumpId=" + (String) pumpId
       + "&state="      + (String) state);
        Serial.println("GET /pushingbox?devid=" + devid
       + "&pump=" + (String) pumpId
       + "&state="      + (bool) state);
      client.println(" HTTP/1.1"); 
      client.print("Host: ");
      client.println(WEBSITE);
      client.println("User-Agent: ESP8266/1.0");
      client.println("Connection: close");
      client.println();
      }
      else {
        digitalWrite(LED2pin, LOW);
        Ethernet.begin(MAC);
        sendData(state);
      }
}

