#pragma once

#include <functional>
#include <iostream>


namespace NoteRecognizer
{
	template <typename Container>
	class Iterator
	{
	public:
		Iterator(Container::iterator it, std::function<void()> next)
			: it(it)
			, next(next)
		{

		}

		Iterator & operator++()
		{
			it++;
			next();
			return *this;
		}

		auto & operator*()
		{
			return *it;
		}

		auto & operator*() const
		{
			return *it;
		}

		bool operator!=(const Iterator<Container> & other) const
		{
			return other.it != it;
		}

	private:
		Container::iterator it;
		std::function<void()> next;
	};


	template <typename Container>
	class ProgressBar
	{
	public:
		using iterator = Iterator<Container>;

		explicit ProgressBar(Container & container, int length = 10)
			: container(container)
			, max(container.size())
			, progressBarLength(length)
		{
			auto temp = std::mem_fn(&ProgressBar<Container>::NextItem);
			next = std::bind(temp, *this);
		}

		iterator begin() const
		{
			return iterator(container.begin(), next);
		}

		iterator end() const
		{
			return iterator(container.end(), next);
		}

	private:
		Container & container;
		int counter = 0;
		int max = 0;

		int progressBarLength = 10;

		std::function<void()> next;

		void NextItem()
		{
			counter++;
			RedrawProgressBar();
		}

		void RedrawProgressBar()
		{
			for (auto i = 0; i < progressBarLength + 3; i++)
			{
				std::cout << "\b";
			}

			std::cout << '[';

			for (auto i = 0; i < progressBarLength * counter / max; i++)
			{
				std::cout << "-";
			}
			std::cout << ">";
			for (auto i = 0; i < progressBarLength - 1 - progressBarLength * counter / max; i++)
			{
				std::cout << " ";
			}
			std::cout << "]";
		}
	};
}
