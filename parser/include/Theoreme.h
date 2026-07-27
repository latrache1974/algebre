#ifndef THEOREME_H
#define THEOREME_H

using namespace std;

#include"Parameters.h"
#include"Variables.h"
#include"Predicats.h"
#include"Corps.h"

class Theoreme
{
    public:
        string name;
        Parameters *params;
        Variables *Vars;
        Predicat *cond;
        Predicats *sentences;
        Theoreme();
        virtual ~Theoreme();
        void AssignFromDoubleIdentList(Parameters *);
        void AssignFromCorpsM(CorpsM *);

    protected:

    private:
};

class Theoremes
{
    public:
    vector <Theoreme*> Items;
    Theoremes();
    virtual ~Theoremes();
};

#endif // THEOREME_H
