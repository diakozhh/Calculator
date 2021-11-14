#include <queue>
#include <map>
#include <memory>
#include <stack>

#include "../token.h"
#include "../operations/description_operator.h"
#include "../error.h"

#pragma once 
/**
* @brief Eval class
*/
class eval {
public:
  /**
  * Default eval constuctor
  */
  eval(){};
  /**
  * Eval function
  * @warning Error in operators
  * @param opers is operator map
  * @params tokens is RPN queue
  * @return result of value
  */
  double evalvater(const std::map<char, std::shared_ptr<description_operator>>& opers, std::queue<token_t>& tokens) {
    token_t num1, num2, token;
    
    std::stack<token_t> stackTokens;

    std::shared_ptr<description_operator> oper;

    while(!tokens.empty()) {
      token = tokens.front();
      tokens.pop();
      if(token.tokenId == tokenId_t::TOKEN_NUMBER)
        stackTokens.push(token);
      else {
        oper = opers.at(token.tokenValue.operationValue.get()->getId());
        if (!oper->checkUnary()) {
          num2 = stackTokens.top();
          stackTokens.pop();
        }

        num1 = stackTokens.top();
        stackTokens.pop();

        num1.tokenValue.number = oper->operation(num1.tokenValue.number, num2.tokenValue.number, error::getError());

        if(error::getError().errorId != error::errorId_t::SUCCESS)
          return -1;

        stackTokens.push(num1);

      }
    }

    num1 = stackTokens.top();
    stackTokens.pop();

    if (!stackTokens.empty()) {
      error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: incorrect eval");
      return 0;
    }
    return num1.tokenValue.number;
  }

};