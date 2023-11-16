#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <iostream>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <stack>

using namespace std;

string anastr;
vector<string> gra;
vector<char> Vn;
vector<char> Vt;
map<char, int> Vncot;
map<char, int> Vtcot;
vector<char> table[20][20];
vector<char> analst;
vector<char> first[10], follow[10];

ofstream out1("progress.txt", ios::app);
ofstream out2("first.txt", ios::app);
ofstream out3("follow.txt", ios::app);
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

void getfirst()
{
	out2 << "计算First集合:\n";
	out2 << "第1轮:\n";
	int iteration = 1;
	int num[100] = {0};
	for (int i = 0; i < gra.size(); i++)
	{
		out2 << gra[i][0] << ": "; // 打印当前处理的非终结符

		int stat = 0; // stat 用于标记是否处理到产生式的右部
		for (int j = 3; j < gra[i].size(); j++)
		{
			if (!isupper(gra[i][j]) && gra[i][j] != '|' && stat == 0)
			{
				if (!inanalst(first[Vncot[gra[i][0]]], gra[i][j])) // inanalst(first[Vncot[gra[i][0]]],gra[i][j])
				{
					first[Vncot[gra[i][0]]].push_back(gra[i][j]);
					out2 << gra[i][j] << " ";
				}
			}
			stat = 1;
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
			if (num[i] != first[i].size())
			{
				flag = false;
				num[i] = first[i].size();
			}
		}

		if (flag == true)
		{
			out2 << "结束\n";
			break;
		}

		for (int i = 0; i < gra.size(); i++)
		{
			int nonTerminalIndex = Vncot[gra[i][0]];
			out2 << gra[i][0] << ": ";
			int flag = 0;

			for (int j = 3; j < gra[i].size(); j++)
			{
				if (isupper(gra[i][j]))
				{
					for (int k = 0; k < first[Vncot[gra[i][j]]].size(); k++)
					{
						if (first[Vncot[gra[i][j]]][k] != 'e' && !inanalst(first[nonTerminalIndex], first[Vncot[gra[i][j]]][k]) && flag == 0) //
						{
							first[nonTerminalIndex].push_back(first[Vncot[gra[i][j]]][k]);
						}
					}
				}
				flag = 1;
				if (gra[i][j] == '|')
				{
					flag = 0;
				}
			}

			for (int j = 0; j < first[nonTerminalIndex].size(); j++)
			{
				out2 << first[nonTerminalIndex][j] << " ";
			}
			out2 << "\n";
		}
	} while (true);

	out2.close();
}

void computeFirstFollow()
{
	// 初始的Follow集合计算
	follow[Vncot[gra[0][0]]].push_back('#'); // 初始化起始符号的Follow集合为#
	out3 << "计算Follow集合:\n";
	out3 << "第1轮:\n";

	for (int i = 0; i < gra.size(); i++)
	{
		for (int j = 3; j < gra[i].size(); j++)
		{
			if ((isupper(gra[i][j])))
			{
				int num1 = Vncot[gra[i][j]];
				if (j < gra[i].size() - 1)
				{
					if ((!isupper(gra[i][j + 1])) && gra[i][j + 1] != '|')
					{
						if (!inanalst(follow[num1], gra[i][j + 1]))
						{
							follow[num1].push_back(gra[i][j + 1]);
						}
					}
					else if (isupper(gra[i][j + 1]))
					{
						int num2 = Vncot[gra[i][j + 1]];
						for (int k = 0; k < first[num2].size(); k++)
						{
							if (first[num2][k] != 'e' && (!inanalst(follow[num1], first[num2][k])))
							{
								follow[num1].push_back(first[num2][k]);
							}
						}
					}
				}
				else
				{
					if (inanalst(follow[num1],'e'))
					{
						follow[num1].push_back('e');
					}
				}
			}
		}
	}
}

void printFollowSets()
{
	// 打印Follow集合结果
	for (int i = 0; i < gra.size(); i++)
	{
		out3 << gra[i][0] << ": ";
		for (char c : follow[Vncot[gra[i][0]]])
		{
			out3 << c << " ";
		}
		out3 << "\n";
	}
}

void updateFollowSets()
{
	// 更多轮次的Follow集合计算
	int iteration = 2;
	int num[100] = {0};

	while (true)
	{
		out3 << "第" << iteration++ << "轮:\n";
		bool sign = true;

		// 检查是否有变化，若无变化则结束循环
		for (int i = 0; i < gra.size(); i++)
		{
			if (num[i] != follow[i].size())
			{
				sign = false;
				num[i] = follow[i].size();
			}
		}

		if (sign == true)
		{
			out3 << "结束\n";
			break;
		}

		for (int i = 0; i < gra.size(); i++)
		{
			for (int j = 3; j < gra[i].size(); j++)
			{
				if ((gra[i][j] >= 'A' && gra[i][j] <= 'Z'))
				{
					if (j < gra[i].size() - 1)
					{
						if (gra[i][j + 1] == '|')
						{
							int num3 = Vncot[gra[i][0]];
							int num4 = Vncot[gra[i][j]];
							for (int k = 0; k < follow[num3].size(); k++)
							{
								if (!inanalst(follow[num4], follow[num3][k]))
								{
									follow[num4].push_back(follow[num3][k]);
								}
							}
						}
						else if (isupper(gra[i][j + 1]))
						{
							int num5 = Vncot[gra[i][j + 1]];
							if (inanalst(first[num5], 'e'))
							{
								int num4 = Vncot[gra[i][j]];
								for (int k = 0; k < follow[num5].size(); k++)
								{
									if (!inanalst(follow[num4], follow[num5][k]))
									{
										follow[num4].push_back(follow[num5][k]);
									}
								}
							}
						}
					}
					else if (j == gra[i].size() - 1)
					{
						int num3 = Vncot[gra[i][0]];
						int num4 = Vncot[gra[i][j]];
						for (int k = 0; k < follow[num3].size(); k++)
						{
							if (!inanalst(follow[num4], follow[num3][k]))
							{
								follow[num4].push_back(follow[num3][k]);
							}
						}
					}
				}
			}
		}

		// 打印Follow集合结果
		printFollowSets();
	}
}

void getfollow()
{
	computeFirstFollow(); // 初始的Follow集合计算

	// 打印初始的Follow集合结果
	printFollowSets();

	// 更新并计算更多轮次的Follow集合
	updateFollowSets();

	out3.close();
}

void printTerminalList()
{
	out4 << "表格如下: \n ";

	// 打印终结符列表
	for (const auto &terminal : Vt)
	{
		out4 << terminal << "   ";
	}
	out4 << "\n";
	for (int j = 0; j < Vt.size(); j++)
	{
		out4 << "___";
	}
	out4 << "\n";
}

void processGrammarSymbols()
{
	// 对每个文法符号循环
	for (int i = 0; i < gra.size(); i++)
	{
		out4 << gra[i][0] << ": ";	 // 打印当前文法符号
		int num1 = Vncot[gra[i][0]]; // 获取文法符号在 Vn 数组中的位置

		// 对于每个终结符循环
		// 对于每个终结符循环
		for (int j = 0; j < Vt.size(); j++)
		{
			// 如果当前终结符在文法符号的 FIRST 集合中
			if (inanalst(first[num1], Vt[j]))
			{
				int stat = 0;
				// 遍历文法产生式右部
				for (int k = 3; k < gra[i].size(); k++)
				{
					// 如果当前字符是非终结符
					if (isupper(gra[i][k]))
					{
						if (stat == 0)
						{
							int num2 = Vncot[gra[i][k]];
							// 如果当前非终结符的 FIRST 集合包含当前终结符
							if (inanalst(first[num2],Vt[j]))
							{
								// 将文法产生式右部加入相应的表格中
								while (k < gra[i].size() && gra[i][k] != '|')
								{
									table[num1][j].push_back(gra[i][k]);
									k++;
								}
								break;
							}
						}
					}
					// 如果当前字符是终结符
					if (gra[i][k] == Vt[j])
					{
						if (stat == 0)
						{
							// 将文法产生式右部加入相应的表格中
							while (k < gra[i].size() && gra[i][k] != '|')
							{
								table[num1][j].push_back(gra[i][k]);
								k++;
							}
							break;
						}
					}
					stat = 1;
					if (gra[i][k] == '|')
					{
						stat = 0;
					}
				}
			}
			else if (inanalst(first[num1],'e') &&
					inanalst(follow[num1],Vt[j]))
			{
				// 如果空串在文法符号的 FIRST 集合中，并且当前终结符在 FOLLOW 集合中
				table[num1][j].push_back('e'); // 将空串加入相应的表格中
			}
		}

		// 打印构建的表格
		for (int j = 0; j < Vt.size(); j++)
		{
			if (!table[num1][j].empty())
			{
				for (char c : table[num1][j])
				{
					out4 << c;
				}
				out4 << "  ";
			}
			else
			{
				out4 << "** "; // 如果表格为空，则打印 "** "
			}
		}
		out4 << "\n";
	}
}

void gettable()
{
	printTerminalList();
	processGrammarSymbols();
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
			if ((!isupper(gra[i][j])) && gra[i][j] != '|' && gra[i][j] != 'e')
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
}

void getrule()
{
	ifstream input("rules.txt");
	if (!input)
	{
		cout << "rules wrong!"
			 << "\n";
		exit(-1);
	}
	string s1;
	while (getline(input, s1))
		gra.push_back(s1);
	input.close();
	if (getRule() != 1)
	{
		cout << "rules wrong!"
			 << "\n";
		exit(-1);
	}
	getfirst();
	getfollow();
	gettable();
}

bool checktopVn(int i)
{
	char top = analst.back();
	return (inanalst(Vn, top));
}

bool checktopVt(int i)
{
	char top = analst.back();
	return (inanalst(Vt, top));
}

bool checkok(char c)
{
	char top_non_terminal = analst.back();
	int non_terminal_index = Vncot[top_non_terminal];
	int terminal_index = Vtcot[c];
	return !table[non_terminal_index][terminal_index].empty();
}

void printanalst(int n)
{
	out1 << "栈内容: ";
	for (int i = 0; i < analst.size(); i++)
	{
		out1 << analst[i] << " ";
	}
	out1 << "   剩余输入: ";
	for (int i = n; i < anastr.size(); i++)
	{
		out1 << anastr[i] << " ";
	}
	out1 << "\n";
}

int main()
{
	ifstream open("input.txt");
	if (!open)
	{
		cout << "files wrong!"
			 << "\n";
		exit(-1);
	}
	string begin = "i";
	getline(open, anastr);
	getrule();
	anastr += '#';
	analst.push_back('#');
	analst.push_back(gra[0][0]);
	int len = 0;
	while (!analst.empty() && len != anastr.length())
	{
		printanalst(len);
		if (checktopVn(len))
		{
			if (checkok(anastr[len]))
			{
				char check = analst.back();
				out1 << check << " 更改规则为：";
				analst.pop_back();
				char check2 = anastr[len];
				if (table[Vncot[check]][Vtcot[check2]][0] != 'e')
				{
					for (int j = table[Vncot[check]][Vtcot[check2]].size() - 1; j >= 0; j--)
					{
						out1 << table[Vncot[check]][Vtcot[check2]][j] << " ";
						analst.push_back(table[Vncot[check]][Vtcot[check2]][j]);
					}
					out1 << "\n";
				}
				else
				{
					out1 << "e\n";
				}
			}
			else
			{
				break;
			}
		}
		else if (checktopVt(len))
		{
			char c = anastr[len];
			if (c != analst.back())
			{
				break;
			}
			else
			{
				analst.pop_back();
				len++;
			}
		}
	}
	/*cout << len << " " << anastr.length() << "\n";
	for(auto it : analst){
		cout << it << "\n";
	}
	*/
	if (analst.empty() && len == anastr.length())
		cout << "success!"
			 << "\n";
	else
		cout << "failed!"
			 << "\n";
	open.close();
	return 0;
}
#pragma GCC diagnostic pop