#include "WorkPlan.h"

WorkPlan::WorkPlan()
{
        Vars=NULL;
        predicats=NULL;
}

WorkPlan::~WorkPlan()
{
  if ( Vars)
    delete Vars;
  if (predicats)
    delete predicats;
}
