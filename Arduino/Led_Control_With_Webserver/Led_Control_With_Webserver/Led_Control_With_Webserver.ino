
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

 if (req.indexOf("/bell-on") != -1) {
    digitalWrite(YELLOW_LED, HIGH);
    Serial.println("Bell ON");
  } else if (req.indexOf("/bell-off") != -1) {
    digitalWrite(YELLOW_LED, LOW);
    Serial.println("Bell OFF");
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("<!DOCTYPE html>");
  client.println("<html lang='en'>");
  client.println("<head>");
  client.println("<meta charset='UTF-8'>");
  client.println("<meta name='viewport' content='width=device-width, initial-scale=1.0'>");
  client.println("");
  client.println("<title>Automatic School Bell</title>");
  client.println("</head>");
  client.println("<body>");
  client.println("<div id='circle_1'></div>");
  client.println("<div id='circle_2'></div>");
  client.println("<div id='app'>");
  client.println("<div id='header'>");
  client.println("<h2>Automatic School Bell</h2>");
  client.println("<img id='icon'>");
  client.println("</div>");
  client.println("<div id='main'>");
  client.println("<a href=\'/bell-on\'><button class='button'>ON</button></a>");
  client.println("<a href=\'/bell-off\'><button class='button'>OFF</button></a>");
  client.println("</div>");
  client.println("</div>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
        
    


