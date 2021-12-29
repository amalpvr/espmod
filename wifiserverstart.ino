#include <WiFi.h>
#include <HTTPClient.h>
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);

char ssid[] = "SM-J730GM";           // SSID of your AP
char pass[] = "amalprakash";  
void setup() {
 Serial.begin(9600);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, pass);

 server.begin();
while (WiFi.status() != WL_CONNECTED) {      //Wait for getting IP assigned by Access Point/ DHCP. 
  //Our case  esp-01 as Access point will assign IP to nodemcu esp12E.
    delay(500);
    Serial.print(".");
  }
 Serial.println();
 Serial.println("accesspoint_bare_01.ino");
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.localIP());

}
void loop() {
   HTTPClient http;
 WiFiClient client = server.available();
 if (!client) {return;}

 String request = client.readStringUntil('\r');
 Serial.println("********************************");
 Serial.println("From the station: " + request);
Serial.println(client.println( "heelooworld\r"));
 client.flush();
 Serial.print("Byte sent to the station: ");
 Serial.println(client.println(request + "ca" + "\r"));
 //Serial.println(request);

}
