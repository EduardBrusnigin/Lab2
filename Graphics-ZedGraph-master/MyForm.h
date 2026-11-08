#pragma once
#include <math.h>

namespace Graph {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace ZedGraph;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: ZedGraph::ZedGraphControl^  zedGraphControl1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::DataGridView^  dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  xi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  vi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ v2i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ vi_v2i;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ OLP;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ hi;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ C1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ C2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ui;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ modui_vi;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ОЛП;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::CheckBox^ checkBox1;




	protected:
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->zedGraphControl1 = (gcnew ZedGraph::ZedGraphControl());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->xi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->vi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->v2i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->vi_v2i = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ОЛП = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->hi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->C1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->C2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ui = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->modui_vi = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();
			// 
			// zedGraphControl1
			// 
			this->zedGraphControl1->Location = System::Drawing::Point(14, 37);
			this->zedGraphControl1->Margin = System::Windows::Forms::Padding(5);
			this->zedGraphControl1->Name = L"zedGraphControl1";
			this->zedGraphControl1->ScrollGrace = 0;
			this->zedGraphControl1->ScrollMaxX = 0;
			this->zedGraphControl1->ScrollMaxY = 0;
			this->zedGraphControl1->ScrollMaxY2 = 0;
			this->zedGraphControl1->ScrollMinX = 0;
			this->zedGraphControl1->ScrollMinY = 0;
			this->zedGraphControl1->ScrollMinY2 = 0;
			this->zedGraphControl1->Size = System::Drawing::Size(668, 402);
			this->zedGraphControl1->TabIndex = 0;
			this->zedGraphControl1->Load += gcnew System::EventHandler(this, &MyForm::zedGraphControl1_Load);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(844, 475);
			this->button1->Margin = System::Windows::Forms::Padding(4);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(189, 36);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Draw";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(11) {
				this->i, this->xi,
					this->vi, this->v2i, this->vi_v2i, this->ОЛП, this->hi, this->C1, this->C2, this->ui, this->modui_vi
			});
			this->dataGridView1->Location = System::Drawing::Point(700, 37);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->Size = System::Drawing::Size(431, 402);
			this->dataGridView1->TabIndex = 2;
			// 
			// i
			// 
			this->i->HeaderText = L"i";
			this->i->MinimumWidth = 6;
			this->i->Name = L"i";
			this->i->ReadOnly = true;
			this->i->Width = 35;
			// 
			// xi
			// 
			this->xi->HeaderText = L"xi";
			this->xi->MinimumWidth = 6;
			this->xi->Name = L"xi";
			this->xi->ReadOnly = true;
			this->xi->Width = 35;
			// 
			// vi
			// 
			this->vi->HeaderText = L"vi";
			this->vi->MinimumWidth = 6;
			this->vi->Name = L"vi";
			this->vi->ReadOnly = true;
			this->vi->Width = 35;
			// 
			// v2i
			// 
			this->v2i->HeaderText = L"v2i";
			this->v2i->MinimumWidth = 6;
			this->v2i->Name = L"v2i";
			this->v2i->ReadOnly = true;
			this->v2i->Width = 35;
			// 
			// vi_v2i
			// 
			this->vi_v2i->HeaderText = L"vi-v2i";
			this->vi_v2i->MinimumWidth = 6;
			this->vi_v2i->Name = L"vi_v2i";
			this->vi_v2i->ReadOnly = true;
			this->vi_v2i->Width = 50;
			// 
			// ОЛП
			// 
			this->ОЛП->HeaderText = L"ОЛП";
			this->ОЛП->MinimumWidth = 6;
			this->ОЛП->Name = L"ОЛП";
			this->ОЛП->ReadOnly = true;
			this->ОЛП->Width = 45;
			// 
			// hi
			// 
			this->hi->HeaderText = L"hi";
			this->hi->MinimumWidth = 6;
			this->hi->Name = L"hi";
			this->hi->ReadOnly = true;
			this->hi->Width = 35;
			// 
			// C1
			// 
			this->C1->HeaderText = L"C1";
			this->C1->MinimumWidth = 6;
			this->C1->Name = L"C1";
			this->C1->ReadOnly = true;
			this->C1->Width = 35;
			// 
			// C2
			// 
			this->C2->HeaderText = L"C2";
			this->C2->MinimumWidth = 6;
			this->C2->Name = L"C2";
			this->C2->ReadOnly = true;
			this->C2->Width = 35;
			// 
			// ui
			// 
			this->ui->HeaderText = L"ui";
			this->ui->MinimumWidth = 6;
			this->ui->Name = L"ui";
			this->ui->ReadOnly = true;
			this->ui->Width = 35;
			// 
			// modui_vi
			// 
			this->modui_vi->HeaderText = L"|ui-vi|";
			this->modui_vi->MinimumWidth = 6;
			this->modui_vi->Name = L"modui_vi";
			this->modui_vi->ReadOnly = true;
			this->modui_vi->Width = 45;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(61, 487);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 16);
			this->label1->TabIndex = 3;
			this->label1->Text = L"a (x0)";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(104, 485);
			this->textBox1->Margin = System::Windows::Forms::Padding(4);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(63, 22);
			this->textBox1->TabIndex = 4;
			this->textBox1->Text = L"0";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(228, 487);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(15, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"b";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(253, 484);
			this->textBox2->Margin = System::Windows::Forms::Padding(4);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(64, 22);
			this->textBox2->TabIndex = 6;
			this->textBox2->Text = L"1";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(383, 490);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(21, 16);
			this->label3->TabIndex = 7;
			this->label3->Text = L"h0";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(408, 485);
			this->textBox3->Margin = System::Windows::Forms::Padding(4);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(80, 22);
			this->textBox3->TabIndex = 8;
			this->textBox3->Text = L"0,1";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(844, 538);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(189, 36);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Zoom";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(253, 538);
			this->textBox4->Margin = System::Windows::Forms::Padding(4);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(64, 22);
			this->textBox4->TabIndex = 13;
			this->textBox4->Text = L"100";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(203, 541);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(42, 16);
			this->label4->TabIndex = 12;
			this->label4->Text = L"Nmax";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(104, 537);
			this->textBox5->Margin = System::Windows::Forms::Padding(4);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(63, 22);
			this->textBox5->TabIndex = 11;
			this->textBox5->Text = L"1";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(79, 539);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(21, 16);
			this->label5->TabIndex = 10;
			this->label5->Text = L"u0";
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(408, 539);
			this->textBox6->Margin = System::Windows::Forms::Padding(4);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(80, 22);
			this->textBox6->TabIndex = 15;
			this->textBox6->Text = L"0,01";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(374, 543);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 16);
			this->label6->TabIndex = 14;
			this->label6->Text = L"eps";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(677, 483);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(135, 20);
			this->checkBox1->TabIndex = 16;
			this->checkBox1->Text = L"Постоянный шаг";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1144, 612);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->zedGraphControl1);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		double k1(double xi, double vi){
			return 2*vi;
		}

		double k2(double xi, double vi, double k1, double hi) {
			return 2 * (vi + (hi * k1) / 2);
		}

		double k3(double xi, double vi, double k2, double hi) {
			return 2 * (vi + (hi * k2) / 2);
		}

		double k4(double xi, double vi, double k1, double k2, double k3, double hi) {
			return 2 * (vi + hi * k3);
		}

		double next_v(double vi, double hi, double k1, double k2, double k3, double k4) {
			return vi + hi * (k1 + 2 * k2 + 2* k3 + k4) / 6;
		}
		


	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		GraphPane^ panel = zedGraphControl1->GraphPane;
		panel->CurveList->Clear();
		PointPairList^ reshenie_list = gcnew ZedGraph::PointPairList();
		PointPairList^ tochnoe_list = gcnew ZedGraph::PointPairList();


		// Интервал, где есть данные
		double xmin = Convert::ToDouble(textBox1->Text);
		double xmax = Convert::ToDouble(textBox2->Text);

		double hi = Convert::ToDouble(textBox3->Text);
		double h2i = hi / 2;

		double _k1, _k2, _k3, _k4;

		double xmin_limit = xmin - 0.1;
		double xmax_limit = xmax + 0.1;



		int i = 0;
		double xi = xmin;
		double vi = Convert::ToDouble(textBox5->Text);
		double vi_;
		double v2i = vi;

		double ui = vi;
		double C = ui / exp(2 * xi);  // точное решение: u = C*e^(2x)

		double S = (v2i - vi) / (pow(2, 4) - 1);  // контрольная величина
		double eps = Convert::ToDouble(textBox5->Text);
		double OLP = S * pow(2, 4);
		double maxOLP = OLP;

		int C1 = 0;
		int C2 = 0;

		double max_hi = hi;
		double max_xi = xi;

		double min_hi = hi;
		double min_xi = xi;

		double ui_vi = fabs(ui - vi);
		double max_ui_vi = ui_vi;
		double max_xi_ui_vi = xi;

		int Nmax = Convert::ToInt32(textBox4->Text);

		reshenie_list->Add(xi, vi);
		tochnoe_list->Add(xi, v2i);
		dataGridView1->Rows->Clear();
		dataGridView1->Rows->Add();
		dataGridView1->Rows[i]->Cells[0]->Value = i;
		dataGridView1->Rows[i]->Cells[1]->Value = floor(xi * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[2]->Value = floor(vi * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[3]->Value = floor(v2i * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[6]->Value = hi;
		dataGridView1->Rows[i]->Cells[4]->Value = floor((vi - v2i) * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[9]->Value = floor(ui * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[10]->Value = floor(fabs(ui - vi) * 1000) / 1000;
		dataGridView1->Rows[i]->Cells[5]->Value = floor(OLP * 1000) / 1000;

		i++;

		if (this->checkBox1->Checked == true) {
			while (xi + hi <= xmax && i <= Nmax)
			{
				dataGridView1->Rows->Add();
				dataGridView1->Rows[i]->Cells[0]->Value = i;

				// считаем коэффициенты для траектории с половинным шагом
				_k1 = k1(xi, v2i);
				_k2 = k2(xi, v2i, _k1, h2i);
				_k3 = k3(xi, v2i, _k2, h2i);
				_k4 = k4(xi, v2i, _k1, _k2, _k3, h2i);

				// траектория с половинным шагом
				v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

				// считаем коэффициенты для траектории с половинным шагом
				_k1 = k1(xi + h2i, v2i);
				_k2 = k2(xi + h2i, v2i, _k1, h2i);
				_k3 = k3(xi + h2i, v2i, _k2, h2i);
				_k4 = k4(xi + h2i, v2i, _k1, _k2, _k3, h2i);

				// траектория с половинным шагом
				v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

				dataGridView1->Rows[i]->Cells[3]->Value = floor(v2i * 1000) / 1000;




				// коэффициенты для траектории с обычным шагом
				_k1 = k1(xi, vi);
				_k2 = k2(xi, vi, _k1, hi);
				_k3 = k3(xi, vi, _k2, hi);
				_k4 = k4(xi, vi, _k1, _k2, _k3, hi);

				vi_ = vi;  // сохраняем v(n) в отдельную переменную
				vi = next_v(vi, hi, _k1, _k2, _k3, _k4);  // считаем v(n+1)
				dataGridView1->Rows[i]->Cells[2]->Value = floor(vi * 1000) / 1000;

				dataGridView1->Rows[i]->Cells[4]->Value = floor((vi - v2i) * 1000) / 1000;


				// коэффициенты для ОЛП
				_k1 = k1(xi, vi_);
				_k2 = k2(xi, vi_, _k1, h2i);
				_k3 = k3(xi, vi_, _k2, h2i);
				_k4 = k4(xi, vi_, _k1, _k2, _k3, h2i);

				vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

				_k1 = k1(xi + h2i, vi_);
				_k2 = k2(xi + h2i, vi_, _k1, h2i);
				_k3 = k3(xi + h2i, vi_, _k2, h2i);
				_k4 = k4(xi + h2i, vi_, _k1, _k2, _k3, h2i);

				vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

				S = (vi_ - vi) / (pow(2, 4) - 1);
				OLP = S * pow(2, 4);

				if (fabs(OLP) > maxOLP) {
					maxOLP = fabs(OLP);
				}

				

				dataGridView1->Rows[i]->Cells[5]->Value = floor(OLP * 100000) / 100000;




				dataGridView1->Rows[i]->Cells[6]->Value = hi;


				xi = xi + hi;
				dataGridView1->Rows[i]->Cells[1]->Value = floor(xi * 1000) / 1000;

				reshenie_list->Add(xi, vi);

				ui = C * exp(2 * xi);
				tochnoe_list->Add(xi, ui);
				dataGridView1->Rows[i]->Cells[9]->Value = floor(ui * 1000) / 1000;
				dataGridView1->Rows[i]->Cells[10]->Value = floor(fabs(ui - vi) * 10000) / 10000;

				if (max_ui_vi < fabs(ui - vi)) {
					max_ui_vi = fabs(ui - vi);
					max_xi_ui_vi = xi;
				}

				i++;
			}
		}

		else {
			dataGridView1->Rows[0]->Cells[7]->Value = 0;
			dataGridView1->Rows[0]->Cells[8]->Value = 0;

			while (xi + hi <= xmax && i <= Nmax)
			{
				double old_vi = vi;
				double old_v2i = v2i;


				// считаем коэффициенты для траектории с половинным шагом
				_k1 = k1(xi, v2i);
				_k2 = k2(xi, v2i, _k1, h2i);
				_k3 = k3(xi, v2i, _k2, h2i);
				_k4 = k4(xi, v2i, _k1, _k2, _k3, h2i);

				// траектория с половинным шагом
				v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

				// считаем коэффициенты для траектории с половинным шагом
				_k1 = k1(xi + h2i, v2i);
				_k2 = k2(xi + h2i, v2i, _k1, h2i);
				_k3 = k3(xi + h2i, v2i, _k2, h2i);
				_k4 = k4(xi + h2i, v2i, _k1, _k2, _k3, h2i);

				// траектория с половинным шагом
				v2i = next_v(v2i, h2i, _k1, _k2, _k3, _k4);

				

				// коэффициенты для траектории с обычным шагом
				_k1 = k1(xi, vi);
				_k2 = k2(xi, vi, _k1, hi);
				_k3 = k3(xi, vi, _k2, hi);
				_k4 = k4(xi, vi, _k1, _k2, _k3, hi);

				vi_ = vi;  // сохраняем v(n) в отдельную переменную
				vi = next_v(vi, hi, _k1, _k2, _k3, _k4);  // считаем v(n+1)



				// коэффициенты для ОЛП
				_k1 = k1(xi, vi_);
				_k2 = k2(xi, vi_, _k1, h2i);
				_k3 = k3(xi, vi_, _k2, h2i);
				_k4 = k4(xi, vi_, _k1, _k2, _k3, h2i);

				vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

				_k1 = k1(xi + h2i, vi_);
				_k2 = k2(xi + h2i, vi_, _k1, h2i);
				_k3 = k3(xi + h2i, vi_, _k2, h2i);
				_k4 = k4(xi + h2i, vi_, _k1, _k2, _k3, h2i);

				vi_ = next_v(vi_, h2i, _k1, _k2, _k3, _k4);

				S = (vi_ - vi) / (pow(2, 4) - 1);

				if (fabs(S) > eps) {
					vi = old_vi;
					v2i = old_v2i;
					hi = hi / 2;
					h2i = hi / 2;

					C1++;
					
					continue;
				}
				else {
					dataGridView1->Rows->Add();

					dataGridView1->Rows[i]->Cells[6]->Value = hi;
					xi = xi + hi;
					dataGridView1->Rows[i]->Cells[1]->Value = floor(xi * 1000) / 1000;

					if (hi > max_hi) {
						max_hi = hi;
						max_xi = xi;
					}

					if (hi < min_hi) {
						min_hi = hi;
						min_xi = xi;
					}


					dataGridView1->Rows[i]->Cells[7]->Value = C1;
					dataGridView1->Rows[i]->Cells[8]->Value = C2;

					if (fabs(S) < eps / pow(2, 5)) {
						hi = 2 * hi;
						h2i = hi / 2;

						C2++;
					}


					OLP = S * pow(2, 4);

					if (fabs(OLP) > maxOLP) {
						maxOLP = fabs(OLP);
					}

					dataGridView1->Rows[i]->Cells[5]->Value = floor(OLP * 100000) / 100000;

					ui = C * exp(2 * xi);
					tochnoe_list->Add(xi, ui);
					dataGridView1->Rows[i]->Cells[9]->Value = floor(ui * 1000) / 1000;
					dataGridView1->Rows[i]->Cells[10]->Value = floor(fabs(ui - vi) * 10000) / 10000;

					if (max_ui_vi < fabs(ui - vi)) {
						max_ui_vi = fabs(ui - vi);
						max_xi_ui_vi = xi;
					}

					reshenie_list->Add(xi, vi);

					dataGridView1->Rows[i]->Cells[3]->Value = floor(v2i * 1000) / 1000;
					dataGridView1->Rows[i]->Cells[2]->Value = floor(vi * 1000) / 1000;
					dataGridView1->Rows[i]->Cells[4]->Value = floor((vi - v2i) * 1000) / 1000;


					dataGridView1->Rows[i]->Cells[0]->Value = i;
					i++;
				}
			}		
		}


		LineItem^ Curve1 = panel->AddCurve("Численное решение", reshenie_list, Color::Red,SymbolType::Plus);
		LineItem^ Curve2 = panel->AddCurve("Точное решение", tochnoe_list, Color::Blue, SymbolType::Plus);

		// Устанавливаем интересующий нас интервал по оси X
		panel->XAxis->Scale->Min = xmin_limit;
		panel->XAxis->Scale->Max = xmax_limit;
/*
		// Устанавливаем интересующий нас интервал по оси Y
		panel->YAxis->Scale->Min = ymin_limit;
		panel->YAxis->Scale->Max = ymax_limit;
*/
		// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
		// В противном случае на рисунке будет показана только часть графика, 
		// которая умещается в интервалы по осям, установленные по умолчанию
		zedGraphControl1->AxisChange();
		// Обновляем график
		zedGraphControl1->Invalidate();


		MessageBox::Show(
			"n = " + (i-1).ToString() + "\t" +
			"b - x_n = " + (xmax - xi).ToString("F6") + "\r\n" +
			"max |ОЛП| = " + maxOLP.ToString("F6") + "\r\n" +
			"Общее число делений: " + C1.ToString() + "\r\n" +
			"Общее число удвоений: " + C2.ToString() + "\r\n" +
			"max|ui - vi|: " + max_ui_vi.ToString("F6") + " при x =" + max_xi_ui_vi.ToString("F6") + "\r\n" +
			"max hi = " + max_hi.ToString("F6") + " при x = " + max_xi.ToString("F6") + "\r\n" +
			"min hi = " + min_hi.ToString("F6") + " при x = " + min_xi.ToString("F6"),
			"Результаты");

	}
	private: System::Void zedGraphControl1_Load(System::Object^  sender, System::EventArgs^  e) {
	}

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
	
	GraphPane^ panel = zedGraphControl1->GraphPane;
	double xmin = Convert::ToDouble(textBox5->Text);
	double xmax = Convert::ToDouble(textBox4->Text);
	// Устанавливаем интересующий нас интервал по оси X
	panel->XAxis->Scale->Min = xmin;
	panel->XAxis->Scale->Max = xmax;

	// Вызываем метод AxisChange (), чтобы обновить данные об осях. 
	// В противном случае на рисунке будет показана только часть графика, 
	// которая умещается в интервалы по осям, установленные по умолчанию
	zedGraphControl1->AxisChange();
	// Обновляем график
	zedGraphControl1->Invalidate();

}
};
}
