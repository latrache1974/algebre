#include "Predicats.h"

Predicats::Predicats()
{
    //ctor
}

Predicats::~Predicats()
{
    //dtor
}

void Predicats::Add(Predicat *p)
{
  Items.push_back(p);
}

Predicats *Predicats::Copy()
{
  Predicats *r=new Predicats();
  for(size_t i=0; i<Items.size(); i++)
    r->Items.push_back(Items[i]->Copy());
  return r;
}

string Predicats::ToAlgebre()
{
  string r = "";
  for (size_t i = 0; i < Items.size(); i++)
  {
    if (i > 0)
      r += " | ";
    r += Items[i]->ToAlgebre();
  }
  return r;
}
