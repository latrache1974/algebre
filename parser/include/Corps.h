#ifndef CORPS_H
#define CORPS_H
using namespace std;
#include"Predicat.h"
#include"Predicats.h"

class Corps
{
    public:
        Predicat *left, *right, *sentence;
        string type;
        Corps();
        virtual ~Corps();
        void Assign(Predicat * ,string ,Predicat * );
        void Assign(Predicat * );

    protected:

    private:
};

class CorpsM
{
    public:
        Predicat *left, *right;
        Predicats *sentences;
        string type;
        CorpsM();
        void Assign(Predicat * ,string ,Predicats * );
        void Assign(Predicat * ,string ,Predicat * );
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
        string type;
        CorpsMM();
        void Assign(Predicats * ,string ,Predicats * );
        void Assign(Predicats * );
        virtual ~CorpsMM();

    protected:

    private:
};

#endif // CORPS_H
