#include <BluetoothSerial.h>
#include <ArduinoJson.h>

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;


bool m = true;
String recieved;
void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param){
  if(event == ESP_SPP_SRV_OPEN_EVT){
    Serial.println("Client Connected");
  
   
   
  }
 
  if(event == ESP_SPP_CLOSE_EVT ){
    Serial.println("Client disconnected");
  }}
void setup() {
             Serial.begin(115200);
             SerialBT.begin("main_ESP_module"); //Bluetooth device name
             Serial.println("The device started, now you can pair it with bluetooth!");
             Serial.println();
             SerialBT.register_callback(callback);
             
            
             }
             
void loop() {
            if(Serial.available())
             SerialBT.write(Serial.read());
  
            if (SerialBT.available()) {
              
                String ans=(SerialBT.readString());
                
                Serial.println(ans);
                StaticJsonBuffer<200> jsonBuffer;
                JsonObject& root = jsonBuffer.parseObject(ans);
                if(!root.success()) {
                   Serial.println("parseObject() failed");
                   }
               String ss = root["mask"];
               Serial.println(ss);
               }
 
            }
