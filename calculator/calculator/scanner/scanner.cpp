#include "scanner.h"

std::queue<token_t> scanner::scan(const std::map<char, std::shared_ptr<description_operator>>& opers, const std::string& input) {
  funcName(opers);
  token_t token;
  int i = 0;
  const char* c_input = input.c_str();
  char *endInput;
  double result;

  std::queue<token_t> tokens;

  while (*c_input != '\0') {
    if (*c_input >= '0' && *c_input <= '9') {
      result = strtod(c_input, &endInput);
      if (errno != 0 || endInput == c_input) {
        error::getError().updateError(error::errorId_t::INVALID_SCANNER, "ERROR: can not read a number");
        return {};
      }
      c_input = endInput;

      token.tokenId = tokenId_t::TOKEN_NUMBER;
      token.tokenValue.number =  result;

      tokens.push(token);
    }
    else {
      token = readFunc(c_input, opers);
      if(error::getError().errorId != error::errorId_t::SUCCESS)
        return {};
      tokens.push(token);
      c_input = c_input + token.tokenValue.operationValue.get()->getOperatorName().length();
    }
  }
  return tokens;
}
