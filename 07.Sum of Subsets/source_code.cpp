// 기본 세팅
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

#define MAX 10000000

// 자료형 이름 재정의
typedef vector<int> row;
typedef vector<vector<int> > matrix;

// 함수 선언
void data_init(int &);
void matrix_init(int, matrix &);
void sum_of_subsets(int, int, int);
bool promising(int, int, int);

int W;
int w[1000];
string include[1000];

int main(){
    ios_base::sync_with_stdio(false);
    int total = 0;

    data_init(total);
    sum_of_subsets(0, 0, total);
    return 0;
}

void data_init(int &dest){
    int n, m;

    cout << "n 입력: ";
    cin >> n;
    cout << "W 입력: ";
    cin >> W;
    for(int i = 0; i < n; i++){
        cout << 'w' << i+1 << "입력: ";
        cin >> m;
        w[i+1] = m;
        dest += m;
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n, MAX));
}
void sum_of_subsets(int i, int weight, int total){
    if(promising(i, weight, total)){
        if(weight == W){
            for(int j = 1; j <= i; j++){
                cout << include[j] << ' ';
            }
        }
        else{
            include[i+1] = "yes";
            sum_of_subsets(i+1, weight+w[i+1], total-w[i+1]);
            include[i+1] = "no";
            sum_of_subsets(i+1, weight, total-w[i+1]);
        }
    }
}
bool promising(int i, int weight, int total){
    return ((weight+total) >= W) && (weight == W || weight+w[i+1] <= W);
}