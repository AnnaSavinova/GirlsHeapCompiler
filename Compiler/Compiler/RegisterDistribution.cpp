#include "RegisterDistribution.h"

#include <assert.h>
#include <iostream>

namespace CodeGeneration
{

    CInterferenceGraph::CInterferenceGraph( const std::list<IInstruction*>& _asmFunction,
        const std::vector<std::string>& registers ) : asmFunction( _asmFunction ), liveInOut( asmFunction ),
        registers( registers )
    {
        do {
            std::cerr << asmFunction.size() << std::endl;
            int cmdIndex = 0;
            if( !uncoloredNodes.empty() ) {
                std::cout << "REGENERATING!!!" << std::endl;
                
                regenerateCode();
                /*for( auto cmd : asmFunction ) {
                    std::cout << cmd->AsmCode;
                }*/
                uncoloredNodes.clear();
                edges.clear();
                nodes.clear();
                nodeMap.clear();
                while( !pulledNodes.empty() ) {
                    pulledNodes.pop();
                }
                liveInOut = CLiveInOutCalculator( asmFunction );
            }
            for( auto cmd : asmFunction ) {
                if( dynamic_cast< CMoveAsm* >( cmd ) == nullptr ) {

                    //At any non-move instruction that defines a variable a, where the live-out variables are
                    //    b1, …, bj, add interference edges( a, b1 ), …, (a, bj).

                    /*auto definedVars = dynamic_cast< CMoveAsm* >(cmd)->DefinedVars();
                    while( definedVars->GetHead() != nullptr ) {
                        std::string a = definedVars->GetHead()->Name();
                        for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
                            addNode( a );
                            addNode( b );
                            addEdge( a, b );
                        }
                        definedVars = definedVars->GetTail();
                    }*/

                    // для каждой не move инструкции добавить ребра между всеми такими переменными a и b
                    // где a принадлежит определяемым в данной инструкции переменным
                    // b - из множества liveOut
                    for( auto a : liveInOut.GetDefines( cmdIndex ) ) {
                        for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
                            addNode( a );
                            addNode( b );
                            addEdge( a, b );
                        }
                    }
                } else {
                    // для каждой move инструкции добавить ребра между всеми такими переменными a и b
                    // где a - куда делается MOVE (c->a)
                    // b из множества liveOut

                    //At a move instruction a ? c, where variables b1, …, bj are live-out, add interference
                    //    edges( a, b1 ), …, (a, bj) for any bi that is not the same as c.
                    std::string a = dynamic_cast< CMoveAsm* >( cmd )->DefinedVars()->GetHead()->Name();
                    for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
                        addNode( a );
                        addNode( b );
                        addEdge( a, b );
                    }

                    const CMoveAsm* moveInst = dynamic_cast< const CMoveAsm* >( cmd );

                    if( moveInst != nullptr && moveInst->UsedVars() != nullptr && moveInst->UsedVars()->GetHead() != nullptr ) {
                        std::string b = moveInst->UsedVars()->GetHead()->Name();
                        addNode( a );
                        addNode( b );
                        addMoveEdge( a, b );
                    }
                }
                for( auto a : liveInOut.GetDefines( cmdIndex ) ) {
                    addNode( a );
                }
                for( auto a : liveInOut.GetUses( cmdIndex ) ) {
                    addNode( a );
                }
                ++cmdIndex;
            }
        } while( !paint() );
    }


    // добавляет вершину в граф, если таковой еще нет
    void CInterferenceGraph::addNode( const std::string& name )
    {
        if( nodeMap.find( name ) != nodeMap.end() ) {
            return;
        }
        nodeMap.insert( std::make_pair( name, nodes.size() ) );
        nodes.emplace_back();
        for( int i = 0; i < edges.size(); ++i ) {
            edges[i].push_back( ET_NoEdge );
        }
        edges.emplace_back( nodes.size(), ET_NoEdge );
    }


    // добавляет move-ребро в граф
    void CInterferenceGraph::addMoveEdge( const std::string& from, const std::string& to )
    {
        int u = nodeMap[from];
        int v = nodeMap[to];
        if( u == v ) {
            return;
        }
        // MOVE-ребро добавляется только тогда, когда не было никакого ребра между этими вершинами
        if( edges[u][v] == ET_NoEdge ) {
            edges[u][v] = ET_MoveEdge;
            edges[v][u] = ET_MoveEdge;
        }
    }


    // добавляет простую зависимость в граф
    void CInterferenceGraph::addEdge( const std::string& from, const std::string& to )
    {
        int u = nodeMap[from];
        int v = nodeMap[to];
        if( u == v ) {
            return;
        }
        edges[u][v] = ET_Edge;
        edges[v][u] = ET_Edge;
    }


    // раскрасить граф
    bool CInterferenceGraph::paint()
    {
        addRegisterColors();
        // похоже на Simplify
        while( hasNonColoredNonStackedNodes() ) {
            // берем вершину с не более чем k соседями
            int node = getColorableNode();
            // если нет таких, то кладем в стек, помечая, как потенциального кандидата
            if( node == -1 ) {
                node = getMaxInterferingNode();
                uncoloredNodes.insert( node );
            }
            // кладем в стек
            pulledNodes.push( node );
            nodes[node].InStack = true;
        }
        // для потенциальных кандидатов
        if( !uncoloredNodes.empty() ) {
            // проверяем всех соседей..?
            //int currNode = uncoloredNodes.top();

        }
        if( !uncoloredNodes.empty() ) {
            return false;
        }
        while( !pulledNodes.empty() ) {
            int currNode = pulledNodes.top();
            pulledNodes.pop();
            std::vector<char> usedColors( registers.size(), 0 );
            for( int i = 0; i < nodes.size(); ++i ) {
                if( edges[currNode][i] != ET_NoEdge  &&  nodes[i].Color != -1 && nodes[i].Color < usedColors.size() ) {
                    usedColors[nodes[i].Color] = 1;
                }
            }
            for( int i = 0; i < usedColors.size(); ++i ) {
                if( !usedColors[i] ) {
                    nodes[currNode].Color = i;
                    break;
                }
            }
        }
        return true;
    }


    // красит вершины, соответствующие регистрам
    void CInterferenceGraph::addRegisterColors()
    {
        for( int i = 0; i < registers.size(); ++i ) {
            auto regNode = nodeMap.find( registers[i] );
            if( regNode != nodeMap.end() ) {
                // если в графе есть вершина, соответствующая этому регистру, 
                // то она должна быть покрашена до запуска основного алгоритма покраски
                nodes[regNode->second].Color = i;
            }
        }

        for( auto it : nodeMap ) {
            if( it.first.length() > 11 ) {
                if( it.first.substr( it.first.length() - 11 ) == "thisPointer" ) {
                    // красим насильно в ESP
                    nodes[it.second].Color = 6;
                }
                if( it.first.substr( it.first.length() - 12 ) == "framePointer" ) {
                    // красим насильно в EBP
                    nodes[it.second].Color = 7;
                }
                if( it.first.substr( it.first.length() - 11 ) == "returnValue" ) {
                    // красим насильно в EDI
                    nodes[it.second].Color = 5;
                }
            }
        }
    }


    // остались ли в графе вершины, которые не положены в стек
    // и не имеют цвет
    bool CInterferenceGraph::hasNonColoredNonStackedNodes() const
    {
        for( int i = 0; i < nodes.size(); ++i ) {
            if( nodes[i].Color == -1 && !nodes[i].InStack ) {
                return true;
            }
        }
        return false;
    }


    // номер вершины, которую в данный момент возможно покрасить
    // или -1 если такой вершины в графе нет
    int CInterferenceGraph::getColorableNode() const
    {
        int colorsNum = registers.size();

        for( int i = 0; i < edges.size(); ++i ) {
            if( nodes[i].Color == -1 && getNeighbourNum( i ) < colorsNum  &&  !nodes[i].InStack ) {
                return i;
            }
        }

        return -1;
    }


    // номер вершины с наибольшим кол-вом соседей
    int CInterferenceGraph::getMaxInterferingNode() const
    {
        int maxNeighbour = -1;
        int nodeIndex = -1;
        for( int i = 0; i < nodes.size(); ++i ) {
            int currNeighbour = getNeighbourNum( i );
            if( currNeighbour > maxNeighbour  &&  !nodes[i].InStack  &&  nodes[i].Color == -1 ) {
                maxNeighbour = currNeighbour;
                nodeIndex = i;
            }
        }
        return nodeIndex;
    }


    // кол-во соседей у текущей вершины
    // не учитывает вершины, расположенные на стеке
    int CInterferenceGraph::getNeighbourNum( int nodeIndex ) const
    {
        int neighbours = 0;
        for( int i = 0; i < edges[nodeIndex].size(); ++i ) {
            if( edges[nodeIndex][i] != ET_NoEdge  &&  !nodes[i].InStack ) {
                neighbours++;
            }
        }
        return neighbours;
    }


    // перегенерировать код, чтобы появилась раскраска
    void CInterferenceGraph::regenerateCode()
    {
        std::list<IInstruction*> newCode;
        for( auto it : asmFunction ) {
            if( it->UsedVars() != nullptr  &&  it->UsedVars()->GetHead() != nullptr  &&
                nodeMap.find( it->UsedVars()->GetHead()->Name() ) != nodeMap.end() ) {
                int varIndex = nodeMap.find( it->UsedVars()->GetHead()->Name() )->second;
                if( uncoloredNodes.find( varIndex ) != uncoloredNodes.end() ) {
                    bool isMove = false;
                    if( dynamic_cast< CodeGeneration::CMoveAsm* >( it ) != nullptr ) {
                        isMove = true;
                    }
                    CTemp* buff = new CTemp();
                    newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", new CTempList( buff, nullptr ), it->UsedVars() ) );
                    if( isMove ) {
                        newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", it->DefinedVars(), new CTempList( buff, nullptr ) ) );
                    } else {
                        const COperAsm* cmd = dynamic_cast< COperAsm* >( it );
                        newCode.push_back( new COperAsm( cmd->GetOperator() + " 's0\n", it->DefinedVars(), new CTempList( buff, nullptr ) ) );
                    }
                } else {
                    newCode.push_back( it );
                }
            } else {
                newCode.push_back( it );
            }
        }
        asmFunction.swap( newCode );
        newCode.clear();
        for( auto it : asmFunction ) {
            if( it->DefinedVars() != nullptr  &&  it->DefinedVars()->GetHead() != nullptr  &&
                nodeMap.find( it->DefinedVars()->GetHead()->Name() ) != nodeMap.end() ) {
                int varIndex = nodeMap.find( it->DefinedVars()->GetHead()->Name() )->second;
                if( uncoloredNodes.find( varIndex ) != uncoloredNodes.end() ) {
                    const CodeGeneration::CMoveAsm* cmd = dynamic_cast< CodeGeneration::CMoveAsm* >( it );
                    assert( cmd != nullptr );
                    CTemp* buff = new CTemp();
                    newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", new CTempList( buff, 0 ), it->UsedVars() ) );
                    newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", it->DefinedVars(), new CTempList( buff, 0 ) ) );
                } else {
                    newCode.push_back( it );
                }
            } else {
                newCode.push_back( it );
            }
        }
        asmFunction.swap( newCode );
    }


    const std::list<IInstruction*>& CInterferenceGraph::GetCode() const
    {
        return asmFunction;
    }


    std::map<std::string, std::string> CInterferenceGraph::GetColors()
    {
        std::map<std::string, std::string> res;
        registers.push_back( "ESP" );
        registers.push_back( "EBP" );
        for( auto it : nodeMap ) {
            res.insert( std::make_pair( it.first, registers[nodes[it.second].Color] ) );
        }
        registers.pop_back();
        registers.pop_back();
        return res;
    }

} // namespace CodeGeneration