#pragma once

#include <valarray>


namespace NoteRecognizer
{
	template <typename T>
	std::valarray<T> LinSpace(T begin, T end, size_t intervalsCount)
	{
		std::valarray<T> result(intervalsCount + 1);
		for (auto i = 0; i < intervalsCount + 1; i++)
		{
			result[i] = begin + i * (end - begin) / intervalsCount;
		}

		return result;
	}
}
