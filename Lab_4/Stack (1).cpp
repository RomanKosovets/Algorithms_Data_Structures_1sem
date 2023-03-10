#include <vector>
#include <fstream>

using namespace std;

struct stack{
    vector<int> st;
    int size = 0;
    explicit stack(int m){
        st.resize(m + 1);
    }
    void push(int value){
        st[++size] = value;
    }
    int pop(){
        return st[size--];
    }
};

int main(){

    ifstream input("C:\\Users\\roman\\CLionProjects\\Project C++\\stack.txt");
    ofstream output("stack.out");
    int m = 0;
    input >> m;
    stack a(m);
    for (int i = 0; i < m; i++){
        string commanda;
        input >> commanda;
        if (commanda == "+"){
            int x = 0;
            input >> x;
            a.push(x);
        }
        else{
            output << a.pop() << '\n';
        }
    }
    return 0;
}


