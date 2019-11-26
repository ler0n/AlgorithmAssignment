// 기본 세팅
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define N 1000

// 사용자 자료형 생성
struct nodetype{
    int parent;
    int depth;
};

// 자료형 이름 재정의
typedef pair<int, pair<int, int> > edge;
typedef vector<edge> edges;
typedef struct nodetype universe[N];

// 전역변수 U 선언
universe U;

// 함수 선언
void data_init(int &, edges &);
void show_union(edges &);
void makeset(int);
int find(int);
void merge(int, int);
bool equal(int, int);
void initial(int);
void kruskal(int, int, edges, edges &);

int main(){
    ios_base::sync_with_stdio(false);
    edges E, F;
    int num;

    data_init(num, E);
    kruskal(num, E.size(), E, F);
    show_union(F);
    return 0;
}

void data_init(int &dest1, edges &dest2){
    int n, m;

    cout << "간선, 정점 개수 입력: ";
    cin >> n >> m;
    dest1 = m;
    cout << "간선경로, 가중치 순으로 입력\n";
    for(int i = 0; i < n; i++){
        int cost, p, q;
        cin >> p >> q >> cost;
        dest2.push_back(edge(cost, make_pair(p, q)));
    }
}
void show_union(edges &src){
    int sz = src.size();
    cout << "집합 출력\n";
    for(int i = 0; i < sz; i++){
        cout << '(' << src[i].second.first << ", " << src[i].second.second << ") - " << src[i].first << '\n';
    }
}
void makeset(int i){
    U[i].parent = i;
    U[i].depth = 0;
}
int find(int i){
    int j = i;
    while(U[i].parent != j) j = U[i].parent;
    return j;
}
void merge(int p, int q){
    if(U[p].depth == U[q].depth){
        U[p].depth += 1;
        U[q].parent = p;
    }
    else if(U[p].depth < U[q].depth) U[p].parent = q;
    else U[q].parent = p;
}
bool equal(int p, int q){
    if(p == q) return true;
    else return false;
}
void initial(int n){
    int i;
    for(i = 1; i<=n; i++) makeset(i);
}
void kruskal(int n, int m, edges E, edges &F){
    int i, j;
    int p, q;
    int index = 0;
    edge e;
    sort(E.begin(), E.end());
    initial(n);

    while(F.size() < n-1){
        e = E[index++];
        i = e.second.first;
        j = e.second.second;

        p = find(i);
        q = find(j);
        if(!equal(p, q)){
            merge(p, q);
            F.push_back(e);
        }
    }
}
