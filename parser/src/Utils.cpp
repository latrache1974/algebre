#include "Utils.h"

Utils::Utils()
{
    //ctor
}

Utils::~Utils()
{
    //dtor
}

Predicat *Utils::CreateNot(Predicat *n)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator1();
  ((NodeOperator1 *)(r->Axiom))->op=otNot;
  ((NodeOperator1 *)(r->Axiom))->node=n->Axiom->Copy();
  delete n;
  return r;
}

Predicat *Utils::CreateOr(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otOr;
  ((NodeOperator2 *)(r->Axiom))->left=a->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=b->Axiom->Copy();
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateAnd(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otAnd;
  ((NodeOperator2 *)(r->Axiom))->left=a->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=b->Axiom->Copy();
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateXor(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otXor;
  ((NodeOperator2 *)(r->Axiom))->left=a->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=b->Axiom->Copy();
  delete a;
  delete b;
  return r;
}


Predicat *Utils::CreateFunction(string n, Predicats* ps)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeFunction();
  ((NodeFunction *)(r->Axiom))->ident=n;
  for(size_t i=0; i<ps->Items.size(); i++)
    ((NodeFunction *)(r->Axiom))->params.push_back(ps->Items[i]->Axiom->Copy());
  delete ps;
  return r;
}

Predicat *Utils::CreateTerminal(string n)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeTerminal();
  ((NodeTerminal *)(r->Axiom))->ident=n;
  return r;
}

Predicat *Utils::CreateAppartient(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeFunction();
  ((NodeFunction *)(r->Axiom))->ident="in";
  ((NodeFunction *)(r->Axiom))->params.push_back(a->Axiom->Copy());
  ((NodeFunction *)(r->Axiom))->params.push_back(b->Axiom->Copy());
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateRelation(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeFunction();
  ((NodeFunction *)(r->Axiom))->ident="relation";
  ((NodeFunction *)(r->Axiom))->params.push_back(a->Axiom->Copy());
  ((NodeFunction *)(r->Axiom))->params.push_back(b->Axiom->Copy());
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateEq(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otEq;
  ((NodeOperator2 *)(r->Axiom))->left=a->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=b->Axiom->Copy();
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateNEq(Predicat *a, Predicat *b)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otNeq;
  ((NodeOperator2 *)(r->Axiom))->left=a->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=b->Axiom->Copy();
  delete a;
  delete b;
  return r;
}

Predicat *Utils::CreateTrue()
{
  return CreateTerminal("true");
}

Predicat *Utils::CreateFalse()
{
  return CreateTerminal("false");
}

Predicat *Utils::CreateReturn()
{
  return CreateTerminal("return");
}

Predicat *Utils::CreateReturn(Predicats *ps)
{
  return CreateFunction("return", ps);
}

void Utils::PerformeInclude(string filename)
{
    string msg;
    UniverseBase *univ=new UniverseBase();
    univ->Parse(filename, &msg);
    universe->CopyFrom(univ);
    delete univ;
}
