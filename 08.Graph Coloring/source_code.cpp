// 기본 세팅
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 자료형 이름 재정의
typedef vector<int> row;
typedef vector<vector<int> > matrix;

// 함수 선언
void data_init(int &, int &);
void matrix_init(int, matrix &);
void m_coloring(int);
bool promising(int);

// 전역변수 선언
int n, m;
int vcolor[100];
matrix W;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    data_init(n, m);
    m_coloring(0);
    return 0;
}

void data_init(int &dest1, int &dest2){
    int path_num, from, to;

    cout << "n 입력: ";
    cin >> dest1;
    cout << "m 입력: ";
    cin >> dest2;
    cout << "경로 수 입력: ";
    cin >> path_num;

    matrix_init(dest1+1, W);
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
void m_coloring(int i){
    if(promising(i)){
        if(i == n){
            for(int j = 1; j <= n; j++){
                cout << vcolor[j] << ' ';
            }
            cout << '\n';
        }
        else{
            for(int color = 1; color <= m; color++){
                vcolor[i+1] = color;
                m_coloring(i+1);
            }
        }
    }
}
bool promising(int i){
    int j = 1;
    bool _switch = true;

    while(j < i && _switch){
        if(W[i][j] && vcolor[i] == vcolor[j]) _switch = false;
        j++;
    }
    return _switch;
}
