// 기본 세팅
#include<iostream>
#include<vector>
using namespace std;

// 자료형 이름 재정의
typedef vector<vector<int> > matrix;
typedef vector<int> row;

// threshold 전역변수 선언
int THRESHOLD = 1;

//함수 선언
void data_init(matrix &, matrix &, matrix &);
void matrix_init(int, matrix &);
void matrix_split(matrix &, matrix &, matrix &, matrix &, matrix &);
void matrix_merge(matrix &, matrix &, matrix &, matrix &, matrix &);
void matrix_add(matrix, matrix, matrix &);
void matrix_sub(matrix, matrix, matrix &);
void matrix_mul(matrix, matrix, matrix &);
void matrix_info(matrix &);
void strassen(int, matrix, matrix, matrix &);

int main(){
    ios_base::sync_with_stdio(false);
    matrix left, right, result;

    data_init(left, right, result);
    strassen(left.size(), left, right, result);
    matrix_info(result);
    return 0;
}

void data_init(matrix &dest1, matrix &dest2, matrix &res){
    int n, cnt = 2;
    matrix *dest[2] = {&dest2, &dest1};
    string dest_name[2] = {"오른쪽", "왼쪽"};

    cout << "행렬 크기 입력: ";
    cin >> n;
    matrix_init(n, res);
    while(cnt--){
        cout << dest_name[cnt] << " 행렬 입력\n";
        matrix_init(n, *dest[cnt]);
        for(int i = 0; i < n; i++){
            cout << i+1 << "번째 행 입력: ";
            for(int j = 0; j < n; j++){
                cin >> (*dest[cnt])[i][j];
            }
        }
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n, 0));
}
void matrix_split(matrix &dest_left_top, matrix &dest_right_top,
                  matrix &dest_left_bottom, matrix &dest_right_bottom,
                  matrix &src){
    int n = src.size() / 2;

    matrix_init(n, dest_left_top);
    matrix_init(n, dest_left_bottom);
    matrix_init(n, dest_right_top);
    matrix_init(n, dest_right_bottom);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dest_left_top[i][j] = src[i][j];
            dest_left_bottom[i][j] = src[i+n][j];
            dest_right_top[i][j] = src[i][j+n];
            dest_right_bottom[i][j] = src[i+n][j+n];
        }
    }
}
void matrix_merge(matrix &src_left_top, matrix &src_right_top,
                  matrix &src_left_bottom, matrix &src_right_bottom,
                  matrix &dest){
    int n = src_left_top.size() * 2;

    matrix_init(n, dest);
    n /= 2;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dest[i][j] = src_left_top[i][j];
            dest[i+n][j] = src_left_bottom[i][j];
            dest[i][j+n] = src_right_top[i][j];
            dest[i+n][j+n] = src_right_bottom[i][j];
        }
    }
}
void matrix_add(matrix src_left, matrix src_right, matrix &dest){
    int n = src_left.size();
    
    matrix_init(n, dest);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dest[i][j] = src_left[i][j] + src_right[i][j];
        }
    }
}
void matrix_sub(matrix src_left, matrix src_right, matrix &dest){
    int n = src_left.size();

    matrix_init(n, dest);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dest[i][j] = src_left[i][j] - src_right[i][j];
        }
    }
}
void matrix_mul(matrix src_left, matrix src_right, matrix &dest){
    int n = src_left.size();

    matrix_init(n, dest);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                dest[i][j] += src_left[i][k] * src_right[k][j];
            }
        }
    }
}
void matrix_info(matrix &src){
    int row_size = src.size();
    
    cout << '\n' << "행렬 정보" << '\n';
    for(int i = 0; i < row_size; i++){
        int col_size = src[i].size();

        for(int j = 0; j < col_size; j++){
            cout << src[i][j] << ' ';
        }
        cout << '\n';
    }
}
void strassen(int n, matrix src_left, matrix src_right, matrix &dest){
    matrix temp1, temp2, A[2][2], B[2][2], M[7], C[2][2];

    if(n <= THRESHOLD){
        matrix_mul(src_left, src_right, dest);
    }
    else{
        // src_left, src_right 행렬 4분할
        matrix_split(A[0][0], A[0][1], A[1][0], A[1][1], src_left);
        matrix_split(B[0][0], B[0][1], B[1][0], B[1][1], src_left);
        
        // M1 계산[(A11 + A22) * (B11 + B22)]
        matrix_add(A[0][0], A[1][1], temp1);
        matrix_add(B[0][0], B[1][1], temp2);
        strassen(n/2, temp1, temp2, M[0]);
        
        // M2 계산[(A21 + A22) * B11]
        matrix_add(A[1][0], A[1][1], temp1);
        strassen(n/2, temp1, B[0][0], M[1]);

        // M3 계산[A11 * (B12 - B22)]
        matrix_sub(B[0][1], B[1][1], temp1);
        strassen(n/2, A[0][0], temp1, M[2]);

        // M4 계산[A22 * (B21 - B11)]
        matrix_sub(B[1][0], B[0][0], temp1);
        strassen(n/2, A[1][1], temp1, M[3]);

        // M5 계산[(A11 + A12) * B22]
        matrix_add(A[0][0], A[0][1], temp1);
        strassen(n/2, temp1, B[1][1], M[4]);

        // M6 계산[(A21 - A11) * (B11 + B12)]
        matrix_sub(A[1][0], A[0][0], temp1);
        matrix_add(B[0][0], B[0][1], temp2);
        strassen(n/2, temp1, temp2, M[5]);

        // M7 계산[(A12 - A22) * (B21 + B22)]
        matrix_sub(A[0][1], A[1][1], temp1);
        matrix_add(B[1][0], B[1][1], temp2);
        strassen(n/2, temp1, temp2, M[6]);

        // C11 계산[M1 + M4 - M5 + M7]
        matrix_add(M[0], M[3], temp1);
        matrix_sub(temp1, M[4], temp2);
        matrix_add(temp2, M[6], C[0][0]);

        // C12 계산[M3 + M5]
        matrix_add(M[2], M[4], C[0][1]);

        // C21 계산[M2 + M4]
        matrix_add(M[1], M[3], C[1][0]);

        // C22 계산[M1 + M3 - M2 + M6]
        matrix_add(M[0], M[2], temp1);
        matrix_sub(temp1, M[1], temp2);
        matrix_add(temp2, M[5], C[1][1]);

        // 4분할 행렬 합병
        matrix_merge(C[0][0], C[0][1], C[1][0], C[1][1], dest);
    }
}