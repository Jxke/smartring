/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME  "Jxke"
#define IO_KEY       "7ad9838529f741d6b237d7dc3ef7809e"

/******************************* WIFI **************************************/

#define WIFI_SSID       "MICA-Open"
#define WIFI_PASS       "18261826"

// comment out the following two lines if you are using fona or ethernet
#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
