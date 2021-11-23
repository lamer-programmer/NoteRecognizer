#pragma once

#include <valarray>


namespace NoteRecognizer
{
	class AudioPreprocessor
	{
	public:
		template <std::floating_point T, typename Transform1, typename... Transforms>
		static void Preprocess(std::valarray<T> & sound)
		{
			Transform1::Apply(sound);
			Preprocess<T, Transforms...>(sound);
		}

	private:
		template <std::floating_point T>
		static void Preprocess(std::valarray<T> & sound)
		{
		
		}
	};
}

