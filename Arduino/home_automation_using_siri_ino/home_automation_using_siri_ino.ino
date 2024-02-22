#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "YourSSID";  // Replace with your WiFi SSID
const char *password = "YourPassword";  // Replace with your WiFi password

const int redPin = D1;    // Pin for the Red LED
const int greenPin = D2;  // Pin for the Green LED
const int yellowPin = D3; // Pin for the Yellow LED

ESP8266WebServer server(80);

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Define web server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/red", HTTP_GET, []() { handleLED(redPin); });
  server.on("/green", HTTP_GET, []() { handleLED(greenPin); });
  server.on("/yellow", HTTP_GET, []() { handleLED(yellowPin); });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><body>";
  html += "<h1>NodeMCU LED Control</h1>";
  html += "<p>Red LED: <a href='/red'><button style='background-color: red; color: white;'>Toggle</button></a></p>";
  html += "<p>Green LED: <a href='/green'><button style='background-color: green; color: white;'>Toggle</button></a></p>";
  html += "<p>Yellow LED: <a href='/yellow'><button style='background-color: yellow;'>Toggle</button></a></p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleLED(int ledPin) {
  digitalWrite(ledPin, !digitalRead(ledPin));
  server.sendHeader("Location", "/");
  server.send(303);
}
