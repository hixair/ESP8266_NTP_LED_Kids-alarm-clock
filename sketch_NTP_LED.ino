#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "SSID";
const char *password = "password";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 600000);

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(2, OUTPUT);               // Initialize GPIO2 pin as an output
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}
 

void loop() {
  digitalWrite(2,HIGH);
  timeClient.update();

  int t = timeClient.getHours() * 100 + timeClient.getMinutes();
  Serial.println(t);

  if ((t >= 800 && t <= 830) || (t >= 1530 && t <= 1630)) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(2, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(2, HIGH);
  }
  
  Serial.println(timeClient.getFormattedTime());

}
