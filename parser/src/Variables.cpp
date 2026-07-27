#include "Variables.h"

Variables::Variables()
{
}

Variables::~Variables()
{
}

void Variables::Add(string q,string n,string t)
{
  Variable *v=new Variable();
  if ( q=="forall" )
    v->q=_forall;
  if ( q=="exists" )
    v->q=_exists;
  if ( q=="existsu" )
    v->q=_existsu;
  v->ident=n;
  v->type=t;
  v->p=NULL;
  Items.push_back(v);
}

void Variables::Add(string q,string n,string t,Predicat *p)
{
  Variable *v=new Variable();
  if ( q=="forall" )
    v->q=_forall;
  if ( q=="exists" )
    v->q=_exists;
  if ( q=="existsu" )
    v->q=_existsu;
  v->ident=n;
  v->type=t;
  v->p=p;
  Items.push_back(v);
}
