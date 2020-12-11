#include <bits/stdc++.h>
using namespace std;
#define  MAX 100
template<typename T>
class operatorStack{
    T operator_array[MAX];
    int stack_size;
    int top;
public:

    operatorStack():top(-1),stack_size(0){};

    void push(T c){
        if(top==MAX){
            cout<<"stack is full unable to push";
            return;
        }
        operator_array[++top]=c;
        stack_size++;
    }
    T pop(){
        if(isempty()){
            cout<<"stack is empty\n";
            exit(1);
        }
        stack_size--;
        return operator_array[top--];
    }

    bool isempty(){
        if(top==-1){
            cout<<"stack is empty\n";
            return true;
        }
        return false;

    }
    T Top(){
        if(isempty()){
            cout<<"stack is empty\n";
            exit(1);
        }
        return operator_array[top];
    }
};

int precision(char c)
{

    if(c == '^')
    return 3;
    else if(c == '*'|| c == '/'|| c=='%')
    return 2;
    else if(c == '+' || c == '-')
    return 1;
    else return -1;
}

string infixToPostfix(string s)
{
    operatorStack<char> os;
    os.push('#');
    int length = s.length();
    string new_string="";
    for(int i = 0; i < length; i++)
    {
        if(s[i]==' ') continue;
        if(isdigit(s[i]) ||s[i]=='.' ){

            new_string+=s[i];

        }
        else if(s[i] == '('){
            new_string+=" ";
            os.push('(');
        }
        else if(s[i] == ')')
        {

            while(os.Top() != '#' && os.Top() != '(')
            {
                new_string+=" ";
                char c = os.pop();
                new_string += c;
            }
            if(os.Top() == '(')
            {
                os.pop();
            //    cout<<new_string<<endl;

            }
        }

        else{
            if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='%'||s[i]=='^'){

                new_string+=" ";
                //cout<<"operator= "<<s[i]<<endl;
                //cout<<new_string<<endl;
                while(os.Top() != '#' && precision(s[i]) <= precision(os.Top()))
                {
                    new_string+=" ";
                    char c = os.pop();
                    new_string += c;
                }
                new_string+=" ";
                os.push(s[i]);
            }
            else {
                cout<<"invalid operator"<<endl;
                new_string+=" ";
                exit(1);
            }
        }

    }
    while(os.Top() != '#')
    {
        char c = os.Top();
        os.pop();
        new_string+=" ";
        new_string += c;
    }

    //cout << endl;
    new_string+=" ";
    return new_string;

}



void calculate(string post){
    operatorStack<string> arr;
    arr.push("$");
    string array[post.length()];
    int l=0;
    for(int i=0;i<post.length();i++){
        string word;
        if(post[i]==' ') continue;
        int j=i;
        for(; post[j]!=' '; j++) {
            word+=post[j];
        }
        //cout<<"each word"<<word<<endl;
        //arr.push(word);
        array[l]=word;
        //cout<<array[l]<<"   ;";
        l++;
        i=j;
    }
    double result=0.0;
    char oper;
    for(int i=0;i<l;i++){
        if(array[i]=="+"||array[i]=="*"||array[i]=="-"||array[i]=="/"||array[i]=="%"||array[i]=="^"){
            string a=arr.pop();//cout<<"a= "<<a<<" "<<endl;
            string b=arr.pop();//cout<<"b= "<<b<<" "<<endl;
            double op1=stod(a);
            double op2=stod(b);//cout<<"op1= "<<op1<<endl;//cout<<"op2= "<<op2<<endl;
            if(array[i]=="+") result= op2+op1;
            if(array[i]=="-") result= op2-op1;
            if(array[i]=="*") result= op2*op1;
            if(array[i]=="/") result= op2/op1;
            if(array[i]=="%") result= int(op2)%int(op1);
            if(array[i]=="^") result= pow(op2,op1);
            string res=to_string(result);
            arr.push(res);
        }
        else{
            arr.push(array[i]);
        }
    }
    //cout<<"";
    cout<<std::fixed<<std::setprecision(6)<<stod(arr.pop())<<endl;
}

int main()
{
    string exp;
    cin>>exp;
    string post_expression=infixToPostfix(exp);
    calculate(post_expression);

    return 0;
}
