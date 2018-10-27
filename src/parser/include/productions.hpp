#ifndef PRODUCTIONS_HPP
#define PRODUCTIONS_HPP

#include "scanner/include/token.hpp"

void program(Token& token);
void vars(Token& token);
void block(Token& token);
void stats(Token& token);
void mStat(Token& token);
void stat(Token& token);
void in(Token& token);
// void out(Token& token);
// void expr(Token& token);

#endif // !PRODUCTIONS_HPP