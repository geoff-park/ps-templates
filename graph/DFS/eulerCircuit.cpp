#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;

void getEulerCircuit(int here, vector<int>& circuit) {
  for (int there = 0; there < adj[here].size(); ++there) {
    while (adj[here][there] > 0) {
      // 양쪽 간선을 모두 지운다.
      adj[here][there]--;
      adj[there][here]--;
      getEulerCircuit(there, circuit);
    }
  }
  circuit.push_back(here);
}
