#pragma once

#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>


namespace NoteRecognizer
{
	class Gnuplot
	{
	public:
		// Getter - функция, которая по индексу позвращает пару x-y
		template <typename GetterType>
		static void CreateGif(
			GetterType dataGetter,
			int frameCount,
			std::string outputFile, 
			int delay)
		{
			WriteTwoColumns(dataGetter, frameCount);

			std::string script = R"(set term gif \
    animate \
    optimize \
    delay )" + std::to_string(delay) + R"( \
    size 600, 300 \
    background "#ffeedf" \
    crop
set border 3
set grid
set output ")" + outputFile + R"("
set datafile separator "\t"
set yrange[0:0.1]
plot ")" + "data.txt" + R"(" index 0 w lines
do for [j=0:340] {
    plot ")" + "data.txt" + R"(" index j w lines lc 7 lw 2 title "graphic ".(j + 1)
})";
			std::ofstream fout("gnuplot_script.txt");
			fout << script;
			fout.close();

			ExecuteScript("gnuplot_script.txt");
		}

		static void ExecuteScript(std::string scriptPath)
		{
			auto command = "gnuplot " + scriptPath;
			auto gnuplot = _popen(command.c_str(), "w");
			if (!gnuplot)
			{
				throw std::runtime_error("gnuplot isn't found");
			}

			_pclose(gnuplot);
		}

	private:
		template <typename GetterType>
		static void WriteTwoColumns(GetterType dataGetter, int frameCount)
		{
			std::ofstream fout("data.txt");

			for (auto i = 0; i < frameCount; i++)
			{
				auto [x, y] = dataGetter(i);

				if (x.size() != y.size())
				{
					throw std::invalid_argument("wrong sizes");
				}

				fout.precision(6);
				fout << std::fixed;

				for (auto i = 0; i < x.size(); i++)
				{
					fout << x[i] << "\t" << y[i] << std::endl;
				}

				fout << std::endl << std::endl;
			}
		}
	};
}
