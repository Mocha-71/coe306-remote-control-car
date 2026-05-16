#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// Create servo objects
Servo Servo_A;
Servo Servo_B;

// Define the GPIO pins
const int servoAPin = 1;
const int servoBPin = 2;

// Define the ESP32 access point Wi-Fi name and password
const char* ap_ssid = "ESP32";
const char* ap_password = "12345678";

// Create a web server object on port 80
WebServer server(80);

// This function sends the HTML page to the mobile browser
void handleRoot() {
  server.send(200, "text/html",
    "<!DOCTYPE html>"
    "<html>"
    "<head>"

    // Makes the page responsive on mobile devices
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"
    // CSS styling for the web page
    "<style>"
    "html { font-family: Helvetica; text-align: center; }"
    "body { margin: 0; padding: 20px; }"
    "h1 { font-size: 26px; margin-bottom: 20px; }"

    //frame that contains the control buttons
    ".card {"
      "max-width: 520px;"
      "width: 100%;"
      "box-sizing: border-box;"
      "margin: 25px auto;"
      "padding: 20px;"
      "border-radius: 18px;"
      "box-shadow: 0 4px 15px rgba(0,0,0,0.15);"
      "background-color: white;"
    "}"
    //Grid layout
    ".controlGrid {"
      "display: grid;"
      "grid-template-columns: repeat(3, 1fr);"
      "gap: 12px;"
      "align-items: center;"
    "}"

    //General button design
    ".button {"
      "background-color: #7F2020;"
      "border: none;"
      "color: white;"
      "padding: 12px 10px;"
      "text-decoration: none;"
      "font-size: 20px;"
      "cursor: pointer;"
      "width: 100%;"
      "border-radius: 12px;"
      "box-sizing: border-box;"
    "}"
    //stop button
    ".stop { background-color: #333333; }"
    ".empty { visibility: hidden; }"
    "</style>"

    "<script>"
    //send HTTP request
    "function sendCommand(cmd){ fetch('/' + cmd); }"
    //Only move while button is pressed
    "function startMove(cmd){ sendCommand(cmd); }"
    //Stop movement when the button is released
    "function stopMove(){ sendCommand('stop'); }"
    "</script>"
    "</head>"

    "<body>"
    "<h1>COE306 Project: Remote Car Control</h1>"
    //frame for styling
    "<div class='card'>"
    "<div class='controlGrid'>"
    // -------- Buttons --------:

      "<div></div>"
      "<button class='button' "
        "onmousedown=\"startMove('forward')\" "
        "onmouseup=\"stopMove()\" "
        "ontouchstart=\"startMove('forward')\" "
        "ontouchend=\"stopMove()\">"
        "FORWARD"
      "</button>"
      "<div></div>"
      "<button class='button' "
        "onmousedown=\"startMove('left')\" "
        "onmouseup=\"stopMove()\" "
        "ontouchstart=\"startMove('left')\" "
        "ontouchend=\"stopMove()\">"
        "LEFT"
      "</button>"

      "<button class='button stop' onclick=\"stopMove()\">STOP</button>"

      "<button class='button' "
        "onmousedown=\"startMove('right')\" "
        "onmouseup=\"stopMove()\" "
        "ontouchstart=\"startMove('right')\" "
        "ontouchend=\"stopMove()\">"
        "RIGHT"
      "</button>"

      "<div></div>"
      "<button class='button' "
        "onmousedown=\"startMove('reverse')\" "
        "onmouseup=\"stopMove()\" "
        "ontouchstart=\"startMove('reverse')\" "
        "ontouchend=\"stopMove()\">"
        "REVERSE"
      "</button>"
      "<div></div>"

    "</div>"
    "</div>"

    "</body>"
    "</html>"
  );
}


// Handler for the forward button
void handleForward() {
  Serial.println("Motor forward");
  // Set servo directions for forward movement
  Servo_A.write(110);
  Servo_B.write(80);
  // Send response to browser
  server.send(200);
}
// Handler for the reverse button
void handleReverse() {
  Serial.println("Motor reverse");
  // Set servo directions for reverse movement
  Servo_A.write(80);
  Servo_B.write(110);
  // Send response to browser
  server.send(200);
}
// Handler for the stop button
void handleStop() {
  Serial.println("Motor stop");
  // 90 degrees is the stop value for continuous rotation servos
  Servo_A.write(90);
  Servo_B.write(90);
  // Send response to browser
  server.send(200);
}
// Handler for the right button
void handleRight(){
  // Set servo directions for right turning
  Servo_B.write(110);
  Servo_A.write(110);
  // Send response to browser
  server.send(200);
}
// Handler for the left button
void handleLeft(){
  // Set servo directions for left turning
  Servo_A.write(70);
  Servo_B.write(80);
  // Send response to browser
  server.send(200);
}


void setup() {
  // Attach the servo objects to their GPIO pins
  Servo_A.attach(servoAPin);
  Servo_B.attach(servoBPin);

  // Define the routes and connect each route to its handler function
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/reverse", handleReverse);
  server.on("/stop", handleStop);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
 // Start serial communication
  Serial.begin(115200); //baud rate
  delay(3000);

  Serial.println("Program started");

  // Start the ESP32 as an access point
 Serial.println("Starting ESP32 Access Point...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_ssid, ap_password);

  Serial.print("ESP32 AP IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  // Start the web server
  server.begin();
  Serial.println("Web server started");
}
  

void loop() {
    // Continuously check for incoming HTTP requests from the mobile browser
  server.handleClient();

}
 
