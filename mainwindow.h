#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QList>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *mainWidget;
    QGridLayout *mainLayout;
    QVBoxLayout *settingLayout;
    QPushButton *button;
    QLabel *cellNumLabel;
    QGraphicsScene* scene;
    QGraphicsView* view;
    bool** cellPlate;
    bool** bufferPlate;

    void initBlankEnvironment();
    void initCells();
    void updateEnvironment();

private slots:
    void grow();
};

#endif // MAINWINDOW_H
