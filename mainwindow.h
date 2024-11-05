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
    QVector<QPixmap> entities;
    QVector<QPixmap> greeneries;
    gameScene* base;
    void drawGameScene();
    void game_loop();



    void updateLives(int lives);
    void gameOver();
    void updateScore();
    protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QTimer *spawnTimer;
    // bool eventFilter(QObject *object, QEvent *event);
    QTimer *treeTimer;
};
#endif // MAINWINDOW_H
