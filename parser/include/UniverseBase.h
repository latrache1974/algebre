#ifndef UNIVERSEBASE_H
#define UNIVERSEBASE_H

#include"Type.h"
#include"Function.h"
#include"Literal.h"
#include"Theoreme.h"
#include"Goal.h"
#include"WorkPlan.h"

class UniverseBase
{
    public:
        Types *types;
        Functions *functions;
        Literals *literals;
        Theoremes *theoremes;
        Goal *goal;
        WorkPlan *plan;
        UniverseBase();
        virtual ~UniverseBase();
        bool Parse(string ,string *);
        void AddType(Type *);
        void AddFunction(Function *);
        void AddLiteral(Literal *);
        void AddTheoreme(Theoreme *);
        void SetGoal(Goal *);
        void CopyFrom(UniverseBase *);
    protected:

    private:
};

extern UniverseBase *universe;

#endif // UNIVERSEBASE_H
