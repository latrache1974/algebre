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
