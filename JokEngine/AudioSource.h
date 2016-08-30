#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H
#include "Component.h"
#include <AL\al.h>
#include <vector>
#include "AudioFile.h"
#include <map>
namespace Jokengine
{
	//An Audio Source Component
	//On Init, it register itself to the Audio service
	//It uses a queue system to play sounds that were previously registered to it
	// Example:
	//
	//	AudioSource *audioSource=gameObject.AddComponent<AudioSource>();
	//  audioSource->RegisterSound(ResourceManager::GetAudioFile("OldGods"), "OldGods");
	//  audioSource->AddToQueue("OldGods");
	class AudioSource:public ComponentCloneable<Component,AudioSource>
	{
	public:
		AudioSource(GameObject *gameObject);
		void Init();
		void Update();
		//Immediately play a sound, stopAll set to false will not interrupt the current sound playing if it is the same as the one requested
		void PlaySound(std::string soundName, GLboolean stopAll=true);
		//Set the current sound to pause
		void PauseSound();
		//Add a new sound to the back of the queue
		void AddToQueue(std::string soundName);
		//Register a new sound to the component
		void RegisterSound(AudioFile audioFile, std::string name);
		//Unregister a sound
		void UnregisterSound(std::string name);
		void SetPitch(GLfloat pitch);
		GLfloat GetPitch();
		void SetGain(GLfloat gain);
		GLfloat GetGain();
		//Should the component loop the last sound in queue if nothing else comes up?
		GLboolean looping;
		private:
			GLint currentAudioState;
			std::vector<std::pair<std::string, AudioFile>> audioQueue;
			std::map<std::string,AudioFile> audioFiles;
			ALuint source;
	};
}
#endif // !AUDIO_SOURCE_H

