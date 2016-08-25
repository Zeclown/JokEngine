#ifndef AUDIO_FILE_H
#define AUDIO_FILE_H
#include <AL\al.h>
#include <AL\alc.h>
namespace Jokengine
{
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
}
#endif // !AUDIO_FILE_H

