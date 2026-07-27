#include "Node.h"


NodeTerminal::NodeTerminal()
{
  ident="";
  nodeType=ntTerminal;
}

NodeTerminal::~NodeTerminal()
{

}

NodeFunction::NodeFunction()
{
  ident="";
  nodeType=ntFunction;
}

NodeFunction::~NodeFunction()
{
}

NodeOperator2::NodeOperator2()
{
  left=NULL;
  right=NULL;
  nodeType=ntOperator2;
}

NodeOperator2::~NodeOperator2()
{
  if (left)
    delete left;
  if (right)
    delete right;
}

NodeOperator1::NodeOperator1()
{
  node=NULL;
  nodeType=ntOperator1;
}

NodeOperator1::~NodeOperator1()
{
  if (node)
    delete node;
}

Node *NodeTerminal::Copy()
{
  NodeTerminal *r=new NodeTerminal();
  r->ident=ident;
  return r;
}

Node *NodeFunction::Copy()
{
  NodeFunction *r=new NodeFunction();
  r->ident=ident;
  for (size_t i=0; i<params.size(); i++)
    r->params.push_back(params[i]->Copy());
  return r;
}

Node *NodeOperator2::Copy()
{
  NodeOperator2 *r=new NodeOperator2();
  r->op=op;
  r->left=left->Copy();
  r->right=right->Copy();
  return r;
}

Node *NodeOperator1::Copy()
{
  NodeOperator1 *r=new NodeOperator1();
  r->op=op;
  r->node=node->Copy();
  return r;
}





