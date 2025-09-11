// solution for BOJ 4196

#include <bits/stdc++.h>

using namespace std;

const int MAXV = 100001;

vector<int> graph[MAXV];
int dfs_num[MAXV];
int low[MAXV];
int visited[MAXV];
int dfs_counter = 0;
stack<int> st;
vector<vector<int>> SCC;

// [ADD] 각 정점의 소속 SCC ID 저장용
int comp_id[MAXV];

void init() {
  for (int i = 0; i < MAXV; ++i) {
    graph[i].clear();
    dfs_num[i] = 0;
    low[i] = 0;
    visited[i] = 0;
    comp_id[i] = -1;
  }
  dfs_counter = 0;
  while (!st.empty()) st.pop();
  SCC.clear();
}

void tarjan(int u) {
  dfs_num[u] = low[u] = ++dfs_counter;
  st.push(u);
  visited[u] = 1;

  for (int v : graph[u]) {
    if (dfs_num[v] == 0) {  // not visited
      tarjan(v);            // after tarjan[v], low[v] is determined
      low[u] = min(low[u], low[v]);
    } else if (visited[v]) {  // visited && not in stack -> inverse edge
      low[u] = min(low[u], dfs_num[v]);
    }
  }

  // root of comp
  if (low[u] == dfs_num[u]) {
    vector<int> comp;
    int curr_id = SCC.size();  // 이번 component의 ID (push 전 size가 곧 ID)
    while (true) {
      int v = st.top();
      st.pop();
      visited[v] = 0;  // now, v is not in stack
      comp.push_back(v);
      comp_id[v] = curr_id;
      if (v == u) break;  // u is root of comp
    }
    SCC.push_back(comp);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    {
      // 매 테스트케이스 전, 필요한 자료구조 모두 초기화
      init();
    }
    int n, m;  // 도미노의 개수, 관계의 개수 = 정점의 개수, 간선의 개수
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      graph[x].push_back(y);
    }

    // tarjan SCC
    for (int vertex = 1; vertex <= n; ++vertex) {
      if (dfs_num[vertex] == 0) {  // not visited yet
        tarjan(vertex);
      }
    }

    // 압축 DAG의 진입차수 계산 (indegree == 0 인 컴포넌트의 개수가 정답)
    vector<int> indeg(SCC.size(), 0);
    for (int u = 1; u <= n; ++u) {  // 모든 정점 순회
      for (int v : graph[u]) {      // u->v 모든 간선 확인
        int cu = comp_id[u];
        int cv = comp_id[v];
        if (cu != cv) indeg[cv]++;
      }
    }

    int ans = 0;
    for (int c = 0; c < SCC.size(); ++c) {
      if (indeg[c] == 0) ans++;
    }

    cout << ans << '\n';
  }
  return 0;
}
