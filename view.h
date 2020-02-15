#ifndef VIEW_H
#define VIEW_H
#include "control.h"

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

private:
    Ui::View *ui;
    Control *control;

public:
    View(Control *cont = nullptr,QWidget *parent = nullptr);

    void renderLists();

    ~View();

private slots:
    void on_selectFolderButton_clicked();
    void on_selectFileButton_clicked();

    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);
};

#endif // VIEW_H
