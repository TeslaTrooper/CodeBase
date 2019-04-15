#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define SAMPLE_SOUND 1

namespace SoundTest {

	static WaveLoader* loader;
	static SoundMaster* soundMaster;
	static const char* const file = "C:\\Users\\Stefan\\Documents\\Visual Studio 2015\\Projects\\Asteroids\\Asteroids\\sounds\\thrust.wav";

	TEST_MODULE_INITIALIZE(init) {
		loader = new WaveLoader();
		soundMaster = new SoundMaster();

		Logger::WriteMessage("Testing...");
	}

	TEST_MODULE_CLEANUP(cleanup) {
		delete loader;
		delete soundMaster;

		Logger::WriteMessage("Finalizing...");
	}

	TEST_CLASS(SoundTest) {

		TEST_METHOD(LoadWaveFile) {
			loader->loadWAVFile(file);
		}

		TEST_METHOD(SoundMaster) {
			soundMaster->load(SAMPLE_SOUND, file);
			soundMaster->playBlocking(SAMPLE_SOUND);
		}

	};

}