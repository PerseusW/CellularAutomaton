#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initWidgets();
    connect(cellNumComboBox,SIGNAL(currentTextChanged(QString)),
            scene,SLOT(changeCellNum(QString)));
    connect(button,SIGNAL(clicked()),
            scene,SLOT(grow()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::initWidgets()
{
    setWindowTitle("Cellular Automaton");

    mainWidget = new QWidget();
    mainLayout = new QHBoxLayout(mainWidget);
    settingLayout = new QVBoxLayout();
    button = new QPushButton("Grow");
    cellNumLabel = new QLabel("Cell Number:");
    cellNumComboBox = new QComboBox();
    settingLayout->addWidget(cellNumLabel);
    settingLayout->addWidget(cellNumComboBox);
    settingLayout->addWidget(button);
    settingLayout->setAlignment(Qt::AlignTop);
    scene = new CellScene();
    view = new QGraphicsView(scene);
    mainLayout->addWidget(view);
    mainLayout->addLayout(settingLayout);

    setCentralWidget(mainWidget);
    cellNumComboBox->addItems(scene->getValidCellNums());
    cellNumComboBox->setCurrentText(QString::number(scene->getCellNum()));
    view->setFixedSize(scene->getSceneSize()+20,scene->getSceneSize()+20);
}
