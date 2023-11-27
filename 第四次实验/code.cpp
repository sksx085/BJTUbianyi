#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <stack>

using namespace std;

vector<string> gra;
vector<char> Vn, Vt;
map<char, int> Vncot, Vtcot;
vector<char> firstVt[100], lastVt[100];
char table[100][100];
vector<char> analst;
string anastr;

ofstream out1("progress.txt", ios::app);
ofstream out2("firstvt.txt", ios::app);
ofstream out3("lastvt.txt", ios::app);
ofstream out4("table.txt", ios::app);
ofstream out5("Vn&Vt.txt", ios::app);

bool inanalst(const vector<char> &vec, char target)
{
	for (char element : vec)
	{
		if (element == target)
		{
			return true;
		}
	}
	return false;
}

void getfirstvt()
{
	out2 << "计算FirstVT集合:\n";
	out2 << "第1轮:\n";
	int iteration = 1;
	int num[100] = {0};
	for (int i = 0; i < gra.size(); i++)
	{
		out2 << gra[i][0] << ": "; // 打印当前处理的非终结符
		int stat = 0;			   // stat 用于标记是否处理到产生式的右部
		for (int j = 3; j < gra[i].size(); j++)
		{
			if (!isupper(gra[i][j]) && gra[i][j] != '|' && stat == 0)
			{
				if (stat == 0)
				{
					firstVt[Vncot[gra[i][0]]].push_back(gra[i][j]);
					out2 << gra[i][j] << " ";
					stat = 1;
				}
			}
			if (gra[i][j] == '|')
				stat = 0;
		}
		out2 << "\n";
	}
	iteration++;
	bool flag = false;

	do
	{
		out2 << "第" << iteration++ << "轮:\n";
		flag = true;

		for (int i = 0; i < gra.size(); i++)
		{
			if (num[i] != firstVt[i].size())
			{
				flag = false;
				num[i] = firstVt[i].size();
			}
		}

		if (flag == true)
		{
			out2 << "结束\n";
			break;
		}

		for (int i = 0; i < gra.size(); i++)
		{

			int flag = 0;

			for (int j = 3; j < gra[i].size(); j++)
			{
				if (isupper(gra[i][j]))
				{
					if (flag == 0)
					{
						for (int k = 0; k < firstVt[Vncot[gra[i][j]]].size(); k++)
						{
							if (!inanalst(firstVt[i], firstVt[Vncot[gra[i][j]]][k]))
							{
								firstVt[i].push_back(firstVt[Vncot[gra[i][j]]][k]);
							}
						}
					}
				}
				if (gra[i][j] == '|')
				{
					flag = 0;
					continue;
				}
				flag = 1;
			}
			out2 << gra[i][0] << ": ";
			for (int j = 0; j < firstVt[i].size(); j++)
			{
				out2 << firstVt[i][j] << " ";
			}
			out2 << "\n";
		}
	} while (true);

	out2 << "firstVT如下：\n";
	for (int i = 0; i < gra.size(); i++)
	{
		out2 << Vn[i] << ": ";
		for (int j = 0; j < firstVt[i].size(); j++)
		{
			out2 << firstVt[i][j] << " ";
		}
		out2 << '\n';
	}
	out2.close();
}

void getlastvt()
{
	out3 << "计算lastVt集合:\n";
	out3 << "第1轮:\n";
	int iteration = 1;
	int num[100] = {0};
	for (int i = 0; i < gra.size(); i++)
	{
		out3 << gra[i][0] << ": "; // 打印当前处理的非终结符
		int stat = 0;			   // stat 用于标记是否处理到产生式的右部
		for (int j = gra[i].size() - 1; j >= 3; j--)
		{
			if (!isupper(gra[i][j]) && gra[i][j] != '|')
			{
				if (stat == 0)
				{
					lastVt[i].push_back(gra[i][j]);
					out3 << gra[i][j] << " ";
					stat = 1;
				}
			}
			if (gra[i][j] == '|')
				stat = 0;
		}
		out3 << "\n";
	}
	iteration++;
	bool flag = false;

	do
	{
		out3 << "第" << iteration++ << "轮:\n";
		flag = true;

		for (int i = 0; i < gra.size(); i++)
		{
			if (num[i] != lastVt[i].size())
			{
				flag = false;
				num[i] = lastVt[i].size();
			}
		}

		if (flag == true)
		{
			out3 << "结束\n";
			break;
		}

		for (int i = 0; i < gra.size(); i++)
		{

			int flag = 0;

			for (int j = gra[i].size() - 1; j >= 3; j--)
			{
				if (isupper(gra[i][j]))
				{
					if (flag == 0)
					{
						for (int k = 0; k < lastVt[Vncot[gra[i][j]]].size(); k++)
						{
							if (!inanalst(lastVt[i], lastVt[Vncot[gra[i][j]]][k]))
							{
								lastVt[i].push_back(lastVt[Vncot[gra[i][j]]][k]);
							}
						}
					}
				}
				if (gra[i][j] == '|')
				{
					flag = 0;
					continue;
				}
				flag = 1;
			}
			out3 << gra[i][0] << ": ";
			for (int j = 0; j < lastVt[i].size(); j++)
			{
				out3 << lastVt[i][j] << " ";
			}
			out3 << "\n";
		}
	} while (true);

	out3 << "lastVt如下：\n";
	for (int i = 0; i < gra.size(); i++)
	{
		out3 << Vn[i] << ": ";
		for (int j = 0; j < lastVt[i].size(); j++)
		{
			out3 << lastVt[i][j] << " ";
		}
		out3 << '\n';
	}
	out3.close();
}

void gettable()
{
	memset(table, '*', sizeof(table));
	for (int i = 0; i < gra.size(); i++)
	{
		for (int j = 3; j < gra[i].size(); j++)
		{
			if (j < gra[i].size() - 1 && (isupper(gra[i][j + 1])) && ((!isupper(gra[i][j])) && gra[i][j] != '|'))
			{
				int num1 = Vncot[gra[i][j + 1]];
				int num2 = Vtcot[gra[i][j]];
				for (int k = 0; k < firstVt[num1].size(); k++)
				{
					if (table[num2][Vtcot[firstVt[num1][k]]] == '*' || table[num2][Vtcot[firstVt[num1][k]]] == '<')
					{
						table[num2][Vtcot[firstVt[num1][k]]] = '<';
					}
					else
					{
						out4 << "错误！ 错误发生在：\t";
						out4 << i << "次序中\n";
						out4 << gra[i][j] << "与" << firstVt[num1][k] << "关系不唯一！\n";
						exit(-1);
					}
				}
			}
			if (j > 3 && (isupper(gra[i][j - 1])) && (!isupper(gra[i][j])) && gra[i][j] != '|')
			{
				int num1 = Vncot[gra[i][j - 1]];
				int num2 = Vtcot[gra[i][j]];
				for (int k = 0; k < lastVt[num1].size(); k++)
				{
					if (table[Vtcot[lastVt[num1][k]]][num2] == '*' || table[Vtcot[lastVt[num1][k]]][num2] == '>')
					{
						table[Vtcot[lastVt[num1][k]]][num2] = '>';
					}
					else
					{
						out4 << "错误！ 错误发生在：\t";
						out4 << num1 << "次序中\n";
						out4 << lastVt[num1][k] << "与" << gra[i][j] << "关系不唯一！\n";
						exit(-1);
					}
				}
			}
			if (j > 3 && j < gra[i].size() && (isupper(gra[i][j])) && ((!isupper(gra[i][j - 1])) && gra[i][j - 1] != '|') && ((!isupper(gra[i][j + 1])) && gra[i][j + 1] != '|'))
			{
				int num1 = Vtcot[gra[i][j - 1]];
				int num2 = Vtcot[gra[i][j + 1]];
				if (table[num1][num2] == '*' || table[num1][num2] == '=')
				{
					table[num1][num2] = '=';
				}
				else
				{
					out4 << "错误！ 错误发生在：\t";
					out4 << i << "次序中\n";
					out4 << gra[i][j - 1] << "与" << gra[i][j + 1] << "关系不唯一！\n";
					exit(-1);
				}
			}
		}
	}
	Vt.push_back('#');
	int num3 = Vtcot['#'];
	table[num3][num3] = '=';
	for (int i = 0; i < firstVt[Vncot[gra[0][0]]].size(); i++)
	{
		int num4 = Vtcot[firstVt[Vncot[gra[0][0]]][i]];
		table[num3][num4] = '<';
	}
	for (int i = 0; i < lastVt[Vncot[gra[0][0]]].size(); i++)
	{
		int num4 = Vtcot[lastVt[Vncot[gra[0][0]]][i]];
		table[num4][num3] = '>';
	}
	out4 << " ";
	for (int i = 0; i < Vt.size(); i++)
	{
		out4 << Vt[i] << " ";
	}
	out4 << "\n";
	for (int i = 0; i < Vt.size(); i++)
	{
		out4 << "__";
	}
	out4 << "\n";
	for (int i = 0; i < Vt.size(); i++)
	{
		out4 << Vt[i] << " ";
		for (int j = 0; j < Vt.size(); j++)
		{
			out4 << table[i][j] << " ";
		}
		out4 << "\n";
	}
	out4.close();
}

int getRule()
{
	out5 << "Vn:\n";

	// 循环遍历文法规则
	for (int i = 0; i < gra.size(); i++)
	{
		// 检查文法规则的开头是否符合非终结符的格式
		if ((isupper(gra[i][0])) && gra[i][1] == '-' && gra[i][2] == '>')
		{
			// 如果是非终结符，则将其添加到Vn数组中
			Vn.push_back(gra[i][0]);
			Vncot[gra[i][0]] = i;	  // 使用非终结符映射到文法规则的索引
			out5 << gra[i][0] << ' '; // 打印非终结符
		}
		else
		{
			// 如果不符合非终结符格式，则打印当前文法规则索引并返回-1
			out5 << i << "\n";
			return -1;
		}
	}
	out5 << "\n";
	out5 << "Vt:\n";
	int num1 = 0;
	// 循环遍历文法规则
	for (int i = 0; i < gra.size(); i++)
	{
		for (int j = 3; j < gra[i].size(); j++)
		{
			// 检查文法规则右侧的字符是否为终结符，并且不是 '|' 或 'e'
			if ((!isupper(gra[i][j])) && gra[i][j] != '|')
			{
				int t, flag = 0;
				// 检查字符是否已存在于Vt数组中
				for (t = 0; t < Vt.size(); t++)
				{
					if (gra[i][j] == Vt[t])
					{
						flag = 1;
						break;
					}
				}
				// 如果字符不在Vt数组中，则将其添加到Vt数组中，并记录其位置到Vtcot中
				if (!flag)
				{
					Vtcot[gra[i][j]] = num1++;
					Vt.push_back(gra[i][j]);
					out5 << gra[i][j] << " "; // 打印终结符
				}
			}
		}
	}
	// 将结束符号 '#' 添加到Vt数组末尾，并记录其位置到Vtcot中
	Vt.push_back('#');
	Vtcot['#'] = num1;
	out5 << "\n";
	return 1; // 返回1表示成功
	out5.close();
}

void getrule()
{
	ifstream input("rules.txt");
	if (!input)
	{
		cout << "ruleput went wrong!\n";
		exit(-1);
	}
	string s1;
	while (getline(input, s1))
		gra.push_back(s1);
	input.close();
	getRule();
	getfirstvt();
	getlastvt();
	gettable();
}

void anaylse()
{
	ifstream input1("anaylsetxt.txt");
	if (!input1)
	{
		out1 << "无法打开！！！\n";
		exit(-1);
	}
	getline(input1, anastr);
	input1.close();
	anastr += '#';
	int cot, i = 0, step = 0;
	char c;
	analst.push_back('#');
	do
	{
		cot = analst.size() - 1;
		while (analst[cot] == 'N')
		{
			cot--;
		}
		if (table[Vtcot[analst[cot]]][Vtcot[anastr[i]]] == '>')
		{
			c = Vtcot[analst[cot]];
			while (analst[cot] == 'N' || Vtcot[analst[cot]] == c)
			{
				cot--;
			}
			for (int p = 0; p < analst.size(); p++)
			{
				out1 << analst[p];
			}
			out1 << "    ";
			for (int p = i; p < anastr.length(); p++)
			{
				out1 << anastr[p];
			}
			out1 << "\t执行归约\n";
			analst.erase(analst.begin() + cot + 1, analst.end());
			analst.push_back('N');
		}
		else if (table[Vtcot[analst[cot]]][Vtcot[anastr[i]]] == '<' || table[Vtcot[analst[cot]]][Vtcot[anastr[i]]] == '=')
		{
			analst.push_back(anastr[i]);
			i++;
			for (int p = 0; p < analst.size(); p++)
			{
				out1 << analst[p];
			}
			out1 << "    ";
			for (int p = i; p < anastr.length(); p++)
			{
				out1 << anastr[p];
			}
			out1 << "  ";
			if (anastr[i] != '#')
			{
				out1 << "\t执行移进"
					 << "\n";
			}
			else
				out1 << "\n";
		}
		else
		{
			out1 << "句子有误"
				 << "\n";
			exit(0);
		}
	} while (anastr[i] != '#');

	cot = analst.size() - 1;
	while (cot > 0)
	{
		while (analst[cot] == 'N')
			cot--;
		if (table[Vtcot[analst[cot]]][Vtcot[anastr[i]]] == '>')
		{
			c = Vtcot[analst[cot]];
			while (analst[cot] == 'N' || Vtcot[analst[cot]] == c)
			{
				cot--;
			}
			analst.erase(analst.begin() + cot + 1, analst.end());
			analst.push_back('N');
			for (int p = 0; p < analst.size(); p++)
			{
				out1 << analst[p];
			}
			out1 << "    ";
			for (int p = i; p < anastr.length(); p++)
			{
				out1 << anastr[p];
			}
			out1 << "\t执行归约\n";
		}
		else
		{
			out1 << "句子有误"
				 << "\n";
			exit(0);
		}
	}
	if(analst.size() == 2 && analst[0] == '#' && analst[1] == 'N'){
		out1 << "分析成功！符合语法！\n";
	}
	out1.close();
}
int main()
{
	getrule();
	anaylse();
	return 0;
}
#pragma GCC diagnostic pop