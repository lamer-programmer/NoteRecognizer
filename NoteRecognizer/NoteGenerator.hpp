#pragma once

#include <vector>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <set>

#include "Note.hpp"
#include "Point.hpp"

namespace NoteRecognizer
{
	class NoteGenerator
	{
	public:
		std::set<Note> GetNotes(const std::vector<Point<float>> & picks) const
		{
			std::set<Note> notes;
			for (const auto & pick : picks)
			{
				auto noteNumber = 12 * std::round(std::log2(pick.X / firstNoteFrequency));
				notes.emplace(noteNumber);
			}

			return notes;
		}

	private:
		const float firstNoteFrequency = 130.82f;
		const int notesNumber = 48;
	};
}
