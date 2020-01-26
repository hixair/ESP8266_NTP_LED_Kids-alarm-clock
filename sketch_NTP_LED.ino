#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "SSID";
const char *password = "Password";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 600000);

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(2, OUTPUT);               // Initialize GPIO2 pin as an output
  Serial.begin(115200);
  Serial.print ( "Connecting " );
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    digitalWrite(2, HIGH);                              //Switch led OFF
    delay ( 500 );                                      //Wait
    digitalWrite(2, LOW);                               //Switch led ON (until connected)
    Serial.print ( "." );
  }

  timeClient.begin();
}
 

void loop() {
  digitalWrite(2,HIGH);     //Switching the led Off
  timeClient.update();      //Updating time from NTP

  int t = timeClient.getHours() * 100 + timeClient.getMinutes();   //present the time in another form to simplyfy operations
  Serial.println(t);

  if ((t >= 800 && t <= 830) || (t >= 1600 && t <= 1630)) {       //Add condition, if time is equal or greater than 8:00, switch leds on. NEVER put 0800 instead 800.
    digitalWrite(LED_BUILTIN, LOW);                               //Switch leds ON
    digitalWrite(2, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(2, HIGH);
  }
  delay ( 500 );
  Serial.println(timeClient.getFormattedTime());                 //print time on serial
  delay ( 500 );
}
