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
    settingLayout = scene->getCellNum();
    button = new QPushButton("Grow");
    settingLayout->addWidget(button);
    settingLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(scene->getMainView());
    mainLayout->addLayout(settingLayout);
    setCentralWidget(mainWidget);
}
