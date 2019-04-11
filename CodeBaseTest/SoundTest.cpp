#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SoundTest {

	static WaveLoader* loader;

	TEST_MODULE_INITIALIZE(init) {
		loader = new WaveLoader();

		Logger::WriteMessage("Testing...");
	}

	TEST_MODULE_CLEANUP(cleanup) {
		delete loader;

		Logger::WriteMessage("Finalizing...");
	}

	TEST_CLASS(SoundTest) {

		TEST_METHOD(LoadWaveFile) {
			loader->loadWAVFile("C:\\Users\\Stefan\\Documents\\Visual Studio 2015\\Projects\\CodeBase\\CodeBase\\test.wav");
		}

	};

}