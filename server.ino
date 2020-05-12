//    Master Board creates Access Point
//******************************SERVER***************************
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const int trigPin = D6;
const int echoPin = D7;
long duration;
int distance;

const char *ssid = "123456879";
const char *pass = "123456879";

unsigned int localPort = 2000; // local port to listen for UDP packets

IPAddress ServerIP(192, 168, 4, 1);
IPAddress ClientIP(192, 168, 4, 2);

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

char packetBuffer[9];   //Where we get the UDP data
//=============================Setup==========================================
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  Serial.println();
  WiFi.softAP(ssid, pass);    //Create Access point
  //Start UDP
  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}
//=========================MAIN LOOP=============================================
void loop()
{
  int cb = udp.parsePacket();
  /*if (!cb)
    {
    //If serial data is recived send it to UDP
    if (Serial.available() > 0)
    {
      udp.beginPacket(ClientIP, 2000);
      //Send UDP requests are to port 2000

      char a[1];
      a[0] = char(Serial.read()); //Serial Byte Read
      udp.write(a, 1); //Send one byte to ESP8266
      udp.endPacket();
    }
    }*/
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  //  /Serial.print("Distance: ");
  ///  Serial.println(distance);
  if (digitalRead(D5) == 1) {
    udp.beginPacket(ClientIP, 2000);
    char a[1];
    a[0] = int('5'); //Serial Byte Read
    udp.write(a, 1); //Send one byte to ESP8266
    udp.endPacket();
  }
  /*if (distance <= 200) {
    udp.beginPacket(ClientIP, 2000);
    char a[1];
    a[0] = char('h'); //Serial Byte Read
    //    /a[2] = char('i');
    udp.write(a, 1); //Send one byte to ESP8266
    udp.endPacket();
    }
    else if (distance >= 100) {
    udp.beginPacket(ClientIP, 2000);
    char b[1];
    b[0] = char('m'); //Serial Byte Read
    //    /b[-1] = char('o');
    udp.write(b, 1); //Send one byte to ESP8266
    udp.endPacket();
    }
    else if (distance >= 200) {
    udp.beginPacket(ClientIP, 2000);
    char b[1];
    b[0] = char('l'); //Serial Byte Read
    //    /b[-1] = char('o');
    udp.write(b, 1); //Send one byte to ESP8266
    udp.endPacket();
    }*/
}
//======================================================================
