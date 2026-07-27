#include "driver.hh"
#include "parser.tab.hh"

Driver::Driver()
    : file(""), result(nullptr)
{
}

int Driver::parse(const std::string& filename)
{
    file = filename;
    location.initialize(&file);

    scan_begin();               // ouvre le fichier, configure flex (yyin, etc.)
    yy::Parser parse(*this);    // *this = le Driver, passé au constructeur du parser
    parse.set_debug_level(trace_parsing);
    int res = parse();          // lance l'analyse
    scan_end();                 // ferme le fichier

    return res;
}
