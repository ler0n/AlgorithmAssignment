// 기본 세팅
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define MAX 10000000

// 자료형 이름 재정의
typedef pair<int, pair<int, int> > edge;
typedef vector<edge> edges;
typedef vector<int> row;
typedef vector<vector<int> > matrix;

// 함수 선언
void data_init(int &, matrix &);
void matrix_init(int, matrix &);
void show_union(edges &);
void dijkstra(int, matrix, edges &);

int main(){
    ios_base::sync_with_stdio(false);
    edges F;
    matrix W;
    int num;

    data_init(num, W);
    dijkstra(num, W, F);
    show_union(F);
    return 0;
}

void data_init(int &dest1, matrix &dest2){
    int n, m;

    cout << "간선, 정점 개수 입력: ";
    cin >> n >> m;
    dest1 = m;
    matrix_init(m+1, dest2);
    cout << "간선경로, 가중치 순으로 입력\n";
    for(int i = 0; i < n; i++){
        int cost, p, q;
        cin >> p >> q >> cost;
        dest2[p][q] = cost;
    }
}
void matrix_init(int n, matrix &dest){
    dest.resize(n, row(n, MAX));
}
void show_union(edges &src){
    int sz = src.size();
    cout << "집합 출력\n";
    for(int i = 0; i < sz; i++){
        cout << '(' << src[i].second.first << "->" << src[i].second.second << ") - " << src[i].first << '\n';
    }
}
void dijkstra(int n, matrix W, edges &F){
    int i, j, vnear;
    row touch, length;
    edge e;

    j = 1;
    touch.resize(n+1, 0);
    length.resize(n+1, 0);
    
    for(i=2; i <= n; i++){
        touch[i] = 1;
        length[i] = W[1][i];
    }
    while(j++ <= n-1){
        int min = MAX;
        for(i=2; i <= n; i++){
            if(length[i] >= 0 && length[i] <= min){
                min = length[i];
                vnear = i;
            }
        }
        int from = touch[vnear];
        int to = vnear;
        e = edge(W[from][to], make_pair(from, to));
        F.push_back(e);
        for(i=2; i <= n; i++){
            if(length[vnear] + W[vnear][i] < length[i]){
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;
            }
        }
        length[vnear] = -1;
    }
}
