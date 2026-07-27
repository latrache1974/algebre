#include "Parameters.h"

Parameters::Parameters()
{
}

Parameters::~Parameters()
{
}

void Parameters::Add(string t,string  n)
{
  Parameter *p=new Parameter();
  p->ident=n;
  p->type=t;
  Items.push_back(p);
}

Parameters *Parameters::Copy()
{
  Parameters *r=new Parameters();
  for(size_t i=0; i<Items.size(); i++)
    r->Items.push_back(Items[i]->Copy());
  return r;
}

Parameter *Parameter::Copy()
{
  Parameter *r= new Parameter();
  r->ident=ident;
  r->type=type;
  return r;
}
