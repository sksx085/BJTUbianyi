#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>

using namespace std;
ifstream input("test.txt");
ofstream output("output.txt",ios::app);
string str,s;
int flag = 0,amt = 0;


void checkF();
void checkS();
void checkMUlT();
void checkT_();
void checkT();
void checkVOC();
void checkADD();
void checkE();
void checkE_();



void checkT(){
    if(flag==0){
    	output << "check T:" << "\t";
        if(s[amt]=='('||s[amt]=='i'){
            checkF();
            if(flag==0){
            	if(s[amt]=='*'||s[amt]=='/'){
            		checkT_();
				}
				else if(s[amt]=='+'||s[amt]=='-'||s[amt]==')'||s[amt]=='#') {
					return;
				}
				else{
					flag=1;
                    output << "T goes ERROR!!!" << "\n";
                    output << "ERROR num is:" << amt << endl;
                      
				}
			}
        }
        else{
        	flag=1;
        	output << "T goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
		}
    }
}
void checkT_(){
    if(flag == 0){
        output << "check T_:"<<'\t';
        if(s[amt] == '*' || s[amt] == '/'){
            checkMUlT();
            if(flag == 0){
                checkF();
                if(flag == 0){
                    checkT_();
                }
            }
        }
        else if(s[amt] == '+' || s[amt] == '-' || s[amt] == ')' || s[amt] == '#'){
            return ;
        }
        else{
            flag = 1;
            output << "T_ goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void checkF(){
    if(flag == 0){
        output << "check F:" << "\t";
        if(s[amt] == '('){
            amt++ ;
            if(s[amt] == '(' || s[amt] == 'i'){
                checkE();
                if(flag == 0){
                    if(s[amt] == ')')
                        amt++;
                    else{
                        flag = 1;
                        output << "F goes ERROR!!!" << "\n";
                        output << "ERROR num is:" << amt << endl;
                          
                    }
                }
            }
            else{
                flag = 1;
                output << "F goes ERROR!!!" << "\n";
                output << "ERROR num is:" << amt << endl;
                  
            }
        }
        else if(s[amt] == 'i')
            amt++;
        else{
            flag = 1;
            output << "F goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void checkADD(){
    if(flag == 0){
        output<<"check ADD:" << "\t";
        if(s[amt] == '+' || s[amt] == '-'){
            amt++;
        }
        else{
            flag = 1;
            output << "ADD goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void checkMUlT(){
    if(flag == 0){
        output<<"check MULT:" << "\t";
        if(s[amt] == '*' || s[amt] == '/'){
            amt++;
        }
        else{
            flag = 1;
            output << "MULT goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void checkVOC(){
    if(flag == 0){
        output<<"check V:" << "\t";
        if(s[amt] == 'i'){
            amt++;
        }
        else{
            flag = 1;
            output << "V goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void checkE(){
    if(flag == 0){
        output << "check E:" << "\t";
        if(s[amt] == '(' || s[amt] == 'i'){
            checkT();
            if(flag==0){
            	if(s[amt]=='+'||s[amt]=='-'){
            		checkE_();
				}   
				else if(s[amt]==')'||s[amt]=='#'){
        			return; //rollback
				}
				else{
					flag=1;
					output << "E goes ERROR!!!" << "\n";
                    output << "ERROR num is:" << amt << endl;
                      
				}
			}  
        }
        else{
			flag=1;
			output << "E goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
		}
    }
}
void checkE_(){
    if(flag == 0){
        output << "check E_:" << "\t";
        if(s[amt] == '+' || s[amt] == '-'){
            checkADD();
            if(flag == 0){
                if(s[amt] == '(' || s[amt] == 'i'){
                    checkT();
                    if(s[amt] == '+' || s[amt] == '-'){
                        checkE_();
                    }
                    else if(s[amt] == ')' || s[amt] == '#'){
                        return ;
                    }
                    else{
                        flag = 1;
                        output << "E_ goes ERROR!!!" << "\n";
                        output << "ERROR num is:" << amt << endl;
                          
                    }
                }
            }
        }
    }
}
void checkS(){
    if(flag == 0){
        output << "check S :" << "\t";
        if(s[amt] == 'i'){
            checkVOC();
            if(flag == 0 && s[amt] == '='){
                amt++;
                checkE();
            }
            else{
                flag = 1;
                output << "S goes ERROR!!!" << "\n";
                output << "ERROR num is:" << amt << endl;
                  
            }
        }
        else{
            flag = 1;
            output << "S goes ERROR!!!" << "\n";
            output << "ERROR num is:" << amt << endl;
              
        }
    }
}
void fcheck(){
    if(s[0] == '#'){
        output<< "system stop!!!" << "\n";
          
    }
}
int main(){
    if(input.is_open()){
        getline(input,str);
        input.close();
        s = str;
        //output << s.length() << endl;
    }
    int len = s.length();
    s += '#';
    for(int i = 0;i < len;i++){
        if(isalpha(s[i]))
            s[i] = 'i';
    }
    //output<< str << "\n";
    fcheck();
    checkS();
    output << "\n";
    if(flag == 0){
        output << "legal" << "\n";
    }
    if(flag == 1){
        output << "illegal" << "\n";
    }
    cout << "program complete!" << "\n";
    output.close();
    return 0;
}