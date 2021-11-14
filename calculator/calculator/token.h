#include <string>
#include <memory>
#include "operations/description_operator.h"

#pragma once
/**
* Token id 
*/
enum class tokenId_t {
  TOKEN_NUMBER, ///< if number
  TOKEN_OPERATION ///< if operation
};

/**
* Content
*/
typedef struct {
  std::shared_ptr<description_operator> operationValue; 
  double number;
} content_t;

/**
* Struct token
*/
typedef struct token_t {
  tokenId_t tokenId;
  content_t tokenValue;
} token_t;