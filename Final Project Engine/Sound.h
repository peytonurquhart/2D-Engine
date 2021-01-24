#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <time.h>

using namespace irrklang;
using std::string;

/*
		Sound

	- It is important to guard code all sound functions in case the user turns sound off so the code wont have to change


*/

class Sound2D
{
public:
	Sound2D(ISoundEngine* Sengine, const string &sFile, bool isLoopingSound);

	void Play();

	void setVolume(float newVol);

	void removeSource() { if (source) { mEngine->removeSoundSource(source); } }

private:
	ISoundEngine * mEngine;

	ISoundSource *source;

	ISound *sound;

	string sFile;

	float volume;

	bool isLooping;

};


