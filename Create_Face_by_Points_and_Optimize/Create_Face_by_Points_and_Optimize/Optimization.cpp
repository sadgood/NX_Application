#include "Optimization.h"

extern  void OptimizeFace(const string &OptName, int *retCode, int paramLen)
{
	Session *theSession = Session::GetSession();
	Part *workPart(theSession->Parts()->Work());

	Optimization::OptimizationBuilder *optimizationBuilder1;
	optimizationBuilder1 = workPart->Optimization()->CreateOptimizationBuilder();

	optimizationBuilder1->SetStudyName(OptName);

	std::vector<NXString> attributenames1(1);
	attributenames1[0] = "p8";
	std::vector<NXObject *> attributeobjects1(1);
	Expression *expression1(dynamic_cast<Expression *>(workPart->Expressions()->FindObject("p8")));
	attributeobjects1[0] = expression1;
	std::vector<Optimization::OptimizationBuilder::OptimizationAttributeType> objectivetypes1(1);
	objectivetypes1[0] = Optimization::OptimizationBuilder::OptimizationAttributeTypeExpression;
	std::vector<double> objectivetargetvalues1(1);
	objectivetargetvalues1[0] = 12570.0;
	optimizationBuilder1->SetOptimizationObjectives(attributenames1, attributeobjects1, objectivetypes1, objectivetargetvalues1);

	std::vector<NXString> attributenames2(2);
	attributenames2[0] = "p9";
	attributenames2[1] = "p10";
	std::vector<NXObject *> attributeobjects2(2);
	Expression *expression2(dynamic_cast<Expression *>(workPart->Expressions()->FindObject("p9")));
	attributeobjects2[0] = expression2;
	Expression *expression3(dynamic_cast<Expression *>(workPart->Expressions()->FindObject("p10")));
	attributeobjects2[1] = expression3;
	std::vector<Optimization::OptimizationBuilder::OptimizationAttributeType> variabletypes1(2);
	variabletypes1[0] = Optimization::OptimizationBuilder::OptimizationAttributeTypeExpression;
	variabletypes1[1] = Optimization::OptimizationBuilder::OptimizationAttributeTypeExpression;
	std::vector<double> variablelowerlimitvalue1(2);
	const double variablelowerlimitvalue1_initial_values[] = {
		-20.0, -30.0
	};
	variablelowerlimitvalue1.assign(variablelowerlimitvalue1_initial_values, variablelowerlimitvalue1_initial_values + 2);
	std::vector<double> variableupperlimitvalue1(2);
	const double variableupperlimitvalue1_initial_values[] = {
		20.0, 30.0
	};
	variableupperlimitvalue1.assign(variableupperlimitvalue1_initial_values, variableupperlimitvalue1_initial_values + 2);
	optimizationBuilder1->SetOptimizationVariables(attributenames2, attributeobjects2, variabletypes1, variablelowerlimitvalue1, variableupperlimitvalue1);

	optimizationBuilder1->SetOptimizationType(Optimization::OptimizationBuilder::OptimizationTargetTypeMinimum);

	optimizationBuilder1->SetAlgorithmType(Optimization::OptimizationBuilder::OptimizationAlgorithmTypePowell);

	optimizationBuilder1->SetConvergenceSpeedType(Optimization::OptimizationBuilder::OptimizationConvergenceSpeedTypeFast);

	optimizationBuilder1->SetMaxTime(1);

	optimizationBuilder1->SetMaxNumberIteration(20);

	optimizationBuilder1->SetAbsoluteConvergenceCriteria(0.001);

	optimizationBuilder1->SetRelativeConvergenceCriteria(2.5);

	optimizationBuilder1->SetShowGraph(false);

	optimizationBuilder1->RunOptimization();

	optimizationBuilder1->Destroy();
}
