// 기본 세팅
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 자료형 이름 재정의
typedef vector<int> row;
typedef vector<vector<int> > matrix;

// 함수 선언
void data_init(int &);
void matrix_init(int, matrix &);
void hamiltonian(int);
bool promising(int);

// 전역변수 선언
int n;
int vindex[100];
matrix W;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    data_init(n);
    hamiltonian(0);
    return 0;
}

void data_init(int &dest){
    int path_num, from, to;

    cout << "n 입력: ";
    cin >> dest;
    cout << "경로 수 입력: ";
    cin >> path_num;

    matrix_init(dest+1, W);
    vindex[0] = 1;
    for(int i = 0; i < path_num; i++){
        cout << "경로 입력: ";
        cin >> from >> to;
        W[from][to] = 1;
        W[to][from] = 1;
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n, 0));
}
void hamiltonian(int i){
    if(promising(i)){
        if(i == n-1){
            for(int j = 1; j < n; j++){
                cout << vindex[j] << ' ';
            }
            cout <<'\n';
        }
        else{
            for(int j = 2; j <= n; j++){
                vindex[i+1] = j;
                hamiltonian(i+1);
            }
        }
    }
}
bool promising(int i){
    bool _switch;

    if(i == n-1 && !W[vindex[n-1]][vindex[0]]) _switch = false;
    else if(i > 0 && !W[vindex[i-1]][vindex[i]]) _switch = false;
    else{
        int j = 1;

        _switch = true;
        while(j < i && _switch){
            if(vindex[i] == vindex[j]) _switch = false;
            j++;
        }
    }
    return _switch;
}
