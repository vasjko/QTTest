#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QMenu>
#include <QAction>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();    


    void fillChart();

private slots:
    void switchTabs();
    void fillList();
private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QAction *generateLog;
};

#endif // MAINWINDOW_H
