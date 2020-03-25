#define BOOST_TEST_MODULE sortName
#include <boost/test/included/unit_test.hpp>
#include "control.h"

using namespace boost::unit_test;

BOOST_AUTO_TEST_SUITE( requestSortedNameAscending )

BOOST_AUTO_TEST_CASE( sortAscending )
{

   BOOST_TEST( );
}
}
/*QStringList Control::requestSortedNameAscending(std::vector<std::string>namesVector){

    bool swapped = false;

    for (unsigned int i = 0; i < namesVector.size() - 1; ++i) {
        for (unsigned int j = 0; j < namesVector.size() - 1 - i; ++j) {

            if (namesVector[j] > namesVector[j + 1]) {
                std::string temp = namesVector[j];
                namesVector[j] = namesVector[j + 1];
                namesVector[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
    }
    QStringList sortedNames = vectorToQStringList(namesVector);
    return sortedNames;
}*/
