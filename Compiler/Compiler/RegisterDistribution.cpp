#include "RegisterDistribution.h"

#include <assert.h>
#include <iostream>

namespace CodeGeneration {

    CInterferenceGraph::CInterferenceGraph( const std::list<const IInstruction*>& _asmFunction,
        const std::vector<const std::string>& registers ) : asmFunction( _asmFunction ), liveInOut( asmFunction ),
        registers( registers )
    {
        do {
            std::cerr << asmFunction.size() << std::endl;
            int cmdIndex = 0;
            if( !uncoloredNodes.empty() ) {
                std::cout << "REGENERATING!!!" << std::endl;
                regenerateCode();
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
                if( dynamic_cast< const CMoveAsm* >(cmd) == nullptr ) {
                    // ��� ������ �� move ���������� �������� ����� ����� ����� ������ ����������� a � b
                    // ��� a ����������� ������������ � ������ ���������� ����������
                    // b - �� ��������� liveOut
                    for( auto a : liveInOut.GetDefines( cmdIndex ) ) {
                        for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
                            addNode( a );
                            addNode( b );
                            addEdge( a, b );
                        }
                    }
                } else {
                    // ��� ������ move ���������� �������� ����� ����� ����� ������ ����������� a � b
                    // ��� a - ���� �������� MOVE (c->a)
                    // b �� ��������� liveOut
                    std::string a = dynamic_cast< const CMoveAsm* >(cmd)->DefinedVars()->GetHead()->Name();
                    for( auto b : liveInOut.GetLiveOut( cmdIndex ) ) {
                        addNode( a );
                        addNode( b );
                        addEdge( a, b );
                    }
                    if( dynamic_cast< const CMoveAsm* >(cmd)->UsedVars() != nullptr ) {
                        std::string b = dynamic_cast< const CMoveAsm* >(cmd)->UsedVars()->GetHead()->Name();
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


    // ��������� ������� � ����, ���� ������� ��� ���
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


    // ��������� move-����� � ����
    void CInterferenceGraph::addMoveEdge( const std::string& from, const std::string& to )
    {
        int u = nodeMap[from];
        int v = nodeMap[to];
        if( u == v ) {
            return;
        }
        // MOVE-����� ����������� ������ �����, ����� �� ���� �������� ����� ����� ����� ���������
        if( edges[u][v] == ET_NoEdge ) {
            edges[u][v] = ET_MoveEdge;
            edges[v][u] = ET_MoveEdge;
        }
    }


    // ��������� ������� ����������� � ����
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


    // ���������� ����
    bool CInterferenceGraph::paint()
    {
        addRegisterColors();
        while( hasNonColoredNonStackedNodes() ) {
            int node = getColorableNode();
            if( node == -1 ) {
                node = getMaxInterferingNode();
                uncoloredNodes.insert( node );
            }
            pulledNodes.push( node );
            nodes[node].InStack = true;
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


    // ������ �������, ��������������� ���������
    void CInterferenceGraph::addRegisterColors()
    {
        for( int i = 0; i < registers.size(); ++i ) {
            auto regNode = nodeMap.find( registers[i] );
            if( regNode != nodeMap.end() ) {
                // ���� � ����� ���� �������, ��������������� ����� ��������, 
                // �� ��� ������ ���� ��������� �� ������� ��������� ��������� ��������
                nodes[regNode->second].Color = i;
            }
        }

        for( auto it : nodeMap ) {
            if( it.first.substr( it.first.length() - 3 ) == "_SP" ) {
                // ������ �������� � ESP
                nodes[it.second].Color = 6;
            }
            if( it.first.substr( it.first.length() - 3 ) == "_FP" ) {
                // ������ �������� � EBP
                nodes[it.second].Color = 7;
            }
            if( it.first.substr( it.first.length() - 3 ) == "_RV" ) {
                // ������ �������� � EDI
                nodes[it.second].Color = 5;
            }
        }
    }


    // �������� �� � ����� �������, ������� �� �������� � ����
    // � �� ����� ����
    bool CInterferenceGraph::hasNonColoredNonStackedNodes() const
    {
        for( int i = 0; i < nodes.size(); ++i ) {
            if( nodes[i].Color == -1 && !nodes[i].InStack ) {
                return true;
            }
        }
        return false;
    }


    // ����� �������, ������� � ������ ������ �������� ���������
    // ��� -1 ���� ����� ������� � ����� ���
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


    // ����� ������� � ���������� ���-��� �������
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


    // ���-�� ������� � ������� �������
    // �� ��������� �������, ������������� �� �����
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


    // ���������������� ���, ����� ��������� ���������
    void CInterferenceGraph::regenerateCode()
    {
        std::list<const IInstruction*> newCode;
        for( auto it : asmFunction ) {
            if( it->UsedVars() != nullptr  &&  it->UsedVars()->GetHead() != nullptr  &&
                nodeMap.find( it->UsedVars()->GetHead()->Name() ) != nodeMap.end() ) {
                int varIndex = nodeMap.find( it->UsedVars()->GetHead()->Name() )->second;
                if( uncoloredNodes.find( varIndex ) != uncoloredNodes.end() ) {
                    bool isMove = false;
                    if( dynamic_cast< const CodeGeneration::CMoveAsm* >(it) != nullptr ) {
                        isMove = true;
                    }
                    CTemp* buff = new CTemp();
                    newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", new CTempList( buff, nullptr ), it->UsedVars() ) );
                    if( isMove ) {
                        newCode.push_back( new CodeGeneration::CMoveAsm( "mov 'd0, 's0\n", it->DefinedVars(), new CTempList( buff, nullptr ) ) );
                    } else {
                        const COperAsm* cmd = dynamic_cast< const COperAsm* >(it);
                        newCode.push_back( new COperAsm( cmd->GetOperator() + " 's0\n", it->DefinedVars(), new CTempList( buff, 0 ) ) );
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
                    const CodeGeneration::CMoveAsm* cmd = dynamic_cast< const CodeGeneration::CMoveAsm* >(it);
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


    const std::list<const IInstruction*>& CInterferenceGraph::GetCode() const
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