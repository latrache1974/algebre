#include "NameSpaceList.h"

NameSpaceList::NameSpaceList()
{
}

NameSpaceList::~NameSpaceList()
{
}

void NameSpaceList::Add(string s)
{
  Items.push_back(s);
}

NameSpaceList *NameSpaceList::Copy()
{
  NameSpaceList *r=new NameSpaceList();
  for(size_t i=0; i<Items.size(); i++)
    r->Add(Items[i]);
  return r;
}

string NameSpaceList::ToAlgebre()
{
  string r = "";
  for (size_t i = 0; i < Items.size(); i++)
  {
    if (i > 0)
      r += ",";
    r += Items[i];
  }
  return r;
}
