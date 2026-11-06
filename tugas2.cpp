#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;

    // hitung jarak terpendek dari source, sekaligus simpan parent untuk rute
    void hitungDijkstra(int source, vector<int>& distance, vector<int>& parent) {
        vector<bool> visited(V, false);
        distance.assign(V, INT_MAX);
        parent.assign(V, -1);
        distance[source] = 0;

        for (int i = 0; i < V; i++) {
            int u = -1;

            for (int j = 0; j < V; j++) {
                if (!visited[j] &&
                    (u == -1 || distance[j] < distance[u])) {
                    u = j;
                }
            }

            if (u == -1 || distance[u] == INT_MAX)
                break;

            visited[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] != 0 && !visited[v]) {
                    int newDistance = distance[u] + adjMatrix[u][v];

                    if (newDistance < distance[v]) {
                        distance[v] = newDistance;
                        parent[v] = u; // catat dari mana rute ke v
                    }
                }
            }
        }
    }

    // cetak rute dengan menelusuri parent dari tujuan ke asal (utk soal no 3)
    void cetakRute(int tujuan, const vector<int>& parent) {
        vector<int> rute;
        for (int v = tujuan; v != -1; v = parent[v]) {
            rute.push_back(v);
        }
        reverse(rute.begin(), rute.end());

        for (size_t i = 0; i < rute.size(); i++) {
            cout << char('A' + rute[i]);
            if (i + 1 < rute.size()) cout << " -> ";
        }
    }

public:
    Graph(int jumlahVertex) {
        V = jumlahVertex;
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
    }

    // jarak terpendek dari source ke semua lokasi lain (utk soal no 1 dan 2)
    void dijkstra(int source) {
        vector<int> distance, parent;
        hitungDijkstra(source, distance, parent);

        cout << "Jarak terpendek dari lokasi " << char('A' + source) << ":" << endl;

        for (int i = 0; i < V; i++) {
            if (i == source) continue;

            cout << char('A' + i) << " : ";
            if (distance[i] == INT_MAX) {
                cout << "Tidak terjangkau" << endl;
            } else {
                cout << "Rute ";
                cetakRute(i, parent);
                cout << " | Total jarak " << distance[i] << " km" << endl;
            }
        }
    }

    // rekomendasi rute tercepat dari asal ke tujuan
    void rekomendasiRute(int asal, int tujuan) {
        if (asal < 0 || asal >= V || tujuan < 0 || tujuan >= V) {
            cout << "Lokasi nonvalid" << endl;
            return;
        }

        vector<int> distance, parent;
        hitungDijkstra(asal, distance, parent);

        if (distance[tujuan] == INT_MAX) {
            cout << "Tidak ada rute dari " << char('A' + asal)
                 << " ke " << char('A' + tujuan) << endl;
            return;
        }

        cout << "Rute tercepat dari " << char('A' + asal)
             << " ke " << char('A' + tujuan) << ": ";
        cetakRute(tujuan, parent);
        cout << endl << "Total jarak: " << distance[tujuan] << " km" << endl;
    }
};

int main() {
    Graph graph(6); // lokasi A-F (A=0, B=1, C=2, D=3, E=4, F=5)

    graph.addEdge(0, 1, 4); // A-B
    graph.addEdge(0, 2, 2); // A-C
    graph.addEdge(1, 2, 1); // B-C
    graph.addEdge(1, 3, 5); // B-D
    graph.addEdge(1, 4, 3); // B-E
    graph.addEdge(2, 3, 8); // C-D
    graph.addEdge(2, 4, 6); // C-E
    graph.addEdge(3, 4, 2); // D-E
    graph.addEdge(3, 5, 4); // D-F
    graph.addEdge(4, 5, 3); // E-F

    // soal 1 dan 2: rute terpendek dari A ke semua lokasi + total jarak
    graph.dijkstra(0);
    cout << endl;

    // soal 3: rekomendasi rute berdasarkan input pengguna
    char asal, tujuan;
    cout << "Masukkan lokasi asal (A-F): ";
    cin >> asal;
    cout << "Masukkan lokasi tujuan (A-F): ";
    cin >> tujuan;

    graph.rekomendasiRute(toupper(asal) - 'A', toupper(tujuan) - 'A');

    return 0;
}