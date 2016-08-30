#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H
#include "AudioFile.h"
#include "AudioSource.h"
namespace Jokengine
{
	//The Audio Service pure virtual class
	//It is used by AudioSources to register new sources and play sounds
	class AudioService
	{
		public:
			virtual void PlaySound(ALuint source)=0;
			virtual ALuint RegisterSource()=0;
	};
}
#endif
