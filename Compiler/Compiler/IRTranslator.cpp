#include "IRTranslator.h"

CIRTranslator::CIRTranslator(const CTable * _symbTable, const  std::map< const void*, std::string > _expTypesTable) : symbTable(_symbTable), expTypesTable(_expTypesTable)
{}

void CIRTranslator::Visit(const CAssignmentStatement * assigmentStatement)
{
	const IIRExp* left(frames.top()->GetField(assigmentStatement->Id()->String())->GetExp(frames.top()->GetFramePointer()));

	assigmentStatement->Expression()->Accept(this);
	const IIRExp* right = exps.top();
	exps.pop();

	stms.push(new CIRMove(left, right));
}

void CIRTranslator::Visit(const CBinExp * binExp)
{
	binExp->Expression1()->Accept(this);

	IIRExp* left = exps.top();
	exps.pop();

	binExp->Expression2()->Accept(this);

	IIRExp* right = exps.top();
	exps.pop();

	if (binExp->Operation() == "+") {
		exps.push(new CIRBinOp(PLUS, left, right));
	}
	else if (binExp->Operation() == "-") {
		exps.push(new CIRBinOp(MINUS, left, right));
	}
	else if (binExp->Operation() == "*") {
		exps.push(new CIRBinOp(MUL, left, right));
	}
	else if (binExp->Operation() == "<") {
		exps.push(new CIRBinOp(LE, left, right));
	}
	else if (binExp->Operation() == "&") {
		exps.push(new CIRBinOp(AND, left, right));
	}
	else if (binExp->Operation() == "|") {
		exps.push(new CIRBinOp(OR, left, right));
	}
	else if (binExp->Operation() == "[]") {
		binExp->Expression1()->Accept(this);
		IIRExp* array = exps.top();
		exps.pop();

		binExp->Expression2()->Accept(this);
		IIRExp* index = exps.top();
		exps.pop();

		IIRExp* offset = new CIRBinOp(MUL, index, new CIRConst(CFrame::GetWordSize()));
		exps.push(new CIRBinOp(PLUS, array, offset));
	}
	else {
		//пичаль
	}
}

void CIRTranslator::Visit(const CClassDecl * classDecl)
{
	currentClass = symbTable->FindClass(classDecl->Id());

	if (classDecl->MethodDeclList() != nullptr) {
		classDecl->MethodDeclList()->Accept(this);
	}

	currentClass = nullptr;
}

void CIRTranslator::Visit(const CClassDeclList * classDecls)
{
	for (auto classDecl : classDecls->ClassDeclList()) {
		classDecl->Accept(this);
	}
}

void CIRTranslator::Visit(const CConstructor * constructor)
{
	int fieldsNumber = 0;
	CClassInfo* classInfo = symbTable->FindClass(constructor->Id());
	while (classInfo != nullptr) {
		fieldsNumber += classInfo->VarList().size();
		classInfo = symbTable->FindClass(classInfo->BaseClassName());
	}

	CLabel* mallocLabel = new CLabel("malloc");
	IIRExp* mallocName = new CIRName(mallocLabel);

	CLabel* memsetLabel = new CLabel("memset");
	IIRExp* memsetName = new CIRName(memsetLabel);

	IIRExp* allocationSize = new CIRBinOp(MUL, new CIRConst(CFrame::GetWordSize()), new CIRConst(fieldsNumber));
	CIRCall* mallocCall = new CIRCall(mallocName, new CIRExpList(allocationSize, nullptr));
	//CIRTemp* tmp = new CIRTemp( frames.top()->GetReturnValue() );  TODO: разобраться, что за tmp
	CIRTemp* tmp = new CIRTemp(new CTemp());
	IIRStm* first = new CIRMove(tmp, mallocCall);
	IIRStm* second = new CIRExp(new CIRCall(memsetName, new CIRExpList(tmp, new CIRExpList(allocationSize, nullptr))));
	exps.push(new CIRESeq(new CIRSeq(first, second), tmp));
	lastObjectClass = symbTable->FindClass(constructor->Id());
}

void CIRTranslator::Visit(const CElementAssignment * elemAssign)
{
	elemAssign->Exp1()->Accept(this);
	IIRExp* index = exps.top();
	exps.pop();

	IIRExp* offset = new CIRBinOp(MUL, index, new CIRConst(CFrame::GetWordSize()));
	IIRExp* array = new CIRMem(frames.top()->GetField(elemAssign->Id()->String())->GetExp(frames.top()->GetFramePointer()));
	IIRExp* lExp = new CIRMem(new CIRBinOp(PLUS, array, offset));

	elemAssign->Exp2()->Accept(this);
	IIRExp* rExp = exps.top();
	exps.pop();

	stms.push(new CIRMove(lExp, rExp));
}

void CIRTranslator::Visit(const CExpList * expList)
{
	std::vector<IIRExp*> vectorExp;
	for (size_t i = 0; i < expList->Expressions().size(); ++i) {
		expList->Expressions()[i]->Accept(this);
		vectorExp.push_back(exps.top());
		exps.pop();
	}
	lists.push(new CIRExpList(vectorExp));
}

void CIRTranslator::Visit(const CFormalList * formalList)
{
	throw std::logic_error("Translator shouldn't visit formalList");
}

void CIRTranslator::Visit(const CId * id)
{
	exps.push(const_cast<IIRExp*>(frames.top()->GetField(id->Id()->String())->GetExp(frames.top()->GetFramePointer())));
}

void CIRTranslator::Visit(const CIfStatement * ifStatement)
{
	ifStatement->Expression()->Accept(this);
	IIRExp* condition = exps.top();
	exps.pop();

	ifStatement->ThenStatement()->Accept(this);
	IIRStm* trueStatement = stms.top();
	stms.pop();

	CLabel* trueLabelTemp = new CLabel();
	CLabel* falseLabelTemp = new CLabel();
	CLabel* endLabelTemp = new CLabel();

	CIRJump* trueJumpToEnd = new CIRJump(endLabelTemp);

	CIRLabel* trueLabel = new CIRLabel(trueLabelTemp);
	CIRLabel* falseLabel = new CIRLabel(falseLabelTemp);
	CIRLabel* endLabel = new CIRLabel(endLabelTemp);

	trueStatement = new CIRSeq(trueLabel, new CIRSeq(trueStatement, trueJumpToEnd));

	IIRStm* falseStatement = nullptr;
	if (ifStatement->ElseStatement() != nullptr) {
		ifStatement->ElseStatement()->Accept(this);
		falseStatement = stms.top();
		stms.pop();
		CIRJump* falseJumpToEnd = new CIRJump(endLabelTemp);
		falseStatement = new CIRSeq(falseLabel, new CIRSeq(falseStatement, falseJumpToEnd));
	}

	CConditionalWrapper wrapper(condition);
	stms.push(new CIRSeq(wrapper.ToConditional(trueLabelTemp, falseLabelTemp), new CIRSeq(trueStatement, new CIRSeq(falseStatement, endLabel))));
}

void CIRTranslator::Visit(const CLengthExp * lengthExp)
{
	lengthExp->Expression()->Accept(this);
	IIRExp* arrayPtr = exps.top();
	exps.pop();

	CIRTemp* lengthVar = new CIRTemp(new CTemp());

	CIRMove* move = new CIRMove(lengthVar, arrayPtr);

	exps.push(new CIRESeq(move, lengthVar));
}

void CIRTranslator::Visit(const CMainClass * mainClass)
{
	CSymbol* id = mainClass->Id();
	IIRStm* statements = nullptr;
	if (symbTable->FindClass(id) == nullptr) {
		std::cerr << "At line " << mainClass->Line() << ": undefined class " << id->String() << std::endl;
	}
	else {
		currentClass = symbTable->FindClass(id);
		if (mainClass->Statements() != nullptr) {
			mainClass->Statements()->Accept(this);
			statements = stms.top();
			stms.pop();
		}
	}
	frames.push(new CFrame(new CSymbol(mainClass->Id()->String() + "___main")));
	frames.top()->AddField(new CSymbol("this"), 0);
	frames.top()->SetRootStatement(statements);
}

void CIRTranslator::Visit(const CMethodCall * methodCall)
{
	// получаем объект, у которого вызывается метод
	methodCall->Exp()->Accept(this);
	IIRExp* object = exps.top();
	exps.pop();

	// имя метода
	CSymbol* method = methodCall->Id();

	CIRExpList* arguments;
	// парсим аргументы (если они есть)
	if (methodCall->Args() != nullptr) {
		methodCall->Args()->Accept(this);
		arguments = lists.top();
		lists.pop();
	}
	else {
		arguments = new CIRExpList(nullptr, nullptr);
	}

	arguments = new CIRExpList(object, arguments);

	CLabel* methodLabel = new CLabel(method->String());
	CIRName* methodName = new CIRName(methodLabel);

	CIRTemp* resultVar = new CIRTemp(new CTemp());
	exps.push(new CIRESeq(new CIRMove(resultVar, new CIRCall(methodName, arguments)), resultVar));
}

void CIRTranslator::Visit(const CMethodDecl * methodDecl)
{
	// ищем инфу о методе
	CMethodInfo* methodInfo = nullptr;
	for (auto method : currentClass->MethodList()) {
		if (method.second->Name() == methodDecl->Name()) {
			methodInfo = method.second;
		}
	}
	if (methodInfo == nullptr) {
		throw std::logic_error("Method " + methodDecl->Name()->String() + " wasn't found in " + currentClass->Name()->String() + " in IR");
	}
	// создаем новый фрейм, в котором записана инфа о методе
	frames.push(new CFrame(currentClass, methodInfo, symbTable));

	// парсим команды метода, если есть
	IIRStm* statements = nullptr;
	if (methodDecl->StatementList() != nullptr) {
		methodDecl->StatementList()->Accept(this);
		statements = stms.top();
		stms.pop();
	}

	// взяли результат выполнения функции
	methodDecl->Result()->Accept(this);
	auto returnedExp = exps.top();
	exps.pop();
	// записали во фрейм
	IIRStm* moveResult = new CIRMove(new CIRTemp(frames.top()->GetReturnValue()), returnedExp);
	// если метод не содержал команд, то все он только считает результат и записывает его в фрейм
	IIRStm* methodStm = moveResult;

	if (statements != nullptr) {
		// иначе сначала выполняем команды и потом возимся с результатом
		methodStm = new CIRSeq(statements, moveResult);
	}

	frames.top()->SetRootStatement(methodStm);
}

void CIRTranslator::Visit(const CMethodDeclList * methodDecls)
{
	for (auto methodDecl : methodDecls->MethodDeclList()) {
		methodDecl->Accept(this);
	}
}

void CIRTranslator::Visit(const CNewInt * newInt)
{
	newInt->Expression()->Accept(this);
	IIRExp* count = exps.top();
	exps.pop();

	IIRExp* allocationSize = new CIRBinOp(PLUS, count, new CIRConst(1));
	IIRExp* realSize = new CIRBinOp(MUL, allocationSize, new CIRConst(CFrame::GetWordSize()));

	CLabel* mallocLabel = new CLabel("malloc");
	IIRExp* mallocName = new CIRName(mallocLabel);

	CLabel* memsetLabel = new CLabel("memset");
	IIRExp* memsetName = new CIRName(memsetLabel);

	CIRCall* mallocCall = new CIRCall(mallocName, new CIRExpList(realSize, nullptr));
	//CIRTemp* tmp = new CIRTemp( frames.top()->GetReturnValue() ); TODO: разобраться, что должно быть в tmp
	CIRTemp* tmp = new CIRTemp(new CTemp());
	IIRStm* first = new CIRExp(mallocCall);
	IIRStm* second = new CIRExp(new CIRCall(memsetName, new CIRExpList(tmp, new CIRExpList(realSize, nullptr))));
	IIRStm* third = new CIRMove(tmp, count);
	second = new CIRSeq(second, third);
	exps.push(new CIRESeq(new CIRSeq(first, second), tmp));
}

void CIRTranslator::Visit(const CNumber * number)
{
	exps.push(new CIRConst(number->Number()));
}

void CIRTranslator::Visit(const CPrintStatement * printStatement)
{
	printStatement->Expression()->Accept(this);
	IIRExp* toPrint = exps.top();
	exps.pop();

	CLabel* printLabel = new CLabel("print");
	IIRExp* printName = new CIRName(printLabel);

	stms.push(new CIRExp(new CIRCall(printName, new CIRExpList(toPrint, nullptr))));
}

void CIRTranslator::Visit(const CProgram * program)
{
	program->MainClass()->Accept(this);

	if (program->ClassDeclList() != nullptr) {
		program->ClassDeclList()->Accept(this);
	}
}

void CIRTranslator::Visit(const CStatementBlock * statementBlock)
{
	statementBlock->Statements()->Accept(this);
}

void CIRTranslator::Visit(const CStatementList * statementList)
{
	for (auto stm : statementList->StatementList()) {
		stm->Accept(this);
	}
	// Выполняем первый
	statementList->StatementList().front()->Accept(this);
	IIRStm* listOfStm = stms.top();
	stms.pop();
	if (statementList->StatementList().size() == 1) {
		stms.push(listOfStm);
		return;
	}
	else {
		auto iter = statementList->StatementList().begin();
		iter++;
		// начинаем со второго
		for (; iter != statementList->StatementList().end(); iter++) {
			(*iter)->Accept(this);
			IIRStm* statementToAdd = 0;
			if (!exps.empty()) {
				// Нам нужны только IStm 
				statementToAdd = new CIRExp(exps.top());
				exps.pop();
			}
			else {
				statementToAdd = stms.top();
				stms.pop();
			}
			listOfStm = new CIRSeq(listOfStm, statementToAdd);
		}
		stms.push(listOfStm);
	}
}

void CIRTranslator::Visit(const CType * type)
{
	throw std::logic_error("Translator shouldn't visit CType");
}

void CIRTranslator::Visit(const CUnExp * unExp)
{
	unExp->Expression()->Accept(this);

	IIRExp* exp = exps.top();
	exps.pop();

	if (unExp->Operation() == "-") {
		exps.push(new CIRMem(new CIRBinOp(MINUS, new CIRConst(0), exp)));
	}
	else if (unExp->Operation() == "!") {
		exps.push(new CIRMem(new CIRBinOp(OR, new CIRConst(0), exp)));
	}
	else {
		// тогда это странный уноп
	}
}

void CIRTranslator::Visit(const CVarDecl * varDecl)
{
	throw std::logic_error("Translator shouldn't visit CVarDecl");
}

void CIRTranslator::Visit(const CVarDeclList * varDecls)
{
	throw std::logic_error("Translator shouldn't visit CVarDeclList");
}

void CIRTranslator::Visit(const CWhileStatement * whileStatement)
{
	whileStatement->Expression()->Accept(this);
	IIRExp* condition = exps.top();
	exps.pop();

	whileStatement->Statement()->Accept(this);
	IIRStm* statements = stms.top();
	stms.pop();

	CLabel* beforeLabelTemp = new CLabel();
	CLabel* inLoopLabelTemp = new CLabel();
	CLabel* endLabelTemp = new CLabel();

	CIRLabel* beforeLabel = new CIRLabel(beforeLabelTemp);
	CIRLabel* inLoopLabel = new CIRLabel(inLoopLabelTemp);
	CIRLabel* endLabel = new CIRLabel(endLabelTemp);

	CConditionalWrapper converter(condition);
	IIRStm* whileStm = converter.ToConditional(inLoopLabelTemp, endLabelTemp);
	IIRStm* conditionStm = new CIRSeq(beforeLabel, new CIRSeq(whileStm, inLoopLabel));
	stms.push( new CIRSeq(conditionStm, new CIRSeq(statements,
		new CIRSeq(new CIRJump(beforeLabelTemp), endLabel))));
}

/*CIRTranslator::EVariablePlace CIRTranslator::getVariablePlace( const CSymbol * var ) const
{
	if( frames.top()->Local( var ) != nullptr ) {
		return E_LOCAL;
	}

	for( size_t i = 0; i < frames.top()->FormalsCount(); ++i ) {
	}
}*/
