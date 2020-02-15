#ifndef CONTROL_H
#define CONTROL_H

class Model;
class View;

#include <QtCore>
#include <string>

class Control
{
private:
    std::string folderPath;
    std::string classifierFilePath;

public:
    Control();
    Model *model;
    View *view;

    std::string getFolderPath() {return folderPath;}

    QStringList requestImageNames();
    QStringList requestClassifierNames();
    QString requestFolderPath();
    QString requestFilePath();

    void setConections(Model *m, View *v) {model = m; view = v;};

    QStringList vectorToQStringList(std::vector<std::string> v);
    std::vector<std::string> qStringListToVector(QStringList list);

};

#endif // CONTROL_H
