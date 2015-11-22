#include "IIRStm.h"

CIRStmList::CIRStmList(IIRStm * head, CIRStmList * tail)
{
    stmList = tail->GetStmList();
    stmList.push_front(*head);
}

std::list<IIRStm> CIRStmList::GetStmList()
{
  return stmList;
}
