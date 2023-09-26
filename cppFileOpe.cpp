#include <iostream>
#include <fstream>

using namespace std;

const string account_number = "55180517";
const int an_length = 10;
const string branch_name = "ning  yu h";
const int bn_length = 10;
const double balance = 37.5;
const int times = 5;

void solution() {
    // 每个属性后面加一个缩进，每个记录后面加一个 #
    ofstream outfile;
    outfile.open("./ning.log", ios::out);
    for(int i = 0; i < times; ++i) {
        outfile << account_number;
        for(int j = account_number.size(); j < an_length; ++j) {
            outfile << ' ';
        }
        outfile << branch_name;
        for(int j = branch_name.size(); j < an_length + 1; ++j) {
            outfile << ' ';
        }
        if(i + 1 != times) outfile << balance << "�\t";
        // outfile << an_length << endl;
    }
    outfile.close();
    ifstream infile;
    char an[an_length + 1];
    char bn[bn_length + 1];
    double bal;
    infile.open("./ning.log", ios::binary);
    infile.read(an, 10);
    infile.read(bn, 10);
    infile >> bal;
    cout << an << endl;
    cout << bn << endl;
    cout << bal << endl;
    cout << endl;
    char ch = infile.get();
    infile.read(an, 10);
    cout << an << endl;
    infile.close();
}


int main(void) {
    solution();         // 12/main/base/13465
    // fstream infile;
    // infile.open("./ning.log");
    // char ch = infile.peek();
    // double num;
    // while(ch != EOF) {
    //     if(isdigit(ch)) {
    //         cout << ch + 1 << endl;
    //         infile >> num;
    //         cout << num << endl;
    //     }
    //     else{
    //         ch = infile.get();
    //         cout << ch << endl;
    //     }
    //     ch = infile.peek();
    // }
    return 0;
}
