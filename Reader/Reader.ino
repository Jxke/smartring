
#if 1
#include <SPI.h>
#include <PN532_SPI.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_SPI pn532spi(SPI, 10);
NfcAdapter nfc = NfcAdapter(pn532spi);
#else

#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

char UNIQUE_KEY = "https://hypnotic-purpose.glitch.me/9JWUhz2MDqlkmrtJzTTacw";
int state = 0;
int piezoPin = 9;

void setup(void) {
  Serial.begin(9600);
  Serial.println("NDEF Reader");
  nfc.begin();

  
}

void loop(void) {
  Serial.println("\nScan a NFC tag\n");

  if (nfc.tagPresent())
  {
    NfcTag tag = nfc.read();
    //Serial.println(tag.getTagType());
    //Serial.print("UID: ");Serial.println(tag.getUidString());

    if (tag.hasNdefMessage()) // every tag won't have a message
    {

      NdefMessage message = tag.getNdefMessage();
      //Serial.print("\nThis NFC Tag contains an NDEF Message with ");
      //Serial.print(message.getRecordCount());
      //Serial.print(" NDEF Record");
      if (message.getRecordCount() != 1) {
        //Serial.print("s");
      }
      //Serial.println(".");

      // cycle through the records, printing some info from each
      int recordCount = message.getRecordCount();
      for (int i = 0; i < recordCount; i++)
      {
        //Serial.print("\nNDEF Record ");Serial.println(i+1);
        NdefRecord record = message.getRecord(i);
        // NdefRecord record = message[i]; // alternate syntax

        //Serial.print("  TNF: ");Serial.println(record.getTnf());
        //Serial.print("  Type: ");Serial.println(record.getType()); // will be "" for TNF_EMPTY

        // The TNF and Type should be used to determine how your application processes the payload
        // There's no generic processing for the payload, it's returned as a byte[]
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);

        // Print the Hex and Printable Characters
        //Serial.print("  Payload (HEX): ");
        //PrintHexChar(payload, payloadLength);

        // Force the data into a String (might work depending on the content)
        // Real code should use smarter processing
        String payloadAsString = "";
        for (int c = 0; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }
        //Serial.print("  Payload (as String): ");
        //Serial.println(payloadAsString);
        if (payloadAsString = UNIQUE_KEY){
          state = state + 1;
          Serial.println(state);
          if ((state % 2) == 0){
            tone(piezoPin, 800, 600);
            delay(100);
            tone(piezoPin, 900, 800);
            delay(4000);
         } else {
            tone(piezoPin, 500, 400);
            delay(200);
            tone(piezoPin, 300, 400);
            delay(200);
            tone(piezoPin, 200, 500);
            delay(200);
            tone(piezoPin, 100, 700);
            delay(4000);
         }
        }

        // id is probably blank and will return ""
        String uid = record.getId();
        if (uid != "") {
          Serial.print("  ID: ");Serial.println(uid);
        }
      }
    }
  }
  delay(300);
}
