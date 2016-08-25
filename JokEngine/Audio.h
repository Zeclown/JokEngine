#ifndef AUDIO_H
#define AUDIO_H
#include "AudioService.h"
namespace Jokengine
{
	class Audio : public AudioService
	{
	public:
		Audio() {};
		~Audio() {};
		void PlaySound(ALuint source);
		ALuint RegisterSource();
	};
}
#endif // !AUDIO_H

