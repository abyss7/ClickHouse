#include <string>

#include <iostream>
#include <sstream>

#include "src/Core/Types.h"
#include "src/IO/ReadBufferFromString.h"
#include "src/IO/WriteBufferFromString.h"
#include "src/IO/ReadHelpers.h"
#include "src/IO/WriteHelpers.h"


int main(int, char **)
{
    try
    {
        Int64 x1 = std::numeric_limits<Int64>::min();
        Int64 x2 = 0;
        std::string s;

        std::cerr << static_cast<Int64>(x1) << std::endl;

        {
            DB::WriteBufferFromString wb(s);
            DB::writeIntText(x1, wb);
        }

        std::cerr << s << std::endl;

        {
            DB::ReadBufferFromString rb(s);
            DB::readIntText(x2, rb);
        }

        std::cerr << static_cast<Int64>(x2) << std::endl;
    }
    catch (const DB::Exception & e)
    {
        std::cerr << e.what() << ", " << e.displayText() << std::endl;
        return 1;
    }

    return 0;
}
