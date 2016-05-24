#pragma once
#include "common.h"
#include "Temp.h"

namespace CodeGeneration
{
    class IInstruction {
    public:
        std::string AsmCode;
        virtual const CTempList* UsedVars() const = 0;
        virtual const CTempList* DefinedVars() const = 0;
        virtual const CLabelList* JumpTargets() const = 0;
        virtual std::string Format() const = 0;
        virtual std::string Format( const std::map<std::string, std::string> varsMapping ) const = 0;
        IInstruction() {}
        ~IInstruction() {}
    };

    class COperAsm : public IInstruction {
    public:
        COperAsm( std::string _assem, const CTempList* _dst, const CTempList* _src,
            CLabelList* _jump ) : dst( _dst ), src( _src ), jump( _jump )
        {
            AsmCode = _assem;
        }

        COperAsm( std::string _assem, const CTempList* _dst, const CTempList* _src ) :
            dst( _dst ), src( _src ), jump( nullptr )
        {
            AsmCode = _assem;
        }

        std::string GetOperator() const { 
            return AsmCode.substr( 0, AsmCode.find( ' ' ) ); 
        }

        const CTempList* UsedVars() const
        {
            return src;
        }

        const CTempList* DefinedVars() const
        {
            return dst;
        }

        const CLabelList* JumpTargets() const
        {
            return jump;
        }

        std::string Format() const
        {
            std::string comment = AsmCode;
            CTempList* curr = const_cast<CTempList*>( dst );
            int index = 0;
            while( curr != 0 ) {
                std::string toReplace = "'d" + std::to_string( index );
                while( comment.find( toReplace ) != std::string::npos ) {
                    comment.replace( comment.find( toReplace ), toReplace.length(), curr->GetHead()->Name() );
                }
                curr = const_cast< CTempList* >( curr->GetTail() );
                ++index;
            }
            curr = const_cast<CTempList*>( src );
            index = 0;
            while( curr != 0 ) {
                std::string toReplace = "'s" + std::to_string( index );
                while( comment.find( toReplace ) != std::string::npos ) {
                    comment.replace( comment.find( toReplace ), toReplace.length(), curr->GetHead()->Name() );
                }
                curr = const_cast< CTempList* >( curr->GetTail() );
                ++index;
            }
            CLabelList* lbl = jump;
            index = 0;
            while( lbl != 0 ) {
                std::string toReplace = "'l" + std::to_string( index );
                while( comment.find( toReplace ) != std::string::npos ) {
                    comment.replace( comment.find( toReplace ), toReplace.length(), lbl->GetHead()->Name() );
                }
                lbl = const_cast< CLabelList * > ( lbl->GetTail() );
                ++index;
            }

            if( comment.find( "\n" ) != std::string::npos ) {
                comment.replace( comment.find( "\n" ), 1, "" );
            }

            comment += ";";
            return comment;
        }

        std::string Format( const std::map<std::string, std::string> varsMapping ) const
        {
            std::string res = AsmCode;
            std::string comment = AsmCode;
            CTempList* curr = const_cast<CTempList*>( dst );
            int index = 0;
            while( curr != 0 ) {
                std::string toReplace = "'d" + std::to_string( index );
                while( res.find( toReplace ) != std::string::npos ) {
                    res.replace( res.find( toReplace ), toReplace.length(), varsMapping.find( curr->GetHead()->Name() )->second );
                    comment.replace( comment.find( toReplace ), toReplace.length(), curr->GetHead()->Name() );
                }
                curr = const_cast< CTempList* >( curr->GetTail() );
                ++index;
            }
            curr = const_cast<CTempList*>(src);
            index = 0;
            while( curr != 0 ) {
                std::string toReplace = "'s" + std::to_string( index );
                while( res.find( toReplace ) != std::string::npos ) {
                    res.replace( res.find( toReplace ), toReplace.length(), varsMapping.find( curr->GetHead()->Name() )->second );
                    comment.replace( comment.find( toReplace ), toReplace.length(), curr->GetHead()->Name() );
                }
                curr = const_cast< CTempList* >( curr->GetTail() );
                ++index;
            }
            CLabelList* lbl = jump;
            index = 0;
            while( lbl != 0 ) {
                std::string toReplace = "'l" + std::to_string( index );
                while( res.find( toReplace ) != std::string::npos ) {
                    res.replace( res.find( toReplace ), toReplace.length(), lbl->GetHead()->Name() );
                    comment.replace( comment.find( toReplace ), toReplace.length(), lbl->GetHead()->Name() );
                }
                lbl = const_cast< CLabelList * > ( lbl->GetTail() );
                ++index;
            }
            res[res.length() - 1] = ' ';
            res = res + "; \t" + comment;
            return res;
        }
    private:
        const CTempList* dst;
        const CTempList* src;
        CLabelList* jump;
    };

    class CMoveAsm : public COperAsm {
    public:
        CMoveAsm( std::string _assem, const CTemp* _dst, const CTemp* _src ) :
            COperAsm( _assem, new CTempList( _dst, nullptr ), new CTempList( _src, nullptr ), nullptr )
        {};
        CMoveAsm( std::string _assem, const CTempList* _dst, const CTempList* _src ) :
            COperAsm( _assem, _dst, _src, nullptr )
        {};
    };

    class CLabelAsm : public IInstruction {
    public:
        CLabelAsm( const CLabel* _label, std::string _assem = "" ) : label( _label )
        {
            AsmCode = _assem;
        }

        CTempList* UsedVars() const
        {
            return nullptr;
        }

        CTempList* DefinedVars() const
        {
            return nullptr;
        }

        CLabelList* JumpTargets() const
        {
            return new CLabelList( label, nullptr );
        }

        std::string Format() const
        {
            return label->Name() + ":\n";
        }

        std::string Format( const std::map<std::string, std::string> varsMapping ) const
        {
            return label->Name() + ":\n";
        }

    private:
        const CLabel* label;
    };

} // namespace CodeGeneration

