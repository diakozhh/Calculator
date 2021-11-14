#include <string>
#include <stack>
#include <queue>
#include <map>
#include <memory>

#include "../error.h"
#include "../token.h"
#include "../operations/description_operator.h"

#pragma once
/**
@brief Class parser
*/
class parser
{
private:
	std::stack<token_t> stack1;
	std::stack<token_t> stack2;
	/**
	@brief Check assoc function
	@param oper1 is first operator
	@param oper2 is second operator
	@return true if assoc, false if not
	*/
	bool checkAssoc(const description_operator* oper1, const description_operator *oper2) {
		return (oper1->getPrior() == oper2->getPrior() &&
			(oper1->getOperatorName() == "^")) ? oper1->getPrior() > oper2->getPrior() :
			oper1->getPrior() >= oper2->getPrior();
	}
	/**
	* Drop operators from 'stack2' to 'stack1'
	* @param opers is operators map
	* @param oper is operator to drop operators from stack
	*/
	void dropOpers(const std::map<char, std::shared_ptr<description_operator>>& opers,const description_operator* oper) {
		token_t token;

		while (!stack2.empty() && checkAssoc(opers.at(stack2.top().tokenValue.operationValue.get()->getId()).get(), oper) != 0) {
			token = stack2.top();
			stack2.pop();
			stack1.push(token);
		}
	}
public:
/**
* Default parser constructor
*/
	parser() {};
/**
* Parse tokens function
* @param opers is operators map
* @param parseTokens is tokens queue to parse
* @return RPN queue tokens
*/
	std::queue<token_t> parse(const std::map<char, std::shared_ptr<description_operator>>& opers, std::queue<token_t>& parseTokens);
};