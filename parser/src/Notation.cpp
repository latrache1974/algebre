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

string Notation::ToAlgebre()
{
  string r = "notation \"" + format + "\"";
  string ns = params->ToAlgebre();
  if (ns != "")
    r += " " + ns;
  r += ";\n";
  return r;
}
