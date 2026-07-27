clear
# 1. Génération C++ de Bison
bison -d parser.yy

# 2. Génération C++ de Flex
flex -o lex.yy.cc lexer.l

