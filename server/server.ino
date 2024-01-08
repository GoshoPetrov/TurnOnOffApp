#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LEDpin D4 
#define SwitchPin D5

const char* ssid = "chopra";
const char* password = "Hidden-Goseke-42";

ESP8266WebServer server(80);

// HTML content for the static web page
const char* htmlContent = 
"<html> \
<head><title>NodeMCU Web Server</title></head> \
<body> \
<h1>Hello from NodeMCU!</h1> \
    <form action=\"/turn\" method=\"post\"> \
        <label for=\"light\">Light:</label> \
        <input type=\"checkbox\" id=\"light\" name=\"light\"> \
        <br> \
        <input type=\"submit\" value=\"Submit\"> \
    </form> \
</body> \
</html>";

const char* htmlContentOn = "<html><head><title>NodeMCU Web Server</title></head><body><h1>The light is ON!</h1></body></html>";
const char* htmlContentOff = "<html><head><title>NodeMCU Web Server</title></head><body><h1>The light is OFF!</h1></body></html>";

void turnOn() {
    Serial.println("Turning light ON");
    digitalWrite(LEDpin, HIGH);
    digitalWrite(SwitchPin, HIGH);
}

void turnOff() {
    Serial.println("Turning light OFF");
    digitalWrite(LEDpin, LOW);
    digitalWrite(SwitchPin, LOW);
}

void handleRoot() {
  server.send(200, "text/html", "Hello World");
}

void handleTurn() {
  
  String lightValue = server.arg("light");
  
  Serial.println("POST /turn");
  Serial.println(lightValue);

  if (lightValue == "on") {
    turnOff();
  } else {
    turnOn();
  }

  server.send(200, "text/html", htmlContent);
}

void handleTurnOn() {
  turnOn();

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(200, "text/html", htmlContentOn);
}

void handleTurnOff() {
  turnOff();

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  server.send(200, "text/html", htmlContentOff);
}

void handleWorld(){
  server.send(200, "text/html", htmlContent);
}

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(LEDpin, OUTPUT);
  pinMode(SwitchPin, OUTPUT);

  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Connected!
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

   // Handle root URL request
  server.on("/", HTTP_GET, handleRoot);
  server.on("/turn", HTTP_POST, handleTurn);
  server.on("/on", HTTP_GET, handleTurnOn);
  server.on("/off", HTTP_GET, handleTurnOff);
  server.on("/hello", HTTP_GET, handleWorld);

  // Start server
  server.begin();
  Serial.print("Web server is listening...");
}

// the loop function runs over and over again forever
void loop() {
  server.handleClient();
}