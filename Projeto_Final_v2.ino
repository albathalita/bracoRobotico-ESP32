#include <WiFi.h>
#include <Servo.h>

Servo servoBase;
Servo servoBracoDir;
Servo servoBracoEsq;
Servo servoGarra;

// GPIO the servo is attached to
static const int servoBasePin = 27;
static const int servoBracoDirPin = 14;
static const int servoBracoEsqPin = 12;
static const int servoGarraPin = 13;


const char* ssid     = "*_*";
const char* password = "Nao_Tem_Senha.";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header1;
String header2;
String header3;
String header4;

// Decode HTTP GET value
String valueString1 = String(5);
String valueString2 = String(5);
String valueString3 = String(5);
String valueString4 = String(5);
int pos1 = 0;
int pos2 = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  servoBase.attach(servoBasePin);
  servoBracoDir.attach(servoBracoDirPin);
  servoBracoEsq.attach(servoBracoEsqPin);
  servoGarra.attach(servoGarraPin);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();
        Serial.print(c);
        Serial.write(c);                    // print it out the serial monitor
        header1 += c;
        header2 += c;
        header3 += c;
        header4 += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>body { text-align: center; font-family: \"Trebuchet MS\", Arial; margin-left:auto; margin-right:auto;}");
            client.println(".slider { width: 300px; }</style>");
            client.println("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
                     
            // ----- Web Page -----
            client.println("</head><body><h1>Braco Robotico</h1>");
            
            // --- BASE ---
            client.println("<h2>Servo da Base: </h2>");
            client.println("<p>Position: <span id=\"servoPos1\"></span></p>");          
            client.println("<input type=\"range\" min=\"0\" max=\"180\" class=\"slider\" id=\"servoSlider1\" onchange=\"servo(this.value)\" value=\""+valueString1+"\"/>");
            
            client.println("<script>var slider1 = document.getElementById(\"servoSlider1\");");
            client.println("var servoP1 = document.getElementById(\"servoPos1\"); servoP1.innerHTML = slider1.value;");
            client.println("slider1.oninput = function() { slider1.value = this.value; servoP1.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(posB) { ");
            client.println("$.get(\"/?value=\" + posB + \"&\"); {Connection: close};}</script>");
           
            // --- BRACO DIREITO ---
            client.println("<h2>Servo Direito: </h2>");
            client.println("<p>Position: <span id=\"servoPos2\"></span></p>");          
            client.println("<input type=\"range\" min=\"30\" max=\"120\" class=\"slider\" id=\"servoSlider2\" onchange=\"servo(this.value)\" value=\""+valueString2+"\"/>");
            
            client.println("<script>var slider2 = document.getElementById(\"servoSlider2\");");
            client.println("var servoP2 = document.getElementById(\"servoPos2\"); servoP2.innerHTML = slider2.value;");
            client.println("slider2.oninput = function() { slider2.value = this.value; servoP2.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(posD) { ");
            client.println("$.get(\"/?value=\" + posD + \"&\"); {Connection: close};}</script>");

            // --- BRACO ESQUERDO ---
            client.println("<h2>Servo Esquerdo: </h2>");
            client.println("<p>Position: <span id=\"servoPos3\"></span></p>");          
            client.println("<input type=\"range\" min=\"70\" max=\"120\" class=\"slider\" id=\"servoSlider3\" onchange=\"servo(this.value)\" value=\""+valueString3+"\"/>");
            
            client.println("<script>var slider3 = document.getElementById(\"servoSlider3\");");
            client.println("var servoP3 = document.getElementById(\"servoPos3\"); servoP3.innerHTML = slider3.value;");
            client.println("slider3.oninput = function() { slider3.value = this.value; servoP3.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos3) { ");
            client.println("$.get(\"/?value=\" + pos3 + \"&\"); {Connection: close};}</script>");

            // --- GARRA ---
            client.println("<h2>Servo da Garra: </h2>");
            client.println("<p>Position: <span id=\"servoPos4\"></span></p>");          
            client.println("<input type=\"range\" min=\"50\" max=\"170\" class=\"slider\" id=\"servoSlider4\" onchange=\"servo(this.value)\" value=\""+valueString4+"\"/>");
            
            client.println("<script>var slider4 = document.getElementById(\"servoSlider4\");");
            client.println("var servoP4 = document.getElementById(\"servoPos4\"); servoP4.innerHTML = slider4.value;");
            client.println("slider4.oninput = function() { slider4.value = this.value; servoP4.innerHTML = this.value; }");
            client.println("$.ajaxSetup({timeout:1000}); function servo(pos4) { ");
            client.println("$.get(\"/?value=\" + pos4 + \"&\"); {Connection: close};}</script>");


            client.println("</body></html>");     
            
            //GET /?value=180& HTTP/1.1
            if(header1.indexOf("GET /?value=")>=0) {
              pos1 = header1.indexOf('=');
              pos2 = header1.indexOf('&');
              valueString1 = header1.substring(pos1+1, pos2);
              
              //Rotate the servo
              servoBase.write(valueString1.toInt());
              //Serial.println("valueString1 " + valueString1); 
            }

            if(header2.indexOf("GET /?value=")>=0) {
              pos1 = header2.indexOf('=');
              pos2 = header2.indexOf('&');
              valueString2 = header2.substring(pos1+1, pos2);
              
              //Rotate the servo
              servoBracoDir.write(valueString2.toInt());
              //Serial.println("valueString2 " + valueString2); 
            }

            if(header3.indexOf("GET /?value=")>=0) {
              pos1 = header3.indexOf('=');
              pos2 = header3.indexOf('&');
              valueString3 = header3.substring(pos1+1, pos2);
              
              //Rotate the servo
              servoBracoEsq.write(valueString3.toInt());
              //Serial.println("valueString3 " + valueString3); 
            }

            if(header4.indexOf("GET /?value=")>=0) {
              pos1 = header4.indexOf('=');
              pos2 = header4.indexOf('&');
              valueString4 = header4.substring(pos1+1, pos2);
              
              //Rotate the servo
              servoGarra.write(valueString4.toInt());
              //Serial.println("valueString4 " + valueString4); 
            }
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header1 = "";
    header2 = "";
    header3 = "";
    header4 = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
