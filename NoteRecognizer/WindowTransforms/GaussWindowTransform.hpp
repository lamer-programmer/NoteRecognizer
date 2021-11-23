#pragma once

#include "IWindowTransform.hpp"


namespace NoteRecognizer
{
	template <std::floating_point T>
	class GaussWindowTransform : public IWindowTransform<T>
	{
	public:
		void Apply(std::valarray<T> & frame) override
		{
			const auto Q = 1.0;

			for (auto i = 0; i < frame.size(); i++)
			{
				auto a = (frame.size() - 1) / 2;
				auto t = (i - a) / (Q * a);
				t = t * t;
				auto coeff = std::exp(-t / 2);

				frame[i] *= coeff;
			}
		}
	};
}
