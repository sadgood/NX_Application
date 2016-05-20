#include "CreateExpression.h"

extern Expression * CreateExpression(string expressionType, string expressionName, double num)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());
	Expression *expression;
	expression = workPart->Expressions()->CreateExpression(expressionType, expressionName);
	return expression;
}

