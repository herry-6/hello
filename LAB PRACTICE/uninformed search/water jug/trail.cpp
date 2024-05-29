#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;

struct State {
    int jug1, jug2;
    vector<string> path;
};

bool isValid(int x, int y, int jug1Capacity, int jug2Capacity) {
    return (x >= 0 && x <= jug1Capacity && y >= 0 && y <= jug2Capacity);
}

void bfs(int jug1Capacity, int jug2Capacity, int target) {
    queue<State> q;
    set<pair<int, int>> visited;

    q.push({0, 0, {}});
    visited.insert({0, 0});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int x = current.jug1;
        int y = current.jug2;

        if (x == target || y == target) {
            for (const string &step : current.path) {
                cout << step << endl;
            }
            return;
        }

        vector<State> nextStates = {
            {jug1Capacity, y, current.path}, // Fill jug1
            {x, jug2Capacity, current.path}, // Fill jug2
            {0, y, current.path}, // Empty jug1
            {x, 0, current.path}, // Empty jug2
            {x - min(x, jug2Capacity - y), y + min(x, jug2Capacity - y), current.path}, // Pour jug1 to jug2
            {x + min(y, jug1Capacity - x), y - min(y, jug1Capacity - x), current.path}  // Pour jug2 to jug1
        };

        nextStates[0].path.push_back("Fill jug1");
        nextStates[1].path.push_back("Fill jug2");
        nextStates[2].path.push_back("Empty jug1");
        nextStates[3].path.push_back("Empty jug2");
        nextStates[4].path.push_back("Pour jug1 to jug2");
        nextStates[5].path.push_back("Pour jug2 to jug1");

        for (State &nextState : nextStates) {
            if (isValid(nextState.jug1, nextState.jug2, jug1Capacity, jug2Capacity) &&
                visited.find({nextState.jug1, nextState.jug2}) == visited.end()) {
                visited.insert({nextState.jug1, nextState.jug2});
                q.push(nextState);
            }
        }
    }

    cout << "No solution found" << endl;
}

int main() {
    int jug1Capacity = 4;
    int jug2Capacity = 3;
    int target = 2;

    bfs(jug1Capacity, jug2Capacity, target);

    return 0;
}
