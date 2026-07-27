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
