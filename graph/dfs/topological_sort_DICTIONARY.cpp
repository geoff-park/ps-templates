// Basic implementation of topological sort
// This code is also a solution for AOJ "DICTIONARY"

// 그래프는 각 알파벳 소문자를 표현하는 26개의 정점을 가지며,
// 글자 i가 j보다 먼저 와야 할 경우 간선 (i,j)를 갖는다.

#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;  // adj matrix

// 주어진 단어들로부터 알파벳 간의 선후관계 그래프를 생성한다.
void makeGraph(const vector<string>& words) {
  adj = vector<vector<int>>(26, vector<int>(26, 0));
  for (int j = 1; j < words.size(); ++j) {
    int i = j - 1;
    int len = min(words[i].size(), words[j].size());

    // word[i]가 word[j] 앞에 오는 이유를 찾는다.
    for (int k = 0; k < len; ++k) {
      if (words[i][k] != words[j][k]) {
        int a = words[i][k] - 'a';
        int b = words[j][k] - 'a';
        adj[a][b] = 1;
        break;
      }
    }
  }
}

// comments
// - 사전에 세 단어 A,B,C가 순서대로 등장한다면,
//   (A,C)는 검사하지 않고 (A,B)와 (B,C) 쌍만 검사해도,
//   위상정렬에 필요한 정보를 모두 얻을 수 있다. (증명 생략)
//

// 위상 정렬의 구현: "DFS를 수행하면서 dfs()가 종료하는 순서를 기록한 뒤, 이 순서를 뒤집는다."

vector<int> seen, order;
void dfs(int here) {
  seen[here] = 1;
  for (int there = 0; there < adj.size(); ++there) {
    if (adj[here][there] && !seen[there]) {
      dfs(there);
    }
  }
  order.push_back(here);  // dfs()가 종료하는 순서 기록
}

vector<int> topologicalSort() {
  int m = adj.size();
  seen = vector<int>(m, 0);
  order.clear();
  for (int i = 0; i < m; ++i)
    if (!seen[i]) dfs(i);
  reverse(order.begin(), order.end());
  // 만약 그래프가 DAG가 아니라면, 정렬 결과에 역방향 간선이 있다.
  for (int i = 0; i < m; ++i) {
    for (int j = i + 1; j < m; ++j) {
      if (adj[order[j]][order[i]]) {
        return vector<int>();
      }
    }
  }
  // 역방향 간선이 없다면, DFS에서 얻은 순서를 반환.
  return order;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) cin >> words[i];
    makeGraph(words);
    vector<int> res = topologicalSort();
    if (res.empty())
      cout << "INVALID HYPOTHESIS\n";
    else {
      for (int i : res) {
        cout << (char)(i + 'a');
      }
      cout << '\n';
    }
  }
  return 0;
}
