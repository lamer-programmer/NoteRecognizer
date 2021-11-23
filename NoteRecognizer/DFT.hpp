#pragma once

#include <valarray>
#include <complex>
#include <concepts>
#include <numbers>
#include <vector>

namespace NoteRecognizer
{

	class DFT
	{
	private:
		template <typename T>
		[[nodiscard]]
		static void ComputeFFT(std::valarray<std::complex<T>> & arr)
		{
			auto n = arr.size();

			if (n == 1)
			{
				return;
			}

			std::valarray<std::complex<T>> a0(n / 2);
			std::valarray<std::complex<T>> a1(n / 2);
			for (auto i = 0; 2 * i < n; i++)
			{
				a0[i] = arr[2 * i];
				a1[i] = arr[2 * i + 1];
			}
			ComputeFFT(a0);
			ComputeFFT(a1);

			auto pi = std::numbers::pi_v<T>;
			auto ang = -2 * pi / n;
			std::complex<T> w(1);
			std::complex<T> wn(std::cos(ang), std::sin(ang));

			for (auto i = 0; 2 * i < n; i++)
			{
				arr[i] = a0[i] + w * a1[i];
				arr[i + n / 2] = a0[i] - w * a1[i];
				w *= wn;
			}
		}

		template <std::floating_point T>
		[[nodiscard]]
		static std::valarray<std::complex<T>> ComputeDFT(const std::valarray<T> & arr)
		{
			auto n = arr.size();
			auto pi = std::numbers::pi_v<T>;
			std::valarray<std::complex<T>> output(n);

			for (auto k = 0; k < n; k++)
			{
				std::complex<T> sum = std::complex<T>(0.0, 0.0);
				for (auto i = 0; i < n; i++)
				{
					auto real_part = std::cos(2 * pi / n * k * i);
					auto imag_part = std::sin(2 * pi / n * k * i);
					std::complex<T> w(real_part, -imag_part);
					sum += arr[i] * w;
				}
				output[k] = sum;
			}

			return output;
		}

	public:
		template <std::floating_point T>
		[[nodiscard]]
		static std::valarray<std::complex<T>> ComputeForward(const std::valarray<T> & arr)
		{
			int n = arr.size();
			if (std::log2(n) == static_cast<int>(std::log2(n)))
			{
				std::valarray<std::complex<T>> answer(n);
				for (auto i = 0; i < n; i++)
				{
					answer[i] = { arr[i], 0 };
				}

				ComputeFFT(answer);
				return answer;
			}
			
			return ComputeDFT(arr);
		}
	};
}
