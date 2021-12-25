#pragma once

#include <concepts>
#include <valarray>
#include <vector>


namespace NoteRecognizer
{
	class AudioFrame
	{
	public:
		using FrequenciesType = std::pair<std::valarray<float>, std::valarray<float>>;

		AudioFrame(const std::valarray<float> & arr, int begin, int end)
			: arr(arr), begin(begin), end(end)
		{
			if (end < begin + 1)
			{
				throw std::invalid_argument("End is equal or less then begin");
			}

			if (end > arr.size())
			{
				end = arr.size();
			}
		}

		AudioFrame(const AudioFrame &) = default;

		AudioFrame(AudioFrame &&) noexcept = default;

		AudioFrame & operator=(const AudioFrame & other)
		{
			if (this == &other)
			{
				return *this;
			}

			begin = other.begin;
			end = other.end;
			return *this;
		}

		AudioFrame & operator=(AudioFrame && other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			begin = other.begin;
			end = other.end;
			return *this;
		}

		template <template <typename> typename WindowTransform>
		[[nodiscard]]
		FrequenciesType GetFrequencies(int sampleRate, int frequencyBoundary) const
		{
			std::valarray<float> interval = GetData();
			WindowTransform<float>().Apply(interval);
			return CalculateDFT(interval, sampleRate, frequencyBoundary);
		}

		[[nodiscard]]
		AudioFrame Shift(int count) const
		{
			if (begin + count > arr.size())
			{
				return AudioFrame(arr, arr.size(), arr.size());
			}

			if (end + count > arr.size())
			{
				return AudioFrame(arr, begin + count, arr.size());
			}

			if (end + count < 0)
			{
				return AudioFrame(arr, 0, 0);
			}

			if (begin + count < 0)
			{
				return AudioFrame(arr, 0, end + count);
			}

			return AudioFrame(arr, begin + count, end + count);
		}

		void Shift(int count)
		{
			if (begin + count > arr.size() && end + count > arr.size())
			{
				begin = end = arr.size();
				return;
			}

			if (end + count > arr.size())
			{
				end = arr.size();
				begin += count;
				return;
			}

			if (end + count < 0)
			{
				begin = end = 0;
				return;
			}

			if (begin + count < 0)
			{
				begin = 0;
				end += count;
				return;
			}

			end += count;
			begin += count;
		}

		[[nodiscard]]
		int Size() const
		{
			return end - begin;
		}

		[[nodiscard]]
		std::valarray<float> GetData() const
		{
			return arr[std::slice(begin, end - begin, 1)];
		}

	private:
		const std::valarray<float> & arr;

		// [begin, end)
		int begin;
		int end;

		[[nodiscard]]
		static std::pair<std::valarray<float>, std::valarray<float>> CalculateDFT(
			const std::valarray<float> & sound,
			const size_t sampleRate,
			const size_t frequencyRange)
		{
			auto spectrum = DFT::ComputeForward(sound);
			std::valarray<float> absolute(spectrum.size() / 2);
			for (auto i = 0; i < spectrum.size() / 2; i++)
			{
				absolute[i] = std::abs(spectrum[i]);
			}

			auto temp = static_cast<float>(absolute.size()) / sampleRate;
			std::valarray<float> time = LinSpace<float>(0.0f, absolute.size(), absolute.size());

			std::slice slice(0, frequencyRange, 1);
			std::valarray<float> timePiece = time[slice];
			std::valarray<float> absolutePiece = absolute[slice];

			return { timePiece / temp, absolutePiece / sound.size() };
		}
	};
}
