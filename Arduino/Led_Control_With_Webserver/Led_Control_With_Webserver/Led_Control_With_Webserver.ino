
/* Modified by Technical Team, REES52 */

#include <ESP8266WiFi.h>

const char* ssid = "Abhas-AirFiber 5G"; // Replace with your WiFi name
const char* password = "Amanagam123"; // Replace with your WiFi password

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
  client.println("<style>");
  client.println("* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: "Roboto mono", monospace;
}

body {
  height: 100vh;
  width: 100vw;
  border-radius: 50px;
  background: linear-gradient(
    135deg,
    rgb(24, 120, 255),
    rgb(78, 78, 219),
    rgb(0, 255, 213)
  );
  box-shadow: 20px 20px 60px #531abe, -20px -20px 60px #7124ff;
  display: flex;
  align-items: center;
  justify-content: center;
}

#circle_1 {
  position: absolute;
  right: 26vw;
  top: 12vh;
  height: 30vh;
  width: 30vh;
  border-radius: 50%;
  background-color: #eb4b98;
  background-size: cover;
  transition: all 2s ease-in-out;
}

#circle_1:hover {
  height: 35vh;
  width: 35vh;
}

#circle_2 {
  position: absolute;
  left: 30vw;
  top: 68vh;
  height: 20vh;
  width: 20vh;
  background-color: rgb(0, 255, 183);
  border-radius: 50%;
  background-size: cover;
  z-index: 0;
  transition: all 2s ease-in-out;
}

#circle_2:hover {
  height: 25vh;
  width: 25vh;
}

#app {
  height: 60vh;
  width: 30vw;
  background: rgba(255, 255, 255, 0.05);
  box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
  -webkit-backdrop-filter: blur(0.5vh);
  backdrop-filter: blur(00.5vh);
  border-radius: 7vh;
  border: 1px solid rgba(255, 255, 255, 0.18);
  border-radius: 7vh;
  transition: all ease-in-out 1s;
}

#header {
  height: 25%;
  width: 100%;
  background: rgba(255, 255, 255, 0.05);
  box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
  -webkit-backdrop-filter: blur(1px);
  backdrop-filter: blur(2px);
  border-radius: 7vh;
  border: 1px solid rgba(255, 255, 255, 0.18);
  color: #2222ff;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 1.8vh;
  font-weight: 100;
  z-index: 3;
}

#icon {
  background-image: url("/image.png");
  background-size: cover;
  height: 9vh;
  width: 9vh;
  border-color: transparent;
  border: none;
  border-radius: 20px;
  margin-left: 1vw;
}

#main {
  height: 75%;
  width: 100%;
  display: flex;
  align-items: center;
  justify-content: center;
}

.button {
  display: inline;
  text-align: center;
  outline: none;
  border-radius: 12vh;
  height: 8vh;
  width: 12vw;
  background: rgb(0, 255, 162);
  background-size: 100vw;
  box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
  -webkit-backdrop-filter: blur(1px);
  backdrop-filter: blur(2px);
  border: 1px solid rgba(255, 255, 255, 0.18);
  color: #2222ff;
  z-index: 2;
  right: 2vw;
  font-size: 1.7vh;
  cursor: pointer;
  margin: 3vw;
  border: none;
  transition: all 2s ease-in-out;
}

.button:hover {
  transition: all 2s ease-in-out;
  background: linear-gradient(135deg, rgb(255, 0, 132), rgb(251, 255, 0));
  background-size: contain;
}
");
  client.println("</style>");
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
        
    


