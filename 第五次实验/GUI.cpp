#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <iostream>
#include <stack>
#include <vector>
#include <map>

using namespace std;

vector<string> gra;
struct node
{
	int num;
	char c;
} action[110][110];
int Goto[110][110];
string s;
map<char, int> Vtcot;
map<char, int> Vncot;
int flag = 0;
void init()
{
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			action[i][j].num = -1;
	for (int i = 0; i < 110; i++)
		for (int j = 0; j < 110; j++)
			Goto[i][j] = -1;
	Vtcot['='] = 0;
	Vtcot['+'] = 1;
	Vtcot['-'] = 2;
	Vtcot['*'] = 3;
	Vtcot['/'] = 4;
	Vtcot['('] = 5;
	Vtcot[')'] = 6;
	Vtcot['i'] = 7;
	Vtcot['#'] = 8;
	Vncot['A'] = 0;
	Vncot['S'] = 1;
	Vncot['E'] = 2;
	Vncot['T'] = 3;
	Vncot['F'] = 4;
	Vncot['V'] = 5;
	gra.push_back("A->S");
	gra.push_back("S->V=E");
	gra.push_back("E->E+T");
	gra.push_back("E->E-T");
	gra.push_back("E->T");
	gra.push_back("T->T*F");
	gra.push_back("T->T/F");
	gra.push_back("T->F");
	gra.push_back("F->(E)");
	gra.push_back("F->i");
	gra.push_back("V->i");
	action[0][7].c = 's', action[0][7].num = 3;
	action[1][8].c = 'r', action[1][8].num = 0;
	action[2][0].c = 's', action[2][0].num = 4;
	action[3][0].c = 'r', action[3][0].num = 10;
	action[4][5].c = 's', action[4][5].num = 8;
	action[4][7].c = 's', action[4][7].num = 9;
	action[5][1].c = 's', action[5][1].num = 10;
	action[5][2].c = 's', action[5][2].num = 11;
	action[5][8].c = 'r', action[5][8].num = 1;
	action[6][1].c = 'r', action[6][1].num = 4;
	action[6][2].c = 'r', action[6][2].num = 4;
	action[6][3].c = 's', action[6][3].num = 12;
	action[6][4].c = 's', action[6][4].num = 13;
	action[6][6].c = 'r', action[6][6].num = 4;
	action[6][8].c = 'r', action[6][8].num = 4;
	action[7][1].c = 'r', action[7][1].num = 7;
	action[7][2].c = 'r', action[7][2].num = 7;
	action[7][3].c = 'r', action[7][3].num = 7;
	action[7][4].c = 'r', action[7][4].num = 7;
	action[7][6].c = 'r', action[7][6].num = 7;
	action[7][8].c = 'r', action[7][8].num = 7;
	action[8][7].c = 's', action[8][7].num = 9;
	action[9][1].c = 'r', action[9][1].num = 9;
	action[9][2].c = 'r', action[9][2].num = 9;
	action[9][3].c = 'r', action[9][3].num = 9;
	action[9][4].c = 'r', action[9][4].num = 9;
	action[9][6].c = 'r', action[9][6].num = 9;
	action[9][8].c = 'r', action[9][8].num = 9;
	action[10][5].c = 's', action[10][5].num = 8;
	action[10][7].c = 's', action[10][7].num = 9;
	action[11][5].c = 's', action[11][5].num = 8;
	action[11][7].c = 's', action[11][7].num = 9;
	action[12][5].c = 's', action[12][5].num = 8;
	action[12][7].c = 's', action[12][7].num = 9;
	action[13][5].c = 's', action[13][5].num = 8;
	action[13][7].c = 's', action[13][7].num = 9;
	action[14][1].c = 's', action[14][1].num = 10;
	action[14][2].c = 's', action[14][2].num = 11;
	action[14][6].c = 's', action[14][6].num = 19;
	action[15][1].c = 'r', action[15][1].num = 2;
	action[15][2].c = 'r', action[15][2].num = 2;
	action[15][3].c = 's', action[15][3].num = 12;
	action[15][4].c = 's', action[15][4].num = 13;
	action[15][6].c = 'r', action[15][6].num = 2;
	action[15][8].c = 'r', action[15][8].num = 2;
	action[16][1].c = 'r', action[16][1].num = 3;
	action[16][2].c = 'r', action[16][2].num = 3;
	action[16][3].c = 's', action[16][3].num = 12;
	action[16][4].c = 's', action[16][4].num = 13;
	action[16][6].c = 'r', action[16][6].num = 3;
	action[16][8].c = 'r', action[16][8].num = 3;
	action[17][1].c = 'r', action[17][1].num = 5;
	action[17][2].c = 'r', action[17][2].num = 5;
	action[17][3].c = 'r', action[17][3].num = 5;
	action[17][4].c = 'r', action[17][4].num = 5;
	action[17][6].c = 'r', action[17][6].num = 5;
	action[17][8].c = 'r', action[17][8].num = 5;
	action[18][1].c = 'r', action[18][1].num = 6;
	action[18][2].c = 'r', action[18][2].num = 6;
	action[18][3].c = 'r', action[18][3].num = 6;
	action[18][4].c = 'r', action[18][4].num = 6;
	action[18][6].c = 'r', action[18][6].num = 6;
	action[18][8].c = 'r', action[18][8].num = 6;
	action[19][1].c = 'r', action[19][1].num = 8;
	action[19][2].c = 'r', action[19][2].num = 8;
	action[19][3].c = 'r', action[19][3].num = 8;
	action[19][4].c = 'r', action[19][4].num = 8;
	action[19][6].c = 'r', action[19][6].num = 8;
	action[19][8].c = 'r', action[19][8].num = 8;
	Goto[0][1] = 1;
	Goto[0][5] = 2;
	Goto[4][2] = 5;
	Goto[4][3] = 6;
	Goto[4][4] = 7;
	Goto[8][2] = 14;
	Goto[8][3] = 6;
	Goto[8][4] = 7;
	Goto[10][3] = 15;
	Goto[10][4] = 7;
	Goto[11][3] = 16;
	Goto[11][4] = 7;
	Goto[12][4] = 17;
	Goto[13][4] = 18;
}
void printStacks(const vector<int> &stack1, const vector<char> &stack2, const string &s)
{
	for (int j = 0; j < stack1.size(); j++)
	{
		cout << stack1[j];
	}
	cout << "\t";
	for (int j = 0; j < stack2.size(); j++)
	{
		cout << stack2[j];
	}
	cout << "\t" << s << "\n";
}
void performReduction(vector<int> &stack1, vector<char> &stack2, const vector<string> &gra, int num1, int &i)
{
	char c1 = stack2.back();
	for (int k = 3; k < gra[action[stack1.back()][num1].num].size(); k++)
	{
		if (stack2[stack2.size() - (gra[action[stack1.back()][num1].num].size() - k)] != gra[action[stack1.back()][num1].num][k])
		{
			cout << "失败！未被接纳！\n";
			exit(-1);
		}
	}
	int tmp = stack1.back();
	int temp = gra[action[stack1.back()][num1].num].size();
	for (int k = 3; k < temp; k++)
	{
		stack2.pop_back();
		stack1.pop_back();
	}

	stack2.push_back(gra[action[tmp][num1].num][0]);
	stack1.push_back(Goto[stack1.back()][Vncot[stack2.back()]]);
}
void printlist(vector<int> &stack1, int &i, vector<char> &stack2)
{
	for (int j = 0; j < stack1.size(); j++)
	{
		cout << stack1[j];
	}
	cout << "\t";
	for (int j = 0; j < stack2.size(); j++)
	{
		cout << stack2[j];
	}
	cout << "\t";
	cout << s.substr(i) << "\t"
		 << "R" << stack1.back() << "\n";
}

void check()
{
	vector<int> stack1;
	stack1.push_back(0);
	vector<char> stack2;
	stack2.push_back('#');
	int i = 0;
	int num = 1;
	while (true)
	{
		if (num == 1)
			printStacks(stack1, stack2, s.substr(i));
		num++;
		if (stack2.size() == 2 && stack2[1] == 'S' && s[i] == '#')
		{
			cout << "语言通过！\n";
			return;
		}

		int num1 = Vtcot[s[i]];

		if (action[stack1.back()][num1].num != -1)
		{
			if (action[stack1.back()][num1].c == 's')
			{
				stack1.push_back(action[stack1.back()][num1].num);
				stack2.push_back(s[i]);
				i++;
			}
			else if (action[stack1.back()][num1].c == 'r')
			{
				performReduction(stack1, stack2, gra, num1, i);
				printlist(stack1, i, stack2);
			}
			else
			{
				cout << "句子错误！\n";
				exit(-1);
			}
		}
		else
		{
			cout << "句子错误！\n";
			exit(-1);
		}
	}
}

void grammarAnalysis(Fl_Input *input, Fl_Output *output)
{
	s = input->value();
	s += '#'; // 将输入的文本赋值给全局变量 s，并添加终止符号 '#'
	cout << "开始分析: " << s << endl;
	cout << "进行文法分析..." << endl;
	check();
	cout << "文法分析完成！" << endl;
	exit(0);
}
void create_gui()
{
	Fl_Window *window = new Fl_Window(400, 300, "文法分析");
	Fl_Input *input = new Fl_Input(150, 50, 150, 30, "输入句子：");
	Fl_Button *button = new Fl_Button(150, 150, 100, 40, "开始分析");
	button->callback([](Fl_Widget *widget, void *data)
					 {
						 Fl_Input *input = (Fl_Input *)data;
						 Fl_Output *output = (Fl_Output *)widget->parent()->child(2); // 获取输出控件
						 grammarAnalysis(input, output); },
					 input);

	window->end();
	window->show();
}

int main()
{
	init();
	Fl::lock(); // 确保多线程安全性
	create_gui();

	return Fl::run();
}
// g++ -std=c++11 -I /usr/local/include -o GUI GUI.cpp -L /usr/local/lib -lfltk -lX11 -lXext -lm
// export LIBRARY_PATH=/opt/X11/lib:$LIBRARY_PATH