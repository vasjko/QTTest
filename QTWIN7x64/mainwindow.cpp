#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>
#include <chrono>
#include <string>

#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QComboBox>
#include <QToolBar>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, SIGNAL (released()), this, SLOT (switchTabs()));
    connect(ui->pushButton, SIGNAL (released()), this, SLOT (fillList()));

    ui->comboBox->addItem("Text");
    ui->comboBox->addItem("Digits");

    fillChart();

    //Main menu
    fileMenu = menuBar()->addMenu(tr("&File"));
    generateLog = new QAction(tr("&Generate Log"), this);
    generateLog->setStatusTip(tr("Create a new log"));
    connect(generateLog, &QAction::triggered, this, &MainWindow::fillList);
    fileMenu->addAction(generateLog);
    //Status bar
    statusBar()->showMessage( tr("Ready"));
    //Tool Bar
    QToolBar* toolbar = addToolBar(tr("Create a new log"));
    toolBarArea(toolbar);
    toolbar->addAction(generateLog);
}


void MainWindow::fillChart()
{
    QLineSeries *series = new QLineSeries();

    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->tab_2->setLayout(new QGridLayout());
    ui->tab_2->layout()->addWidget(chartView);
}

void MainWindow::switchTabs()
{
    ui->tabWidget->setCurrentIndex(1);
}

void MainWindow::fillList()
{
    ui->listWidget->clear();
    for(int i=0; i<100;i++)
    {
        std::string item = "Item: ";
        QString str = ui->comboBox->currentIndex()==0
                ?QString::fromStdString(item + std::to_string(i))
                                                    :QString::fromStdString(std::to_string(i));

        ui->listWidget->addItem(str);
        ui->progressBar->setValue(i+1);
        QApplication::processEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

