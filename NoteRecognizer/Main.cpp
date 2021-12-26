#include <iostream>
#include <functional>
#include <filesystem>
#include <fstream>

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

std::string GetPath(int argc, char ** argv)
{
	std::string path;
	for (auto i = 1; i < argc; i++)
	{
		if (i != 1)
		{
			path += " ";
		}

		path += argv[i];
	}

	return path;
}

void WriteNotesToFile(std::ofstream & notesFile, const std::set<Note> & notes)
{
	for (auto note : notes)
	{
		notesFile << note.GetNumber() << " ";
	}

	notesFile << std::endl;
}

int main(char *argv)
{
	//auto path = GetPath(argc, argv);
	std::cout << std::endl << argv << std::endl; // << argc << std::endl;
	auto [timeline, sound, info] = AudioLoader::Load(argv);

	NoteGenerator noteGenerator;
	const float pickBoundary = 0.01f;

	std::ofstream notesFile("Notes.txt");

	auto i = 0;

	for (AudioFrame frame(sound, 0, 4'096 * 2); frame.Size() != 0; frame.Shift(frame.Size()))
	{
		auto frequencies
			= frame.GetFrequencies<RectangleWindowTransform>(info.GetSampleRate(), 250);

		auto picks = GetPicks(frequencies, pickBoundary);
		auto notes = noteGenerator.GetNotes(picks);
		WriteNotesToFile(notesFile, notes);
		i++;
	}
}
