#include <string>
#include <stack>
#include <queue>
#include <map>
#include <set>

#include <memory>

#include "../error.h"
#include "../operations/description_operator.h"
#include "../token.h"
#include <memory>
#pragma once

/**
@brief Class scanner
*/

class scanner {
private:
  std::set<std::pair<std::string, char>> operators;
  /**
  * Fill operator's name and id
  * @param opers is operator's map
  */
  void funcName(const std::map<char, std::shared_ptr<description_operator>> opers) {
    for(auto& func : opers)
      if(func.second->getId() != '!')
        operators.emplace(std::pair<std::string, char>(func.second->getOperatorName(), func.second->getId()));
  }
  /**
  * Read function from input string
  * @param input is input string
  * @param opers is operator's map
  * @return new token operator
  */
  token_t readFunc(const char* input, const std::map<char, std::shared_ptr<description_operator>> opers) {
    token_t token;
    int i;
    for (auto& op : operators) {
      const char* char_name = op.first.c_str();
      for(i = 0; i < op.first.length() && input[i] != 0; i++)
        if(char_name[i] != input[i])
          break;
      if (i == op.first.length()) {
        token.tokenId = tokenId_t::TOKEN_OPERATION;

        token.tokenValue.operationValue = opers.find(op.second)->second;
        return token;
      }
    }
    error::getError().updateError(error::errorId_t::INVALID_SCANNER, "ERROR: invalid operator or function");
    return token;
  }
public:
/**
* Scanner function
* @param opers is operators map
* @param input is input string to parse
* @return queue tokens
*/
  scanner(){};
  std::queue<token_t> scan(const std::map<char, std::shared_ptr<description_operator>>& opers, const std::string& input);
};