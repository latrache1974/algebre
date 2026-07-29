#ifndef CORPS_H
#define CORPS_H
using namespace std;
#include"Predicat.h"
#include"Predicats.h"

class Corps
{
    public:
        Predicat *left, *right, *sentence;
        bool eq;
        Corps();
        virtual ~Corps();
        void Assign(Predicat * ,bool ,Predicat * );
        void AssignLeft(Predicat * );
        void AssignRight(Predicat * );

    protected:

    private:
};

class CorpsM
{
    public:
        Predicat *left, *right;
        Predicats *sentences;
        bool eq;
        CorpsM();
        void Assign(Predicat * ,bool ,Predicats * );
        void Assign(Predicat * ,bool ,Predicat * );
        void Assign(Predicats * );
        virtual ~CorpsM();

    protected:

    private:
};

class CorpsMM
{
    public:
        Predicats *conds;
        Predicats *sentences;
        bool eq;
        CorpsMM();
        void Assign(Predicats * ,bool ,Predicats * );
        void Assign(Predicats * );
        virtual ~CorpsMM();

    protected:

    private:
};

#endif // CORPS_H
