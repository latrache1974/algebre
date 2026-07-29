#include "Literal.h"

using namespace std;
#include<string>

Literal::Literal()
{
        type="";
        eq=false;
        name="";
        notation=NULL;
        Vars=NULL;
        cond=NULL;
        sentence=NULL;
}

Literal::~Literal()
{
  if (notation)
      delete notation;
  if (Vars )
    delete Vars;
  if (cond)
    delete cond;
  if (sentence)
    delete sentence;
}

void Literal::AssignFromCorps(Corps *c)
{
   eq=c->eq;
   if ( eq )
   {
       sentence=NULL;
       cond=Predicat::Or(c->left, c->right);
       delete c;
       return;
   }
   if ( c->left )
       cond=c->left->Copy();
   if ( c->right )
     sentence=c->right->Copy();
  delete c;
}

Literals::Literals()
{
}

Literals::~Literals()
{
}

Literal *Literals::GetFromName(string name)
{
  for(size_t i=0; i<Items.size(); i++)
    if ( Items[i]->name == name )
      return Items[i];
  return NULL;
}

string Literal::ToAlgebre()
{
  string r = "literal " + name + " : " + type + ";\n";
  if (notation)
    r += notation->ToAlgebre();
  if (Vars)
    r += Vars->ToAlgebre();
  r += "begin\n  ";
  if (cond)
    r += cond->ToAlgebre()+ " => ";
  if (sentence)
    r += sentence->ToAlgebre() + ";\n";
  r += "end\n";
  return r;
}
