#pragma once
#include "classes.h"
#include <stack>
#include <set>
#include "IRClasses.h"
#include "SymbolsTable.h"
#include "Frame.h"
#include "IRConditionalWrapper.h"
#include "IRTreePrettyPrinter.h"


struct CBlock {
  std::vector<const IIRStm*> stms;
  std::string rootLabel;
  bool isInverted;
  bool isNoConditions;
  CBlock() : isNoConditions(false), isInverted(false), rootLabel("emptyRootLabel") {}
};

class CTracer {
public:
  CTracer();
  CIRSeq* Transform(const CIRSeq* list);
private:
  CLabel* doneLabel;
  std::map<const CLabel*, int> labelMap;
  std::vector<CBlock> blockSequence;
  std::vector<int> resultVector;

  void findBlocks(const CIRSeq* list);
  void sortBlocks();
  void dfs(int blockId, std::vector<int>& used);
};
