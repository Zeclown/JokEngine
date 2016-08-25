#include "AudioFile.h"
namespace Jokengine
{
	AudioFile::AudioFile(int frequency, int lenght, int channels, ALuint buffer)
		:frequency(frequency),lenght(lenght),channels(channels), buffer(buffer)
	{

	}
	int AudioFile::GetChannelsCount()
	{
		return channels;
	}
	int AudioFile::GetLenght()
	{
		return lenght;
	}
	int AudioFile::GetFrequency()
	{
		return frequency;
	}

}