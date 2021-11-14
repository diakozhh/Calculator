#include "parser.h"
#include "../error.h"

std::queue<token_t> parser::parse(const std::map<char, std::shared_ptr<description_operator>>& opers, std::queue<token_t>& parseTokens) {
  token_t token;
  
  std::queue<token_t> RPN;

  std::shared_ptr<description_operator> tmpOper;

  enum class state_t{
    STATE_PREFIX,
    STATE_SUFFIX,
    STATE_DONE,
    STATE_END
  };
  state_t state = state_t::STATE_PREFIX;
  while (state != state_t::STATE_END) {
    if (state <= state_t::STATE_SUFFIX) {
      if (parseTokens.empty()) {
        if(state == state_t::STATE_SUFFIX)
          state = state_t::STATE_DONE;
        else {
          error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: unexpected end of expression");
          state = state_t::STATE_END;
        }
      }
      else {
        token = parseTokens.front();
        parseTokens.pop();
      }
    }

    switch (state) {
    case state_t::STATE_PREFIX:
      if (token.tokenId == tokenId_t::TOKEN_NUMBER) {
        state = state_t::STATE_SUFFIX;
        stack1.push(token);
      }

      else if (token.tokenId == tokenId_t::TOKEN_OPERATION) {
        if(token.tokenValue.operationValue.get()->getOperatorName() == "(")
          stack2.push(token);

        else if (token.tokenValue.operationValue.get()->getOperatorName() == "-") {
          token.tokenValue.operationValue = opers.find('!')->second;
          stack2.push(token);
        }
        else {
          tmpOper = opers.at(token.tokenValue.operationValue.get()->getId());
          if (tmpOper->checkUnary())
            stack2.push(token);
          else {
            error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: expected number or opening bracket");
            state = state_t::STATE_END;
          }
        }
      }
      break;

    case state_t::STATE_SUFFIX:
      if (token.tokenId == tokenId_t::TOKEN_OPERATION && token.tokenValue.operationValue.get()->getOperatorName() != "(") {
        dropOpers(opers, opers.at(token.tokenValue.operationValue.get()->getId()).get());
        if (token.tokenValue.operationValue.get()->getOperatorName() != ")") {
          stack2.push(token);
          state = state_t::STATE_PREFIX;
        }
        else {
          if (stack2.empty()) {
            error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: expected opening bracket");
            state = state_t::STATE_END;
          }
          else {
            token = stack2.top();
            stack2.pop();
            state = state_t::STATE_SUFFIX;
          }
        }
      }
      else {
        error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: expected closing bracket");
        state = state_t::STATE_END;
      }
      break;
    case state_t::STATE_DONE:
      dropOpers(opers, opers.at(')').get());
      if (!stack2.empty()) {
        error::getError().updateError(error::errorId_t::INVALID_PARSER, "ERROR: expected closing bracket");
        state = state_t::STATE_END;
      }
      while (!stack1.empty()) {
        token = stack1.top();
        stack1.pop();
        stack2.push(token);
      }
      while (!stack2.empty()) {
        token = stack2.top();
        stack2.pop();
        RPN.push(token);
      }
      state = state_t::STATE_END;
      break;
    default:
      break;
    }
  }
  return RPN;
}
