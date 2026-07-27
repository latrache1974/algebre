#ifndef WORKPLAN_H
#define WORKPLAN_H

using namespace std;
#include"Variables.h"
#include"Predicats.h"

class WorkPlan
{
    public:
        Variables *Vars;
        Predicats *predicats;
        WorkPlan();
        virtual ~WorkPlan();
        void ExportToAlgebre(string filename);

    protected:

    private:
};

#endif // WORKPLAN_H
