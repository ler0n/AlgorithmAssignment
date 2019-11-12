// 기본 세팅
#include<iostream>
#include<vector>
using namespace std;

#define NONE -1
#define MAX 1000000

// 자료형 이름 재정의
typedef vector<vector<int> > matrix;
typedef vector<int> row;

// 전역변수 P행렬 선언
matrix P;

void data_init(row &, matrix &);
void matrix_init(int, matrix &);
int minmult(int, const row &, matrix &);
void order(int, int);

int main(){
    ios_base::sync_with_stdio(false);
    row d;

    data_init(d, P);
    minmult(d.size(), d, P);
    order(0, P.size()-1);
    return 0;
}

void data_init(row &dest1, matrix &dest2){
    int n;

    cout << "행렬 개수 입력: ";
    cin >> n;
    matrix_init(n, dest2);
    for(int i = 0; i < n+1; i++){
        int temp;
        cin >> temp;
        dest1.push_back(temp);
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n, MAX));
}
int minmult(int n, const row &d, matrix &p){
    matrix M;
    int j;

    n--;
    matrix_init(n, M);
    for(int i = 0; i < n; i++) M[i][i] = 0;
    for(int diag = 1; diag <= n-1; diag++){
        for(int i = 1; i <= n-diag; i++){
            j = i + diag;
            for(int k = i; k <= j-1; k++){
                int temp = M[i-1][k-1] + M[k][j-1] + d[i-1]*d[k]*d[j];
                if(temp < M[i-1][j-1]){
                    M[i-1][j-1] = temp;
                    P[i-1][j-1] = k-1;
                }
            }
        }
    }
    return M[0][n-1];
}
void order(int i, int j){
    if(i == j) cout << "A" << i+1;
    else{
        int k = P[i][j];

        cout << "(";
        order(i, k);
        order(k+1, j);
        cout << ")";
    }
}