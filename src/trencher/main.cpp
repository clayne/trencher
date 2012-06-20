#include <fstream>
#include <iostream>

#include <trench/NaiveParser.h>
#include <trench/NaivePrinter.h>
#include <trench/SpinPrinter.h>
#include <trench/Program.h>
#include <trench/Reduction.h>
#include <trench/SpinModelChecker.h>

void help() {
	std::cout << "Usage: trencher file..." << std::endl;
}

int main(int argc, char **argv) {
	if (argc <= 1) {
		help();
		return 1;
	}

	try {
		for (int i = 1; i < argc; ++i) {
			trench::Program program;
			trench::NaiveParser parser;

			std::ifstream in(argv[i]);
			parser.parse(in, program);

			trench::Program augmentedProgram;
			trench::reduce(program, augmentedProgram, program.threads().front());

#if 0
			trench::NaivePrinter naivePrinter;
			naivePrinter.print(std::cout, program);

			trench::SpinPrinter spinPrinter;
			spinPrinter.print(std::cout, augmentedProgram);
#endif
			trench::SpinModelChecker checker;
			std::cerr << "Has violations: " << checker.check(augmentedProgram) << std::endl;
		}
	} catch (const std::exception &exception) {
		std::cerr << "trencher: " << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
