#include "list.h"
#include "print.h"
#include "basic_lines.h"

#include <iostream>
#include <string>

int main(void)
{
    constexpr char const* sourceCode = \
         "10 PRINT \"Hello, World!\"\n"
         "20 GOTO 10\n"
         "30 PRINT \"Hi\"\n"
         "RUN";

    auto basicLines = BasicLines(sourceCode);

#if 0
    auto it = basicLines.getLines().getIterator();
    while (it.hasNext())
    {
        auto elem = it.next();
        std::cout << "\"" << std::string(elem.begin, elem.begin + elem.lenLine) << "\"" << ", " << elem.lenLine << std::endl;
    }

    std::cout << "===" << std::endl;
#endif
    std::cout << basicLines.search(Token("30", 2, INTEGER_LITERAL_TYPE)) << std::endl;

    return 0;
}
