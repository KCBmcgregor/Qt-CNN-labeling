#include <boost/test/included/unit_test.hpp>
#include "control.h"

QStringList vectorToQStringList(std::vector<std::string> v)
{
    QStringList returnList;
    for(unsigned i=0; i < v.size(); i++) {
        QString item = QString::fromStdString(v[i]);
        returnList.append(item);
    }
    return returnList;
}
QStringList requestSortedNameAscending(std::vector<std::string>namesVector){

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
}

BOOST_AUTO_TEST_CASE( Sort_Name_Ascending_Test1 )
{
   std::vector<std::string> names = {"dog","cow","cat"};
   QStringList expectedResult = {"cat","cow","dog"};

   BOOST_TEST( requestSortedNameAscending(names)== (expectedResult));
}

