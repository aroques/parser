#ifndef PRODUCTIONS_HPP
#define PRODUCTIONS_HPP

#include "scanner/include/token.hpp"

void program(Token& token);
void vars(Token& token);
void block(Token& token);

#endif // !PRODUCTIONS_HPP