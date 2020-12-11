#include<bits/stdc++.h>
using namespace std;
class BigInteger {

public:
    string number;
    BigInteger() { // empty constructor initializes zero
        number = "0";
    }
    BigInteger(string b) {
        this->number = b;
    }
    BigInteger(int b) {
        this->number = to_string(b);
    }

    BigInteger operator=(BigInteger b){
        //BigInteger k{"0"};
        this->number= b.number;
        //return k;
        return *this;
    }

    friend ostream &operator <<(ostream &os, const BigInteger &x);
    friend istream &operator >>(istream &is,  BigInteger &x);

    BigInteger operator + (BigInteger b){
        BigInteger k{"0"};
        k.number=addition(this->number,b.number);
        return k;
    }
    BigInteger operator - (BigInteger b){
        BigInteger k{"0"};
        k.number=subraction(this->number,b.number);
        return k;
    }
    BigInteger operator * (BigInteger b){
        BigInteger k{"0"};
        k.number=multiply(this->number,b.number);
        return k;
    }
    BigInteger operator / (BigInteger b){
        BigInteger k{"0"};
        k.number=division(this->number,b.number);
        return k;
    }
    string addition(string op1, string op2)
    {
        if(op1.at(0) == '-' && op2.at(0)!='-')
            {
                op1 = op1.substr(1);
                return subraction(op2,op1);
            }
        else if(op1.at(0) != '-' && op2.at(0) == '-')
            {
                op2 = op2.substr(1);
                return subraction(op1,op2);
            }
        else if(op1.at(0) == '-' && op2.at(0) == '-')
            {
                op1 = op1.substr(1);
                op2 = op2.substr(1);
                return ("-"+addition(op1,op2));
            }

        if (op1.length() > op2.length())
            swap(op1, op2);
        string result = "";
        int n1 = op1.length(), n2 = op2.length();
        reverse(op1.begin(), op1.end());
        reverse(op2.begin(), op2.end());

        int carry = 0;
        for (int i=0; i<n1; i++)
        {
            int value = ((op1[i]-'0')+(op2[i]-'0')+carry);
            result.push_back(value%10 + '0');
            carry = value/10;
        }
        for (int i=n1; i<n2; i++)
        {
            int value = ((op2[i]-'0')+carry);
            result.push_back(value%10 + '0');
            carry = value/10;
        }

        //  remaining carry
        if (carry)
            result.push_back(carry+'0');

        // reverse for final result
        reverse(result.begin(), result.end());

        return result;
    }
    bool smallerString(string op1, string op2)
    {
        int n1 = op1.length(), n2 = op2.length();

        if (n1 < n2)
        return true;
        if (n2 < n1)
        return false;

        for (int i=0; i<n1; i++)
        if (op1[i] < op2[i])
            return true;
        else if (op1[i] > op2[i])
            return false;

        return false;
    }

    string subraction(string op1, string op2)
    {
        string result = "";
        bool flag = false;
        if(op1.at(0) == '-' && op2.at(0)!='-')
            {
                op1 = op1.substr(1);
                return ("-"+addition(op1,op2));
            }
        else if(op1.at(0) != '-' && op2.at(0) == '-')
            {
                op2 = op2.substr(1);
                return addition(op1,op2);
            }
        else if(op1.at(0) == '-' && op2.at(0) == '-')
            {
                op1 = op1.substr(1);
                op2 = op2.substr(1);
                return subraction(op2,op1);
            }
        if (smallerString(op1, op2)){
            swap(op1, op2);
            flag=true;
        }

        int n1 = op1.length(), n2 = op2.length();

        reverse(op1.begin(), op1.end());
        reverse(op2.begin(), op2.end());

        int carry = 0;
        for (int i=0; i<n2; i++)
        {
            int value = ((op1[i]-'0')-(op2[i]-'0')-carry);

            //if subraction is less than zero then we add 10 and make carry 1.
            if (value < 0)
            {
                value = value + 10;
                carry = 1;
            }
            else
                carry = 0;

            result.push_back(value + '0');
        }

        for (int i=n2; i<n1; i++)
        {
            int value = ((op1[i]-'0') - carry);

            if (value < 0)
            {
                value = value + 10;
                carry = 1;
            }
            else
                carry = 0;

            result.push_back(value + '0');
        }
        if(flag==true){
            result+="-";
        }
        reverse(result.begin(), result.end());

        return result;
    }

    string multiply(string op1, string op2)
    {
        char sign='+';
        if((op1.at(0) == '-' && op2.at(0) == '-' ) || (op1.at(0) != '-' && op2.at(0) != '-') )
            sign='+';
        else sign='-';
        if(op1.at(0) == '-' && op2.at(0)!='-')
            {
                op1 = op1.substr(1);
            }
        else if(op1.at(0) != '-' && op2.at(0) == '-')
            {
                op2 = op2.substr(1);
            }
        else if(op1.at(0) == '-' && op2.at(0) == '-')
            {
                op1 = op1.substr(1);
                op2 = op2.substr(1);
            }
        int len1 = op1.size();
        int len2 = op2.size();
        if (len1 == 0 || len2 == 0)
        return "0";
        vector<int> result(len1 + len2, 0);
        //int *result=new int[resultsize];
        //result.fill(0);
        int pos1 = 0;
        int pos2 = 0;
        for (int i=len1-1; i>=0; i--)
        {
            int carry = 0;
            int n1 = op1[i] - '0';
            pos2 = 0;
            for (int j=len2-1; j>=0; j--)
            {
                int n2 = op2[j] - '0';
                int sum = n1*n2 + result[pos1 + pos2] + carry;
                carry = sum/10;
                result[pos1 + pos2] = sum % 10;
                pos2++;
            }
            if (carry > 0)
                result[pos1 + pos2] += carry;
            pos1++;
        }
        int i = result.size() - 1;
        while (i>=0 && result[i] == 0)
        i--;
        if (i == -1)
        return "0"; //either one of them is zero then the result will be zero.
        string s = "";

        if(sign=='-'){
            s+=sign;
        }
        while (i >= 0){
            s += std::to_string(result[i]);
            i--;
        }

        return s;
    }
    string division(string op1, string op2){
        char sign='+';
        if((op1.at(0) == '-' && op2.at(0) == '-' ) || (op1.at(0) != '-' && op2.at(0) != '-') )
            sign='+';
        else sign='-';
        if(op1.at(0) == '-' && op2.at(0)!='-')
            {
                op1 = op1.substr(1);
            }
        else if(op1.at(0) != '-' && op2.at(0) == '-')
            {
                op2 = op2.substr(1);
            }
        else if(op1.at(0) == '-' && op2.at(0) == '-')
            {
                op1 = op1.substr(1);
                op2 = op2.substr(1);
            }
        if(op2.size()<=sizeof(long long)){
            long long div=0;
            stringstream f(op2);
            f>>div;
            string result;
            if(sign=='-') result+="-";
            long long i = 0;
            long long temp = op1[i] - '0';
            while (temp < div)
                temp = temp * 10 + (op1[++i] - '0');

            while (op1.size() > i) {
                result += (temp / div) + '0';
                temp = (temp % div) * 10 + op1[++i] - '0';
            }
            if (result.length() == 0)
                return "0";

            return result;
       }
        else{
            string k=op1;
            int count=0;
            string rem=op1;
            string trim1="";
            string trim2="";
            while(rem!="" && rem[0]!='-'){
                count++;
                k=subraction(op1,op2);
                trim1=k;
                trim1.erase(0, trim1.find_first_not_of('0'));
                trim2=op2;
                trim2.erase(0, trim2.find_first_not_of('0'));
                if (smallerString(trim1, trim2)){

                    op1=trim2;
                    op2=trim1;
                }
                else{
                    op1=trim1;
                    op2=trim2;
                }


                rem=k;

                rem.erase(0, rem.find_first_not_of('0'));
            }
            string res="";
            if(sign=='-') {
                res+="-";
                --count;
                res+=to_string(count);
                return res;
            }
            return to_string(--count);
        }
    }
    friend BigInteger factorial(BigInteger& f);
    friend string gcd(BigInteger a, BigInteger b);
    friend string exponentiation(BigInteger a, int b);

};


string gcd(BigInteger a, BigInteger b){
    BigInteger op1;
    BigInteger op2;
    if (op1.smallerString(a.number, b.number)){
        op1=b;
        op2=a;
    }
    else{
        op1=a;
        op2=b;
    }
    int count=0;
    if(a.number=="0" && b.number=="0") return "0";
    else if(a.number=="0" && b.number!="0")  return b.number;
    else if(b.number=="0" && a.number!="0")  return a.number;
    string prev="";
    string rem=op1.number;
    string trim1="";
    string trim2="";
    BigInteger k=op1;
    while(rem[0]!='-' && rem!=""){
        count++;
        prev=rem;
        k=op1-op2;
        trim1=k.number;
        trim1.erase(0, trim1.find_first_not_of('0'));
        trim2=op2.number;
        trim2.erase(0, trim2.find_first_not_of('0'));
        if (k.smallerString(trim1, trim2)){

            op1.number=trim2;
            op2.number=trim1;
        }
        else{
            op1.number=trim1;
            op2.number=trim2;
        }


        rem=k.number;

        rem.erase(0, rem.find_first_not_of('0'));
    }
    return prev;



}

string exponentiation(BigInteger k, int b){
    //string a=k.number;
    if(b==0) return "1";
    else if(b==1) return k.number;
    else{
        BigInteger R{exponentiation(k,b/2)};
        //cout<<"R value = "<<R<<endl;

        if(b%2==0){
            BigInteger v=R*R;
        //    cout<<"R even value = "<<R<<endl;
            return v.number;
        }
        else{
            BigInteger u=(R*k);
            BigInteger p=u*R;
        //    cout<<"R odd value = "<<R<<endl;
            return p.number;
        }
    }
}

BigInteger factorial(BigInteger& f){
    stringstream b(f.number);
    long long x=0;
    b>>x;
    if(x==0|| x==1 ) return BigInteger{"1"};
    BigInteger k{"0"};
    string result="1";
    for(long long l=2;l<=x;l++){
        result=k.multiply(result,to_string(l));
    }

    k.number=result;
    return k;

}
ostream &operator <<(ostream &os, const BigInteger &x){
    os<<x.number;
    return os;
}
istream &operator >>(istream &is,  BigInteger &x){
    is>>x.number;
    return is;
}

int main(){
    BigInteger a1;
    BigInteger a2;
    BigInteger b2;
    BigInteger f;
    int exp1;
    long long Qcount,Qno;
    cin>>Qcount;
    bool flag1=false,flag2=false,flag3=false;
    while(Qcount--){
        cin>>Qno;
        switch (Qno) {
            case 1:
                cin>>a1;
                cin>>exp1;
                flag1=true;
                cout<<exponentiation(a1,exp1)<<endl;
                break;
            case 2:
                cin>>a2;
                cin>>b2;
                flag2=true;
                cout<<gcd(a2,b2)<<endl;
                break;
            case 3:
                cin>>f;
                flag3=true;
                cout<<factorial(f)<<endl;
                break;
            default:
                break;
        }

    }
    /*
    if(flag1==true) cout<<exponentiation(a1,exp1)<<endl;
    if(flag2==true) cout<<gcd(a2,b2)<<endl;
    if(flag3==true) cout<<factorial(f)<<endl;*/
    return 0;

}
