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
  visited[u] = 1;
  for (int v : graph[u]) {
    if (dfs_num[v] == 0) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (visited[v]) {
      low[u] = min(low[u], dfs_num[v]);
    }
  }
  if (low[u] == dfs_num[u]) {
    vector<int> comp;
    while (true) {
      int v = st.top();
      st.pop();
      visited[v] = 0;
      comp.push_back(v);
      if (v == u) break;
    }
    SCC.push_back(comp);
  }
}