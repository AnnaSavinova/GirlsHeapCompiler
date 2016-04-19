#pragma once
#include "common.h"

class CIRSeq : public IIRStm {
public:
    CIRSeq( const IIRStm* _left, const IIRStm* _right ) : left( _left ), right( _right ) {};
    const CIRExpList* Kids() const;
    const IIRStm* Build( const CIRExpList* ) const;
    CIRSeq( std::list<IIRStm*> list );
    ~CIRSeq();
    virtual void Accept( CIRTreePrettyVisitor* printer ) const
    {
        printer->Visit( this );
    }

    void PopBack()
    {
      CIRSeq* lastLastVertex = 0;
      CIRSeq* lastVertex = this;
      CIRSeq* curVertex = const_cast<CIRSeq*>(dynamic_cast<const CIRSeq*>(right));
      while (curVertex) {
        lastLastVertex = lastVertex;
        lastVertex = curVertex;
        curVertex = const_cast<CIRSeq*>(dynamic_cast<const CIRSeq*>(curVertex->right));
      }
      lastLastVertex->right = nullptr;
    }

    const IIRStm* left;
    const IIRStm* right;
};

