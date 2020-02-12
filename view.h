#ifndef VIEW_H
#define VIEW_H
#include "control.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class View; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Control * = nullptr,QWidget *parent = nullptr);
    ~View();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::View *ui;
    Control *control;
};
#endif // VIEW_H
