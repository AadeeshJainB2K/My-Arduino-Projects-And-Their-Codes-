
/* Made By Aadeesh Jain */

#include <ESP8266WiFi.h>

const char* ssid = "Atal Lab";  // Replace with your WiFi name
const char* password = "123456788";    // Replace with your WiFi password

#define BELL D3

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(BELL, OUTPUT);

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
    digitalWrite(BELL, HIGH);
    Serial.println("Bell ON");
  } else if (req.indexOf("/bell-off") != -1) {
    digitalWrite(BELL, LOW);
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
  client.println("<body style = 'height: 100vh;width: 100vw;border-radius: 50px;background: linear-gradient(135deg,rgb(24, 120, 255),rgb(78, 78, 219),rgb(0, 255, 213));box-shadow: 20px 20px 60px #531abe, -20px -20px 60px #7124ff;display: flex;align-items: center;justify-content: center;margin: 0;padding: 0;box-sizing: border-box;}'>");
  client.println("<div class='circle_1' style = 'margin: 0;padding: 0;box-sizing: border-box;position: absolute;right: 26vw;top: 12vh;height: 30vh;width: 30vh;border-radius: 50%;background-color: #eb4b98;background-size: cover;transition: all 2s ease-in-out;'></div>");
  client.println("<div class='circle_2' style = 'margin: 0;padding: 0;box-sizing: border-box;position: absolute;left: 30vw;top: 68vh;height: 20vh;width: 20vh;background-color: rgb(0, 255, 183);border-radius: 50%;background-size: cover;z-index: 0;transition: all 2s ease-in-out;'></div>");
  client.println("<div class='app'style = 'margin: 0;padding: 0;box-sizing: border-box; height: 60vh;width: 30vw;background: rgba(255, 255, 255, 0.05);box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);-webkit-backdrop-filter: blur(0.5vh);backdrop-filter: blur(00.5vh);border-radius: 7vh;border: 1px solid rgba(255, 255, 255, 0.18);border-radius: 7vh;transition: all ease-in-out 1s;' >");
  client.println("<div class='header' style = 'margin: 0;padding: 0;box-sizing: border-box;height: 25%;width: 100%;background: rgba(255, 255, 255, 0.05);box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);-webkit-backdrop-filter: blur(1px);backdrop-filter: blur(2px);border-radius: 7vh;border: 1px solid rgba(255, 255, 255, 0.18);color: #2222ff;display: flex;align-items: center;justify-content: center;font-size: 2vh;font-weight: 100;z-index: 3;'>");
  client.println("<h2>Automatic School Bell</h2>");
  client.println("<img id='icon' style = '  background-image: url('https://i.pinimg.com/originals/5a/4e/f9/5a4ef9b9d7806da10afb1e9b3efdb22d.png');background-size: cover;height: 9vh;width: 9vh;border-color: transparent;border: none;border-radius: 20px;margin-left: 1vw;'>");
  client.println("</div>");
  client.println("<div class='main' style = 'margin: 0;padding: 0;box-sizing: border-box;height: 75%;width: 100%; display: flex;align-items: center;justify-content: center;'>");
  client.println("<a href=\'/bell-on\' style = 'align-self: center;margin: 0;padding: 0;box-sizing: border-box;display: flex; align-items:center;justify-content:center;text-align: center;outline: none;text-decoration:none;border-radius: 20vh;height: 8vh;width: 12vw;'><button class='button' id = 'onButton' style = 'text-decoration:none;padding: 0;box-sizing: border-box;display: inline;text-align: center;outline: none;border-radius: 12vh;height: 8vh;width: 12vw;background: rgb(0, 255, 162);background-size: 100vw;box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);-webkit-backdrop-filter: blur(1px);backdrop-filter: blur(2px);border: 1px solid rgba(255, 255, 255, 0.18);color: #2222ff;z-index: 2;right: 2vw;font-size: 1.7vh;cursor: pointer;margin: 3vw;border: none;transition: all 2s ease-in-out;'>ON</button></a>");
  client.println("<a href=\'/bell-off\' style = 'align-self: center;margin: 0;padding: 0;box-sizing: border-box;display: flex;align-items:center;justify-content:center;text-align: center;outline: none;text-decoration:none;border-radius: 20vh;height: 8vh;width: 12vw;'><button class='button' id = 'offButton' style = 'text-decoration:none;padding: 0;box-sizing: border-box;display: inline;text-align: center;outline: none;border-radius: 20vh;height: 8vh;width: 12vw;background: rgb(0, 255, 162);background-size: 100vw;box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);-webkit-backdrop-filter: blur(1px);backdrop-filter: blur(2px);border: 1px solid rgba(255, 255, 255, 0.18);color: #2222ff;z-index: 2;right: 2vw;font-size: 1.7vh;cursor: pointer;margin: 3vw;border: none;transition: all 2s ease-in-out;'>OFF</button></a>");
  client.println("</div>");
  client.println("</div>");
  client.println("<script>");
  client.println("// Automatic Bell Project | Aadeesh Jain");
  client.println("let bellOnButton = document.querySelector('#onButton');");
  client.println("let bellOffButton = document.querySelector('#offButton');");
  client.println("bellOnButton.addEventListener('click', () => {console.log('Bell is ON');});");
  client.println("bellOffButton.addEventListener('click', () => {console.log('Bell is OFF');});");
  client.println("function bellRing() {bellOnButton.click();setTimeout(() => {bellOffButton.click();}, 3000);}");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("");
  client.println("</script>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
