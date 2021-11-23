#include <iostream>
#include <functional>
#include <filesystem>

#include "DFT.hpp"
#include "AudioLoader.hpp"
#include "AudioPreprocessor.hpp"
#include "ProgressBar.hpp"
#include "AudioFrame.hpp"
#include "WindowTransforms/RectangleWindowTransform.hpp"
#include "NoteGenerator.hpp"
#include "Note.hpp"
#include "Gnuplot.hpp"
#include "Point.hpp"

using namespace NoteRecognizer;

std::vector<Point<float>> GetPicks(
	const std::pair<std::valarray<float>, std::valarray<float>> & frequencies, 
	float boundary
)
{
	std::vector<Point<float>> picks;
	for (auto i = 0; i < frequencies.first.size(); i++)
	{
		if (frequencies.second[i] > boundary)
		{
			picks.emplace_back(frequencies.first[i], frequencies.second[i]);
		}
	}

	return picks;
}


int main()
{
	auto [timeline, sound, info] = AudioLoader::Load("Вторая октава.wav");

	AudioFrame frame(sound, 0, 4'096);
	for (auto i = 0; i < 70; i++)
	{
		frame.Shift(frame.Size());
	}

	auto frequencies = frame.GetFrequencies<RectangleWindowTransform>(info.GetSampleRate(), 120);

	auto picks = GetPicks(frequencies, 0.01f);
	NoteGenerator noteGenerator;
	auto notes = noteGenerator.GetNotes(picks);
}
