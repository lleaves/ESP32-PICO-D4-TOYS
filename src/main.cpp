#include <Wire.h>
#include <SPI.h>
#include <string.h>
#include <sd_card.h>
#include <TFT_eSPI.h>
// #include <Encoder.h>
#include <JPEGDecoder.h>
#include "WiFi.h";
TFT_eSPI tft = TFT_eSPI();
// Encoder myEnc(34, 35);
SdCard tf;
// JPEG decoder library
// int btn1=34;
// int btn2=35;
#include <NeoPixelBus.h>

const uint16_t PixelCount = 3; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 9;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

HslColor hslRed(red);
HslColor hslGreen(green);
HslColor hslBlue(blue);
HslColor hslWhite(white);
HslColor hslBlack(black);
// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);
int xpos=1;
int ypos=1;
int btn_click=27;
// int TFT_SW=5;
// int getuv=33;
//####################################################################################################
// Setup
//####################################################################################################
void setup() {
  Serial.begin(115200);
  strip.Begin();
  strip.SetPixelColor(0, red);
  strip.SetPixelColor(1, green);
  strip.SetPixelColor(2, blue);
  strip.Show();
  // tf.init();
  pinMode(btn_click,INPUT);
  // pinMode(btn1,INPUT);
  // pinMode(btn2,INPUT);
  // Set all chip selects high to avoid bus contention during initialisation of each peripheral
  //digitalWrite(22, HIGH); // Touch controller chip select (if used)
  digitalWrite(15, HIGH); // TFT screen chip select
  // digitalWrite(5,HIGH);
  // digitalWrite(25, HIGH); // SD card chips select, must use GPIO 5 (ESP32 SS)
  // String wssid="";
  // String wpwd="";
  // tf.readFile("/wifi.txt");
  

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_GREEN);
  // int n=WiFi.scanNetworks();
  // if(n==0){
  //   Serial.println("nowifi");
  // }else{
  //   tft.setTextSize(1);
  //   Serial.println("dingdingding");
  //   tft.print(n);
  //   tft.println(" networks found");
  //   for (int i = 0; i < n; ++i) {
  //       tft.setTextColor(random(0xFFFF));
  //       // Print SSID and RSSI for each network found
  //       tft.print(i + 1);
  //       tft.print(": ");
  //       tft.print(WiFi.SSID(i));
  //       tft.print(" (");
  //       tft.print(WiFi.RSSI(i));
  //       tft.print(")");
  //       tft.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
  //       delay(10);
  //   }
  // }
  Serial.println("initialisation done.");
  
}

RgbColor getcolor(){
  int _r=rand()%128;
  int _g=rand()%128;
  int _b=rand()%128;
  RgbColor _c=(_r,_g,_g);
  return _c;
}

// float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
// {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }
// int averageAnalogRead(int pinToRead)
// {
//   byte numberOfReadings = 12;
//   unsigned int runningValue = 0; 

//   for(int x = 0 ; x < numberOfReadings ; x++)
//     runningValue += analogRead(pinToRead);
//   runningValue /= numberOfReadings;

//   return(runningValue);  

// }
// void jpegInfo() {

//   // Print information extracted from the JPEG file
//   Serial.println("JPEG image info");
//   Serial.println("===============");
//   Serial.print("Width      :");
//   Serial.println(JpegDec.width);
//   Serial.print("Height     :");
//   Serial.println(JpegDec.height);
//   Serial.print("Components :");
//   Serial.println(JpegDec.comps);
//   Serial.print("MCU / row  :");
//   Serial.println(JpegDec.MCUSPerRow);
//   Serial.print("MCU / col  :");
//   Serial.println(JpegDec.MCUSPerCol);
//   Serial.print("Scan type  :");
//   Serial.println(JpegDec.scanType);
//   Serial.print("MCU width  :");
//   Serial.println(JpegDec.MCUWidth);
//   Serial.print("MCU height :");
//   Serial.println(JpegDec.MCUHeight);
//   Serial.println("===============");
//   Serial.println("");
// }
// void showTime(uint32_t msTime) {
//   //tft.setCursor(0, 0);
//   //tft.setTextFont(1);
//   //tft.setTextSize(2);
//   //tft.setTextColor(TFT_WHITE, TFT_BLACK);
//   //tft.print(F(" JPEG drawn in "));
//   //tft.print(msTime);
//   //tft.println(F(" ms "));
//   Serial.print(F(" JPEG drawn in "));
//   Serial.print(msTime);
//   Serial.println(F(" ms "));
// }


// //####################################################################################################
// // Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
// //####################################################################################################
// // This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// // fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
// void jpegRender(int xpos, int ypos) {

//   //jpegInfo(); // Print information from the JPEG file (could comment this line out)

//   uint16_t *pImg;
//   uint16_t mcu_w = JpegDec.MCUWidth;
//   uint16_t mcu_h = JpegDec.MCUHeight;
//   uint32_t max_x = JpegDec.width;
//   uint32_t max_y = JpegDec.height;

//   bool swapBytes = tft.getSwapBytes();
//   tft.setSwapBytes(true);
  
//   // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
//   // Typically these MCUs are 16x16 pixel blocks
//   // Determine the width and height of the right and bottom edge image blocks
//   uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
//   uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

//   // save the current image block size
//   uint32_t win_w = mcu_w;
//   uint32_t win_h = mcu_h;

//   // record the current time so we can measure how long it takes to draw an image
//   uint32_t drawTime = millis();

//   // save the coordinate of the right and bottom edges to assist image cropping
//   // to the screen size
//   max_x += xpos;
//   max_y += ypos;

//   // Fetch data from the file, decode and display
//   while (JpegDec.read()) {    // While there is more data in the file
//     pImg = JpegDec.pImage ;   // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

//     // Calculate coordinates of top left corner of current MCU
//     int mcu_x = JpegDec.MCUx * mcu_w + xpos;
//     int mcu_y = JpegDec.MCUy * mcu_h + ypos;

//     // check if the image block size needs to be changed for the right edge
//     if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
//     else win_w = min_w;

//     // check if the image block size needs to be changed for the bottom edge
//     if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
//     else win_h = min_h;

//     // copy pixels into a contiguous block
//     if (win_w != mcu_w)
//     {
//       uint16_t *cImg;
//       int p = 0;
//       cImg = pImg + win_w;
//       for (int h = 1; h < win_h; h++)
//       {
//         p += mcu_w;
//         for (int w = 0; w < win_w; w++)
//         {
//           *cImg = *(pImg + w + p);
//           cImg++;
//         }
//       }
//     }

//     // calculate how many pixels must be drawn
//     uint32_t mcu_pixels = win_w * win_h;

//     // draw image MCU block only if it will fit on the screen
//     if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
//       tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
//     else if ( (mcu_y + win_h) >= tft.height())
//       JpegDec.abort(); // Image has run off bottom of screen so abort decoding
//   }

//   tft.setSwapBytes(swapBytes);

//   showTime(millis() - drawTime); // These lines are for sketch testing only
// }

// //####################################################################################################
// // Draw a JPEG on the TFT pulled from SD Card
// //####################################################################################################
// // xpos, ypos is top left corner of plotted image
// void drawSdJpeg(const char *filename, int xpos, int ypos) {

//   // Open the named file (the Jpeg decoder library will close it)
//   File jpegFile = SD.open( filename, FILE_READ);  // or, file handle reference for SD library
 
//   if ( !jpegFile ) {
//     Serial.print("ERROR: File \""); Serial.print(filename); Serial.println ("\" not found!");
//     return;
//   }

//   Serial.println("===========================");
//   Serial.print("Drawing file: "); Serial.println(filename);
//   Serial.println("===========================");

//   // Use one of the following methods to initialise the decoder:
//   bool decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
//   //bool decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

//   if (decoded) {
//     // print information about the image to the serial port
//     jpegInfo();
//     // render the image onto the screen at given coordinates
//     jpegRender(xpos, ypos);
//   }
//   else {
//     Serial.println("Jpeg file format not supported!");
//   }
// }

//####################################################################################################
// Main loop
//####################################################################################################
long oldPosition  = -999;
int left=10;
int right=190;
int middel=100;
// String pstr="hileaves";
char pstr[]="hileaves";
void loop() {

Serial.println("Colors R, G, B, W...");

    // set the colors, 
    // if they don't match in order, you need to use NeoGrbFeature feature
    //strip.SetPixelColor(0, red);
    // strip.SetPixelColor(1, green);
    // strip.SetPixelColor(2, blue);
    // the following line demonstrates rgbw color support
    // if the NeoPixels are rgbw types the following line will compile
    // if the NeoPixels are anything else, the following line will give an error
    //strip.SetPixelColor(3, RgbwColor(colorSaturation));
    

  // Serial.println(digitalRead(btn1));
  // Serial.println(myEnc.read());
  // int uvLevel = averageAnalogRead(getuv);

  // float outputVoltage = 3.3 * uvLevel/1024;
  // float uvIntensity = mapfloat(outputVoltage, 0.99, 2.9, 0.0, 15.0);

  // Serial.print("UVAnalogOutput: ");
  // Serial.print(uvLevel);

  // Serial.print(" OutputVoltage: ");
  // Serial.print(outputVoltage);

  // Serial.print(" UV Intensity: ");
  // Serial.print(uvIntensity);
  // Serial.print(" mW/cm^2");

  // Serial.println(); 
  // Serial.println(analogRead(getuv) * 3300 / 4095);
  // long newPosition = myEnc.read();
  // if (newPosition != oldPosition) {
  //   tft.fillScreen(TFT_BGR);
  //   tft.setTextSize(2);
  //   if (newPosition > oldPosition)
  //   {
  //     if (middel <= right)
  //     {
  //       middel+=10;  
  //       tft.setTextColor(random(0xFFFF));
  //       // pstr=">>>";
  //       strcpy(pstr,">>>");
  //     }else{
  //       tft.setTextColor(TFT_RED);
  //       // pstr="!!!";
  //       strcpy(pstr,"!!!");
  //     }
  //   }

  //   if (newPosition < oldPosition)
  //   {
  //     if (middel >= left)
  //     {
  //       middel-=10;
  //       tft.setTextColor(random(0xFFFF));
  //       // pstr="<<<";
  //       strcpy(pstr,"<<<");
  //     }else{
  //       tft.setTextColor(TFT_RED);
  //       // pstr="!!!";
  //       strcpy(pstr,"!!!");
  //     }
  //   }
    // tft.setCursor(middel,15);
    // tft.println(pstr);
    
    
    // oldPosition = newPosition;

    // Serial.print(middel);
    // Serial.print("--");
    // Serial.println(newPosition);
  // }
  // Serial.print(analogRead(btn1));
  // Serial.print("---");
  // Serial.println(analogRead(btn2));
  if (digitalRead(btn_click) == LOW)
  {
    strip.SetPixelColor(rand()%3,getcolor());
    strip.Show();
    Serial.println("btn click");
    tft.fillScreen(random(0xFFFF));
    tft.setTextSize(1);
    tft.setCursor(20,15);
    tft.println("Color_random");
    // tft.printf("Color_random%s",random(0xFFFF));
  }
  delay(500);
  // tft.fillScreen(random(0xFFFF));
  // Serial.println("random_color");
  // delay(2000);
  
  // tft.setRotation(1);  // portrait
  // tft.fillScreen(random(0xFFFF));

  // The image is 300 x 300 pixels so we do some sums to position image in the middle of the screen!
  // Doing this by reading the image width and height from the jpeg info is left as an exercise!
  // int x = (tft.width()  - 300) / 2 - 1;
  // int y = (tft.height() - 300) / 2 - 1;

  // drawSdJpeg("/EagleEye.jpg", x, y);     // This draws a jpeg pulled off the SD Card
  // delay(2000);


  // tft.setRotation(1);  // portrait
  // tft.fillScreen(random(0xFFFF));
  // drawSdJpeg("/Baboon40.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card
  // delay(2000);

  // tft.setRotation(1);  // portrait
  // tft.fillScreen(random(0xFFFF));
  // drawSdJpeg("/lena20k.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card
  // delay(2000);

  // tft.setRotation(1);  // landscape
  // tft.fillScreen(random(0xFFFF));
  // drawSdJpeg("/Mouse480.jpg", 0, 0);     // This draws a jpeg pulled off the SD Card

  // delay(2000);
}


