#include <SoftwareSerial.h>
#include <DFMiniMp3.h>
#include <Arduino.h>

class Mp3Notify
{
public:
  static void PrintlnSourceAction(DfMp3_PlaySources source, const char* action)
  {
    if (source & DfMp3_PlaySources_Sd)
    {
        
    }
    if (source & DfMp3_PlaySources_Usb)
    {
       
    }
    if (source & DfMp3_PlaySources_Flash)
    {
       
    }
  
  }
  static void OnError(uint16_t errorCode)
  {
    // see DfMp3_Error for code meaning
 
  }
  static void OnPlayFinished(DfMp3_PlaySources source, uint16_t track)
  {
 
  }
  static void OnPlaySourceOnline(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "online");
  }
  static void OnPlaySourceInserted(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "inserted");
  }
  static void OnPlaySourceRemoved(DfMp3_PlaySources source)
  {
    PrintlnSourceAction(source, "removed");
  }
};

SoftwareSerial secondarySerial(10, 11); // RX, TX
DFMiniMp3<SoftwareSerial, Mp3Notify> mp3(secondarySerial);

void setupDFM(uint8_t volume)
{
    mp3.begin();
    mp3.setVolume(volume);
}

void play(const int num)
{
    mp3.playMp3FolderTrack(num);
}

void stop_play()
{
    mp3.stop();
}

void set_volume(uint8_t volume)
{
  mp3.setVolume(volume);
}

void play_needed_track(int file, int track)
{
    mp3.playFolderTrack16(file, track);
}
