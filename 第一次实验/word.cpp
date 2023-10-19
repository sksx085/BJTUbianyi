#include<bits/stdc++.h>
using namespace std;
string s[110] = {"void","int","float","double","if","else","for","do","while","return","break","main","include"};

int main(){

    ifstream input("test.txt");
    ofstream output("output.txt", ios::app);
    char ch;
    input.get(ch);

    while(input){
    	if(ch == ' '||ch == '\t'){
    		input.get(ch);
    		continue;
		}

		else if(ch == '\n'){
			output<<endl;
			input.get(ch);
			continue;
		}

		else if(isalpha(ch)){
			char str[100];
			int amt = 0;
            int mid = 0;
			str[amt++] = ch;
			do{
				input.get(ch);
				str[amt++] = ch;
			}while(isalnum(ch));
			str[amt - 1] = '\0';
			for(int i = 0;i <= 12;i++){
				if(str == s[i]){
				output << "[Key words] : "<< str <<endl;
                mid = 1;
                }
			}
            if(mid == 0)
                output << "[STR] :" << str << endl;
		}

		else if(isdigit(ch)){
			char str1[100];
			int amt = 0;
			str1[amt++] = ch;
			do{
				input.get(ch);
				str1[amt++] = ch;
			}while(isdigit(ch));
			str1[amt - 1] = '\0';
			output << "[number]:" << str1 <<endl;
			input.get(ch);
		}

		else if(ch == '!' || ch == '@' || ch == '#' || ch == '$' || ch == '%'||ch == '^' || ch == '&' || ch == '*' || ch == '(' || ch == ')'||ch == '{' || ch == '}'||ch == '[' ||  ch == ']' || ch == ';'){
				output << "[Special characters] : "<< ch << endl;
			input.get(ch);
		}

		else if (ch == '>') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :>= \n";
                input.get(ch);
            } else if (ch == '>') {
                output << "[calculating signs] :>> \n";
                input.get(ch);
            } else {
                output << "[calculating signs] :> \n";
            }
        }

		else if (ch == '<') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :<= \n";
                input.get(ch);
            } else if (ch == '<') {
                output << "[calculating signs] :<< \n";
                input.get(ch);
            } else {
                output << "[calculating signs] :< \n";
            }
        }

		else if (ch == '!') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :!= \n";
                input.get(ch);
            } else {
                output << "[calculating signs] :! \n";
            }
        }

		else if (ch == '=') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :== \n";
                input.get(ch);
            } else {
                output << "[calculating signs] := \n";
            }
        }

        else if (ch == '&') {
            input.get(ch);
            if (ch == '&') {
                output << "[calculating signs] :&& \n";
                input.get(ch);
            } else {
                output << "[calculating signs] :& \n";
            }
        }
        else if (ch == '|') {
            input.get(ch);
            if (ch == '|') {
                output << "[calculating signs] :|| \n";
                input.get(ch);
            } else {
                output << "[calculating signs] : | \n";
            }
        }

        else if (ch == '+') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] : +=\n";
                input.get(ch);
            } else if (ch == '+') {
                output << "[calculating signs] :++ \n";
                input.get(ch);
            } else {
                output << "[calculating signs] :+ \n";
            }
        }
        
        else if (ch == '-') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :-=\n";
                input.get(ch);
            } else if (ch == '-') {
                output << "[calculating signs] :--\n";
                input.get(ch);
            } else {
                output << "[calculating signs] :-\n";
            }
        }

        else if (ch == '*') {
            input.get(ch);
            if (ch == '=') {
                output << "[calculating signs] :*=\n";
                input.get(ch);
            } else {
                output << "[calculating signs] :*\n";
            }
        }

		else if (ch == '/') {
            input.get(ch);
            if (ch == '*') {
                output << "[Start annotation] :/*\n [test] : ";
                do {
                    int flag = 0;
					int amt = 0;
					char s[110];
                    input.get(ch);
					while(ch != '*'){
						input.get(ch);
						s[amt++] = ch;
					}
                    while(ch == '*') {
                        input.get(ch);
                        if (ch == '/') {
							s[amt - 1] = '\0';
							output << s;
							output << "\n";
                            output << "[end annotation] : */ \n";
                            input.get(ch);
                            flag = 1;
                        }
                    }
                    if (flag == 1)
                        break;
                } while (true);
            }

            else if (ch == '/') {
                output << "[Inline comments] : // \n[test] : ";
				int amt = 0;
				char s[110];
                do {
                    input.get(ch);
					s[amt++] = ch;
                } while (ch != '\n');
				amt++;
				s[amt - 1] = '\0';
				output << s;
                output << "\n";
                input.get(ch);
            }
            else if (ch == '=') {
                output << "[calculating signs] :/= \n";
                input.get(ch);
            }
            else {
                output << "[calculating signs] : / \n";
            }
        }
        else {
            output << "[ERROR!!!] CHECK INPUT!!!\n";
            input.get(ch);
        }
	}
	input.close();
    output.close();
	cout << "Analysis completed!\n";
    return  0;
}
