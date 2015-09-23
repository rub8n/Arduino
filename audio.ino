//https://github.com/TMRh20/TMRpcm/wiki
//https://s-media-cache-ak0.pinimg.com/736x/f9/cf/ec/f9cfec14e2ffa4820ec8ec7c5044ee73.jpg

#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
 
TMRpcm tmrpcm;   // create an object for use in this sketch

void setup(){
 
  tmrpcm.speakerPin = 9; //11 on Mega, 9 on Uno, Nano, etc
 
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
  return;   // don't do anything more if not
  }
 tmrpcm.volume(1);
 tmrpcm.play("1.wav"); //the sound file "1" will play each time the arduino powers up, or is reset
}
 
void loop(){  
	tmrpcm.play("2.wav");
	delay(2000);
	tmrpcm.play("3.wav");
	delay(2000);
	tmrpcm.play("4.wav");
	delay(2000);
}
