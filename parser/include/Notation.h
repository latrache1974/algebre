#ifndef NOTATION_H
#define NOTATION_H

using namespace std;
#include<string>
#include"NameSpaceList.h"

class Notation
{
    public:
        string format;
        NameSpaceList *params;
        Notation();
        virtual ~Notation();
        Notation *Copy();

    protected:

    private:
};

#endif // NOTATION_H
