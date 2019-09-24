#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWidgets();
    connect(button,SIGNAL(clicked()),
            scene,SLOT(grow()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
        scene->grow();
    }
}

void MainWindow::initWidgets()
{
    setWindowTitle("Cellular Automaton");

    scene = new CellScene();
    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout(mainWidget);
    settingLayout = new QVBoxLayout();
    button = new QPushButton("Grow");
    cellNumLabel = new QLabel("Cell Number:");
    settingLayout->addWidget(cellNumLabel);
    settingLayout->addWidget(scene->getValidCellNums());
    settingLayout->addWidget(button);
    settingLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(scene->getView());
    mainLayout->addLayout(settingLayout);
    button->setFocus();
    button->setShortcut(Qt::Key_Enter);
    setCentralWidget(mainWidget);
}
