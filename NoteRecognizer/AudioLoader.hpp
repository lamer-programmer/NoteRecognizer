#pragma once

#include <valarray>

#include "3rdparty/AudioFile.cpp"
#include "LinSpace.hpp"
#include "AudioInfo.hpp"


namespace NoteRecognizer
{
	class AudioLoader
	{
	public:
		// Загружается только первый канал, т.к. непонятно, что делать с другими
		// { timeLine, sound }
		static std::tuple<std::valarray<float>, std::valarray<float>, AudioInfo> Load(
			const std::string filename
		)
		{
			AudioFile<float> audioFile;

			auto loadedOk = audioFile.load(filename);
			assert(loadedOk);

			AudioInfo info(
				filename,
				audioFile.getLengthInSeconds(),
				audioFile.getSampleRate(),
				audioFile.getNumChannels(),
				audioFile.getBitDepth()
			);
			const auto samplesCount = audioFile.samples[0].size();

			auto timeLine = LinSpace<float>(0.0f, info.GetDuration(), samplesCount - 1);
			std::valarray<float> sound(
				audioFile.samples[0].data(),
				audioFile.samples[0].size()
			);

			return { timeLine, sound, info };
		}
	};
}
