
/* Modified by Technical Team, REES52 */

#include <ESP8266WiFi.h>

const char* ssid = "FTTH-E7A2"; // Replace with your WiFi name
const char* password = "20101980"; // Replace with your WiFi password

#define RED_LED D1
#define GREEN_LED D2
#define YELLOW_LED D3

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started at...");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  Serial.println("new client");

  while (!client.available()) {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if (req.indexOf("/red-on") != -1) {
    digitalWrite(RED_LED, HIGH);
    Serial.println("Red LED ON");
  } else if (req.indexOf("/red-off") != -1) {
    digitalWrite(RED_LED, LOW);
    Serial.println("Red LED OFF");
  } else if (req.indexOf("/green-on") != -1) {
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("Green LED ON");
  } else if (req.indexOf("/green-off") != -1) {
    digitalWrite(GREEN_LED, LOW);
    Serial.println("Green LED OFF");
  } else if (req.indexOf("/yellow-on") != -1) {
    digitalWrite(YELLOW_LED, HIGH);
    Serial.println("Yellow LED ON");
  } else if (req.indexOf("/yellow-off") != -1) {
    digitalWrite(YELLOW_LED, LOW);
    Serial.println("Yellow LED OFF");
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("");

  client.println("<!DOCTYPE HTML>");
  client.println("<HTML>");
  client.println("<H1> LED CONTROL </H1>");
  client.println("<br />");

  client.println("<a href=\"/red-on\"><button style='background-color: red; color: white; font-size: 20px;'> Red LED ON </button></a>");
  client.println("<a href=\"/red-off\"><button style='background-color: red; color: white; font-size: 20px;'> Red LED OFF </button></a>");
  client.println("<br />");

  client.println("<a href=\"/green-on\"><button style='background-color: green; color: white; font-size: 20px;'> Green LED ON </button></a>");
  client.println("<a href=\"/green-off\"><button style='background-color: green; color: white; font-size: 20px;'> Green LED OFF </button></a>");
  client.println("<br />");

  client.println("<a href=\"/yellow-on\"><button style='background-color: yellow; font-size: 20px;'> Yellow LED ON </button></a>");
  client.println("<a href=\"/yellow-off\"><button style='background-color: yellow; font-size: 20px;'> Yellow LED OFF </button></a>");

  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
