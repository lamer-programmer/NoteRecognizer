#pragma once

#include "IWindowTransform.hpp"


namespace NoteRecognizer
{
	template <std::floating_point T>
	class RectangleWindowTransform : public IWindowTransform<T>
	{
	public:
		void Apply(std::valarray<T> & frame) override
		{

		}
	};
}
