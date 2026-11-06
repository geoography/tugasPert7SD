#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Graph{
    private:
        int numberVertex;
        vector<vector<int>> adjMatrix;

    public:
        Graph(int banyakTitik){
            numberVertex = banyakTitik;
            adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
        }

    void addEdge (int i, int j) {
        if (i>=0 && i<numberVertex && j>=0 && j<numberVertex) {
            adjMatrix[i][j] = 1;
            adjMatrix[j][i] = 1;
        } else {
            cout << "Vertex nonvalid" << endl;
        }
    }

    void printAdjMatrix() {
        cout << "  ";
        for (int i = 0; i < numberVertex; i++) {
            cout << char('A' + i) << " "; // konversi angka 0-6 kembali ke A-F sesuai standari ASCII
        }
        cout << endl;

        for (int i = 0; i < numberVertex; i++) {
            cout << char('A' + i) << " "; // konversi angka 0-6 kembali ke A-F sesuai standar ASCII
            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bfs (int startVertex) {
        if (startVertex < 0 || startVertex >= numberVertex) {
            cout << "Vertex awal nonvalid" << endl;
            return;
        }

        vector<bool> visited(numberVertex, false);
        queue<int>titikVisit;

        visited[startVertex] = true;
        titikVisit.push(startVertex);

        cout << "Urutan kunjungan BFS: ";
        while(!titikVisit.empty()) {
            int currentVertex = titikVisit.front();
            titikVisit.pop();
            cout << char('A' + currentVertex) << " "; // konversi angka 0-6 kembali ke A-F sesuai standar ASCII

            for (int i=0; i<numberVertex; i++){
                if(adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    titikVisit.push(i);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    Graph graphh(6); // vertex A-F, menggunakan indexing 0 sampai 5

    int jumlahEdge;
    cout << "Masukkan jumlah edge: ";
    cin >> jumlahEdge;

    cout << "Masukkan edge (contoh: A B)" << endl;
    for (int k = 0; k < jumlahEdge; k++) {
        char u, v;
        cout << "Edge ke-" << k + 1 << ": ";
        cin >> u >> v;
        graphh.addEdge(toupper(u) - 'A', toupper(v) - 'A'); // konversi agar sesuai dgn standar no indeks array (0 sampai 5)
    }

    cout << endl << "Adjacency Matrix:" << endl;
    graphh.printAdjMatrix();
    cout << endl;

    char start;
    cout << "Masukkan vertex awal: ";
    cin >> start;

    graphh.bfs(toupper(start) - 'A'); // konversi agar sesuai dgn standar no indeks array (0 sampai 5)
    return 0;
}