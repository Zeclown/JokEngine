#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H
#include <AL\al.h>
#include <AL\alc.h>

//An audio file loaded from a file by the Resource Manager
// Example:
//
//  ResourceManager::LoadAudioFile("SwordSlash.wav", "SwordSlash01");
//  AudioFile aFile = ResourceManager::GetAudioFile("SwordSlash01");

class AudioFile
{
public:
	AudioFile() {};
	AudioFile(int frequency,int lenght,int channels, ALuint buffer);
	int GetChannelsCount();
	int GetLenght();
	int GetFrequency();
	ALuint buffer;
private:
	int frequency;
	int lenght;
	int channels;
		


};

#endif // !AUDIO_FILE_H

