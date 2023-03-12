#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector < pair<int , int>> pri_queue;

int SiftDown(int i){

    while (2 * i + 1 < pri_queue.size()){
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int j = left;
        if(right < pri_queue.size() && pri_queue[right].first < pri_queue[left].first)
            j = right;
        if(pri_queue[i].first <= pri_queue[j].first)
            break;
        swap(pri_queue[i], pri_queue[j]);
        i = j;
    }
    return 0;
}

int SiftUp(int i){

    while (i != 0 && pri_queue[i].first < pri_queue[(i - 1) / 2].first){
        swap(pri_queue[i], pri_queue[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return 0;
}

int push(int val, int number){

    pri_queue.push_back(make_pair(val, number));
    SiftUp(pri_queue.size() - 1);

    return 0;
}

int extractMin(){

    int min = pri_queue[0].first;
    pri_queue[0] = pri_queue[pri_queue.size() - 1];
    pri_queue.pop_back();
    SiftDown(0);
    return min;
}

int decreaseKey(int num, int val){

    for(int i = 0; i < pri_queue.size(); i++)
        if(pri_queue[i].second == num){
            pri_queue[i].first = val;
            SiftUp(i);
            break;
        }
    return 0;
}

int main(){

    std::ifstream fin("priorityqueue.in");
    std::ofstream fout("priorityqueue.out");

    string command;
    int value, index, new_value;
    int count = 1;

    while (cin >> command){
        if (command == "push"){
            cin >> value;
            push(value, count);
        }
        else if (command == "extract-min"){
            if (pri_queue.empty())
                cout << "*" << "\n";
            else
                cout << extractMin() << "\n";
        }
        else if (command == "decrease-key"){
            cin >> index >> new_value;
            decreaseKey(index, new_value);
        }
        count++;
    }
}
