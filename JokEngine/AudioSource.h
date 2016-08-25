#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H
#include "Component.h"
#include <AL\al.h>
#include <vector>
#include "AudioFile.h"
#include <map>
namespace Jokengine
{

	class AudioSource:public ComponentCloneable<Component,AudioSource>
	{
	public:
		AudioSource(GameObject *gameObject);
		void Init();
		void Update();
		void PlaySound(std::string soundName, GLboolean stopAll=true);
		void PauseSound();
		void AddToQueue(std::string soundName);
		void RegisterSound(AudioFile audioFile, std::string name);
		void UnregisterSound(std::string name);
		void SetPitch(GLfloat pitch);
		GLfloat GetPitch();
		void SetGain(GLfloat gain);
		GLfloat GetGain();
		GLboolean looping;
		private:
			GLint currentAudioState;
			std::vector<std::pair<std::string, AudioFile>> audioQueue;
			std::map<std::string,AudioFile> audioFiles;
			ALuint source;
	};
}
#endif // !AUDIO_SOURCE_H

