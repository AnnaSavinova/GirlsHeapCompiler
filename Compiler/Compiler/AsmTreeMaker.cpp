#include "AsmTreeMaker.h"

namespace CodeGeneration
{
    void CAsmTreeMaker::InitializeTree( const CIRSeq * cmdList ) const
    {
        const CIRSeq* next = cmdList;
        while( next != 0 ) {
            munchStm( next->left );
            next = dynamic_cast<const CIRSeq*>( next->right );
        }
    }
}
