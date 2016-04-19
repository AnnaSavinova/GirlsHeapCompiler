#include "IRBlockDecompositor.h"

CTracer::CTracer()
{
  doneLabel = new CLabel("DoneLabel");
}

CIRSeq* CTracer::Transform(const CIRSeq* list) {
  findBlocks(list);

  sortBlocks();
  CIRSeq* result = 0;

  for (int i = 0; i < resultVector.size() - 1; i++) {
    int len = blockSequence[resultVector[i]].stms.size();
    auto isJump = dynamic_cast<const CIRJump*>(blockSequence[resultVector[i]].stms[len - 1]);
    if (isJump) {
      auto isTargetLabel = dynamic_cast<const CIRLabel*>(blockSequence[resultVector[i + 1]].stms[0]);
      if (isTargetLabel && isTargetLabel->label->Name() == isJump->label->Name()) {
        blockSequence[resultVector[i]].stms.pop_back();
      }
    }
  }

  for (int i = resultVector.size() - 1; i >= 0; i--) {
    int len = blockSequence[resultVector[i]].stms.size();
    if (blockSequence[resultVector[i]].isInverted) {
      const CIRCjump* cjump = dynamic_cast<const CIRCjump*>(blockSequence[resultVector[i]].stms[len - 1]);
      result = new CIRSeq(new CIRCjump(CIRCjump::BuildNotCondition(cjump->relop),
          cjump->left, cjump->right, cjump->ifTrue, cjump->ifFalse), result);
      len--;
    } else if (blockSequence[resultVector[i]].isNoConditions) {
      const CIRCjump* cjump = dynamic_cast<const CIRCjump*>(blockSequence[resultVector[i]].stms[len - 1]);
      const CLabel* tLabel = new CLabel("TempCJumpLabel");
      CIRCjump* newHead = new CIRCjump(cjump->relop, cjump->left, cjump->right, cjump->ifTrue, tLabel);
      result = new CIRSeq(new CIRLabel(tLabel),
        new CIRSeq(new CIRJump(cjump->ifFalse), result));
      result = new CIRSeq(newHead, result);
      len--;
    }
    for (int j = len - 1; j >= 0; j--) {
      result = new CIRSeq(blockSequence[resultVector[i]].stms[j], result);
    }
  }

  CIRSeq* noEdgeLabels = const_cast<CIRSeq*>(dynamic_cast<const CIRSeq*>(result->right));
  noEdgeLabels->PopBack();
  return noEdgeLabels;
}

void CTracer::findBlocks(const CIRSeq* list) {
  for (const CIRSeq* curVertex = list; curVertex; ) {
    const CIRLabel* label = dynamic_cast<const CIRLabel*>(curVertex->left);
    blockSequence.push_back(CBlock());
    int last = blockSequence.size() - 1;

    if (label) {
      blockSequence[last].rootLabel = label->label->Name();
      blockSequence[last].stms.push_back(curVertex->left);
      curVertex = static_cast<const CIRSeq*>(curVertex->right);
    } else {
      std::string newLabelName("RandomLabel" + std::to_string(std::rand()));
      blockSequence[last].stms.push_back(new CIRLabel(new CLabel(newLabelName)));
      blockSequence[last].rootLabel = newLabelName;
    }

    while (true) {
      if (curVertex && (dynamic_cast<const CIRJump*>(curVertex->left) ||
        dynamic_cast<const CIRCjump*>(curVertex->left))) {
        blockSequence[last].stms.push_back(curVertex->left);
        curVertex = static_cast<const CIRSeq*>(curVertex->right);
        break;
      } else if (curVertex && dynamic_cast<const CIRLabel*>(curVertex->left)) {
        blockSequence[last].stms.push_back(new CIRJump(dynamic_cast<const CIRLabel*>(curVertex->left)->label));
        break;
      } else if (!curVertex || !curVertex->left) {
        blockSequence[last].stms.push_back(new CIRJump(doneLabel));
        break;
      } else {
        blockSequence[last].stms.push_back(curVertex->left);
        curVertex = static_cast<const CIRSeq*>(curVertex->right);
      }
    }
  }
}

void CTracer::dfs(int blockId, std::vector<int>& used) {
  resultVector.push_back(blockId);
  used[blockId] = true;
  int lastStmtId = blockSequence[blockId].stms.size() - 1;
  const IIRStm* lastCur = blockSequence[blockId].stms[lastStmtId];
  const CIRJump* jump = dynamic_cast<const CIRJump*>(lastCur);
  const CIRCjump* cjump = dynamic_cast<const CIRCjump*>(lastCur);
  if (jump) {
    auto targetIter = labelMap.find(dynamic_cast<const CLabel*>(jump->label));
    if (targetIter == labelMap.end()) {
      return;
    }
    int targetId = targetIter->second;
    if (!used[targetId]) {
      dfs(targetId, used);
    }
  } else if (cjump) {
    auto falseIter = labelMap.find(dynamic_cast<const CLabel*>(cjump->ifFalse));
    auto trueIter = labelMap.find(dynamic_cast<const CLabel*>(cjump->ifTrue));
    if (falseIter == labelMap.end() || trueIter == labelMap.end()) {
      assert(false);
    } else {
      if (!used[falseIter->second]) {
        dfs(falseIter->second, used);
      } else if (!used[trueIter->second]) {
        blockSequence[blockId].isInverted = true;
        dfs(trueIter->second, used);
      } else {
        blockSequence[blockId].isNoConditions = true;
      }
    }
  } else {
    assert(false);
  }
}

void CTracer::sortBlocks() {
  std::vector< int > used(blockSequence.size(), 0);

  for (int i = 0; i < blockSequence.size(); i++) {
    auto value = dynamic_cast<const CIRLabel*>(blockSequence[i].stms[0])->label;
    labelMap.insert(std::make_pair(value, i));
  }

  for (int i = 0; i < blockSequence.size(); i++) {
    if (!used[i]) {
      dfs(i, used);
    }
  }
}