#include "Audio.h"

void Audio::PlaySound(ALuint source)
{
	alSourcePlay(source);
}
ALuint Audio::RegisterSource()
{
	ALuint source;
	alGenSources((ALuint)1, &source);
	return source;
}
