#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,1); // RX, TX
const char* ssid =  "THE_END";//type your ssid
const char* password = "eng190151";//type your password
 int ledPin_1 = D2; // GPIO2 of ESP8266
int ledPin_2 = D3; // GPIO2 of ESP8266
int ledPin_3 = D4; // GPIO2 of ESP8266
int ledPin_4 = D5; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
void setup() {
  Serial.begin(115200); // For debugging
    mySerial.begin(115200); // Initialize SoftwareSerial
  delay(10);
 
  pinMode(ledPin_1, OUTPUT);
  pinMode(ledPin_2, OUTPUT);
  pinMode(ledPin_3, OUTPUT);
  pinMode(ledPin_4, OUTPUT);
    //
   
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
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/front") != -1) {
    digitalWrite(ledPin_1,HIGH);
   mySerial.println('F');
    Serial.println('F');
    delay(1000);
        
    value = LOW;
  } 
    if (request.indexOf("/lback") != -1) {
    digitalWrite(ledPin_1,HIGH);
   mySerial.println('B');
    Serial.println('B');
    delay(1000);
        
    value = LOW;
  } 
  
  if (request.indexOf("/right") != -1) {
    digitalWrite(ledPin_1,HIGH);
   mySerial.println('R');
    Serial.println('R');
    delay(1000);
        
    value = LOW;
  } 
  if (request.indexOf("/left") != -1){
    digitalWrite(ledPin_1,LOW);
   mySerial.println('L');
    Serial.println('L');
    delay(1000);
    
    value = HIGH;
  }
     if (request.indexOf("/stop") != -1)
  {
     mySerial.println('S');
    Serial.println('S');
    value = LOW;
  }
   if (request.indexOf("/fan_on") != -1)
  {
     mySerial.println('P');
    Serial.println('P');
    value = LOW;
  }
  if (request.indexOf("/fan_off") != -1)
  {
     mySerial.println('p');
    Serial.println('p');
    value = LOW;
  }
  if (request.indexOf("/lamp1_on") != -1)
  {
     mySerial.println('U');
    Serial.println('U');
    value = LOW;
  }
  if (request.indexOf("/lamp1_off") != -1)
  {
     mySerial.println('u');
    Serial.println('u');
    value = LOW;
  }
  if (request.indexOf("/lamp2_on")") != -1)
  {
     mySerial.println('A');
    Serial.println('A');
    value = LOW;
  }

  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here turn the LED on pin 2 OFF<br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}
