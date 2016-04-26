#pragma once
#include "common.h"
#include "Temp.h"

namespace CodeGeneration {
    class IInstruction
    {
    public:
        std::string AsmCode;
        virtual CTempList* UsedVars() const = 0;
        virtual CTempList* DefindedVars() const = 0;
        virtual CLabelList* JumpTargets() const = 0;
        virtual std::string Format( const std::map<std::string, std::string> varsMapping ) const = 0;
        IInstruction() {}
        ~IInstruction() {}
    };

    class COperAsm : public IInstruction
    {
    public:
        COperAsm( std::string _assem, CTempList* _dst, CTempList* _src,
            CLabelList* _jump ) : dst( _dst ), src( _src ), jump( _jump )
        {
            AsmCode = _assem;
        }

        COperAsm( std::string _assem, CTempList* _dst, CTempList* _src ) :
            dst( _dst ), src( _src ), jump( nullptr )
        {
            AsmCode = _assem;
        }

        CTempList* UsedVars() const
        {
            return src;
        }

        CTempList* DefindedVars() const
        {
            return dst;
        }

        CLabelList* JumpTargets() const
        {
            return jump;
        }

        std::string Format( const std::map<std::string, std::string> varsMapping )
        {
          std::string res = AsmCode;
          std::string comment = AsmCode;
          auto curr = dst;
          int index = 0;
          while (curr != 0) {
            std::string toReplace = "'d" + std::to_string(index);
            while (res.find(toReplace) != std::string::npos) {
              res.replace(res.find(toReplace), toReplace.length(), varsMapping.find(curr->getHead()->Name())->second);
              comment.replace(comment.find(toReplace), toReplace.length(), curr->getHead()->Name());
            }
            curr = curr->getTail();
            ++index;
          }
          curr = src;
          index = 0;
          while (curr != 0) {
            std::string toReplace = "'s" + std::to_string(index);
            while (res.find(toReplace) != std::string::npos) {
              res.replace(res.find(toReplace), toReplace.length(), varsMapping.find(curr->getHead()->Name())->second);
              comment.replace(comment.find(toReplace), toReplace.length(), curr->getHead()->Name());
            }
            curr = curr->getTail();
            ++index;
          }
          auto lbl = jump;
          index = 0;
          while (lbl != 0) {
            std::string toReplace = "'l" + std::to_string(index);
            while (res.find(toReplace) != std::string::npos) {
              res.replace(res.find(toReplace), toReplace.length(), lbl->getHead()->Name());
              comment.replace(comment.find(toReplace), toReplace.length(), lbl->getHead()->Name());
            }
            lbl = lbl->getTail();
            ++index;
          }
          res[res.length() - 1] = ' ';
          res = res + "; \t" + comment;
          return res;
        }
    private:
        CTempList* dst;
        CTempList* src;
        CLabelList* jump;
    };

    class CMoveAsm : public COperAsm
    {
    public:
        CMoveAsm( std::string _assem, CTemp* _dst, CTemp* _src ) : 
            COperAsm( _assem, new CTempList( _dst, nullptr ), new CTempList( _src, nullptr ), nullptr )
        {};
    };

    class CLabelAsm : public IInstruction
    {
    public:
        CLabelAsm( std::string _assem, CLabel* _label ) : label( _label )
        {
            AsmCode = _assem;
        }

        CTempList* UsedVars() const
        {
            throw std::logic_error( "LabelAsm shouldn't have usedVars" );
        }

        CTempList* DefindedVars() const
        {
            throw std::logic_error( "LabelAsm shouldn't have definedVars" );
        }

        CLabelList* JumpTargets() const
        {
            return new CLabelList( label, nullptr );
        }

        std::string Format( const std::map<std::string, std::string> varsMapping )
        {
            return label->Name() + ":\n";
        }

    private:
        CLabel* label;
    };

} // namespace CodeGeneration

