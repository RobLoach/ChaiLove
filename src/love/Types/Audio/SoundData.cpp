#include "SoundData.h"
#include <string>
#include <iostream>

#include "../../../ChaiLove.h"
#include "AudioState.h"
#include "physfs.h"

namespace love {
namespace Types {
namespace Audio {

SoundData::SoundData(const std::string& filename) {
	ChaiLove* app = ChaiLove::getInstance();
	PHYSFS_file* file = app->filesystem.openFile(filename);
	if (file == NULL) {
		return;
	}

	/*
	TODO: Load bytes.
	int result = PHYSFS_readBytes(file, &sndta.head, sizeof(uint8_t) * WAV_HEADER_SIZE);
	if (result < 0) {
		std::cout << "[ChaiLove] Failed to load SoundData " << filename << app->filesystem.getLastError() << std::endl;
		return;
	}*/
}

SoundData::~SoundData() {
	unload();
}

float SoundData::getVolume() {
	return m_volume;
}

SoundData& SoundData::setVolume(float volume) {
	if (volume > 1.0f) {
		volume = 1.0f;
	} else if (volume < 0.0f) {
		volume = 0.0f;
	}
	m_volume = volume;
	return *this;
}

void SoundData::unload() {
	if (isLoaded()) {
		//PHYSFS_close(sndta.fp);

		audio_mixer_destroy(m_sound);
		m_sound = NULL;
	}
}

bool SoundData::play() {
	if (isLoaded()) {
		//PHYSFS_seek(sndta.fp, WAV_HEADER_SIZE);
		state = Playing;
		return true;
	}
	return false;
}

bool SoundData::resume() {
	if (isLoaded()) {
		state = Playing;
		return true;
	}
	return false;
}

bool SoundData::pause() {
	if (isLoaded()) {
		state = Paused;
		return true;
	}
	return false;
}

bool SoundData::stop() {
	state = Stopped;
	if (isLoaded()) {
		//PHYSFS_seek(sndta.fp, WAV_HEADER_SIZE);
	}
	return true;
}

bool SoundData::isLoaded() {
	return m_sound != NULL;
}

bool SoundData::isPlaying() {
	return state == Playing;
}

bool SoundData::isLooping() {
	return loop;
}

SoundData& SoundData::setLooping(bool looping) {
	loop = looping;
	return *this;
}

}  // namespace Audio
}  // namespace Types
}  // namespace love
