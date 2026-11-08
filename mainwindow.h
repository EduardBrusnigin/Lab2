#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_draw_clicked();
    void on_pushButton_zoom_clicked();

private:
    Ui::MainWindow *ui;

    // Ваши математические функции (перенесены из C++/CLI)
    double k1(double xi, double vi);
    double k2(double xi, double vi, double k1, double hi);
    double k3(double xi, double vi, double k2, double hi);
    double k4(double xi, double vi, double k1, double k2, double k3, double hi);
    double next_v(double vi, double hi, double k1, double k2, double k3, double k4);

    // Вспомогательная функция для вывода в таблицу
    void setTableItem(int row, int col, double value, int precision = 3);
};
#endif // MAINWINDOW_H
