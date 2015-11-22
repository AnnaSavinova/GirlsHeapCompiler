#include "IIRExp.h"
#include "IIRStm.h"

IIRExp::IIRExp()
{
}


IIRExp::~IIRExp()
{
}

CIRExpList::CIRExpList(IIRExp* head, CIRExpList* tail)
{
  expList = tail->GetExpList();
  expList.push_front(*head);
}

CIRExpList::~CIRExpList()
{
}

std::list<IIRExp> CIRExpList::GetExpList()
{
  return expList;
}
