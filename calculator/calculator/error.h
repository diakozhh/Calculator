#include <string>
#include <utility>

#pragma once
/**
@brief Calculate error class
*/
class error {
private:
  /**
  * Default error_t constructor
  */
  error(){};

public:
  /**
  * Enum error class
  */
  enum class errorId_t {
    SUCCESS, ///< success
    INVALID_PARSER,///< error in parser
    INVALID_SCANNER,///<error in scanner
    INVALID_EVAL, ///< error in eval
    INVALID_OPERATION ///< invalid operation
  };

  errorId_t errorId; ///<error type
  std::string errorName; ///<error message
  /**
  * Return existed error instance
  * @return error reference
  */
  static error& getError() {
    static error returnedError;
    return returnedError;
  }

  /**
  * Update error 
  * @param newErrorId is new error id
  * @param newErrorName is new error message
  */

  void updateError(errorId_t newErrorId, std::string&& newErrorName) {
    errorId = newErrorId;
    errorName = std::move(newErrorName);
  }
};