#pragma once
#include <math.h>
#include <cmath>

namespace Graph {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace ZedGraph;

    // окно справки
    public ref class HelpForm : public System::Windows::Forms::Form
    {
    public:
        HelpForm(String^ title, String^ text) {
            System::Windows::Forms::TextBox^ tb = gcnew System::Windows::Forms::TextBox();
            tb->Multiline = true;
            tb->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            tb->ReadOnly = true;
            tb->Dock = System::Windows::Forms::DockStyle::Fill;
            tb->Text = text;
            tb->Font = gcnew System::Drawing::Font(L"Consolas", 10.0F);
            tb->WordWrap = false;
            tb->BorderStyle = System::Windows::Forms::BorderStyle::None;
            this->Controls->Add(tb);

            System::Drawing::Size sz = System::Windows::Forms::TextRenderer::MeasureText(
                text, tb->Font, System::Drawing::Size(2000, 2000),
                System::Windows::Forms::TextFormatFlags::Left
                | System::Windows::Forms::TextFormatFlags::Top
                | System::Windows::Forms::TextFormatFlags::NoPrefix);

            int w = sz.Width + 40;
            int h = sz.Height + 50;
            if (w < 520) w = 520;
            if (h < 220) h = 220;
            if (w > 1400) w = 1400;
            if (h > 900) h = 900;

            this->Text = title;
            this->ClientSize = System::Drawing::Size(w, h);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = false;
        }
    };

    // таблицы 4 и 5
    public ref class TableForm : public System::Windows::Forms::Form
    {
    public:
        TableForm(String^ title, System::Windows::Forms::DataGridView^ grid,
            System::Drawing::Size clientSize) {
            grid->Dock = System::Windows::Forms::DockStyle::Fill;
            this->Controls->Add(grid);
            this->Text = title;
            this->ClientSize = clientSize;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
        }
    };

    // графики коэффициентов
    public ref class CoeffForm : public System::Windows::Forms::Form
    {
    public:
        CoeffForm(double xsi, bool isTest) {
            this->Text = isTest
                ? "Коэффициенты тестовой задачи около x = " + xsi.ToString("F2")
                : "Коэффициенты основной задачи около x = " + xsi.ToString("F2");
            this->ClientSize = System::Drawing::Size(830, 760);
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
            this->MinimizeBox = false;

            this->Controls->Add(makeGraph(10, 10, xsi, 0,
                "1/k(x): для интеграла a_i", isTest));
            this->Controls->Add(makeGraph(10, 260, xsi, 1,
                "q(x): для интеграла d_i", isTest));
            this->Controls->Add(makeGraph(10, 510, xsi, 2,
                "f(x): для интеграла phi_i", isTest));
        }

    private:
        ZedGraphControl^ makeGraph(int X, int Y, double xsi, int mode, String^ title, bool isTest) {
            ZedGraphControl^ z = gcnew ZedGraphControl();
            z->Location = System::Drawing::Point(X, Y);
            z->Size = System::Drawing::Size(800, 240);

            GraphPane^ pane = z->GraphPane;
            pane->CurveList->Clear();
            pane->GraphObjList->Clear();

            pane->Title->FontSpec->Size = 20.0f;
            pane->Title->FontSpec->Family = "Segoe UI";
            pane->Title->FontSpec->IsBold = true;
            pane->Legend->FontSpec->Size = 16.0f;
            pane->Legend->FontSpec->Family = "Segoe UI";

            pane->Title->Text = title;
            pane->XAxis->Title->Text = "x";
            pane->XAxis->Title->FontSpec->Size = 15.0f;
            pane->XAxis->Title->FontSpec->Family = "Segoe UI";
            pane->YAxis->Title->Text = (mode == 0 ? "1/k(x)" : (mode == 1 ? "q(x)" : "f(x)"));
            pane->YAxis->Title->FontSpec->Size = 15.0f;
            pane->YAxis->Title->FontSpec->Family = "Segoe UI";
            pane->XAxis->Scale->FontSpec->Size = 14.0f;
            pane->YAxis->Scale->FontSpec->Size = 14.0f;

            pane->Legend->IsVisible = true;

            pane->XAxis->MajorGrid->IsVisible = true;
            pane->XAxis->MajorGrid->Color = Color::LightGray;
            pane->XAxis->MajorGrid->PenWidth = 1.0f;
            pane->YAxis->MajorGrid->IsVisible = true;
            pane->YAxis->MajorGrid->Color = Color::LightGray;
            pane->YAxis->MajorGrid->PenWidth = 1.0f;
            pane->Chart->Fill->Color = Color::WhiteSmoke;
            pane->Chart->Fill->IsVisible = true;

            double L = 0.1;
            double a = xsi - L; if (a < 0) a = 0;
            double b = xsi + L; if (b > 1) b = 1;

            int Npts = 300;
            PointPairList^ leftList = gcnew PointPairList();
            PointPairList^ rightList = gcnew PointPairList();

            for (int i = 0; i <= Npts; i++) {
                double x = a + (xsi - a) * i / (double)Npts;
                if (x >= xsi) x = xsi - 1e-9;
                double v = isTest ? evalTest(mode, true, xsi) : evalMain(mode, x, true);
                leftList->Add(x, v);
            }

            for (int i = 0; i <= Npts; i++) {
                double x = xsi + (b - xsi) * i / (double)Npts;
                if (x < xsi) x = xsi + 1e-9;
                double v = isTest ? evalTest(mode, false, xsi) : evalMain(mode, x, false);
                rightList->Add(x, v);
            }

            String^ n1 = (mode == 0 ? "1/k1" : (mode == 1 ? "q1" : "f1"));
            String^ n2 = (mode == 0 ? "1/k2" : (mode == 1 ? "q2" : "f2"));
            if (isTest) { n1 += "*"; n2 += "*"; }

            LineItem^ l1 = pane->AddCurve(n1, leftList, Color::Blue, SymbolType::None);
            l1->Line->Width = 2.5f;
            LineItem^ l2 = pane->AddCurve(n2, rightList, Color::Red, SymbolType::None);
            l2->Line->Width = 2.5f;

            pane->XAxis->Scale->Min = a;
            pane->XAxis->Scale->Max = b;
            pane->XAxis->Scale->MajorStep = (b - a) / 10.0;
            pane->XAxis->Scale->MinorStep = (b - a) / 20.0;
            pane->XAxis->Scale->Format = "F2";

            z->AxisChange();

            double ymin = pane->YAxis->Scale->Min;
            double ymax = pane->YAxis->Scale->Max;
            LineObj^ vline = gcnew LineObj(Color::Black, xsi, ymin, xsi, ymax);
            vline->Line->Style = System::Drawing::Drawing2D::DashStyle::Dot;
            vline->Line->Width = 1.5f;
            pane->GraphObjList->Add(vline);

            z->Invalidate();
            return z;
        }

        double evalMain(int mode, double x, bool left) {
            switch (mode) {
            case 0: return left ? (1.0 / (x + 1.0)) : (1.0 / x);
            case 1: return left ? x : (x * x);
            case 2: return left ? x : exp(-x);
            }
            return 0.0;
        }

        double evalTest(int mode, bool left, double xsi) {
            switch (mode) {
            case 0: return left ? (1.0 / 1.4) : (1.0 / 0.4);
            case 1: return left ? 0.4 : 0.16;
            case 2: return left ? 0.4 : exp(-xsi);
            }
            return 0.0;
        }
    };

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void) {
            InitializeComponent();
            XSI = 0.4;
            computeAnalyticConstants();

            this->MinimumSize = System::Drawing::Size(1000, 650);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

            styleGrid(dataGridView1);

            System::Drawing::Font^ fLbl = gcnew System::Drawing::Font(L"Segoe UI", 10.0F);
            label_n0->Font = fLbl;
            label_Nmax->Font = fLbl;
            label_eps->Font = fLbl;
            checkAuto->Font = fLbl;

            zedGraphControl1->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
            zedGraphControl2->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right;
            dataGridView1->Anchor = AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right | AnchorStyles::Bottom;

            buttonHelp->Visible = false;
            buttonOrder->Visible = false;
            buttonCoeff->Visible = false;

            lastTask = 0;
            lastEps = 0;
            lastInfoTitle = "";
            lastInfoText = "";
        }

    protected:
        ~MyForm() { if (components) delete components; }

    private:
        ZedGraph::ZedGraphControl^ zedGraphControl1;
        ZedGraph::ZedGraphControl^ zedGraphControl2;
        System::Windows::Forms::DataGridView^ dataGridView1;

        System::Windows::Forms::TextBox^ textBox_n0;
        System::Windows::Forms::TextBox^ textBox_Nmax;
        System::Windows::Forms::TextBox^ textBox_eps;
        System::Windows::Forms::Label^ label_n0;
        System::Windows::Forms::Label^ label_Nmax;
        System::Windows::Forms::Label^ label_eps;
        System::Windows::Forms::CheckBox^ checkAuto;

        System::Windows::Forms::Button^ buttonTest;
        System::Windows::Forms::Button^ buttonMain;
        System::Windows::Forms::Button^ buttonClear;
        System::Windows::Forms::Button^ buttonResetZoom;
        System::Windows::Forms::Button^ buttonCoeff;
        System::Windows::Forms::Button^ buttonOrder;
        System::Windows::Forms::Button^ buttonHelp;

        System::ComponentModel::IContainer^ components;

        double XSI;
        double k1_star, k2_star, q1_star, q2_star, f1_star, f2_star;
        double alpha1_an, alpha2_an;
        double C1_an, C2_an;
        double A1_an, B1_an;
        double A2_an, B2_an;

        int     lastTask;
        double  lastEps;
        String^ lastInfoTitle;
        String^ lastInfoText;

        double parseDouble(String^ s) {
            if (String::IsNullOrWhiteSpace(s))
                throw gcnew Exception("Пустое поле ввода");
            s = s->Trim()->Replace(",", ".");
            return Double::Parse(s, System::Globalization::CultureInfo::InvariantCulture);
        }
        int parseInt(String^ s) {
            if (String::IsNullOrWhiteSpace(s))
                throw gcnew Exception("Пустое поле ввода");
            return Int32::Parse(s->Trim());
        }

        void styleGrid(System::Windows::Forms::DataGridView^ g) {
            g->AllowUserToAddRows = false;
            g->AllowUserToDeleteRows = false;
            g->ReadOnly = true;
            g->RowHeadersVisible = false;
            g->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::CellSelect;
            g->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
            g->ColumnHeadersHeightSizeMode =
                System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            g->RowTemplate->Height = 20;
            g->ColumnHeadersDefaultCellStyle->Alignment =
                System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
            g->GridColor = System::Drawing::Color::LightGray;
        }

        void computeAnalyticConstants() {
            k1_star = 1.4;
            k2_star = 0.4;
            q1_star = 0.4;
            q2_star = 0.16;
            f1_star = 0.4;
            f2_star = exp(-XSI);

            alpha1_an = sqrt(q1_star / k1_star);
            alpha2_an = sqrt(q2_star / k2_star);
            C1_an = f1_star / q1_star;
            C2_an = f2_star / q2_star;

            double E1 = exp(alpha1_an * XSI);
            double E1m = exp(-alpha1_an * XSI);
            double E2 = exp(alpha2_an * XSI);
            double E2m = exp(-alpha2_an * XSI);
            double E2_1 = exp(alpha2_an);
            double E2_1m = exp(-alpha2_an);

            double M[3][4] = {
                {
                    E1 - E1m,
                    -E2,
                    -E2m,
                    C2_an - C1_an + E1m
                },
                {
                    k1_star * alpha1_an * (E1 + E1m),
                    -k2_star * alpha2_an * E2,
                    k2_star * alpha2_an * E2m,
                    -k1_star * alpha1_an * E1m
                },
                {
                    0.0,
                    E2_1,
                    E2_1m,
                    1.0 - C2_an
                }
            };

            for (int i = 0; i < 3; i++) {
                int piv = i;
                for (int j = i + 1; j < 3; j++)
                    if (fabs(M[j][i]) > fabs(M[piv][i])) piv = j;
                for (int k = 0; k < 4; k++) {
                    double t = M[i][k]; M[i][k] = M[piv][k]; M[piv][k] = t;
                }
                for (int j = i + 1; j < 3; j++) {
                    double fac = M[j][i] / M[i][i];
                    for (int k = i; k < 4; k++) M[j][k] -= fac * M[i][k];
                }
            }

            B2_an = M[2][3] / M[2][2];
            A2_an = (M[1][3] - M[1][2] * B2_an) / M[1][1];
            A1_an = (M[0][3] - M[0][1] * A2_an - M[0][2] * B2_an) / M[0][0];
            B1_an = -C1_an - A1_an;
        }

        double uTest(double x) {
            if (x <= XSI)
                return C1_an + A1_an * exp(alpha1_an * x)
                + B1_an * exp(-alpha1_an * x);
            else
                return C2_an + A2_an * exp(alpha2_an * x)
                + B2_an * exp(-alpha2_an * x);
        }

        double aTestSeg(double xl, double xr) {
            if (xr <= XSI) return k1_star;
            if (xl >= XSI) return k2_star;
            return (xr - xl) / ((XSI - xl) / k1_star + (xr - XSI) / k2_star);
        }

        double aMainSeg(double xl, double xr) {
            if (xr <= XSI) return (xr - xl) / (log(xr + 1.0) - log(xl + 1.0));
            if (xl >= XSI) return (xr - xl) / (log(xr) - log(xl));
            double I1 = log(XSI + 1.0) - log(xl + 1.0);
            double I2 = log(xr) - log(XSI);
            return (xr - xl) / (I1 + I2);
        }

        double intQ(double xa, double xb) {
            if (xb <= XSI) return (xb * xb - xa * xa) / 2.0;
            if (xa >= XSI) return (xb * xb * xb - xa * xa * xa) / 3.0;
            return (XSI * XSI - xa * xa) / 2.0 + (xb * xb * xb - XSI * XSI * XSI) / 3.0;
        }

        double intF(double xa, double xb) {
            if (xb <= XSI) return (xb * xb - xa * xa) / 2.0;
            if (xa >= XSI) return exp(-xa) - exp(-xb);
            return (XSI * XSI - xa * xa) / 2.0 + (exp(-XSI) - exp(-xb));
        }

        // прогонка
        array<double>^ thomas(int n,
            array<double>^ a, array<double>^ b, array<double>^ c, array<double>^ d,
            double mu1, double mu2)
        {
            array<double>^ alpha = gcnew array<double>(n + 1);
            array<double>^ beta = gcnew array<double>(n + 1);
            array<double>^ v = gcnew array<double>(n + 1);

            alpha[0] = 0.0;
            beta[0] = mu1;

            for (int i = 1; i < n; i++) {
                double den = c[i] - a[i] * alpha[i - 1];
                alpha[i] = b[i] / den;
                beta[i] = (a[i] * beta[i - 1] - d[i]) / den;
            }
            v[n] = mu2;
            for (int i = n - 1; i >= 1; i--)
                v[i] = alpha[i] * v[i + 1] + beta[i];
            v[0] = mu1;
            return v;
        }

        // Схема (4.14) для тестовой задачи
        array<double>^ solveTest(int n, double mu1, double mu2) {
            double h = 1.0 / n;
            array<double>^ a = gcnew array<double>(n + 1);
            array<double>^ b = gcnew array<double>(n + 1);
            array<double>^ c = gcnew array<double>(n + 1);
            array<double>^ d = gcnew array<double>(n + 1);

            for (int i = 1; i < n; i++) {
                double ai = aTestSeg((i - 1) * h, i * h);
                double aip1 = aTestSeg(i * h, (i + 1) * h);
                double xm = (i - 0.5) * h;
                double xp = (i + 0.5) * h;

                double Q, F;
                if (xp <= XSI) { Q = q1_star; F = f1_star; }
                else if (xm >= XSI) { Q = q2_star; F = f2_star; }
                else {
                    double l = XSI - xm, r = xp - XSI;
                    Q = (q1_star * l + q2_star * r) / h;
                    F = (f1_star * l + f2_star * r) / h;
                }

                a[i] = ai / (h * h);
                b[i] = aip1 / (h * h);
                c[i] = a[i] + b[i] + Q;
                d[i] = -F;
            }
            return thomas(n, a, b, c, d, mu1, mu2);
        }

        // разностная схема
        array<double>^ solveMain(int n, double mu1, double mu2) {
            double h = 1.0 / n;
            array<double>^ a = gcnew array<double>(n + 1);
            array<double>^ b = gcnew array<double>(n + 1);
            array<double>^ c = gcnew array<double>(n + 1);
            array<double>^ d = gcnew array<double>(n + 1);

            for (int i = 1; i < n; i++) {
                double ai = aMainSeg((i - 1) * h, i * h);
                double aip1 = aMainSeg(i * h, (i + 1) * h);
                double xm = (i - 0.5) * h;
                double xp = (i + 0.5) * h;

                double Q = intQ(xm, xp) / h;
                double F = intF(xm, xp) / h;

                a[i] = ai / (h * h);
                b[i] = aip1 / (h * h);
                c[i] = a[i] + b[i] + Q;
                d[i] = -F;
            }
            return thomas(n, a, b, c, d, mu1, mu2);
        }

        void setupPane(ZedGraphControl^ zgc, String^ title) {
            GraphPane^ pane = zgc->GraphPane;
            pane->CurveList->Clear();
            pane->Title->Text = title;
            pane->XAxis->Title->Text = "x";
            pane->YAxis->Title->Text = "y";
            pane->Legend->IsVisible = true;
            pane->XAxis->Scale->Min = 0.0;
            pane->XAxis->Scale->Max = 1.0;
        }
        void refresh(ZedGraphControl^ zgc) {
            zgc->AxisChange();
            zgc->Invalidate();
        }
        void showError(Exception^ ex) {
            MessageBox::Show(
                "Ошибка: " + ex->Message,
                "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        }

        String^ makeTestInfo(int nsolved, double eps, double eps1, double xmax) {
            bool converged = (eps1 <= eps);
            double h = 1.0 / nsolved;
            String^ s =
                "Для решения задачи использована равномерная сетка с\r\n"
                "числом разбиений n = " + nsolved.ToString() + ";\r\n"
                "шаг сетки h = (1.0-0.0)/n = " + h.ToString("F6") + ";\r\n"
                "задача должна быть решена с погрешностью не более eps = "
                + eps.ToString("E2") + ";\r\n"
                "задача решена с погрешностью eps1 = " + eps1.ToString("E3") + ";\r\n"
                "максимальное отклонение аналитического и численного решений\r\n"
                "наблюдается в точке x = " + xmax.ToString("F6") + ".\r\n\r\n";
            s += converged ? "Заданная точность достигнута."
                : "Заданная точность НЕ достигнута.";
            return s;
        }
        String^ makeMainInfo(int nsolved, double eps, double eps2, double xmax) {
            bool converged = (eps2 <= eps);
            double h = 1.0 / nsolved;
            String^ s =
                "Для решения задачи использована равномерная сетка с\r\n"
                "числом разбиений n = " + nsolved.ToString() + ";\r\n"
                "шаг сетки h = (1.0-0.0)/n = " + h.ToString("F6") + ";\r\n"
                "задача должна быть решена с заданной точностью eps = "
                + eps.ToString("E2") + ";\r\n"
                "задача решена с точностью eps2 = " + eps2.ToString("E3") + ";\r\n"
                "максимальная разность численных решений в общих узлах сетки\r\n"
                "наблюдается в точке x = " + xmax.ToString("F6") + ".\r\n\r\n";
            s += converged ? "Заданная точность достигнута."
                : "Заданная точность НЕ достигнута.";
            return s;
        }

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->components = (gcnew System::ComponentModel::Container());
            this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
            this->zedGraphControl2 = (gcnew ZedGraph::ZedGraphControl());
            this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());

            this->textBox_n0 = (gcnew System::Windows::Forms::TextBox());
            this->textBox_Nmax = (gcnew System::Windows::Forms::TextBox());
            this->textBox_eps = (gcnew System::Windows::Forms::TextBox());
            this->label_n0 = (gcnew System::Windows::Forms::Label());
            this->label_Nmax = (gcnew System::Windows::Forms::Label());
            this->label_eps = (gcnew System::Windows::Forms::Label());
            this->checkAuto = (gcnew System::Windows::Forms::CheckBox());

            this->buttonTest = (gcnew System::Windows::Forms::Button());
            this->buttonMain = (gcnew System::Windows::Forms::Button());
            this->buttonClear = (gcnew System::Windows::Forms::Button());
            this->buttonResetZoom = (gcnew System::Windows::Forms::Button());
            this->buttonCoeff = (gcnew System::Windows::Forms::Button());
            this->buttonOrder = (gcnew System::Windows::Forms::Button());
            this->buttonHelp = (gcnew System::Windows::Forms::Button());

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
            this->SuspendLayout();

            this->zedGraphControl1->Location = System::Drawing::Point(10, 100);
            this->zedGraphControl1->Name = L"zedGraphControl1";
            this->zedGraphControl1->Size = System::Drawing::Size(730, 400);
            this->zedGraphControl1->TabIndex = 0;

            this->zedGraphControl2->Location = System::Drawing::Point(750, 100);
            this->zedGraphControl2->Name = L"zedGraphControl2";
            this->zedGraphControl2->Size = System::Drawing::Size(730, 400);
            this->zedGraphControl2->TabIndex = 1;

            this->dataGridView1->Location = System::Drawing::Point(10, 510);
            this->dataGridView1->Name = L"dataGridView1";
            this->dataGridView1->Size = System::Drawing::Size(1470, 280);
            this->dataGridView1->TabIndex = 2;

            this->label_n0->Location = System::Drawing::Point(15, 22);
            this->label_n0->Name = L"label_n0";
            this->label_n0->Size = System::Drawing::Size(40, 20);
            this->label_n0->Text = L"n0 =";
            this->label_n0->TabIndex = 3;

            this->textBox_n0->Location = System::Drawing::Point(55, 19);
            this->textBox_n0->Name = L"textBox_n0";
            this->textBox_n0->Size = System::Drawing::Size(80, 22);
            this->textBox_n0->Text = L"10";
            this->textBox_n0->TabIndex = 4;

            this->label_Nmax->Location = System::Drawing::Point(155, 22);
            this->label_Nmax->Name = L"label_Nmax";
            this->label_Nmax->Size = System::Drawing::Size(60, 20);
            this->label_Nmax->Text = L"Nmax =";
            this->label_Nmax->TabIndex = 5;

            this->textBox_Nmax->Location = System::Drawing::Point(220, 19);
            this->textBox_Nmax->Name = L"textBox_Nmax";
            this->textBox_Nmax->Size = System::Drawing::Size(100, 22);
            this->textBox_Nmax->Text = L"100000";
            this->textBox_Nmax->TabIndex = 6;

            this->label_eps->Location = System::Drawing::Point(345, 22);
            this->label_eps->Name = L"label_eps";
            this->label_eps->Size = System::Drawing::Size(45, 20);
            this->label_eps->Text = L"eps =";
            this->label_eps->TabIndex = 7;

            this->textBox_eps->Location = System::Drawing::Point(395, 19);
            this->textBox_eps->Name = L"textBox_eps";
            this->textBox_eps->Size = System::Drawing::Size(120, 22);
            this->textBox_eps->Text = L"0,0000005";
            this->textBox_eps->TabIndex = 8;

            this->checkAuto->Location = System::Drawing::Point(535, 19);
            this->checkAuto->Name = L"checkAuto";
            this->checkAuto->Size = System::Drawing::Size(180, 24);
            this->checkAuto->Text = L"Перебор n";
            this->checkAuto->Checked = true;
            this->checkAuto->TabIndex = 9;

            this->buttonTest->Location = System::Drawing::Point(15, 55);
            this->buttonTest->Name = L"buttonTest";
            this->buttonTest->Size = System::Drawing::Size(160, 32);
            this->buttonTest->Text = L"Тестовая задача";
            this->buttonTest->TabIndex = 10;
            this->buttonTest->Click += gcnew System::EventHandler(this, &MyForm::buttonTest_Click);

            this->buttonMain->Location = System::Drawing::Point(185, 55);
            this->buttonMain->Name = L"buttonMain";
            this->buttonMain->Size = System::Drawing::Size(160, 32);
            this->buttonMain->Text = L"Основная задача";
            this->buttonMain->TabIndex = 11;
            this->buttonMain->Click += gcnew System::EventHandler(this, &MyForm::buttonMain_Click);

            this->buttonClear->Location = System::Drawing::Point(385, 55);
            this->buttonClear->Name = L"buttonClear";
            this->buttonClear->Size = System::Drawing::Size(120, 32);
            this->buttonClear->Text = L"Очистить";
            this->buttonClear->TabIndex = 12;
            this->buttonClear->Click += gcnew System::EventHandler(this, &MyForm::buttonClear_Click);

            this->buttonResetZoom->Location = System::Drawing::Point(515, 55);
            this->buttonResetZoom->Name = L"buttonResetZoom";
            this->buttonResetZoom->Size = System::Drawing::Size(160, 32);
            this->buttonResetZoom->Text = L"Сброс масштаба";
            this->buttonResetZoom->TabIndex = 13;
            this->buttonResetZoom->Click += gcnew System::EventHandler(this, &MyForm::buttonResetZoom_Click);

            this->buttonCoeff->Location = System::Drawing::Point(1050, 55);
            this->buttonCoeff->Name = L"buttonCoeff";
            this->buttonCoeff->Size = System::Drawing::Size(120, 32);
            this->buttonCoeff->Text = L"Коэффициенты";
            this->buttonCoeff->TabIndex = 14;
            this->buttonCoeff->Anchor = AnchorStyles::Top | AnchorStyles::Right;
            this->buttonCoeff->Click += gcnew System::EventHandler(this, &MyForm::buttonCoeff_Click);

            this->buttonOrder->Location = System::Drawing::Point(1180, 55);
            this->buttonOrder->Name = L"buttonOrder";
            this->buttonOrder->Size = System::Drawing::Size(180, 32);
            this->buttonOrder->Text = L"Порядок сходимости";
            this->buttonOrder->TabIndex = 15;
            this->buttonOrder->Anchor = AnchorStyles::Top | AnchorStyles::Right;
            this->buttonOrder->Click += gcnew System::EventHandler(this, &MyForm::buttonOrder_Click);

            this->buttonHelp->Location = System::Drawing::Point(1370, 55);
            this->buttonHelp->Name = L"buttonHelp";
            this->buttonHelp->Size = System::Drawing::Size(110, 32);
            this->buttonHelp->Text = L"Справка";
            this->buttonHelp->TabIndex = 16;
            this->buttonHelp->Anchor = AnchorStyles::Top | AnchorStyles::Right;
            this->buttonHelp->Click += gcnew System::EventHandler(this, &MyForm::buttonHelp_Click);

            this->ClientSize = System::Drawing::Size(1490, 800);
            this->Controls->Add(this->checkAuto);
            this->Controls->Add(this->buttonClear);
            this->Controls->Add(this->buttonResetZoom);
            this->Controls->Add(this->buttonCoeff);
            this->Controls->Add(this->buttonHelp);
            this->Controls->Add(this->buttonOrder);
            this->Controls->Add(this->buttonMain);
            this->Controls->Add(this->buttonTest);
            this->Controls->Add(this->label_eps);
            this->Controls->Add(this->textBox_eps);
            this->Controls->Add(this->label_Nmax);
            this->Controls->Add(this->textBox_Nmax);
            this->Controls->Add(this->label_n0);
            this->Controls->Add(this->textBox_n0);
            this->Controls->Add(this->dataGridView1);
            this->Controls->Add(this->zedGraphControl2);
            this->Controls->Add(this->zedGraphControl1);
            this->Name = L"MyForm";
            this->Text = L"Лабораторная работа 2";

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }
#pragma endregion

        // тестовая задача
    private: System::Void buttonTest_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            int    n = parseInt(textBox_n0->Text);
            int    Nmax = parseInt(textBox_Nmax->Text);
            double eps = parseDouble(textBox_eps->Text);

            if (n < 2)    throw gcnew Exception("n0 должно быть >= 2");
            if (n > Nmax) throw gcnew Exception("n0 должно быть <= Nmax");
            if (eps <= 0) throw gcnew Exception("eps должно быть > 0");

            bool autoMode = checkAuto->Checked;

            const double mu1 = 0.0, mu2 = 1.0;
            int    nsolved = 0;
            double eps1 = 1e100;
            double h = 0.0;
            int    maxIdx = 0;
            array<double>^ v = nullptr;

            int ncur = n;
            do {
                v = solveTest(ncur, mu1, mu2);
                h = 1.0 / ncur;
                eps1 = 0.0; maxIdx = 0;
                for (int i = 0; i <= ncur; i++) {
                    double diff = fabs(uTest(i * h) - v[i]);
                    if (diff > eps1) { eps1 = diff; maxIdx = i; }
                }
                nsolved = ncur;
                if (!autoMode) break;
                if (eps1 <= eps) break;
                ncur *= 2;
            } while (ncur <= Nmax);

            if (v == nullptr) throw gcnew Exception("Расчёт не запустился");

            dataGridView1->Rows->Clear();
            dataGridView1->Columns->Clear();
            dataGridView1->Columns->Add("i", "i");
            dataGridView1->Columns->Add("xi", "x_i");
            dataGridView1->Columns->Add("ui", "u(x_i)");
            dataGridView1->Columns->Add("vi", "v(x_i)");
            dataGridView1->Columns->Add("dv", "u(x_i) - v(x_i)");

            int step = (nsolved > 300) ? (nsolved / 300) : 1;
            for (int i = 0; i <= nsolved; i += step) {
                double xi = i * h;
                double ui = uTest(xi);
                int r = dataGridView1->Rows->Add();
                dataGridView1->Rows[r]->Cells[0]->Value = i.ToString();
                dataGridView1->Rows[r]->Cells[1]->Value = String::Format("{0:F6}", xi);
                dataGridView1->Rows[r]->Cells[2]->Value = String::Format("{0:F8}", ui);
                dataGridView1->Rows[r]->Cells[3]->Value = String::Format("{0:F8}", v[i]);
                dataGridView1->Rows[r]->Cells[4]->Value = String::Format("{0:E3}", ui - v[i]);
            }

            setupPane(zedGraphControl1, "Тестовая задача: u(x) и v(x)");
            PointPairList^ pe = gcnew PointPairList();
            PointPairList^ pv = gcnew PointPairList();
            int plotStep = (nsolved > 5000) ? (nsolved / 5000) : 1;
            for (int i = 0; i <= nsolved; i += plotStep) {
                pe->Add(i * h, uTest(i * h));
                pv->Add(i * h, v[i]);
            }
            zedGraphControl1->GraphPane->AddCurve("u(x)", pe, Color::Blue, SymbolType::None);
            zedGraphControl1->GraphPane->AddCurve("v(x)", pv, Color::Red, SymbolType::None);
            refresh(zedGraphControl1);

            setupPane(zedGraphControl2, "Тестовая задача: u(x_i) - v(x_i)");
            zedGraphControl2->GraphPane->YAxis->Title->Text = "u - v";
            PointPairList^ pd = gcnew PointPairList();
            for (int i = 0; i <= nsolved; i += plotStep)
                pd->Add(i * h, uTest(i * h) - v[i]);
            zedGraphControl2->GraphPane->AddCurve("u - v", pd, Color::DarkGreen, SymbolType::None);
            refresh(zedGraphControl2);

            double xmaxNode = maxIdx * h;

            lastTask = 1;
            lastEps = eps;
            lastInfoTitle = "Справка по тестовой задаче";
            lastInfoText = makeTestInfo(nsolved, eps, eps1, xmaxNode);

            buttonOrder->Visible = true;
            buttonHelp->Visible = true;
            buttonCoeff->Visible = true;

            (gcnew HelpForm(lastInfoTitle, lastInfoText))->Show();
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // Основная задача
    private: System::Void buttonMain_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            int    n = parseInt(textBox_n0->Text);
            int    Nmax = parseInt(textBox_Nmax->Text);
            double eps = parseDouble(textBox_eps->Text);

            if (n < 2)    throw gcnew Exception("n0 должно быть >= 2");
            if (n > Nmax) throw gcnew Exception("n0 должно быть <= Nmax");
            if (eps <= 0) throw gcnew Exception("eps должно быть > 0");

            bool autoMode = checkAuto->Checked;

            const double mu1 = 0.0, mu2 = 1.0;
            int    nsolved = 0;
            double eps2 = 1e100;
            double h = 0.0;
            int    maxIdx = 0;
            array<double>^ v = nullptr;
            array<double>^ v2 = nullptr;

            int ncur = n;
            do {
                v = solveMain(ncur, mu1, mu2);
                v2 = solveMain(2 * ncur, mu1, mu2);
                h = 1.0 / ncur;
                eps2 = 0.0; maxIdx = 0;
                for (int i = 0; i <= ncur; i++) {
                    double diff = fabs(v[i] - v2[2 * i]);
                    if (diff > eps2) { eps2 = diff; maxIdx = i; }
                }
                nsolved = ncur;
                if (!autoMode) break;
                if (eps2 <= eps) break;
                ncur *= 2;
            } while (ncur <= Nmax);

            if (v == nullptr || v2 == nullptr) throw gcnew Exception("Расчёт не запустился");

            dataGridView1->Rows->Clear();
            dataGridView1->Columns->Clear();
            dataGridView1->Columns->Add("i", "i");
            dataGridView1->Columns->Add("xi", "x_i");
            dataGridView1->Columns->Add("vi", "v(x_i)");
            dataGridView1->Columns->Add("v2i", "v2(x_2i)");
            dataGridView1->Columns->Add("dv", "v(x_i) - v2(x_2i)");

            int step = (nsolved > 300) ? (nsolved / 300) : 1;
            for (int i = 0; i <= nsolved; i += step) {
                double xi = i * h;
                int r = dataGridView1->Rows->Add();
                dataGridView1->Rows[r]->Cells[0]->Value = i.ToString();
                dataGridView1->Rows[r]->Cells[1]->Value = String::Format("{0:F6}", xi);
                dataGridView1->Rows[r]->Cells[2]->Value = String::Format("{0:F8}", v[i]);
                dataGridView1->Rows[r]->Cells[3]->Value = String::Format("{0:F8}", v2[2 * i]);
                dataGridView1->Rows[r]->Cells[4]->Value = String::Format("{0:E3}", v[i] - v2[2 * i]);
            }

            setupPane(zedGraphControl1, "Основная задача: v(x) и v2(x)");
            PointPairList^ pv = gcnew PointPairList();
            PointPairList^ pv2 = gcnew PointPairList();
            int plotStep = (nsolved > 5000) ? (nsolved / 5000) : 1;
            for (int i = 0; i <= nsolved; i += plotStep) {
                pv->Add(i * h, v[i]);
                pv2->Add(i * h, v2[2 * i]);
            }
            zedGraphControl1->GraphPane->AddCurve("v(x)  (n)", pv, Color::Red, SymbolType::None);
            zedGraphControl1->GraphPane->AddCurve("v2(x) (2n)", pv2, Color::Blue, SymbolType::None);
            refresh(zedGraphControl1);

            setupPane(zedGraphControl2, "Основная задача: v(x_i) - v2(x_2i)");
            zedGraphControl2->GraphPane->YAxis->Title->Text = "v - v2";
            PointPairList^ pd = gcnew PointPairList();
            for (int i = 0; i <= nsolved; i += plotStep)
                pd->Add(i * h, v[i] - v2[2 * i]);
            zedGraphControl2->GraphPane->AddCurve("v - v2", pd, Color::DarkGreen, SymbolType::None);
            refresh(zedGraphControl2);

            double xmaxNode = maxIdx * h;

            lastTask = 2;
            lastEps = eps;
            lastInfoTitle = "Справка по основной задаче";
            lastInfoText = makeMainInfo(nsolved, eps, eps2, xmaxNode);

            buttonOrder->Visible = true;
            buttonHelp->Visible = true;
            buttonCoeff->Visible = true;

            (gcnew HelpForm(lastInfoTitle, lastInfoText))->Show();
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // Проверка порядка сходимости
    private: System::Void buttonOrder_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            if (lastTask == 0) {
                return;
            }

            const double mu1 = 0.0, mu2 = 1.0;
            array<int>^ ns = gcnew array<int> { 10, 20, 40, 50, 80, 100, 200, 500, 1000, 2000 };
            int count = ns->Length;

            System::Windows::Forms::DataGridView^ g =
                gcnew System::Windows::Forms::DataGridView();
            styleGrid(g);

            if (lastTask == 1) {
                g->Columns->Add("n", "n");
                g->Columns->Add("e1", "eps1(сетка n)");
                g->Columns->Add("r1", "eps1(сетка n) / eps1(сетка 2n)");
                g->Columns->Add("o1", "Порядок");

                array<double>^ e1 = gcnew array<double>(count);
                for (int k = 0; k < count; k++) {
                    int n = ns[k];
                    double h = 1.0 / n;
                    array<double>^ vt = solveTest(n, mu1, mu2);
                    double err = 0.0;
                    for (int i = 0; i <= n; i++) {
                        double d = fabs(uTest(i * h) - vt[i]);
                        if (d > err) err = d;
                    }
                    e1[k] = err;
                }

                for (int k = 0; k < count - 1; k++) {
                    double ratio = (e1[k + 1] > 0) ? e1[k] / e1[k + 1] : 0.0;
                    double ord = (ratio > 0) ? log(ratio) / log((double)ns[k + 1] / ns[k]) : 0.0;

                    int r = g->Rows->Add();
                    g->Rows[r]->Cells[0]->Value = ns[k].ToString();
                    g->Rows[r]->Cells[1]->Value = String::Format("{0:E6}", e1[k]);
                    g->Rows[r]->Cells[2]->Value = String::Format("{0:F6}", ratio);
                    g->Rows[r]->Cells[3]->Value = String::Format("{0:F6}", ord);
                }

                (gcnew TableForm("Таблица 4 (тестовая задача)",
                    g, System::Drawing::Size(560, 360)))->Show();
            }
            else {
                g->Columns->Add("n", "n");
                g->Columns->Add("e2", "eps2(сетка n)");
                g->Columns->Add("r2", "eps2(сетка n) / eps2(сетка 2n)");
                g->Columns->Add("o2", "Порядок");

                array<double>^ e2 = gcnew array<double>(count);
                for (int k = 0; k < count; k++) {
                    int n = ns[k];
                    array<double>^ vn = solveMain(n, mu1, mu2);
                    array<double>^ v2n = solveMain(2 * n, mu1, mu2);
                    double err = 0.0;
                    for (int i = 0; i <= n; i++) {
                        double d = fabs(vn[i] - v2n[2 * i]);
                        if (d > err) err = d;
                    }
                    e2[k] = err;
                }

                for (int k = 0; k < count - 1; k++) {
                    double ratio = (e2[k + 1] > 0) ? e2[k] / e2[k + 1] : 0.0;
                    double ord = (ratio > 0) ? log(ratio) / log((double)ns[k + 1] / ns[k]) : 0.0;

                    int r = g->Rows->Add();
                    g->Rows[r]->Cells[0]->Value = ns[k].ToString();
                    g->Rows[r]->Cells[1]->Value = String::Format("{0:E6}", e2[k]);
                    g->Rows[r]->Cells[2]->Value = String::Format("{0:F6}", ratio);
                    g->Rows[r]->Cells[3]->Value = String::Format("{0:F6}", ord);
                }

                (gcnew TableForm("Таблица 5 (основная задача)",
                    g, System::Drawing::Size(560, 360)))->Show();
            }
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // графики коэффициентов
    private: System::Void buttonCoeff_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            if (lastTask == 0) {
                return;
            }
            (gcnew CoeffForm(XSI, lastTask == 1))->Show();
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // Справка
    private: System::Void buttonHelp_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            if (lastTask == 0 || String::IsNullOrEmpty(lastInfoText)) {
                return;
            }
            (gcnew HelpForm(lastInfoTitle, lastInfoText))->Show();
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // Сброс масштаба
    private: System::Void buttonResetZoom_Click(System::Object^ sender, System::EventArgs^ e)
    {
        try {
            GraphPane^ p1 = zedGraphControl1->GraphPane;
            p1->XAxis->Scale->MinAuto = true;
            p1->XAxis->Scale->MaxAuto = true;
            p1->YAxis->Scale->MinAuto = true;
            p1->YAxis->Scale->MaxAuto = true;
            p1->XAxis->Scale->Min = 0.0;
            p1->XAxis->Scale->Max = 1.0;

            GraphPane^ p2 = zedGraphControl2->GraphPane;
            p2->XAxis->Scale->MinAuto = true;
            p2->XAxis->Scale->MaxAuto = true;
            p2->YAxis->Scale->MinAuto = true;
            p2->YAxis->Scale->MaxAuto = true;
            p2->XAxis->Scale->Min = 0.0;
            p2->XAxis->Scale->Max = 1.0;

            zedGraphControl1->AxisChange();
            zedGraphControl1->Invalidate();
            zedGraphControl2->AxisChange();
            zedGraphControl2->Invalidate();
        }
        catch (Exception^ ex) { showError(ex); }
    }

           // очистка
    private: System::Void buttonClear_Click(System::Object^ sender, System::EventArgs^ e)
    {
        dataGridView1->Rows->Clear();
        dataGridView1->Columns->Clear();
        zedGraphControl1->GraphPane->CurveList->Clear();
        zedGraphControl2->GraphPane->CurveList->Clear();
        refresh(zedGraphControl1);
        refresh(zedGraphControl2);

        lastTask = 0;
        lastEps = 0;
        lastInfoTitle = "";
        lastInfoText = "";
        buttonHelp->Visible = false;
        buttonOrder->Visible = false;
        buttonCoeff->Visible = false;
    }

    }; // class MyForm
} // namespace Graph