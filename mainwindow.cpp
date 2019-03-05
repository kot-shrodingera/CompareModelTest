#include "mainwindow.h"

#include <QTableView>
#include <QGridLayout>
#include <QTabBar>
#include <QStackedWidget>
#include <QPushButton>

#include "tablemodel.h"
#include "comparemodel.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{

  resize(1000, 600);
  auto centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  auto mainLayout = new QGridLayout(centralWidget);

  auto tabBar = new QTabBar(this);
  tabBar->addTab("First");
  tabBar->addTab("Second");
  tabBar->addTab("Compare");

  mainLayout->addWidget(tabBar, 0, 0);

  auto stackedWidget = new QStackedWidget(this);

  auto firstModel = new TableModel(this);
  firstModel->appendRow("KKS1", "Val1");
  firstModel->appendRow("KKS2", "Val2");
  firstModel->appendRow("KKS3", "Val3");

  auto firstView = new QTableView(this);
  firstView->setModel(firstModel);
  stackedWidget->addWidget(firstView);

  auto secondModel = new TableModel(this);
  secondModel->appendRow("KKS2", "Val2");
  secondModel->appendRow("KKS3", "NotVal3");
  secondModel->appendRow("KKS4", "Val4");

  auto secondView = new QTableView(this);
  secondView->setModel(secondModel);
  stackedWidget->addWidget(secondView);

  auto compareModel = new CompareModel({firstModel, secondModel}, this);

  auto compareView = new QTableView(this);
  compareView->setModel(compareModel);
  stackedWidget->addWidget(compareView);

  mainLayout->addWidget(stackedWidget, 1, 0);

  auto button = new QPushButton("Compare", this);

  mainLayout->addWidget(button, 2, 0);

  connect(button, &QPushButton::clicked,
          compareModel, &CompareModel::RunComparition);

  connect(tabBar, &QTabBar::tabBarClicked,
          stackedWidget, &QStackedWidget::setCurrentIndex);
}

MainWindow::~MainWindow()
{

}
