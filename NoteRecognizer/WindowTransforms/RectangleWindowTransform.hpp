#pragma once

#include "IWindowTransform.hpp"


namespace NoteAnalyzer
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
