#ifndef NAMESPACELIST_H
#define NAMESPACELIST_H

using namespace std;
#include<string>
#include<vector>

class NameSpaceList
{
    public:
        vector<string> Items;
        NameSpaceList();
        virtual ~NameSpaceList();
        void Add(string );
        NameSpaceList *Copy();

    protected:

    private:
};

#endif // NAMESPACELIST_H
