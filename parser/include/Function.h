#ifndef FUNCTION_H
#define FUNCTION_H
using namespace std;
#include<string>
#include"Notation.h"
#include"Parameters.h"
#include"Predicat.h"
#include"Variables.h"
#include"Corps.h"

class Function
{
    public:
        string name;
        Notation *notation;
        Parameters *params;
        Variables *Vars;
        Predicat *cond, *sentence;
        Function();
        virtual ~Function();
        void AssignFromDoubleIdentList(Parameters *);
        void AssignFromCorps(Corps *);

    protected:

    private:
};

class Functions
{
    public:
      vector<Function*> Items;
      Functions();
      virtual ~Functions();
};

#endif // FUNCTION_H
