#include <Wire.h>
#include <RTClib.h>
//#include <Time.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include "DHT.h"

// Declare I2C objects
//
RTC_DS1307 rtc;
Adafruit_8x8matrix matrix1 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();

// Initialize DHT sensor
const int firstButtonPin = 4;
const int secondButtonPin = 3;
const int thirdButtonPin = 5;
const int speakerPin = 6;

// Define temprature settings
#define DHTPIN 14    
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Declare global variables
//DateTime now(2015, 9, 13, 15, 58, 0);
DateTime now;

int currentInvader = 1;
int firstButtonState = 0;
int secondButtonState = 0;

int sec = 0;

// Store bitmaps
static const uint8_t PROGMEM
hour_one_bmp[] =
{ B00000000,
  B00000100,
  B00000100,
  B00000101,
  B00000100,
  B00000101,
  B00000100,
  B00000000
},
hour_two_bmp[] =
{ B00000000,
  B00011100,
  B00000100,
  B00000101,
  B00011100,
  B00010001,
  B00011100,
  B00000000
},
hour_three_bmp[] =
{ B00000000,
  B00011100,
  B00000100,
  B00000101,
  B00001100,
  B00000101,
  B00011100,
  B00000000
},
hour_four_bmp[] =
{ B00000000,
  B00010100,
  B00010100,
  B00010101,
  B00011100,
  B00000101,
  B00000100,
  B00000000
},
hour_five_bmp[] =
{ B00000000,
  B00011100,
  B00010000,
  B00010001,
  B00011100,
  B00000101,
  B00011100,
  B00000000
},
hour_six_bmp[] =
{ B00000000,
  B00011100,
  B00010000,
  B00010001,
  B00011100,
  B00010101,
  B00011100,
  B00000000
},
hour_seven_bmp[] =
{ B00000000,
  B00011100,
  B00000100,
  B00000101,
  B00000100,
  B00000101,
  B00000100,
  B00000000
},
hour_eight_bmp[] =
{ B00000000,
  B00011100,
  B00010100,
  B00010101,
  B00011100,
  B00010101,
  B00011100,
  B00000000
},
hour_nine_bmp[] =
{ B00000000,
  B00011100,
  B00010100,
  B00010101,
  B00011100,
  B00000101,
  B00011100,
  B00000000
},
hour_ten_bmp[] =
{ B00000000,
  B01011100,
  B01010100,
  B01010101,
  B01010100,
  B01010101,
  B01011100,
  B00000000
},
hour_eleven_bmp[] =
{ B00000000,
  B01000100,
  B01000100,
  B01000101,
  B01000100,
  B01000101,
  B01000100,
  B00000000
},
hour_twelve_bmp[] =
{ B00000000,
  B01011100,
  B01000100,
  B01000101,
  B01011100,
  B01010001,
  B01011100,
  B00000000
},
minute_zero_bmp[] =
{ B00000000,
  B01110111,
  B01010101,
  B01010101,
  B01010101,
  B01010101,
  B01110111,
  B00000000
},
minute_one_bmp[] =
{ B00000000,
  B01110001,
  B01010001,
  B01010001,
  B01010001,
  B01010001,
  B01110001,
  B00000000
},
minute_two_bmp[] =
{ B00000000,
  B01110111,
  B01010001,
  B01010001,
  B01010111,
  B01010100,
  B01110111,
  B00000000
},
minute_three_bmp[] =
{ B00000000,
  B01110111,
  B01010001,
  B01010001,
  B01010111,
  B01010001,
  B01110111,
  B00000000
},
minute_four_bmp[] =
{ B00000000,
  B01110101,
  B01010101,
  B01010101,
  B01010111,
  B01010001,
  B01110001,
  B00000000
},
minute_five_bmp[] =
{ B00000000,
  B01110111,
  B01010100,
  B01010100,
  B01010111,
  B01010001,
  B01110111,
  B00000000
},
minute_six_bmp[] =
{ B00000000,
  B01110111,
  B01010100,
  B01010100,
  B01010111,
  B01010101,
  B01110111,
  B00000000
},
minute_seven_bmp[] =
{ B00000000,
  B01110111,
  B01010001,
  B01010001,
  B01010001,
  B01010001,
  B01110001,
  B00000000
},
minute_eight_bmp[] =
{ B00000000,
  B01110111,
  B01010101,
  B01010101,
  B01010111,
  B01010101,
  B01110111,
  B00000000
},
minute_nine_bmp[] =
{ B00000000,
  B01110111,
  B01010101,
  B01010101,
  B01010111,
  B01010001,
  B01110001,
  B00000000
},
minute_ten_bmp[] =
{ B00000000,
  B00010111,
  B00010101,
  B00010101,
  B00010101,
  B00010101,
  B00010111,
  B00000000
},
minute_eleven_bmp[] =
{ B00000000,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00000000
},
minute_twelve_bmp[] =
{ B00000000,
  B00010111,
  B00010001,
  B00010001,
  B00010111,
  B00010100,
  B00010111,
  B00000000
},
minute_thirteen_bmp[] =
{ B00000000,
  B00010111,
  B00010001,
  B00010001,
  B00010111,
  B00010001,
  B00010111,
  B00000000
},
minute_fourteen_bmp[] =
{ B00000000,
  B00010101,
  B00010101,
  B00010101,
  B00010111,
  B00010001,
  B00010001,
  B00000000
},
minute_fifteen_bmp[] =
{ B00000000,
  B00010111,
  B00010100,
  B00010100,
  B00010111,
  B00010001,
  B00010111,
  B00000000
},
minute_sixteen_bmp[] =
{ B00000000,
  B00010111,
  B00010100,
  B00010100,
  B00010111,
  B00010101,
  B00010111,
  B00000000
},
minute_seventeen_bmp[] =
{ B00000000,
  B00010111,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00000000
},
minute_eighteen_bmp[] =
{ B00000000,
  B00010111,
  B00010101,
  B00010101,
  B00010111,
  B00010101,
  B00010111,
  B00000000
},
minute_nineteen_bmp[] =
{ B00000000,
  B00010111,
  B00010101,
  B00010101,
  B00010111,
  B00010001,
  B00010111,
  B00000000
},
minute_twenty_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110101,
  B01000101,
  B01110111,
  B00000000
},
minute_twentyone_bmp[] =
{ B00000000,
  B01110001,
  B00010001,
  B00010001,
  B01110001,
  B01000001,
  B01110001,
  B00000000
},
minute_twentytwo_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110111,
  B01000100,
  B01110111,
  B00000000
},
minute_twentythree_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110111,
  B01000001,
  B01110111,
  B00000000
},
minute_twentyfour_bmp[] =
{ B00000000,
  B01110101,
  B00010101,
  B00010101,
  B01110111,
  B01000001,
  B01110001,
  B00000000
},
minute_twentyfive_bmp[] =
{ B00000000,
  B01110111,
  B00010100,
  B00010100,
  B01110111,
  B01000001,
  B01110111,
  B00000000
},
minute_twentysix_bmp[] =
{ B00000000,
  B01110111,
  B00010100,
  B00010100,
  B01110111,
  B01000101,
  B01110111,
  B00000000
},
minute_twentyseven_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110001,
  B01000001,
  B01110001,
  B00000000
},
minute_twentyeight_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110111,
  B01000101,
  B01110111,
  B00000000
},
minute_twentynine_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110111,
  B01000001,
  B01110111,
  B00000000
},
minute_thirty_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110101,
  B00010101,
  B01110111,
  B00000000
},
minute_thirtyone_bmp[] =
{ B00000000,
  B01110001,
  B00010001,
  B00010001,
  B01110001,
  B00010001,
  B01110001,
  B00000000
},
minute_thirtytwo_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110111,
  B00010100,
  B01110111,
  B00000000
},
minute_thirtythree_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_thirtyfour_bmp[] =
{ B00000000,
  B01110101,
  B00010101,
  B00010101,
  B01110111,
  B00010001,
  B01110001,
  B00000000
},
minute_thirtyfive_bmp[] =
{ B00000000,
  B01110111,
  B00010100,
  B00010100,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_thirtysix_bmp[] =
{ B00000000,
  B01110111,
  B00010100,
  B00010100,
  B01110111,
  B00010101,
  B01110111,
  B00000000
},
minute_thirtyseven_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B01110001,
  B00010001,
  B01110001,
  B00000000
},
minute_thirtyeight_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110111,
  B00010101,
  B01110111,
  B00000000
},
minute_thirtynine_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010101,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_forty_bmp[] =
{ B00000000,
  B01010111,
  B01010101,
  B01010101,
  B01110101,
  B00010101,
  B00010111,
  B00000000
},
minute_fortyone_bmp[] =
{ B00000000,
  B01010001,
  B01010001,
  B01010001,
  B01110001,
  B00010001,
  B00010001,
  B00000000
},
minute_fortytwo_bmp[] =
{ B00000000,
  B01010111,
  B01010001,
  B01010001,
  B01110111,
  B00010100,
  B00010111,
  B00000000
},
minute_fortythree_bmp[] =
{ B00000000,
  B01010111,
  B01010001,
  B01010001,
  B01110111,
  B00010001,
  B00010111,
  B00000000
},
minute_fortyfour_bmp[] =
{ B00000000,
  B01010101,
  B01010101,
  B01010101,
  B01110111,
  B00010001,
  B00010001,
  B00000000
},
minute_fortyfive_bmp[] =
{ B00000000,
  B01010111,
  B01010100,
  B01010100,
  B01110111,
  B00010001,
  B00010111,
  B00000000
},
minute_fortysix_bmp[] =
{ B00000000,
  B01010111,
  B01010100,
  B01010100,
  B01110111,
  B00010101,
  B00010111,
  B00000000
},
minute_fortyseven_bmp[] =
{ B00000000,
  B01010111,
  B01010001,
  B01010001,
  B01110001,
  B00010001,
  B00010001,
  B00000000
},
minute_fortyeight_bmp[] =
{ B00000000,
  B01010111,
  B01010101,
  B01010101,
  B01110111,
  B00010101,
  B00010111,
  B00000000
},
minute_fortynine_bmp[] =
{ B00000000,
  B01010111,
  B01010101,
  B01010101,
  B01110111,
  B00010001,
  B00010111,
  B00000000
},
minute_fifty_bmp[] =
{ B00000000,
  B01110111,
  B01000101,
  B01000101,
  B01110101,
  B00010101,
  B01110111,
  B00000000
},
minute_fiftyone_bmp[] =
{ B00000000,
  B01110001,
  B01000001,
  B01000001,
  B01110001,
  B00010001,
  B01110001,
  B00000000
},
minute_fiftytwo_bmp[] =
{ B00000000,
  B01110111,
  B01000001,
  B01000001,
  B01110111,
  B00010100,
  B01110111,
  B00000000
},
minute_fiftythree_bmp[] =
{ B00000000,
  B01110111,
  B01000001,
  B01000001,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_fiftyfour_bmp[] =
{ B00000000,
  B01110101,
  B01000101,
  B01000101,
  B01110111,
  B00010001,
  B01110001,
  B00000000
},
minute_fiftyfive_bmp[] =
{ B00000000,
  B01110111,
  B01000100,
  B01000100,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_fiftysix_bmp[] =
{ B00000000,
  B01110111,
  B01000100,
  B01000100,
  B01110111,
  B00010101,
  B01110111,
  B00000000
},
minute_fiftyseven_bmp[] =
{ B00000000,
  B01110111,
  B01010001,
  B01010001,
  B01010001,
  B01010001,
  B01110001,
  B00000000
},
minute_fiftyeight_bmp[] =
{ B00000000,
  B01110111,
  B01000101,
  B01000101,
  B01110111,
  B00010101,
  B01110111,
  B00000000
},
minute_fiftynine_bmp[] =
{ B00000000,
  B01110111,
  B01000101,
  B01000101,
  B01110111,
  B00010001,
  B01110111,
  B00000000
},
minute_sixty_bmp[] =
{ B00000000,
  B01000111,
  B01000101,
  B01000101,
  B01110101,
  B01010101,
  B01110111,
  B00000000
},
minute_sixtyone_bmp[] =
{ B00000000,
  B01000001,
  B01000001,
  B01000001,
  B01110001,
  B01010001,
  B01110111,
  B00000000
},
minute_sixtytwo_bmp[] =
{ B00000000,
  B01000111,
  B01000001,
  B01000111,
  B01110100,
  B01010100,
  B01110111,
  B00000000
},
minute_seventythree_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010111,
  B00010001,
  B00010001,
  B00010111,
  B00000000
},
minute_seventyfour_bmp[] =
{ B00000000,
  B01110101,
  B00010101,
  B00010111,
  B00010001,
  B00010001,
  B00010001,
  B00000000
},
minute_seventyfive_bmp[] =
{ B00000000,
  B01110111,
  B00010100,
  B00010111,
  B00010001,
  B00010001,
  B00010111,
  B00000000
},
minute_seventysix_bmp[] =
{ B00000000,
  B01110100,
  B00010100,
  B00010111,
  B00010101,
  B00010101,
  B00010111,
  B00000000
},
minute_seventyseven_bmp[] =
{ B00000000,
  B01110111,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00010001,
  B00000000
},
minute_seventyeight_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010111,
  B00010101,
  B00010101,
  B00010111,
  B00000000
},
minute_seventynine_bmp[] =
{ B00000000,
  B01110111,
  B00010101,
  B00010111,
  B00010001,
  B00010001,
  B00010001,
  B00000000
},
minute_eighty_bmp[] =
{ B00000000,
  B01110111,
  B01010101,
  B01110101,
  B01010101,
  B01010101,
  B01110111,
  B00000000
},
minute_eightyone_bmp[] =
{ B00000000,
  B01110001,
  B01010001,
  B01110001,
  B01010001,
  B01010001,
  B01110001,
  B00000000
},
minute_eightytwo_bmp[] =
{ B00000000,
  B01110111,
  B01010100,
  B01110111,
  B01010001,
  B01010001,
  B01110111,
  B00000000
},
minute_eightythree_bmp[] =
{ B00000000,
  B01110111,
  B01010001,
  B01110111,
  B01010001,
  B01010001,
  B01110111,
  B00000000
},
minute_eightyfour_bmp[] =
{ B00000000,
  B01110101,
  B01010101,
  B01110111,
  B01010001,
  B01010001,
  B01110001,
  B00000000
},
text_pressA_bmp[] =
{ B00000000,
  B00000011,
  B00000010,
  B00000010,
  B01110011,
  B00000010,
  B00000010,
  B00000000
},
text_pressB_bmp[] =
{ B00000000,
  B10111011,
  B10101010,
  B10101010,
  B10101011,
  B00110010,
  B00101011,
  B00000000
},
text_pressC_bmp[] =
{ B00000000,
  B10111011,
  B00100010,
  B00100010,
  B10111011,
  B00001000,
  B10111011,
  B00000000
},
text_pressD_bmp[] =
{ B00000000,
  B10000000,
  B00000000,
  B00000000,
  B10011100,
  B10000000,
  B10000000,
  B00000000
},
text_startA_bmp[] =
{ B00000000,
  B00000011,
  B00000010,
  B00000010,
  B01110011,
  B00000000,
  B00000011,
  B00000000
},
text_startB_bmp[] =
{ B00000000,
  B10111011,
  B00010010,
  B00010010,
  B10010011,
  B10010010,
  B10010010,
  B00000000
},
text_startC_bmp[] =
{ B00000000,
  B10111011,
  B10101001,
  B10101001,
  B10101001,
  B10110001,
  B10101001,
  B00000000
},
text_startD_bmp[] =
{ B00000000,
  B10000000,
  B00000000,
  B00000000,
  B00011100,
  B00000000,
  B00000000,
  B00000000
},
invader_1AA_bmp[] =
{ B00000001,
  B00000011,
  B00000111,
  B00001101,
  B00001111,
  B00000010,
  B00000101,
  B00001010
},
invader_1AB_bmp[] =
{ B10000000,
  B11000000,
  B11100000,
  B10110000,
  B11110000,
  B01000000,
  B10100000,
  B01010000
},
invader_1BA_bmp[] =
{ B00000001,
  B00000011,
  B00000111,
  B00001101,
  B00001111,
  B00000101,
  B00001000,
  B00000100
},
invader_1BB_bmp[] =
{ B10000000,
  B11000000,
  B11100000,
  B10110000,
  B11110000,
  B10100000,
  B00010000,
  B00100000
},
invader_2AA_bmp[] =
{ B00000100,
  B00000010,
  B00000111,
  B00001101,
  B00011111,
  B00010111,
  B00010100,
  B00000011
},
invader_2AB_bmp[] =
{ B00010000,
  B00100000,
  B11110000,
  B11011000,
  B11111100,
  B11110100,
  B00010100,
  B01100000
},
invader_2BA_bmp[] =
{ B00000100,
  B00010010,
  B00010111,
  B00011101,
  B00001111,
  B00000111,
  B00000100,
  B00001000
},
invader_2BB_bmp[] =
{ B00010000,
  B00100100,
  B11110100,
  B11011100,
  B11111000,
  B11110000,
  B00010000,
  B00001000
},
invader_3AA_bmp[] =
{ B00000011,
  B00011111,
  B00111111,
  B00111001,
  B00111111,
  B00000110,
  B00001101,
  B00110000,
},
invader_3AB_bmp[] =
{ B11000000,
  B11111000,
  B11111100,
  B10011100,
  B11111100,
  B01100000,
  B10110000,
  B00001100,
},
invader_3BA_bmp[] =
{ B00000011,
  B00011111,
  B00111111,
  B00111001,
  B00111111,
  B00001110,
  B00011001,
  B00001100,
},
invader_3BB_bmp[] =
{ B11000000,
  B11111000,
  B11111100,
  B10011100,
  B11111100,
  B01110000,
  B10011000,
  B00110000
},
invader_popA_bmp[] =
{ B00001000,
  B00000100,
  B00000010,
  B00111000,
  B00000000,
  B00001001,
  B00010010,
  B00000010
},
invader_popB_bmp[] =
{ B10000000,
  B10010010,
  B00010100,
  B00100000,
  B00001110,
  B00000000,
  B01010000,
  B01001000
},
text_sundayA_bmp[] =
{ B00000000,
  B01111010,
  B01000010,
  B01111010,
  B00001010,
  B00001010,
  B01111011,
  B00000000
},
text_sundayB_bmp[] =
{ B00000000,
  B01010010,
  B01011010,
  B01010110,
  B01010010,
  B01010010,
  B11010010,
  B00000000
},
text_mondayA_bmp[] =
{ B00000000,
  B01001011,
  B01111010,
  B01001010,
  B01001010,
  B01001010,
  B01001011,
  B00000000
},
text_mondayB_bmp[] =
{ B00000000,
  B11010010,
  B01011010,
  B01010110,
  B01010010,
  B01010010,
  B11010010,
  B00000000
},
text_tuesdayA_bmp[] =
{ B00000000,
  B11111010,
  B00100010,
  B00100010,
  B00100010,
  B00100010,
  B00100011,
  B00000000
},
text_tuesdayB_bmp[] =
{ B00000000,
  B01011110,
  B0101000,
  B01011110,
  B01010000,
  B01010000,
  B11011110,
  B00000000
},
text_wednesdayA_bmp[] =
{ B00000000,
  B10001011,
  B10001010,
  B10001011,
  B10101010,
  B10101010,
  B11111011,
  B00000000
},
text_wednesdayB_bmp[] =
{ B00000000,
  B11011100,
  B00010010,
  B11010010,
  B00010010,
  B00010010,
  B11011100,
  B00000000
};

void setup()
{

  Serial.begin(9600);

  // Pass in I2C addresses
  matrix4.begin(0x70);
  matrix3.begin(0x74);
  matrix2.begin(0x72);
  matrix1.begin(0x71);

  // Setup time & temp
  rtc.begin();
  dht.begin();

  Serial.println("DHTxx test!");
  
  if (! rtc.isrunning())
  {
    // This sets the RTC to the date and time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Setup display
  matrix1.setRotation(1);
  matrix2.setRotation(1);
  matrix3.setRotation(1);
  matrix4.setRotation(1);

  matrix1.setBrightness(5);
  matrix2.setBrightness(5);
  matrix3.setBrightness(5);
  matrix4.setBrightness(5);

  // Setup buttons
  pinMode(firstButtonPin, INPUT);
  pinMode(secondButtonPin, INPUT);
  pinMode(thirdButtonPin, INPUT);
  digitalWrite(secondButtonPin, HIGH); 
  digitalWrite(thirdButtonPin, HIGH);
  
  // Setup speaker
  pinMode(speakerPin, OUTPUT);


  // Splash screen
  firstButtonState = digitalRead(firstButtonPin);
  secondButtonState = digitalRead(secondButtonPin);

  while (!firstButtonState)
  {
    matrix1.clear();
    matrix2.clear();
    matrix3.clear();
    matrix4.clear();

    matrix1.drawBitmap(0, 0, text_pressA_bmp, 8, 8, LED_ON);//RED);
    matrix2.drawBitmap(0, 0, text_pressB_bmp, 8, 8, LED_ON);//RED);
    matrix3.drawBitmap(0, 0, text_pressC_bmp, 8, 8, LED_ON);//RED);
    matrix4.drawBitmap(0, 0, text_pressD_bmp, 8, 8, LED_ON);//RED);

    matrix1.writeDisplay();
    matrix2.writeDisplay();
    matrix3.writeDisplay();
    matrix4.writeDisplay();

    tone(speakerPin, 139, 600);

    delay(600);

    firstButtonState = digitalRead(firstButtonPin);

    if (firstButtonState == HIGH)
      break;

    tone(speakerPin, 123, 600);

    delay(600);

    firstButtonState = digitalRead(firstButtonPin);

    if (firstButtonState == HIGH)
      break;

    matrix1.clear();
    matrix2.clear();
    matrix3.clear();
    matrix4.clear();

    matrix1.drawBitmap(0, 0, text_startA_bmp, 8, 8, LED_ON);//RED);
    matrix2.drawBitmap(0, 0, text_startB_bmp, 8, 8, LED_ON);//RED);
    matrix3.drawBitmap(0, 0, text_startC_bmp, 8, 8, LED_ON);//RED);
    matrix4.drawBitmap(0, 0, text_startD_bmp, 8, 8, LED_ON);//RED);

    matrix1.writeDisplay();
    matrix2.writeDisplay();
    matrix3.writeDisplay();
    matrix4.writeDisplay();

    tone(speakerPin, 110, 600);

    delay(800);

    firstButtonState = digitalRead(firstButtonPin);

    if (firstButtonState == HIGH)
      break;

    tone(speakerPin, 104, 600);

    delay(800);

    firstButtonState = digitalRead(firstButtonPin);
  }

  matrix1.clear();
  matrix2.clear();
  matrix3.clear();
  matrix4.clear();

  matrix1.writeDisplay();
  matrix2.writeDisplay();
  matrix3.writeDisplay();
  matrix4.writeDisplay();

  Serial.println("leaving setup");

  delay(1000);
}


void loop()
{
  
  // Check for button press
  secondButtonState = digitalRead(secondButtonPin);

  if (secondButtonState == HIGH){
    displayTemp();
  }
  else {
    displayTime();
  }

}

void displayTime(){

  // Check for button press
  firstButtonState = digitalRead(firstButtonPin);

  if (firstButtonState == HIGH)
    shootInvader();
 
    // Update time
    now = rtc.now();
  
    // Display time
    displayHour(now.hour());
    displayDigits(now.minute(),2);
  
    // Update invader every hour
    if (now.minute() == 0 && now.second() == 0)
      currentInvader = cycleInvader(currentInvader);
  
    // Display invader
    //displayInvader(currentInvader, now.second());
    sec = sec + 1;
    displayInvader(currentInvader, sec);
  
    delay(1000);
}

void displayTemp(){

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Day: ");
  Serial.print(now.day());
  Serial.print(" %\t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(f);
  Serial.println(" *F\t");

  displayDay(now.day());
  displayDigits((int)f,3);

  delay(2000);
  
}

void displayDay (int h)
{
  
  matrix3.clear();
  matrix4.clear();

  switch (h)
  {
    case 1:
      matrix3.drawBitmap(0, 0, text_sundayA_bmp, 8, 8, LED_ON);//GREEN);
      matrix4.drawBitmap(0, 0, text_sundayB_bmp, 8, 8, LED_ON);//GREEN);      
      break;
    case 2:
      matrix3.drawBitmap(0, 0, text_mondayA_bmp, 8, 8, LED_ON);//GREEN);
      matrix4.drawBitmap(0, 0, text_mondayB_bmp, 8, 8, LED_ON);//GREEN);     
      break;
    case 3:
      matrix3.drawBitmap(0, 0, text_tuesdayA_bmp, 8, 8, LED_ON);//GREEN);
      matrix4.drawBitmap(0, 0, text_tuesdayB_bmp, 8, 8, LED_ON);//GREEN); 
      break;
    case 4:
      matrix3.drawBitmap(0, 0, text_wednesdayA_bmp, 8, 8, LED_ON);//GREEN);
      matrix4.drawBitmap(0, 0, text_wednesdayB_bmp, 8, 8, LED_ON);//GREEN); 
      break;
    case 5:
      matrix1.drawBitmap(0, 0, hour_five_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 6:
      matrix1.drawBitmap(0, 0, hour_six_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 7:
      matrix1.drawBitmap(0, 0, hour_seven_bmp, 8, 8, LED_ON);//GREEN);
      break;
  }

  matrix3.writeDisplay();
  matrix4.writeDisplay();
}


void displayHour (int h)
{
  matrix1.clear();

  switch (h)
  {
    case 1: case 13:
      matrix1.drawBitmap(0, 0, hour_one_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 2: case 14:
      matrix1.drawBitmap(0, 0, hour_two_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 3: case 15:
      matrix1.drawBitmap(0, 0, hour_three_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 4: case 16:
      matrix1.drawBitmap(0, 0, hour_four_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 5: case 17:
      matrix1.drawBitmap(0, 0, hour_five_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 6: case 18:
      matrix1.drawBitmap(0, 0, hour_six_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 7: case 19:
      matrix1.drawBitmap(0, 0, hour_seven_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 8: case 20:
      matrix1.drawBitmap(0, 0, hour_eight_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 9: case 21:
      matrix1.drawBitmap(0, 0, hour_nine_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 10: case 22:
      matrix1.drawBitmap(0, 0, hour_ten_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 11: case 23:
      matrix1.drawBitmap(0, 0, hour_eleven_bmp, 8, 8, LED_ON);//GREEN);
      break;
    case 12: case 24:
      matrix1.drawBitmap(0, 0, hour_twelve_bmp, 8, 8, LED_ON);//GREEN);
      break;
  }

  matrix1.writeDisplay();
}

void displayDigits (int d, int m)
{
  
  const uint8_t* bmp = getDigitBMP(d);  

  switch (m)
  {
    case 1:
      matrix1.clear();
      matrix1.drawBitmap(0, 0, bmp, 8, 8, LED_ON);
      break;
    case 2:
      matrix2.clear();
      matrix2.drawBitmap(0, 0, bmp, 8, 8, LED_ON);
      break;
    case 3:
      matrix3.clear();
      matrix3.drawBitmap(0, 0, bmp, 8, 8, LED_ON);
      break;
    case 4:
      matrix4.clear();
      matrix4.drawBitmap(0, 0, bmp, 8, 8, LED_ON);
      break;  
  }

}

const uint8_t* getDigitBMP(int d){

  switch (d)
  {
    case 0:
      return minute_zero_bmp;
      break;
    case 1:
      return minute_one_bmp;
      break;
    case 2:
      return minute_two_bmp;
      break;
    case 3:
      return minute_three_bmp;
      break;
    case 4:
      return minute_four_bmp;
      break;
    case 5:
      return minute_five_bmp;
      break;
    case 6:
      return minute_six_bmp;
      break;
    case 7:
      return minute_seven_bmp;
      break;
    case 8:
      return minute_eight_bmp;
      break;
    case 9:
      return minute_nine_bmp;
      break;
    case 10:
      return minute_ten_bmp;
      break;
    case 11:
      return minute_eleven_bmp;
      break;
    case 12:
      return minute_twelve_bmp;
      break;
    case 13:
      return minute_thirteen_bmp;
      break;
    case 14:
      return minute_fourteen_bmp;
      break;
    case 15:
      return minute_fifteen_bmp;
      break;
    case 16:
      return minute_sixteen_bmp;
      break;
    case 17:
      return minute_seventeen_bmp;
      break;
    case 18:
      return minute_eighteen_bmp;
      break;
    case 19:
      return minute_nineteen_bmp;
      break;
    case 20:
      return minute_twenty_bmp;
      break;
    case 21:
      return minute_twentyone_bmp;
      break;
    case 22:
      return minute_twentytwo_bmp;
      break;
    case 23:
      return minute_twentythree_bmp;
      break;
    case 24:
      return minute_twentyfour_bmp;
      break;
    case 25:
      return minute_twentyfive_bmp;
      break;
    case 26:
      return minute_twentysix_bmp;
      break;
    case 27:
      return minute_twentyseven_bmp;
      break;
    case 28:
      return minute_twentyeight_bmp;
      break;
    case 29:
      return minute_twentynine_bmp;
      break;
    case 30:
      return minute_thirty_bmp;
      break;
    case 31:
      return minute_thirtyone_bmp;
      break;
    case 32:
      return minute_thirtytwo_bmp;
      break;
    case 33:
      return minute_thirtythree_bmp;
      break;
    case 34:
      return minute_thirtyfour_bmp;
      break;
    case 35:
      return minute_thirtyfive_bmp;
      break;
    case 36:
      return minute_thirtysix_bmp;
      break;
    case 37:
      return minute_thirtyseven_bmp;
      break;
    case 38:
      return minute_thirtyeight_bmp;
      break;
    case 39:
      return minute_thirtynine_bmp;
      break;
    case 40:
      return minute_forty_bmp;
      break;
    case 41:
      return minute_fortyone_bmp;
      break;
    case 42:
      return minute_fortytwo_bmp;
      break;
    case 43:
      return minute_fortythree_bmp;
      break;
    case 44:
      return minute_fortyfour_bmp;
      break;
    case 45:
      return minute_fortyfive_bmp;
      break;
    case 46:
      return minute_fortysix_bmp;
      break;
    case 47:
      return minute_fortyseven_bmp;
      break;
    case 48:
      return minute_fortyeight_bmp;
      break;
    case 49:
      return minute_fortynine_bmp;
      break;
    case 50:
      return minute_fifty_bmp;
      break;
    case 51:
      return minute_fiftyone_bmp;
      break;
    case 52:
      return minute_fiftytwo_bmp;
      break;
    case 53:
      return minute_fiftythree_bmp;
      break;
    case 54:
      return minute_fiftyfour_bmp;
      break;
    case 55:
      return minute_fiftyfive_bmp;
      break;
    case 56:
      return minute_fiftysix_bmp;
      break;
    case 57:
      return minute_fiftyseven_bmp;
      break;
    case 58:
      return minute_fiftyeight_bmp;
      break;
    case 59:
      return minute_fiftynine_bmp;
      break;
    case 60:
      return minute_sixty_bmp;
      break;
    case 61:
      return minute_sixtyone_bmp;
      break;
    case 62:
      return minute_sixtytwo_bmp;
      break;  
    case 73:
      return minute_seventythree_bmp;
      break;  
    case 74:
      return minute_seventyfour_bmp;
      break;  
    case 75:
      return minute_seventyfive_bmp;
      break;  
    case 76:
      return minute_seventysix_bmp;
      break;  
    case 77:
      return minute_seventyseven_bmp;
      break;
    case 78:
      return minute_seventyeight_bmp;
      break;  
    case 79:
      return minute_seventynine_bmp;
      break;  
    case 80:
      return minute_eighty_bmp;
      break; 
    case 81:
      return minute_eightyone_bmp;
      break; 
    case 82:
      return minute_eightytwo_bmp;
      break; 
    case 83:
      return minute_eightythree_bmp;
      break;  
    case 84:
      return minute_eightyfour_bmp;
      break;       
    }

}

int cycleInvader (int i)
{
  if (i == 3)
    i = 1;
  else
    i += 1;

  return i;
}


void displayInvader (int i, int s)
{
  matrix3.clear();
  matrix4.clear();

  // Animate invader
  if ((s % 2) == 0)
  {
    switch (i)
    {
      case 1:
        matrix3.drawBitmap(0, 0, invader_1AA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_1AB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
      case 2:
        matrix3.drawBitmap(0, 0, invader_2AA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_2AB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
      case 3:
        matrix3.drawBitmap(0, 0, invader_3AA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_3AB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
    }
  }
  else
  {
    switch (i)
    {
      case 1:
        matrix3.drawBitmap(0, 0, invader_1BA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_1BB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
      case 2:
        matrix3.drawBitmap(0, 0, invader_2BA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_2BB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
      case 3:
        matrix3.drawBitmap(0, 0, invader_3BA_bmp, 8, 8, LED_ON);//YELLOW);
        matrix4.drawBitmap(0, 0, invader_3BB_bmp, 8, 8, LED_ON);//YELLOW);
        break;
    }
  }

  matrix3.writeDisplay();
  matrix4.writeDisplay();
}


void shootInvader ()
{
  matrix3.clear();
  matrix4.clear();

  matrix3.drawBitmap(0, 0, invader_popA_bmp, 8, 8, LED_ON);//YELLOW);
  matrix4.drawBitmap(0, 0, invader_popB_bmp, 8, 8, LED_ON);//YELLOW);

  matrix3.writeDisplay();
  matrix4.writeDisplay();

  tone(speakerPin, 698, 250);

  delay(250);

  tone(speakerPin, 523, 250);

  delay(250);

  matrix3.clear();
  matrix4.clear();

  matrix3.writeDisplay();
  matrix4.writeDisplay();

  delay(1500);

  currentInvader = cycleInvader(currentInvader);
}
