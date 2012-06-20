#pragma once

#include <string>

namespace trench {

class Program;

class SpinModelChecker {
	std::string spinCommandLine_;
	std::string compilerCommandLine_;
	std::string verifierCommandLine_;

	public:

	SpinModelChecker();

	void setSpinCommandLine(const std::string &commandLine) { spinCommandLine_ = commandLine; }
	const std::string &spinCommandLine() const { return spinCommandLine_; }

	void setCompilerCommandLine(const std::string &commandLine) { compilerCommandLine_ = commandLine; }
	const std::string &compilerCommandLine() const { return compilerCommandLine_; }

	void setVerifierCommandLine(const std::string &commandLine) { verifierCommandLine_ = commandLine; }
	const std::string &verifierCommandLine() const { return verifierCommandLine_; }

	bool check(const Program &program);
};

} // namespace trench
