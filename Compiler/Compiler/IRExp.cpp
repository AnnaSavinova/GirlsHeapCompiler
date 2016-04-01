#include "IRExp.h"

CIRExp::~CIRExp()
{}

CIRExp::CIRExp( const IIRExp* _exp ) : exp(_exp)
{}

const CIRExpList * CIRExp::Kids() const
{
    return new CIRExpList(exp, nullptr);
}

const IIRStm * CIRExp::Build(const CIRExpList* kids) const
{
    return kids ? new CIRExp(kids->head) : nullptr;
}
