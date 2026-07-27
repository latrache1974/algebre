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

void Variables::Add(string q, string ident, string type, Predicat *p, NameSpaceList *deps)
{
    Variable *v = new Variable();
  if ( q=="forall" )
    v->q=_forall;
  if ( q=="exists" )
    v->q=_exists;
  if ( q=="existsu" )
    v->q=_existsu;
    v->ident = ident;
    v->type = type;
    v->p = p;
    v->depends = deps;
    Items.push_back(v);
}

Variables *Variables::Copy()
{
  Variables *r=new Variables();
  for(size_t i=0; i<Items.size(); i++)
    r->Items.push_back(Items[i]->Copy());
  return r;
}

Variable *Variable::Copy()
{
  Variable *r=new Variable();
  r->ident=ident;
  r->q=q;
  r->type=type;
  if (p)
    r->p=p->Copy();
  if (depends)
    r->depends=depends->Copy();
  return r;
}
