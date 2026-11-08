#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qcustomplot.h"
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plotWidget->setInteraction(QCP::iRangeDrag, true);
    ui->plotWidget->setInteraction(QCP::iRangeZoom, true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::k1(double xi, double vi) { Q_UNUSED(xi); return 2 * vi; }
double MainWindow::k2(double xi, double vi, double k1, double hi) { Q_UNUSED(xi); return 2 * (vi + (hi * k1) / 2); }
double MainWindow::k3(double xi, double vi, double k2, double hi) { Q_UNUSED(xi); return 2 * (vi + (hi * k2) / 2); }
double MainWindow::k4(double xi, double vi, double k1, double k2, double k3, double hi) { Q_UNUSED(xi); Q_UNUSED(k1); Q_UNUSED(k2); return 2 * (vi + hi * k3); }
double MainWindow::next_v(double vi, double hi, double k1, double k2, double k3, double k4) { return vi + hi * (k1 + 2 * k2 + 2 * k3 + k4) / 6; }

void MainWindow::setTableItem(int row, int col, double value, int precision) {
    double rounded = std::floor(value * std::pow(10, precision)) / std::pow(10, precision);
    ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::number(rounded, 'f', precision)));
}

void MainWindow::on_pushButton_draw_clicked()
{
    double xmin = ui->lineEdit_a->text().replace(",", ".").toDouble();
    double xmax = ui->lineEdit_b->text().replace(",", ".").toDouble();
    double hi = ui->lineEdit_h0->text().replace(",", ".").toDouble();
    double h2i = hi / 2;
    double vi = ui->lineEdit_u0->text().replace(",", ".").toDouble();
    double eps = ui->lineEdit_eps->text().replace(",", ".").toDouble();
    int Nmax = ui->lineEdit_Nmax->text().toInt();

    ui->plotWidget->clearGraphs();
    QVector<double> x_data, y_data, x_exact, y_exact;

    double _k1, _k2, _k3, _k4;
    double xmin_limit = xmin - 0.1;
    double xmax_limit = xmax + 0.1;

    int i = 0;
    double xi = xmin;
    double vi_;
    double v2i = vi;
    double ui_exact = vi;
    double C = ui_exact / std::exp(2 * xi);
    double S = (v2i - vi) / (std::pow(2, 4) - 1);
    double OLP = S * std::pow(2, 4);
    double maxOLP = std::fabs(OLP);
    int C1 = 0, C2 = 0;
    double max_hi = hi, max_xi = xi;
    double min_hi = hi, min_xi = xi;
    double max_ui_vi = std::fabs(ui_exact - vi);
    double max_xi_ui_vi = xi;

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->insertRow(0);

    x_data.append(xi); y_data.append(vi);
    x_exact.append(xi); y_exact.append(vi);
    setTableItem(0, 0, i, 0);
    setTableItem(0, 1, xi);
    setTableItem(0, 2, vi);
    setTableItem(0, 3, v2i);
    setTableItem(0, 4, vi - v2i);
    setTableItem(0, 5, OLP, 5);
    setTableItem(0, 6, hi);
    setTableItem(0, 9, ui_exact);
    setTableItem(0, 10, std::fabs(ui_exact - vi), 4);
    i++;

    if (ui->checkBox_adapt->isChecked()) {
        while (xi + hi <= xmax && i <= Nmax) {
            ui->tableWidget->insertRow(i);
            setTableItem(i, 0, i, 0);

            _k1 = k1(xi, v2i); _k2 = k2(xi, v2i, _k1, h2i);
            _k3 = k3(xi, v2i, _k2, h2i); _k4 = k4(xi, v2i, _k1, _k2, _k3, h2i);
            v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

            _k1 = k1(xi + h2i, v2i); _k2 = k2(xi + h2i, v2i, _k1, h2i);
            _k3 = k3(xi + h2i, v2i, _k2, h2i); _k4 = k4(xi + h2i, v2i, _k1, _k2, _k3, h2i);
            v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);
            setTableItem(i, 3, v2i);

            _k1 = k1(xi, vi); _k2 = k2(xi, vi, _k1, hi);
            _k3 = k3(xi, vi, _k2, hi); _k4 = k4(xi, vi, _k1, _k2, _k3, hi);
            vi_ = vi;
            vi = next_v(vi, hi, _k1, _k2, _k3, _k4);
            setTableItem(i, 2, vi);
            setTableItem(i, 4, vi - v2i);

            _k1 = k1(xi, vi_); _k2 = k2(xi, vi_, _k1, h2i);
            _k3 = k3(xi, vi_, _k2, h2i); _k4 = k4(xi, vi_, _k1, _k2, _k3, h2i);
            vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);
            _k1 = k1(xi + h2i, vi_); _k2 = k2(xi + h2i, vi_, _k1, h2i);
            _k3 = k3(xi + h2i, vi_, _k2, h2i); _k4 = k4(xi + h2i, vi_, _k1, _k2, _k3, h2i);
            vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

            S = (vi_ - vi) / (std::pow(2, 4) - 1);
            OLP = S * std::pow(2, 4);
            if (std::fabs(OLP) > maxOLP) maxOLP = std::fabs(OLP);
            setTableItem(i, 5, OLP, 5);
            setTableItem(i, 6, hi);

            xi = xi + hi;
            setTableItem(i, 1, xi);
            x_data.append(xi); y_data.append(vi);
            ui_exact = C * std::exp(2 * xi);
            x_exact.append(xi); y_exact.append(ui_exact);
            setTableItem(i, 9, ui_exact);
            setTableItem(i, 10, std::fabs(ui_exact - vi), 4);

            if (max_ui_vi < std::fabs(ui_exact - vi)) {
                max_ui_vi = std::fabs(ui_exact - vi);
                max_xi_ui_vi = xi;
            }
            i++;
        }
    } else {
        setTableItem(0, 7, 0, 0);
        setTableItem(0, 8, 0, 0);
        while (xi + hi <= xmax && i <= Nmax) {
            double old_vi = vi;
            double old_v2i = v2i;
            _k1 = k1(xi, v2i); _k2 = k2(xi, v2i, _k1, h2i);
            _k3 = k3(xi, v2i, _k2, h2i); _k4 = k4(xi, v2i, _k1, _k2, _k3, h2i);
            v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);
            _k1 = k1(xi + h2i, v2i); _k2 = k2(xi + h2i, v2i, _k1, h2i);
            _k3 = k3(xi + h2i, v2i, _k2, h2i); _k4 = k4(xi + h2i, v2i, _k1, _k2, _k3, h2i);
            v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

            _k1 = k1(xi, vi); _k2 = k2(xi, vi, _k1, hi);
            _k3 = k3(xi, vi, _k2, hi); _k4 = k4(xi, vi, _k1, _k2, _k3, hi);
            vi_ = vi;
            vi = next_v(vi, hi, _k1, _k2, _k3, _k4);

            _k1 = k1(xi, vi_); _k2 = k2(xi, vi_, _k1, h2i);
            _k3 = k3(xi, vi_, _k2, h2i); _k4 = k4(xi, vi_, _k1, _k2, _k3, h2i);
            vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);
            _k1 = k1(xi + h2i, vi_); _k2 = k2(xi + h2i, vi_, _k1, h2i);
            _k3 = k3(xi + h2i, vi_, _k2, h2i); _k4 = k4(xi + h2i, vi_, _k1, _k2, _k3, h2i);
            vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

            S = (vi_ - vi) / (std::pow(2, 4) - 1);
            if (std::fabs(S) > eps) {
                vi = old_vi; v2i = old_v2i;
                hi = hi / 2; h2i = hi / 2;
                C1++;
                continue;
            } else {
                ui->tableWidget->insertRow(i);
                setTableItem(i, 6, hi);
                xi = xi + hi;
                setTableItem(i, 1, xi);
                if (hi > max_hi) { max_hi = hi; max_xi = xi; }
                if (hi < min_hi) { min_hi = hi; min_xi = xi; }
                setTableItem(i, 7, C1, 0);
                setTableItem(i, 8, C2, 0);
                if (std::fabs(S) < eps / std::pow(2, 5)) {
                    hi = 2 * hi; h2i = hi / 2;
                    C2++;
                }
                OLP = S * std::pow(2, 4);
                if (std::fabs(OLP) > maxOLP) maxOLP = std::fabs(OLP);
                setTableItem(i, 5, OLP, 5);
                ui_exact = C * std::exp(2 * xi);
                x_exact.append(xi); y_exact.append(ui_exact);
                setTableItem(i, 9, ui_exact);
                setTableItem(i, 10, std::fabs(ui_exact - vi), 4);
                if (max_ui_vi < std::fabs(ui_exact - vi)) {
                    max_ui_vi = std::fabs(ui_exact - vi);
                    max_xi_ui_vi = xi;
                }
                x_data.append(xi); y_data.append(vi);
                setTableItem(i, 3, v2i);
                setTableItem(i, 2, vi);
                setTableItem(i, 4, vi - v2i);
                setTableItem(i, 0, i, 0);
                i++;
            }
        }
    }

    ui->plotWidget->addGraph();
    ui->plotWidget->graph(0)->setData(x_data, y_data);
    ui->plotWidget->graph(0)->setName("Численное решение");
    ui->plotWidget->graph(0)->setPen(QPen(Qt::red));
    ui->plotWidget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 6));

    ui->plotWidget->addGraph();
    ui->plotWidget->graph(1)->setData(x_exact, y_exact);
    ui->plotWidget->graph(1)->setName("Точное решение");
    ui->plotWidget->graph(1)->setPen(QPen(Qt::blue));

    ui->plotWidget->legend->setVisible(true);
    ui->plotWidget->xAxis->setRange(xmin_limit, xmax_limit);
    ui->plotWidget->graph(0)->rescaleValueAxis(true);
    ui->plotWidget->graph(1)->rescaleValueAxis(true, true);
    ui->plotWidget->replot();

    QMessageBox::information(this, "Статистика",
                             "n = " + QString::number(i - 1) + "\t" +
                                 "b - x_n = " + QString::number(xmax - xi, 'f', 6) + "\n" +
                                 "max |OLP| = " + QString::number(maxOLP, 'f', 6) + "\n" +
                                 "Шагов уменьшено: " + QString::number(C1) + "\n" +
                                 "Шагов увеличено: " + QString::number(C2) + "\n" +
                                 "max|ui - vi|: " + QString::number(max_ui_vi, 'f', 6) + " при x =" + QString::number(max_xi_ui_vi, 'f', 6) + "\n" +
                                 "max hi = " + QString::number(max_hi, 'f', 6) + " при x = " + QString::number(max_xi, 'f', 6) + "\n" +
                                 "min hi = " + QString::number(min_hi, 'f', 6) + " при x = " + QString::number(min_xi, 'f', 6));
}

void MainWindow::on_pushButton_zoom_clicked()
{
    double xmin = ui->lineEdit_a->text().replace(",", ".").toDouble();
    double xmax = ui->lineEdit_b->text().replace(",", ".").toDouble();
    ui->plotWidget->xAxis->setRange(xmin, xmax);
    ui->plotWidget->replot();
}
