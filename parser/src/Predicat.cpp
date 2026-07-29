#include "Predicat.h"

Predicat::Predicat()
{
    //ctor
}

Predicat::~Predicat()
{
    //dtor
}

Predicat *Predicat::Copy()
{
  Predicat *r=new Predicat();
  r->Axiom=Axiom->Copy();
  return r;
}

string Predicat::ToAlgebre()
{
  return Axiom->ToString();
}

Predicat *Predicat::And(Predicat *l, Predicat *r1)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otAnd;
  ((NodeOperator2 *)(r->Axiom))->left=l->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=r1->Axiom->Copy();
  return r;
}

Predicat *Predicat::Or(Predicat *l, Predicat *r1)
{
  Predicat *r=new Predicat();
  r->Axiom=new NodeOperator2();
  ((NodeOperator2 *)(r->Axiom))->op=otOr;
  ((NodeOperator2 *)(r->Axiom))->left=l->Axiom->Copy();
  ((NodeOperator2 *)(r->Axiom))->right=r1->Axiom->Copy();
  return r;
}
