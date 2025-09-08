/*
타잔 알고리즘의 핵심 직관

DFS를 돌면서, 두 가지 숫자를 관리한다.
1. dfs_num[u]: DFS에서 u를 방문한 순서 (첫 방문 시 매기는 번호) -> "탐색 순서 번호"
2. low[u]: u에서 올라갈 수 있는 가장 작은 dfs_num -> "이 정점이 속한 SCC의 대표 번호"

만약 `low[u] == dfs_num[u]`라면, u는 “SCC 하나의 시작점(root)” 이고, 그 순간 스택에서 정점들을 꺼내면 하나의 SCC가 완성된다.

---

왜 이게 되지? (직관적인 설명)
- DFS로 쭉 내려가면서 방문 순서를 매겨.
- 만약 DFS 중에 “이미 방문한 정점”으로 역방향 간선을 타고 갈 수 있으면, low 값을 갱신하면서 “아, 이쪽으로 돌아가면 같은 SCC 안에 있구나!”를 기록해.
- 결국 low[u]는 “u에서 출발해서 되돌아갈 수 있는 정점 중 제일 위쪽(작은 번호)”을 가리킴.
- 루트 역할을 하는 정점에서만 “여기서 SCC 하나 끊을 수 있다!”를 알 수 있어.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 10005;

vector<int> graph[MAX];
int dfs_num[MAX], low[MAX], visited[MAX];
int dfs_counter = 0;
stack<int> st;
vector<vector<int>> SCC;

void tarjan(int u) {
  dfs_num[u] = low[u] = ++dfs_counter;

  st.push(u);
  // u를 SCC 후보 스택에 넣어둔다.
  // 같은 SCC로 판정되면, 여기서부터 연속으로 팝해서 컴포넌트를 만든다.

  visited[u] = 1;
  // 스택 안에 있다 표시
  // DFS 방문 여부는 dfs_num[u]가 0인지로 판별
  // visited 배열은 "아직 스택에 남아 있는가?"를 추적하는 용도

  for (int v : graph[u]) {  // u에서 나가는 모든 간선(u->v)를 돈다.
    if (dfs_num[v] == 0) {  // not visited
      tarjan(v);            // 재귀 호출로 v의 서브트리를 다 처리하고 돌아온다.

      low[u] = min(low[u], low[v]);
      // TODO: 여기서부터 주석 + 코드 작성
    }
  }
}