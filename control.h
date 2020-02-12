#ifndef CONTROL_H
#define CONTROL_H

#include <string>

class Control
{
private:


public:
    Control();
    std::string folderPath;
    std::string getFolderPath();
    void setFolderPath(std::string);
};

#endif // CONTROL_H
