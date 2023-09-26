// Includes *****************************
#include <ESP8266WiFi.h>
// #include <SocketIoClient.h>
#include <SocketIOclient.h>
#include <WebSocketsClient.h>
// **************************************

const char* ssid = "Galaxy Note9";
const char* passwd = "Awa2a0w0a1";
 
const char* host = "https://iot-master.dev";
const int port = 443;

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