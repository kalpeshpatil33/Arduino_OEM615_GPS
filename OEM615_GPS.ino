// Reading and parsing GPS data from OEM615 GPS NovAtel System //
// ---------------------------- Created by ----------------------------//
// --------------------------- Kalpesh Patil ---------------------------//
// ---------------------------------------------------------------------//

// Reads position NEMA GPGGA data
// Reads velocity NEMA GPVTG data
// Prints the data on Serial Monitor
// Saves the data in SD Card as GPS.txt file

#include <SPI.h>
#include <SD.h>

#define SIZE 120
char data_GPS_cmp[SIZE];
String data_GPS;
// String val_1, val_2, val_3, val_4, val_5, val_6, val_7, val_8, val_9, val_10;
// String velocity;

String line,line1,line2;
File GPS;

// Creating extra Serial Port 4, its a hidden serial port with pin 11 and 52.
RingBuffer rx_buffer5;
RingBuffer tx_buffer5;
USARTClass Serial4(USART2, USART2_IRQn, ID_USART2, &rx_buffer5, &tx_buffer5);
void USART2_Handler(void)
{
  Serial4.IrqHandler();
}

void setup() {
  Serial.begin(115200);
  PIO_Configure(PIOB, PIO_PERIPH_A, PIO_PB20A_TXD2 | PIO_PB21A_RXD2, PIO_DEFAULT);
  Serial4.begin(115200);
  //  Serial4.write("UNLOGALL\n");
  //  Serial4.write("LOG COM1 GPGGA ONTIME 0.2\n");
  //  Serial4.write("LOG COM1 GPVTG ONTIME 0.2\n");
  //  Serial4.write("saveconfig\n");

  Serial.println("Initializing the SD Card.....");
  if (!SD.begin(4))
  {
    Serial.println("Failed....");
    return;
  }
  Serial.println("Done...");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial4.available() > 0)
  {
    data_GPS = Serial4.readStringUntil('\n');
    data_GPS.toCharArray(data_GPS_cmp, SIZE);
    if (strncmp(data_GPS_cmp, "$GPGGA", 6) == 0)
    {
      line1 = data_GPS.substring(0, 120);
      //      int commaIndex_1 = data_GPS.indexOf(',');
      //      int commaIndex_2 = data_GPS.indexOf(',', commaIndex_1 + 1);
      //      int commaIndex_3 = data_GPS.indexOf(',', commaIndex_2 + 1);
      //      int commaIndex_4 = data_GPS.indexOf(',', commaIndex_3 + 1);
      //      int commaIndex_5 = data_GPS.indexOf(',', commaIndex_4 + 1);
      //      int commaIndex_6 = data_GPS.indexOf(',', commaIndex_5 + 1);
      //      int commaIndex_7 = data_GPS.indexOf(',', commaIndex_6 + 1);
      //      int commaIndex_8 = data_GPS.indexOf(',', commaIndex_7 + 1);
      //      int commaIndex_9 = data_GPS.indexOf(',', commaIndex_8 + 1);
      //      int commaIndex_10 = data_GPS.indexOf(',', commaIndex_9 + 1);
      //
      //      val_1 = data_GPS.substring(commaIndex_1 + 1, commaIndex_2);
      //      val_2 = data_GPS.substring(commaIndex_2 + 1, commaIndex_3);
      //      val_3 = data_GPS.substring(commaIndex_3 + 1, commaIndex_4);
      //      val_4 = data_GPS.substring(commaIndex_4 + 1, commaIndex_5);
      //      val_5 = data_GPS.substring(commaIndex_5 + 1, commaIndex_6);
      //      val_6 = data_GPS.substring(commaIndex_6 + 1, commaIndex_7);
      //      val_7 = data_GPS.substring(commaIndex_7 + 1, commaIndex_8);
      //      val_8 = data_GPS.substring(commaIndex_8 + 1, commaIndex_9);
      //      val_9 = data_GPS.substring(commaIndex_9 + 1, commaIndex_10);
    }
    if (strncmp(data_GPS_cmp, "$GPVTG", 6) == 0)
    {
      line2 = data_GPS.substring(0, 120);
      //      int commaIndex_1 = data_GPS.indexOf(',');
      //      int commaIndex_2 = data_GPS.indexOf(',', commaIndex_1 + 1);
      //      int commaIndex_3 = data_GPS.indexOf(',', commaIndex_2 + 1);
      //      int commaIndex_4 = data_GPS.indexOf(',', commaIndex_3 + 1);
      //      int commaIndex_5 = data_GPS.indexOf(',', commaIndex_4 + 1);
      //      int commaIndex_6 = data_GPS.indexOf(',', commaIndex_5 + 1);
      //      int commaIndex_7 = data_GPS.indexOf(',', commaIndex_6 + 1);
      //      int commaIndex_8 = data_GPS.indexOf(',', commaIndex_7 + 1);
      //      int commaIndex_9 = data_GPS.indexOf(',', commaIndex_8 + 1);
      //
      //      String val_1 = data_GPS.substring(commaIndex_1 + 1, commaIndex_2);
      //      String val_2 = data_GPS.substring(commaIndex_2 + 1, commaIndex_3);
      //      String val_3 = data_GPS.substring(commaIndex_3 + 1, commaIndex_4);
      //      String val_4 = data_GPS.substring(commaIndex_4 + 1, commaIndex_5);
      //      String val_5 = data_GPS.substring(commaIndex_5 + 1, commaIndex_6);
      //      String val_6 = data_GPS.substring(commaIndex_6 + 1, commaIndex_7);
      //      velocity = data_GPS.substring(commaIndex_7 + 1, commaIndex_8);
      //      String val_8 = data_GPS.substring(commaIndex_8 + 1, commaIndex_9);
    }

    line = line1 + line2;
    Serial.println(line);

    File GPS = SD.open("GPS.txt", FILE_WRITE);
    if (GPS) {
      GPS.println(data_GPS);
      GPS.close();
    }
  }
  Serial.flush();
  Serial4.flush();
}

