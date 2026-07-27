
using namespace std;
#include <iostream>
#include <fstream>
#include "lexer.hh"
#include "src/parser.tab.hh"
#include "Corps.h"
#include "UniverseBase.h"

UniverseBase *universe;

int main(int argc, char* argv[]) {
    string msg;
    universe=new UniverseBase();
    universe->Parse("./algebre/main.algebre", &msg);
    delete universe;
    return 0;
}
