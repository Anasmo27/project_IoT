/*
name : Anas mohamed 
linkedin : https://www.linkedin.com/in/anas-mohamed-401263287
date : apr 2025
board : esp32
*/

// Include the required libraries for Wi-Fi and MQTT communication
#include <WiFi.h>                        // Include the WiFi library for ESP32
#include <PubSubClient.h>               // Include the MQTT client library

// Define GPIO pins
#define led 4                           // Define GPIO4 as the LED pin
#define IR_sen 5                        // Define GPIO5 as the IR sensor pin

char arr_char[50];                      // Character array to store incoming MQTT messages

int IR_Read = 0 ;                       // Variable to store the state of IR sensor

// Wi-Fi credentials
const char ssid [] = "anas";            // SSID of the Wi-Fi network
const char pass [] = "123456789";       // Password of the Wi-Fi network

// MQTT broker information
const char *broker = "broker.emqx.io";  // MQTT broker address
const int port = 1883;                  // Port number used by the broker

// WiFi and MQTT clients
WiFiClient ESPClient;                   // Create a WiFi client object
PubSubClient client(ESPClient);         // Create an MQTT client using the WiFi client

long long int duration = 0;             // Timer variable to control publishing interval

// Declare the callback function for MQTT messages
void callback(char topic[], byte payload[], int length);

void setup() 
{ 
  Serial.begin(9600);                         // Start serial communication at 9600 baud rate
  
  pinMode(led, OUTPUT);                       // Set LED pin as output
  digitalWrite(led, LOW);                     // Turn off LED initially
  
  pinMode(IR_sen, INPUT);                     // Set IR sensor pin as input

  WiFi.begin(ssid, pass);                     // Connect to the Wi-Fi network

  // Wait until Wi-Fi is connected
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);                               // Wait for half a second
    Serial.println("Connecting to WiFi..");   // Display connecting message
    Serial.println(WiFi.status());            // Display Wi-Fi status code
    delay(500);                               // Additional wait
  }

  Serial.println("WiFi Connected!");          // Wi-Fi successfully connected
  Serial.println(WiFi.localIP());             // Print the IP address assigned to ESP32

  client.setServer(broker, port);             // Set the MQTT broker and port
  client.setCallback(callback);               // Set the function to handle incoming MQTT messages

  // Try connecting to the MQTT broker
  while (!client.connect("anas3030152"))      
  {
    Serial.println("MQTT connection failed"); // Print error if connection fails
  }

  Serial.println("MQTT connection is accepted"); // MQTT connection successful

  // Subscribe to the LED control topic
  while (!client.subscribe("/test/sector/led"))
  {
    Serial.println("subscrabtion is false");  // Print subscription failure
    delay(500);                               // Wait and retry
  }

  Serial.println("subscrabtion is true");     // Print subscription success

  duration = millis();                        // Store the current time for publishing interval
}

void loop() 
{
  IR_Read = digitalRead(IR_sen);              // Read the current state of the IR sensor

  client.loop();                              // Maintain MQTT connection and handle incoming messages

  // If IR sensor detects an object (assuming active LOW)
  if (IR_Read == 0)
  {
    // Publish every 50ms
    if (millis() - duration >= 50)
    {   
      client.publish("/test/sector/anas", "detect object");  // Publish detection message
      duration = millis();                      // Update time
    }
  }
  else 
  {
    // If object is not detected, publish message every 50ms
    if (millis() - duration >= 50)
    {   
      client.publish("/test/sector/anas", "not detect object");  // Publish no detection message
      duration = millis();                      // Update time
    }
  }
}

// Callback function triggered when an MQTT message is received
void callback(char topic[], byte payload[], int length)
{
  Serial.println("msg received on topic");    // Notify user a message was received
  Serial.println(topic);                      // Print the topic the message came from

  // Loop through payload to copy message into character array and display it
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);           // Print each character
    arr_char[i] = (char)payload[i];           // Store character in array
  }

  arr_char[length] = '\0';                    // Terminate the string with null character
  Serial.println();                           // Print a newline for clarity

  // Compare the message and control the LED accordingly
  if (strcmp(arr_char, "turn on") == 0)       
  {
    digitalWrite(led, HIGH);                  // Turn on the LED
    Serial.println("successflly of turn on led"); // Confirm action
  }
  else if (strcmp(arr_char, "turn off") == 0)
  {
    digitalWrite(led, LOW);                   // Turn off the LED
    Serial.println("successflly of turn off led"); // Confirm action
  }
  else
  {
    Serial.println("command is wrong ");      // Inform user the command was invalid

    // Blink LED 5 times as an error indication
    for (int i = 0; i <= 4; i++)
    {
      digitalWrite(led, HIGH);                // Turn LED on
      delay(500);                             // Wait half a second
      digitalWrite(led, LOW);                 // Turn LED off
      delay(500);                             // Wait half a second
    }  
  }
}
