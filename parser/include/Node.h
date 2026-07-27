#ifndef NODE_H
#define NODE_H
using namespace std;
#include<string>
#include<vector>

enum NodeType { ntTerminal, ntFunction, ntOperator1 , ntOperator2};
enum OperatorType1 { otNot};
enum OperatorType2 { otAnd, otOr, otXor, otEq, otNeq};

class Node
{
    public:
        NodeType nodeType;
        virtual ~Node() = default;
        virtual Node *Copy()=0;
        virtual string ToString()=0;
    protected:

    private:
};
typedef Node *PNode;
typedef vector<PNode> Nodes;

class NodeTerminal : public Node
{
    public:
        string ident;
        NodeTerminal();
        virtual ~NodeTerminal();
        Node *Copy() override;
        string ToString() override;
    protected:

    private:
};

class NodeFunction : public Node
{
    public:
        string ident;
        Nodes params;
        NodeFunction();
        virtual ~NodeFunction();
        Node *Copy() override;
        string ToString() override;
    protected:

    private:
};

class NodeOperator2 : public Node
{
    public:
        OperatorType2 op;
        Node *left, *right;
        NodeOperator2();
        virtual ~NodeOperator2();
        Node *Copy() override;
        string ToString() override;
    protected:

    private:
};

class NodeOperator1 : public Node
{
    public:
        OperatorType1 op;
        Node *node;
        NodeOperator1();
        virtual ~NodeOperator1();
        Node *Copy() override;
        string ToString() override;
    protected:

    private:
};

#endif // NODE_H
