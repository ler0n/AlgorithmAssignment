// 기본 세팅
#include<iostream>
#include<vector>
using namespace std;

#define NONE -1
#define MAX 1000000.0

// 자료형 이름 재정의
typedef vector<vector<int> > matrix;
typedef vector<vector<float> > matrix_f;
typedef vector<int> row;
typedef vector<float> row_f;

// 전역변수 행렬 R 선언
matrix R;

void data_init(row_f &, matrix &);
void matrix_init(int, matrix &);
void matrix_init(int, matrix_f &);
void matrix_info(matrix &);
void matrix_info(matrix_f &);
float sum_percent(int, int, const row_f);
void optsearchtree(int n, const row_f, float &, matrix &);

int main(){
    ios_base::sync_with_stdio(false);
    row_f p;
    float min_avg;

    data_init(p, R);
    optsearchtree(p.size()-1, p, min_avg, R);
    cout << "R\n";
    matrix_info(R);
    return 0;
}

void data_init(row_f &dest1, matrix &dest2){
    int n;

    cout << "노드 개수 입력: ";
    cin >> n;
    matrix_init(n+2, dest2);
    dest1.push_back(0.0);
    for(int i = 0; i < n; i++){
        float temp;
        cin >> temp;
        dest1.push_back(temp);
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n-1, int(MAX)));
}
void matrix_init(int n, matrix_f &dest){
    dest.resize(n, row_f(n-1, MAX));
}
void matrix_info(matrix &src){
    int row_size = src.size();
    
    cout << "행렬 정보\n";
    for(int i = 1; i < row_size; i++){
        int col_size = src[i].size();

        for(int j = 0; j < col_size; j++){
            int val = src[i][j];
            if(val == MAX) cout << ' ' << ' ';
            else cout << val << ' ';
        }
        cout << '\n';
    }
}
void matrix_info(matrix_f &src){
    int row_size = src.size();
    
    cout << "행렬 정보\n";
    for(int i = 1; i < row_size; i++){
        int col_size = src[i].size();

        for(int j = 0; j < col_size; j++){
            float val = src[i][j];
            if(val == MAX) cout << ' ' << ' ' <<  "    ";
            else cout << val << ' ';
        }
        cout << '\n';
    }
}
float sum_percent(int start, int end, const row_f p){
    float result = 0;
    for(int i = start; i <= end; i++){
        result += p[i];
    }
    return result;
}
void optsearchtree(int n, const row_f p, float &minavg, matrix &R){
    int j;
    matrix_f A;
    matrix_init(n+2, A);
    for(int i = 1; i < n+1; i++){
        A[i][i-1] = 0; A[i][i] = p[i]; R[i][i] = i; R[i][i-1] = 0;
    }
    A[n+1][n] = 0; R[n+1][n] = 0;
    for(int diag = 1; diag <= n-1; diag++){
        for(int i = 1; i <= n-diag; i++){
            int sum = 0;
            
            j = i + diag;
            for(int k = i; k <= j; k++){
                float temp = A[i][k-1]+A[k+1][j];
                if(temp < A[i][j]){
                    A[i][j] = temp;
                    R[i][j] = k;
                }
            }
            A[i][j] += sum_percent(i, j, p);
        }
        minavg = A[1][n];
    }
    cout << "A\n";
    matrix_info(A);
}