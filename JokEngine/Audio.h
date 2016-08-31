#ifndef AUDIO_H
#define AUDIO_H
#include "AudioService.h"

//The default Audio Service class
//It is used to register new sources of audio
//It then allocate a buffer in OpenAL to play wav files
// It is rarely used alone and should be used from the AudioSource component 
class Audio : public AudioService
{
public:
	Audio() {};
	~Audio() {};
	//Play what is currently in the buffer of a certain source
	void PlaySound(ALuint source);
	//Register a new OpenAL source
	ALuint RegisterSource();
};

#endif // !AUDIO_H

