#ifndef PARAMETERS_H
#define PARAMETERS_H

using namespace std;
#include<string>
#include<vector>

class Parameter{
  public:
    string type, ident;
};

class Parameters
{
    public:
        vector<Parameter*> Items;
        Parameters();
        virtual ~Parameters();
        void Add(string ,string );

    protected:

    private:
};

#endif // PARAMETERS_H
