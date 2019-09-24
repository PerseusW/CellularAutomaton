#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QDebug>

#include "cellscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    QWidget *mainWidget;
    QHBoxLayout *mainLayout;
    QVBoxLayout *settingLayout;
    QPushButton *button;
    QLabel *cellNumLabel;
    CellScene* scene;

    void initWidgets();
};

#endif // MAINWINDOW_H
