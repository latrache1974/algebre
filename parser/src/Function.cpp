#include "Function.h"

Function::Function()
{
        name="";
        notation=NULL;
        params=NULL;
        Vars=NULL;
        cond=NULL;
        sentence=NULL;
}

Function::~Function()
{
  if (notation)
    delete notation;
  if (params)
    delete params;
  if (Vars )
    delete Vars;
  if (cond)
    delete cond;
  if (sentence)
    delete sentence;
}

void Function::AssignFromDoubleIdentList(Parameters *ps)
{
  params=ps;
}

void Function::AssignFromCorps(Corps *c)
{
  if ( ( c->type=="=>" ) || ( c->type=="<=>") )
    {
    cond=c->left->Copy();
    sentence=c->right->Copy();
    }
  if ( ( c->type=="sentence" )  )
    {
    sentence=c->sentence->Copy();
    }
  delete c;
}

Functions::Functions()
{
}

Functions::~Functions()
{
}
