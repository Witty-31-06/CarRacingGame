#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "entities.h"
#include "qgraphicsscene.h"
QT_BEGIN_NAMESPACE


//Forward Declarations
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MainPlayer player;
    // QGraphicsScene base;


protected:
    void keyPressEvent(QKeyEvent *event) override;
private slots:
    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    // bool eventFilter(QObject *object, QEvent *event);
};
#endif // MAINWINDOW_H
