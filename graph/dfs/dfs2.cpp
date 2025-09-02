/* 간선을 구분하는 DFS 구현 */
#include <bits/stdc++.h>
using namespace std;

// 그래프의 인접 리스트 표현
vector<vector<int>> adj;

vector<int> discovered;  // discovered[i]: i번 정점 발견 순서
vector<int> finished;    // finished[i]: dfs(i)가 종료했으면 1, 아니면 0

// 지금까지 발견한 정점의 수
int counter;

void dfs2(int here) {
  discovered[here] = counter++;

  // 모든 인접 정점을 순회하면서
  for (int i = 0; i < adj[here].size(); ++i) {
    int there = adj[here][i];
    cout << "(" << here << "," << there << ") is a ";  // (here,there) is ~

    // 아직 방문한 적 없다면 방문한다.
    if (discovered[there] == -1) {
      cout << "tree edge" << endl;  // dfs 진행 중 방문했다면, there는 트리 간선(tree edge)이다.
      dfs2(there);
    }

    // 여기까지 내려왔다면, there를 이미 방문했다는 뜻임.

    // 만약 there가 here보다 늦게 발견됐으면 there는 here의 후손이다.
    else if (discovered[here] < discovered[there]) {
      cout << "forward edge" << endl;  // 순방향 간선(forward edge)
    }

    // 만약 dfs2(there)가 아직 종료하지 않았으면 there는 here의 선조다.
    // (dfs2가 아직 진행 중인데, there가 이미 방문된 상태고, there->here 순으로 발견된다는 뜻이므로)
    else if (finished[there] == 0) {
      cout << "back edge" << endl;  // 역방향 간선(back edge)
    }

    // 이 외의 경우는 모두 교차 간선
    else {
      cout << "cross edge" << endl;
    }
  }

  finished[here] = 1;
}