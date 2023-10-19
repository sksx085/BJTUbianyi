#include<bits/stdc++.h>
using namespace std;
int isLetter(char c) {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    else return 0;
}

int isNumber(char c) {
    if (c >= '0' && c <= '9') return 1;
    else return 0;
}

int getIdentifier_id(const char s[]) {
    if (strcmp(s, "void") == 0) {
        return 3;
    }
    else if (strcmp(s, "int") == 0) {
        return 4;
    }
    else if (strcmp(s, "float") == 0) {
        return 5;
    }
    else if (strcmp(s, "double") == 0) {
        return 6;
    }
    else if (strcmp(s, "if") == 0) {
        return 7;
    }
    else if (strcmp(s, "else") == 0) {
        return 8;
    }
    else if (strcmp(s, "for") == 0) {
        return 9;
    }
    else if (strcmp(s, "do") == 0) {
        return 10;
    }
    else if (strcmp(s, "while") == 0) {
        return 11;
    }
    else if (strcmp(s, "return") == 0) {
        return 12;
    }
    else if (strcmp(s, "break") == 0) {
        return 13;
    }
    else {
        return 1;
    }
}

int getSinglechar_id(char c) {
    if (c == ';') return 17;
    else if (c == ',') return 18;
    else if (c == '(') return 19;
    else if (c == ')') return 20;
    else if (c == '[') return 21;
    else if (c == ']') return 22;
    else if (c == '{') return 23;
    else if (c == '}') return 24;
    else if (c == '%') return 34;
    else return 0;
}

int main() {

    ifstream inputFile("t4.txt");
    ofstream outputFile("test4.txt", ios::app);
    char ch;
    inputFile.get(ch);

    while (inputFile) {
        if (ch == ' ' || ch == '\t') {
            inputFile.get(ch);
            continue;
        } else if (ch == '\n') {
            outputFile << "\n";
            inputFile.get(ch);
            continue;
        } 
        else if (isLetter(ch) == 1) {
            char s1[32];
            int i = 0;
            s1[i++] = ch;
            do {
                inputFile.get(ch);
                s1[i++] = ch;
            } while (isLetter(ch) == 1 || isNumber(ch) == 1);
            s1[i - 1] = '\0';
            int id = getIdentifier_id(s1);
            outputFile << "(" << id << "," << s1 << ")";
        } 
        else if (isNumber(ch) == 1) {
            char s2[32];
            int i = 0;
            s2[i++] = ch;
            do {
                inputFile.get(ch);
                s2[i++] = ch;
            } while (isNumber(ch) == 1);
            s2[i - 1] = '\0';
            outputFile << "(2," << s2 << ")";
        } else if (getSinglechar_id(ch) != 0) {
            outputFile << "(" << getSinglechar_id(ch) << "," << ch << ")";
            inputFile.get(ch);
        } else if (ch == '>') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(30,>=)";
                inputFile.get(ch);
            } else if (ch == '>') {
                outputFile << "(41,>>)";
                inputFile.get(ch);
            } else {
                outputFile << "(25,>)";
            }
        } else if (ch == '<') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(31,<=)";
                inputFile.get(ch);
            } else if (ch == '<') {
                outputFile << "(42,<<)";
                inputFile.get(ch);
            } else {
                outputFile << "(26,<)";
            }
        } else if (ch == '!') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(32,!=)";
                inputFile.get(ch);
            } else {
                outputFile << "(28,!)";
            }
        } else if (ch == '=') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(33,==)";
                inputFile.get(ch);
            } else {
                outputFile << "(27,=)";
            }
        } 
        else if (ch == '/') {
            inputFile.get(ch);
            if (ch == '*') {
                outputFile << "(此处是注释的开始,/*)";
                do {
                    int flag = 0;
                    inputFile.get(ch);
                    while (ch == '*') {
                        inputFile.get(ch);
                        if (ch == '/') {
                            outputFile << "(此处是注释的结束,*/)";
                            inputFile.get(ch);
                            flag = 1;
                        }
                    }
                    if (flag == 1) break;
                } while (true);
            } 
            else if (ch == '/') {
                outputFile << "(单行注释,//)";
                do {
                    inputFile.get(ch);
                } while (ch != '\n');
                outputFile << "\n";
                inputFile.get(ch);
            } 
            else if (ch == '=') {
                outputFile << "(40,/=)";
                inputFile.get(ch);
            } 
            else {
                outputFile << "(29,/)";
            }
        } 
        else if (ch == '&') {
            inputFile.get(ch);
            if (ch == '&') {
                outputFile << "(43,&&)";
                inputFile.get(ch);
            } else {
                outputFile << "(46,&)";
            }
        } 
        else if (ch == '|') {
            inputFile.get(ch);
            if (ch == '|') {
                outputFile << "(44,||)";
                inputFile.get(ch);
            } else {
                outputFile << "(46,|)";
            }
        } 
        else if (ch == '+') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(37,+=)";
                inputFile.get(ch);
            } else if (ch == '+') {
                outputFile << "(35,++)";
                inputFile.get(ch);
            } else {
                outputFile << "(14,+)";
            }
        } 
        else if (ch == '-') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(38,-=)";
                inputFile.get(ch);
            } else if (ch == '-') {
                outputFile << "(36,--)";
                inputFile.get(ch);
            } else {
                outputFile << "(15,-)";
            }
        } 
        else if (ch == '*') {
            inputFile.get(ch);
            if (ch == '=') {
                outputFile << "(39,*=)";
                inputFile.get(ch);
            } else {
                outputFile << "(16,*)";
            }
        } else {
            outputFile << "错误：未定义的符号";
            cout << "错误：未定义的符号\n";
            break;
        }
    }

    inputFile.close();
    outputFile.close();
    cout << "二元式序列组成的中间文件已生成\n";
    return 0;
}

