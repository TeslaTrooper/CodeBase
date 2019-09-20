#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SoundTest {

	static const char* const file = "C:\\Users\\stefa\\Documents\\Visual Studio 2019\\Projects\\Asteroids\\Asteroids\\sounds\\saucerBig.wav";
	static WaveLoader* waveLoader;
	
	TEST_CLASS(WaveLoaderTest) {

		TEST_METHOD_INITIALIZE(setup) {
			waveLoader = new WaveLoader();
		}
		
		TEST_METHOD(LoadWaveFile) {
			waveLoader->loadWAVFile(file);
		}

		TEST_METHOD_CLEANUP(cleanup) {
			delete waveLoader;
		}

	};

}