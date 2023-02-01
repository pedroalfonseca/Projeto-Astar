// basics
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#define INF 0x7fffffff
using namespace std;

// line colors
enum Color {
    ERR,
    R,
    G,
    B,
    Y
};

// subway station
using Station = pair<int, Color>;
#define id first
#define line second
#define make_Station make_pair

// subway connection
struct Connection {
    float direct_dist, real_dist;
    Color line;
};

// Paris subway map
Connection map[14][14];

// A* algorithm
void Astar(const int src, const int dst) {
    float duration[14];
    int precursors[14];
    for (int i = 0; i < 14; i++) {
        duration[i] = INF;
        precursors[i] = -1;
    }
    duration[src] = 0;

    priority_queue<Station, vector<Station>, greater<Station>> pq;
    pq.push(make_Station(src, B));

    while (!pq.empty()) {
        int min = pq.top().id;
        Color cur_line = pq.top().line;
        pq.pop();

        for (int j = min + 1; j < 14; j++)
            if (map[min][j].line != ERR) {
                float heuristic = map[min][j].real_dist + map[min][j].direct_dist;
                heuristic /= 30; // converts from distance to hours
                heuristic *= 60; // converts from hours to minutes
                if (map[min][j].line != cur_line)
                    heuristic += 4; // adds line change additional time

                if (duration[min] + heuristic < duration[j]) {
                    duration[j] = duration[min] + heuristic;
                    precursors[j] = min;

                    pq.push(make_Station(j, map[min][j].line));
                }
            }
    }

    stack<int> s;
    for (int p = dst; p != -1; p = precursors[p])
        s.push(p + 1);
    
    printf("Estimated time: %.2f minutes\n", duration[dst]);
    printf("Route: ");
    while (!s.empty()) {
        printf("%d ", s.top());
        s.pop();
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    map[ 0][ 1] = {   10,   10,   B };
    map[ 0][ 2] = { 18.5,    0, ERR };
    map[ 0][ 3] = { 24.8,    0, ERR };
    map[ 0][ 4] = { 36.4,    0, ERR };
    map[ 0][ 5] = { 38.8,    0, ERR };
    map[ 0][ 6] = { 35.8,    0, ERR };
    map[ 0][ 7] = { 25.4,    0, ERR };
    map[ 0][ 8] = { 17.6,    0, ERR };
    map[ 0][ 9] = {  9.1,    0, ERR };
    map[ 0][10] = { 16.7,    0, ERR };
    map[ 0][11] = { 27.3,    0, ERR };
    map[ 0][12] = { 27.6,    0, ERR };
    map[ 0][13] = { 29.8,    0, ERR };

    map[ 1][ 2] = {  8.5,  8.5,   B };
    map[ 1][ 3] = { 14.8,    0, ERR };
    map[ 1][ 4] = { 26.6,    0, ERR };
    map[ 1][ 5] = { 29.1,    0, ERR };
    map[ 1][ 6] = { 26.1,    0, ERR };
    map[ 1][ 7] = { 17.3,    0, ERR };
    map[ 1][ 8] = {   10,   10,   Y };
    map[ 1][ 9] = {  3.5,  3.5,   Y };
    map[ 1][10] = { 15.5,    0, ERR };
    map[ 1][11] = { 20.9,    0, ERR };
    map[ 1][12] = { 19.1,    0, ERR };
    map[ 1][13] = { 21.8,    0, ERR };

    map[ 2][ 3] = {  6.3,  6.3,   B };
    map[ 2][ 4] = { 18.2,    0, ERR };
    map[ 2][ 5] = { 20.6,    0, ERR };
    map[ 2][ 6] = { 17.6,    0, ERR };
    map[ 2][ 7] = { 13.6,    0, ERR };
    map[ 2][ 8] = {  9.4,  9.4,   R };
    map[ 2][ 9] = { 10.3,    0, ERR };
    map[ 2][10] = { 19.5,  3.5,   R };
    map[ 2][11] = { 19.1,    0, ERR };
    map[ 2][12] = { 12.1, 18.7,   R };
    map[ 2][13] = { 16.6,    0, ERR };

    map[ 3][ 4] = {   12,   13,   B };
    map[ 3][ 5] = { 14.4,    0, ERR };
    map[ 3][ 6] = { 11.5,    0, ERR };
    map[ 3][ 7] = { 12.4, 15.3,   G };
    map[ 3][ 8] = { 12.6,    0, ERR };
    map[ 3][ 9] = { 16.7,    0, ERR };
    map[ 3][10] = { 23.6,    0, ERR };
    map[ 3][11] = { 18.6,    0, ERR };
    map[ 3][12] = { 10.6, 12.8,   G };
    map[ 3][13] = { 15.4,    0, ERR };

    map[ 4][ 5] = {    3,    3,   B };
    map[ 4][ 6] = {  2.4,  2.4,   Y };
    map[ 4][ 7] = { 19.4,   30,   Y };
    map[ 4][ 8] = { 23.3,    0, ERR };
    map[ 4][ 9] = { 28.2,    0, ERR };
    map[ 4][10] = { 34.2,    0, ERR };
    map[ 4][11] = { 24.8,    0, ERR };
    map[ 4][12] = { 14.5,    0, ERR };
    map[ 4][13] = { 17.9,    0, ERR };

    map[ 5][ 6] = {  3.3,    0, ERR };
    map[ 5][ 7] = { 22.3,    0, ERR };
    map[ 5][ 8] = { 25.7,    0, ERR };
    map[ 5][ 9] = { 30.3,    0, ERR };
    map[ 5][10] = { 36.7,    0, ERR };
    map[ 5][11] = { 27.6,    0, ERR };
    map[ 5][12] = { 15.2,    0, ERR };
    map[ 5][13] = { 18.2,    0, ERR };

    map[ 6][ 7] = {   20,    0, ERR };
    map[ 6][ 8] = {   23,    0, ERR };
    map[ 6][ 9] = { 27.3,    0, ERR };
    map[ 6][10] = { 34.2,    0, ERR };
    map[ 6][11] = { 25.7,    0, ERR };
    map[ 6][12] = { 12.4,    0, ERR };
    map[ 6][13] = { 15.6,    0, ERR };

    map[ 7][ 8] = {  8.2,  9.6,   Y };
    map[ 7][ 9] = { 20.3,    0, ERR };
    map[ 7][10] = { 16.1,    0, ERR };
    map[ 7][11] = {  6.4,  6.4,   G };
    map[ 7][12] = { 22.7,    0, ERR };
    map[ 7][13] = { 27.6,    0, ERR };

    map[ 8][ 9] = { 13.5,    0, ERR };
    map[ 8][10] = { 11.2, 12.2,   R };
    map[ 8][11] = { 10.9,    0, ERR };
    map[ 8][12] = { 21.2,    0, ERR };
    map[ 8][13] = { 26.6,    0, ERR };

    map[ 9][10] = { 17.6,    0, ERR };
    map[ 9][10] = { 24.6,    0, ERR };
    map[ 9][10] = { 18.7,    0, ERR };
    map[ 9][10] = { 21.2,    0, ERR };

    map[10][11] = { 14.2,    0, ERR };
    map[10][12] = { 31.5,    0, ERR };
    map[10][13] = { 35.5,    0, ERR };

    map[11][12] = { 28.8,    0, ERR };
    map[11][13] = { 33.6,    0, ERR };

    map[12][13] = {  5.1,  5.1,   G };

    if (argc != 3) {
        printf("Usage: %s [source] [destination]\n", argv[0]);
        exit(1);
    }

    int src = atoi(argv[1]), dst = atoi(argv[2]);

    if ((src < 1 || src > 14) || (dst < 1 || dst > 14)) {
        puts("Error: Both source and destination station " \
            "must be at least 1 and at most 14.");
        exit(1);
    }

    Astar(atoi(argv[1]) - 1, atoi(argv[2]) - 1);

    return 0;
}