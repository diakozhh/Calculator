// calculator.cpp: определяет точку входа для приложения.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "calculator.h"

using namespace std;

void Process() {
	calculation calc("../../../../calculator/dllFunction/build/plugins");
	std::string inputStr;
	double result;

	while (std::getline(std::cin, inputStr)) {
		error::getError().updateError(error::errorId_t::SUCCESS, "SUCCESS");

		inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), ' '), inputStr.end());
		inputStr.erase(std::remove(inputStr.begin(), inputStr.end(), '\t'), inputStr.end());

		result = calc.executor(inputStr);
		if (error::getError().errorId != error::errorId_t::SUCCESS)
			std::cout << error::getError().errorName << std::endl;
		else
			std::cout << inputStr << " = " << result << std::endl;
	}
}


int main() {
	Process();
	_CrtDumpMemoryLeaks();
	return 0;
}
