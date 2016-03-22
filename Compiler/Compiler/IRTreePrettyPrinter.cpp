#include "IRTreePrettyPrinter.h"
#include "IRClasses.h"

using namespace std;

void CIRTreePrettyVisitor::Visit( const CIRMove* node )
{
    node->Dst()->Accept( this );
    string destString = lastNodeName;

    node->Src()->Accept( this );
    string srcString = lastNodeName;

    nextNameWithId( "move" );

    treeRepresentation.AddEdge( lastNodeName, destString, "dest" );
    treeRepresentation.AddEdge( lastNodeName, srcString, "src" );
}

void CIRTreePrettyVisitor::Visit( const CIRExp* node )
{
    node->exp->Accept( this );
    string prevString = lastNodeName;

    nextNameWithId( "exp" );
    treeRepresentation.AddEdge( lastNodeName, prevString );
}

void CIRTreePrettyVisitor::Visit( const CIRJump* node )
{
    nextNameWithId( "jump" );
    treeRepresentation.AddEdge( lastNodeName, node->label->Name(), "to_label" );
}

void CIRTreePrettyVisitor::Visit( const CIRCjump* node )
{
    node->right->Accept( this );
    string rightString = lastNodeName;
    node->left->Accept( this );
    string leftString = lastNodeName;

    nextNameWithId( "Cjump" );

    treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
    treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
    treeRepresentation.AddEdge( lastNodeName, node->ifTrue->label->Name(), "iftrue" );
    treeRepresentation.AddEdge( lastNodeName, node->ifFalse->label->Name(), "iffalse" );
}

void CIRTreePrettyVisitor::Visit( const CIRSeq* node )
{
    if( node->left != nullptr ) {
        node->left->Accept( this );
        string leftString = lastNodeName;
        if( node->right != nullptr ) {
            node->right->Accept( this );
            string rightString = lastNodeName;
            nextNameWithId( "seq" );
            treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
            treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
        } else {
            nextNameWithId( "seq" );
            treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
        }
    } else {
        nextNameWithId( "seq" );
    }
}

void CIRTreePrettyVisitor::Visit( const CIRConst* node )
{
    nextNameWithId( string( "const_" ) + to_string( node->value ) );
}

void CIRTreePrettyVisitor::Visit( const CIRName* node )
{
    nextNameWithId( string( "name_" ) + node->label->Name() );
}

void CIRTreePrettyVisitor::Visit( const CIRTemp* node )
{
    nextNameWithId( string( "temp_" ) + node->temp->Name() );
}

void CIRTreePrettyVisitor::Visit( const CIRBinOp* node )
{
    node->left->Accept( this );
    string leftString = lastNodeName;
    node->right->Accept( this );
    string rightString = lastNodeName;
    //graphviz отказывается работать с символами типа + *
    switch( node->operation ) {
        case MUL:
            nextNameWithId( "binop__Mul" );
            break;
        case PLUS:
            nextNameWithId( "binop__Plus" );
            break;
        case DIV:
            nextNameWithId( "binop__Division" );
            break;
        case MINUS:
            nextNameWithId( "binop__Minus" );
            break;
        case XOR:
            nextNameWithId( "binop__Xor" );
            break;
        case LE:
            nextNameWithId( "binop__Less" );
            break;
        case GE:
            nextNameWithId( "binop__Greater" );
            break;
        case AND:
            nextNameWithId( "binop__And" );
            break;
        default:
            assert( false );
            break;
    }
    treeRepresentation.AddEdge( lastNodeName, rightString, "right" );
    treeRepresentation.AddEdge( lastNodeName, leftString, "left" );
}

void CIRTreePrettyVisitor::Visit( const CIRMem* node )
{
    node->exp->Accept( this );
    string prevString = lastNodeName;
    nextNameWithId( "mem" );
    treeRepresentation.AddEdge( lastNodeName, prevString );
}

void CIRTreePrettyVisitor::Visit( const CIRCall* node )
{
    node->func->Accept( this );
    string funcString = lastNodeName;
    node->args->Accept( this );
    string argsString = lastNodeName;
    nextNameWithId( "call" );
    treeRepresentation.AddEdge( lastNodeName, funcString, "func" );
    treeRepresentation.AddEdge( lastNodeName, argsString, "args" );
}

void CIRTreePrettyVisitor::Visit( const CIRESeq* node )
{
    node->stm->Accept( this );
    string stmString = lastNodeName;
    node->exp->Accept( this );
    string expString = lastNodeName;
    nextNameWithId( "eseq" );
    treeRepresentation.AddEdge( lastNodeName, expString, "exp" );
    treeRepresentation.AddEdge( lastNodeName, stmString, "stm" );
}

void CIRTreePrettyVisitor::Visit( const CIRExpList* node )
{
    if( node->head != nullptr ) {
        node->head->Accept( this );
        string headString = lastNodeName;
        if( node->tail != nullptr ) {
            node->tail->Accept( this );
            string tailString = lastNodeName;
            nextNameWithId( "expList" );
            treeRepresentation.AddEdge( lastNodeName, headString, "head" );
            treeRepresentation.AddEdge( lastNodeName, tailString, "tail" );
        } else {
            nextNameWithId( "expList" );
            treeRepresentation.AddEdge( lastNodeName, headString, "head" );
        }
    } else {
        nextNameWithId( "expList" );
    }

}

void CIRTreePrettyVisitor::Visit( const CIRLabel* node )
{
    if( node->label->Name() == "tempLabel1" ) {
        int a = 1;
    }
    nextNameWithId( string( "label:" ) + node->label->Name() );
}

void CIRTreePrettyVisitor::nextNameWithId( std::string label )
{
    lastNodeName = label + string( "__id_" ) + to_string( minId++ );
    treeRepresentation.SetNodeLabel( lastNodeName, label );
}

void CIRTreePrettyVisitor::LinkedVisit( const IIRStm* node )
{
    string fromName = lastNodeName;
    node->Accept( this );
    string toName = lastNodeName;
    if( !fromName.empty() ) {
        treeRepresentation.AddEdge( fromName, toName, "next" );
    }
}

void CIRTreePrettyVisitor::LinkedVisit( const IIRExp* node )
{
    string fromName = lastNodeName;
    node->Accept( this );
    string toName = lastNodeName;
    if( !fromName.empty() ) {
        treeRepresentation.AddEdge( fromName, toName, "next" );
    }
}
