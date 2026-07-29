#ifndef UTILS_H
#define UTILS_H

using namespace std;
#include<string>
#include"Predicat.h"
#include"Predicats.h"
#include"UniverseBase.h"
#include"UniverseProductionsBase.h"

class Utils
{
    public:
        Utils();
        virtual ~Utils();
        static Predicat *CreateNot(Predicat *);
        static Predicat *CreateOr(Predicat *, Predicat *);
        static Predicat *CreateAnd(Predicat *, Predicat *);
        static Predicat *CreateXor(Predicat *, Predicat *);
        static Predicat *CreateFunction(string , Predicats*);
        static Predicat *CreateTerminal(string );
        static Predicat *CreateAppartient(Predicat *, Predicat * );
        static Predicat *CreateRelation(Predicat * , Predicat * );
        static Predicat *CreateEq(Predicat *, Predicat *);
        static Predicat *CreateNEq(Predicat *, Predicat *);
        static Predicat *CreateTrue();
        static Predicat *CreateFalse();
        static Predicat *CreateReturn();
        static Predicat *CreateReturn(Predicats *);
        static void PerformeInclude(string );
    protected:

    private:
};


#endif // UTILS_H
