#include "Init.h"


Sound2D::Sound2D(ISoundEngine* Sengine, const string &sFile, bool isLoopingSound)
{
	this->isLooping = isLoopingSound;
	this->sFile = sFile;
	this->mEngine = Sengine;
	this->source = nullptr;
	this->volume = 1.0f;

	source = mEngine->addSoundSourceFromFile(sFile.c_str());
	
	if (!source)
	{
		cout << "sound source initialization error" << endl;
	}

}

void Sound2D::Play()
{
	if (source)
	{
		mEngine->play2D(source);
	}
}

void Sound2D::setVolume(float newVol)
{
	this->volume = newVol;

	if (source)
	{
		source->setDefaultVolume(newVol);
	}
}