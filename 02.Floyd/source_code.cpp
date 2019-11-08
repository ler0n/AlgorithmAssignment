// 기본 세팅
#include<iostream>
#include<vector>
using namespace std;

// INF, NONE 매크로 정의
#define INF 10000000
#define NONE -1

// 자료형 이름 재정의
typedef vector<vector<int> > matrix;
typedef vector<int> row;

// 전역변수 P행렬 선언
matrix P;

// 예제 데이터
// 0, 1, INF, 1, 5
// 9, 0, 3, 2, INF
// INF, INF, 0, 4, INF
// INF, INF, 2, 0, 3
// 3, INF, INF, INF, 0

// 함수 선언
void data_init(matrix &, matrix &, matrix &);
void matrix_init(int, matrix &);
void floyd(int, matrix &, matrix &, matrix &);
void path(int, int);
void path();

int main() {
	ios_base::sync_with_stdio(false);
	matrix W, D;

	data_init(W, D, P);
	floyd(W.size(), W, D, P);
	path();
	#ifdef _WIN32
	system("timeout 5 > NUL");
	#endif
	return 0;
}

void data_init(matrix &dest1, matrix &dest2, matrix &dest3) {
	int n;

	cout << "정점 개수 입력: ";
	cin >> n;
	matrix_init(n, dest1);
	matrix_init(n, dest2);
	matrix_init(n, dest3);
	for(int i = 0; i < n; i++) {
		cout << i + 1 << "번째 정점의 경로들의 값 입력(무한대는 -1로 입력): ";
		for(int j = 0; j < n; j++) {
			int temp;
			cin >> temp;
			dest1[i][j] = (temp == -1) ? INF : temp;
		}
	}
}
void matrix_init(int n, matrix &dest) {
	dest.resize(n, row(n, 0));
}
void floyd(int n, matrix &W, matrix &D, matrix &P) {
	for (int i = 0; i<n; i++) {
		for (int j = 0; j<n; j++) {
			P[i][j] = NONE;
		}
	}
	D = W;

	for(int k = 0; k<n; k++) {
		for(int i = 0; i<n; i++) {
			for(int j = 0; j<n; j++) {
				if((D[i][k] + D[k][j]) < D[i][j]) {
					P[i][j] = k;
					D[i][j] = (D[i][k] + D[k][j]);
				}
			}
		}
	}
}
void path(int q, int r) {
	if (P[q][r] != NONE) {
		path(q, P[q][r]);
		cout << " V" << P[q][r] + 1;
		path(P[q][r], r);
	}
}
void path() {
	int p, q;

	cout << "구하려는 경로 정점 번호 입력: ";
	cin >> p >> q;
	cout << "시작정점(V" << p << ")";
	path(p - 1, q - 1);
	cout << " 끝정점(V" << q << ")";
}
