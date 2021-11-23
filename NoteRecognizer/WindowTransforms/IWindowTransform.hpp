#pragma once

#include <valarray>


namespace NoteRecognizer
{
	template <std::floating_point T>
	class IWindowTransform
	{
	public:
		virtual void Apply(std::valarray<T> & frame) = 0;
	};
}
