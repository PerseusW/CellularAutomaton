#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLayout>
#include <QPushButton>
#include <QComboBox>
#include <QMainWindow>
#include <QList>

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
    CellScene* scene;

    void initWidgets();
};

#endif // MAINWINDOW_H
