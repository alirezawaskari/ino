// Includes *****************************
#include <ESP8266WiFi.h>
// #include <SocketIoClient.h>
#include <SocketIOclient.h>
#include <WebSocketsClient.h>
// **************************************

const char* ssid = "yourSSID"; 
const char* passwd = "yourPASSWD"; 
 
const char* host = "HOSTNAME"; // "192.168.5.127" or "https://example.domain" or even "http://example.domain"
const int port = 443; // 80 for http and 443 for https

SocketIOclient socketIO;

//void messageEvenetHandler(const char * payload, size_t length) {
void Event(socketIOmessageType_t type, uint8_t * payload, size_t length){
  switch (type) {
    case sIOtype_DISCONNECT:
    Serial.printf("[IOc] Disconnected!\n");
    break;
    case sIOtype_CONNECT:
    Serial.printf("[IOc] Connected to url: %s\n", payload);
    default:
    Serial.printf("got message: %s\n", payload);
  }
}

void setup() {
  Serial.begin(115200);
  // Initialize WiFi
  WiFi.begin(ssid, passwd);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  socketIO.onEvent(Event);
  socketIO.begin(host, port);
}



void loop() {
  socketIO.loop();
}
