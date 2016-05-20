#pragma once
#include <NXOpen/PartCollection.hxx>
#include <NXOpen/ExpressionCollection.hxx>
#include <string>

using namespace std;
using namespace NXOpen;

extern Expression * CreateExpression(string expressionType, string expressionName, double num);