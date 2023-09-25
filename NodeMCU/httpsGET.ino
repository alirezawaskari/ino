// Includes *******************
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
// ****************************

// Definition of WiFi Properties
const char* ssid = "yourSSID";
const char* password = "yourPASSWD";

// Definition of Host Properties
String host = "yourHOST"; // use "http://example.domain" format (for ssl use https instead of http)
String port = "yourPORT"; // 80 for http and 443 for https

HTTPClient https;

// Perparing up

void setup() {
  Serial.begin(115200);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to Wifi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    
    // Starting HTTPS Request
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();
    
    String url = host + ":";
    url = url + port;
    url = url + "/";
    
    if (https.begin(*client, url)) {  // HTTPS
      Serial.print("[HTTPS] GET...\n");
       // start connection and send HTTPS header
      int ResponseCode = https.GET();

      if ((ResponseCode>0) && (ResponseCode==200)) {
        Serial.println("Connected to server");
        String payload = https.getString();
        Serial.println("Message from server: ");
        Serial.println(payload);
      } else if ((ResponseCode == HTTP_CODE_OK) || ResponseCode == (HTTP_CODE_MOVED_PERMANENTLY)) {
        Serial.print("[HTTPS] GET... Response code: ");
        Serial.println(ResponseCode);
        String payload = https.getString();
        Serial.println(payload);
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(ResponseCode).c_str());
      }
    }
    
    // Free resources
    https.end();

  } else {
    Serial.println("WiFi Disconnected");
  }
}



void loop() {

}
