#pragma once

#include <string>


namespace NoteRecognizer
{
	class AudioInfo
	{
	public:
		AudioInfo(std::string filename,
			float duration,
			int sampleRate,
			int numChannels,
			int bitDepth)
			: filename(filename)
			, duration(duration)
			, sampleRate(sampleRate)
			, numChannels(numChannels)
			, bitDepth(bitDepth)
		{

		}

		[[nodiscard]]
		std::string GetFilename() const
		{
			return filename;
		}

		[[nodiscard]]
		float GetDuration() const
		{
			return duration;
		}

		[[nodiscard]]
		int GetSampleRate() const
		{
			return sampleRate;
		}

		[[nodiscard]]
		int GetNumChannels() const
		{
			return numChannels;
		}

		[[nodiscard]]
		int GetBitDepth() const
		{
			return bitDepth;
		}

	private:
		std::string filename;
		float duration;
		int sampleRate;
		int numChannels;
		int bitDepth;
	};
}
