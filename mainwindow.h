#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include "entities.h"
#include "gamescene.h"
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
    QList<Entity> entities;
    gameScene* base;
    void drawGameScene();
    void game_loop();



protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_resetButton_clicked();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;

    // bool eventFilter(QObject *object, QEvent *event);
};
#endif // MAINWINDOW_H
