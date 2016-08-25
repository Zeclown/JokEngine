#ifndef AUDIO_SERVICE_H
#define AUDIO_SERVICE_H
#include "AudioFile.h"
#include "AudioSource.h"
namespace Jokengine
{
	class AudioService
	{
		public:
			virtual void PlaySound(ALuint source)=0;
			virtual ALuint RegisterSource()=0;
	};
}
#endif
