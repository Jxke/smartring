#include <SPI.h>
#include <PN532_SPI.h>                    
//#include <Wire.h>
//#include <PN532_I2C.h>
#include <PN532.h>   // The following files are included in the libraries Installed
//#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
PN532 nfc(pn532spi);

//NfcAdapter nfc = NfcAdapter(pn532_i2c);  // Indicates the Shield you are using

void setup() {
    Serial.begin(9600);
    Serial.println("NFC Tag Writer"); // Serial Monitor Message
    nfc.begin();
}

void loop() {
    Serial.println("\nPlace an NFC Tag that you want to Record these Messages on!"); // Command for the Serial Monitor
    if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addTextRecord("My First NFC Tag Write"); // Text Message you want to Record
        message.addUriRecord("http://facebook.com"); // Website you want to Record
        message.addTextRecord("Way to Go, It Worked!");  // Ednding Message for you to Record
        boolean success = nfc.write(message);
        if (success) {
            Serial.println("Good Job, now read it with your phone!"); // if it works you will see this message 
        } else {
            Serial.println("Write failed"); // If the the rewrite failed you will see this message
        }
    }
    delay(10000);
}
