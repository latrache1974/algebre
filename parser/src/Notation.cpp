#include "Notation.h"

Notation::Notation()
{
}

Notation::~Notation()
{
}

Notation *Notation::Copy()
{
  Notation *r=new Notation();
  r->format=format;
  r->params=params->Copy();
  return r;
}
