#pragma once
#include "common.h"
#include "Instruction.h"
#include "Frame.h"
#include <set>

namespace CodeGeneration {
    // ������� �����
    struct CNode
    {
        // �������� �����
        std::vector<int> in;
        // ��������� �����
        std::vector<int> out;
    };


    // ����
    class CGraph
    {
    public:
        explicit CGraph( int size );

        // �������� ����� � ���� �� ������� from � ������� to
        void AddEdge( int from, int to );

        // ���������� ������ � �����
        int Size() const;

        // �������� �������
        const CNode& GetNode( int index ) const;

    protected:
        // ���� �����
        // ��� ���������� � ������ �������� ������ ������
        std::vector<CNode> nodes;
    };


    // ���� ������ ����������
    class CWorkFlowGraph : public CGraph
    {
    public:
        // �����������
        // ��������� �� ���� map ��� ���� - ��� ������� � �������� - ������ ������������ ������
        explicit CWorkFlowGraph( const std::list<IInstruction*>& asmFunction );

    private:
        // ������������ ����� ������� � ��������� �����
        std::map<std::string, int> labels;

        void buildLabelMap( const std::list< IInstruction*>& asmFunction );
        void addEdges( const std::list< IInstruction*>& asmFunction );
    };


    // ���� �������� live-in live-out 
    class CLiveInOutCalculator
    {
    public:
        // �����������
        // ��������� �� ���� map ��� ���� - ��� ������� � �������� - ������ ������������ ������
        explicit CLiveInOutCalculator( const std::list<IInstruction*>& asmFunction );

        // �������� ������ live-in ���������� ��� ��������� �������/����������
        const std::set<std::string>& GetLiveIn( int nodeIndex ) const;

        // �������� ������ live-out ���������� ��� ��������� �������/����������
        const std::set<std::string>& GetLiveOut( int nodeIndex ) const;

        // �������� ������ ����������� ���������� ��� ��������� �������/����������
        const std::set<std::string>& GetDefines( int nodeIndex ) const;

        const std::set<std::string>& GetUses( int nodeIndex ) const;

    private:
        // ���� ������ ����������
        CWorkFlowGraph workflow;

        // ��������� live-in � live-out ���������� ��� ������ �� ������ �����
        std::vector<std::set<std::string>> liveIn;
        std::vector<std::set<std::string>> liveOut;

        // ��������� defines � uses
        std::vector<std::set<std::string>> defines;
        std::vector<std::set<std::string>> uses;

        // ������ � ������������� ���������
        std::vector<IInstruction*> commands;

        bool theSame( const std::set<std::string>& x, const std::set<std::string>& y ) const;
        void buildCommands( const std::list<IInstruction*>& asmFunction );
        void buildDefines( const std::list<IInstruction*>& asmFunction );
        void buildUses( const std::list<IInstruction*>& asmFunction );
    };

    class CPrologEpilogBuilder {
    public:
        CPrologEpilogBuilder( std::list<IInstruction*> _instructions );

        std::list<IInstruction*> AddPrologAndEpilog( CFrame* frame );
    private:
        void addEpilog( CFrame* frame );
        void addProlog( CFrame* frame );
        std::list<IInstruction*> instructions;
    };
} // namespace CodeGeneration