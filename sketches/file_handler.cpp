#include "DFMiniMp3.h"
#include <SoftwareSerial.h>

class Mp3Notify; 

SoftwareSerial secondarySerial(10, 11); // RX, TX
typedef DFMiniMp3<SoftwareSerial, Mp3Notify> DfMp3;
DfMp3 dfmp3(secondarySerial);

void setupDFM()
{
  
    dfmp3.begin();
    
    dfmp3.setVolume(5);
  
}

void waitMilliseconds(uint16_t msWait)
{
    uint32_t start = millis();
  
    while ((millis() - start) < msWait)
    {
        dfmp3.play(1);
        delay(1);
        
    }
}

void play(const int num)
{
    dfmp3.playMp3FolderTrack(num);
}

void stop()
{
    dfmp3.stop();
}

void play_needed_track(int file, int track)
{
    playFolderTrack16(file, track);
}

