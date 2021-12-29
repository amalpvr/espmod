#include <WiFi.h>


const char* ssid = "SM-J730GM";
const char* password = "amalprakash";

IPAddress server(192,168,43,70); 
const int port = 80;

WiFiClient client;

void setup() {
  Serial.begin(9600);
  connectWifi();
  connectServer();  
}

void loop() {
  sendData(connectValue());
}
  

//-------------------------------------------------------------------------------functions----------------------------------------------------------------------- 
void connectWifi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");    
  } 
  Serial.print("wifi connected to: ");
  Serial.println(ssid);
}

void connectServer(){
  int conn =client.connect(server,port); 
  if(conn ==1)
  {
    Serial.print("connected to the server");
  }
}

int connectValue()
{
  return client.connect(server,port);
}


void sendData(int conn){
  if (conn == 1) {    
  String path = String("Open_Door \r");
  Serial.println(); 
  Serial.println("Sending Data");   
   //Request
  client.println("POST "+path);
  
  while (client.available() == 0);

   //Print Server Response
   while (client.available()) {
      String c = client.readStringUntil('/');
      Serial.println("Received Data = "+c);
   }
} else {
   client.stop();
   Serial.println("Connection Failed");
}
}
