#include "AudioSource.h"
#include "AudioService.h"
#include "Game.h"

AudioSource::AudioSource(GameObject* gameObject)
	:ComponentCloneable(gameObject)
{

}
void AudioSource::Update()
{

	alGetSourcei(source, AL_SOURCE_STATE, &currentAudioState);
	if (currentAudioState == AL_INITIAL && audioQueue.size() == 1)
	{
		AudioFile toPlay = audioQueue[0].second;
		alSourcei(source, AL_BUFFER, toPlay.buffer);
		Game::GetInstance().GetAudioService().PlaySound(source);
	}
	else
	{
		while (currentAudioState == AL_STOPPED && audioQueue.size() > 1) //find the next available sound or stop at the last one
		{
			audioFiles.erase(0);
			AudioFile toPlay = audioQueue[0].second;
			alSourcei(source, AL_BUFFER, toPlay.buffer);
			Game::GetInstance().GetAudioService().PlaySound(source);
			alGetSourcei(source, AL_SOURCE_STATE, &currentAudioState);
		}
		if (audioQueue.size() == 1 && currentAudioState == AL_STOPPED)//if we are at the end of the queue and the audio finished playing
		{
			if (looping)
			{
				alSourceRewind(source);
			}
			else
			{
				audioFiles.erase(0);
			}
		}
	}
}
void AudioSource::PauseSound()
{
	alSourcePause(source);
}
void AudioSource::Init()
{
	owner->Update.connect(boost::bind(&AudioSource::Update, this));
	source = Game::GetInstance().GetAudioService().RegisterSource();
	SetGain(1);
	SetPitch(1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);
}
void AudioSource::SetPitch(GLfloat pitch)
{
	alSourcef(source, AL_PITCH, pitch);
}
GLfloat AudioSource::GetPitch()
{
	GLfloat pitch;
	alGetSourcef(source,AL_PITCH,&pitch);
	return pitch;
}
void AudioSource::SetGain(GLfloat gain)
{
	alSourcef(source, AL_GAIN, gain);
}
GLfloat AudioSource::GetGain()
{
	GLfloat gain;
	alGetSourcef(source, AL_GAIN, &gain);
	return gain;
}
void AudioSource::PlaySound(std::string soundName, GLboolean stopAll)
{
	std::map<std::string,AudioFile>::iterator iter = audioFiles.find(soundName);

	if (iter != audioFiles.end())
	{
		AudioFile toPlay = iter->second;
		if (stopAll || audioQueue.size() == 0 || soundName != audioQueue[0].first) // We clear the queue and put the audio file on top
		{
			audioQueue.clear();
			audioQueue.push_back(std::make_pair(soundName,toPlay));
		}
			
	}
}
void AudioSource::AddToQueue(std::string soundName)
{
	std::map<std::string, AudioFile>::iterator iter = audioFiles.find(soundName);

	if (iter != audioFiles.end())
	{
		AudioFile toPlay = iter->second;
		audioQueue.push_back(std::make_pair(soundName, toPlay));
	}
}
void AudioSource::RegisterSound(AudioFile audioFile, std::string name)
{
	audioFiles[name] = audioFile;
}
void AudioSource::UnregisterSound(std::string name)
{
	audioFiles.erase(name);
}
