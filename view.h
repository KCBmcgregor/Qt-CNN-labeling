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

public:
    View(Control *cont = nullptr,QWidget *parent = nullptr);
    ~View();

    void renderLists();

private slots:
    void on_selectFolderButton_clicked();

    void on_shapeDrawButton_clicked();

    void on_imageNamesList_currentItemChanged(QListWidgetItem *current);

    void on_selectFileButton_clicked();

private:
    Ui::View *ui;
    Control *control;
};
#endif // VIEW_H
