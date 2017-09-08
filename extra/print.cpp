#include "print.h"

std::ostream & operator<<(std::ostream &os, Lang::Token const &token)
{ 
    char tokenText[128];
    token.getNullTerminatedText(tokenText, sizeof(tokenText));
    return os << "\"" << tokenText << "\" (" << token.getType() << ", " << token.getLen() << ")";
}
