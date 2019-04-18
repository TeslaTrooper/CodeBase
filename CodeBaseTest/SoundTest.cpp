#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define SAMPLE_SOUND 1

namespace SoundTest {

	static SoundDriver* soundDriver;
	static const char* const file = "C:\\Users\\Stefan\\Documents\\Visual Studio 2015\\Projects\\Asteroids\\Asteroids\\sounds\\saucerBig.wav";

	TEST_MODULE_INITIALIZE(init) {
		soundDriver = new SoundDriver();

		Logger::WriteMessage("Testing...");
	}

	TEST_MODULE_CLEANUP(cleanup) {
		delete soundDriver;

		Logger::WriteMessage("Finalizing...");
	}

	TEST_CLASS(SoundTest) {

		TEST_METHOD(SoundDriver) {
			soundDriver->load(SAMPLE_SOUND, file);
			soundDriver->playBlocking(SAMPLE_SOUND);
		}

	};

}