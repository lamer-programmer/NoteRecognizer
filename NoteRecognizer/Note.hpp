#pragma once



namespace NoteRecognizer
{
	class Note
	{
	public:
		// нумерация с нуля с До малой октавы
		Note(int noteNumber) : noteNumber(noteNumber)
		{

		}

		// нумерация с малой октавы c нуля
		Note(int noteNumber, int octaveNumber)
			: noteNumber(noteNumber + octaveNumber * 12)
		{
			
		}

		auto operator<=>(const Note & otherNote) const = default;

	private:
		int noteNumber;
	};
}
