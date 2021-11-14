#include <windows.h>

#include <list>
#include <queue>
#include <stack>
#include <map>
#include <memory>
#include <filesystem>

#include "../error.h"
#include "../token.h"
#include "../eval/eval.h"
#include "../operations/description_operator.h"
#include "../operations/operation.h"
#include "../parser/parser.h"
#include "../scanner/scanner.h"


#pragma once
/**
* Calculation class
*/
class calculation {
private:
  /**
  * Fill in the operator map with standard operators
  */
  std::map<char, std::shared_ptr<description_operator>> opers;
  std::list<HMODULE> DLLs;

  void fillDefaultOpers() {
    std::shared_ptr<description_operator> operation = std::make_shared<addition>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<subtraction>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<multiplication>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<division>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<unary_minus>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<opening_bracket>();
    opers.emplace(std::make_pair(operation->getId(), operation));

    operation = std::make_shared<closing_bracket>();
    opers.emplace(std::make_pair(operation->getId(), operation));

  }
  /**
  * Fill in the operator map with operators from dll
  * @param DLLPath is path to folder dlls
  */
  void fillDllsOpers(const std::string& DLLPath) {

    for (auto& file : std::filesystem::directory_iterator(DLLPath)) {
      if(file.path().extension().string() != ".dll")
        continue;
      HMODULE dll = LoadLibrary(file.path().string().c_str());
      if (dll == nullptr) {
        continue;
      }

      description_operator* (__cdecl* descripFunc)(void) = (description_operator * (__cdecl*)(void))GetProcAddress(dll, "descOper");

      if (descripFunc == nullptr) {
        FreeLibrary(dll);
        continue;
      }
      description_operator* oper = descripFunc();
      opers.emplace(std::make_pair(oper->getId(), oper));
      DLLs.push_back(dll);
    }
  }

public:
  /**
  * Calculator constructor
  * @param DLLPath is path to folder dlls
  */
  calculation(const std::string& DLLPath) {
    fillDefaultOpers();
    fillDllsOpers(DLLPath);
  }
  /**
  * Executor function
  * @warning there may be scanner, parser, eval errors
  * @param input is input string
  */
  double executor(const std::string& input) {
    scanner _scanner;
    parser _parser;
    eval _eval;
    
    double result;

    auto tQueue = _scanner.scan(opers, input);
    if (error::getError().errorId != error::errorId_t::SUCCESS)
      return 0;
    auto RPN = _parser.parse(opers, tQueue);
    if (error::getError().errorId != error::errorId_t::SUCCESS)
      return 0;
    result = _eval.evalvater(opers, RPN);
    if (error::getError().errorId != error::errorId_t::SUCCESS)
      return 0;

    return result;

  }
  /**
  * Default calculator's destructor
  */
  ~calculation() {
    for(auto& dll: DLLs)
      FreeLibrary(dll);
  }
};