#include<iostream>
#include<vector>
#include<unordered_map>
#include<sstream>
#include<list>
#include<queue>
#include<stack>

using namespace std;

class Vertex {
    public:
    int Number();
};

class Edge {
    protected:
        Vertex* vertex0;
        Vertex* vertex1;
    public:
        Edge (Vertex* _v0, Vertex* _v1): vertex0(_v0), vertex1(_v1){}
        Vertex* v0 () const {return vertex0;}
        Vertex* v1 () const {return vertex1;}
        Vertex* Mate (Vertex * v) const {
            if (v->Number() == vertex0->Number()) return vertex1;
            else if(v->Number()==vertex1->Number()) return vertex0;
        }
};

class Graph {
protected:
    int NumberOfEdges;
    int NumberOfVerticles;
    bool Directed;
    vector <list<int>> ListaSasiedztwa;

public:
    const vector<list<int>>& getListaSasiedztwa() const { return ListaSasiedztwa; }

    Graph(int n = 0, bool directed = false): NumberOfVerticles(n), NumberOfEdges(0), Directed(directed){
        ListaSasiedztwa.resize(n);
    }
    virtual ~Graph () {};
    void MakeNull () {
        for(auto& list : ListaSasiedztwa){
            list.clear();
        }
        NumberOfEdges = 0;
    }
    int getNumberOfVerticles () { return NumberOfVerticles; }
    int getNumberOfEdges () { return NumberOfEdges; }
    bool isDirected () { return Directed; }

    void AddEdge (int u, int v) {
        if (u >= 0 && u < NumberOfVerticles && v >= 0 && v < NumberOfVerticles) {
            ListaSasiedztwa[u].push_back(v);
            if (!Directed) {
                ListaSasiedztwa[v].push_back(u);
            }
            NumberOfEdges++;
                      //  cout << "Edge added between " << u << " and " << v << endl;

        }
    }

    bool IsEdge (int u, int v){
        if (u >= 0 && u < NumberOfVerticles) {
            for (auto i : ListaSasiedztwa[u]) {
                if (i == v) {
                    return true;
                }
            }
        }
        return false;
    }
    vector <int> bfs (int poczatek, int koniec){

        queue<int> kolejka;
        kolejka.push(poczatek);
        
        vector<int> parent(NumberOfVerticles, -1);
        vector<bool> visited(NumberOfVerticles, false);

        visited[poczatek] = true;

        while(!kolejka.empty()){
            int aktualny = kolejka.front();
            kolejka.pop();
            if(aktualny == koniec){
                vector<int> droga;
                stack<int> odwroconaDroga;

        for (int i = koniec; i != -1; i = parent[i]) {
            odwroconaDroga.push(i);
        }
        while(!odwroconaDroga.empty()){
            droga.push_back(odwroconaDroga.top());
            odwroconaDroga.pop();

        }
        return droga;
            }
            for (int neighbor : ListaSasiedztwa[aktualny]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    parent[neighbor] = aktualny;
                    kolejka.push(neighbor);
                }
            }
        }
    return {}; 
    }
}; 



int main(){
    int n;
    cin >> n;
    cin.ignore();
    vector<string> przystanki (n);
    for(int i=0;i<n;i++){
        getline(cin, przystanki[i]);
    }
    Graph graph (n, false);
    int m;
    cin >> m;
    cin.ignore();
    unordered_map<string, vector<string>> linie;

    unordered_map<string, int> przystankiIndex;
    for (int i = 0; i < n; i++) {
    przystankiIndex[przystanki[i]] = i;
}
    for(int i=0;i<m;i++){
        string line_input;
        getline(cin,line_input);
        istringstream line_stream(line_input);
        string linia_nazwa;
        line_stream >> linia_nazwa;

        vector<string> trasa;
        string przystanek;
        while(line_stream >> przystanek){
            trasa.push_back(przystanek);
        }
        linie[linia_nazwa]=trasa;
    }
      for (const auto& pair : linie) {
    const vector<string>& trasa = pair.second;
    for (size_t j = 1; j < trasa.size(); j++) {
        int u = przystankiIndex[trasa[j - 1]];
        int v = przystankiIndex[trasa[j]];
        graph.AddEdge(u, v);
        //cout << "Added edge between " << trasa[j - 1] << " and " << trasa[j] << endl;

    }
}

    string poczatek,koniec;
    cin >> poczatek >> koniec;

    std::cout << "Przystanki:\n";
    for (const auto& przystanek : przystanki) {
        std::cout << przystanek << "\n";
    }

    std::cout << "Linie i ich przystanki:\n";
    for (const auto& linia : linie) {
        std::cout << linia.first << ": ";
        for (const auto& p : linia.second) {
            std::cout << p << " ";
        }
        std::cout << "\n";
    }

    std::cout << "Szukana trasa z " << poczatek << " do " << koniec << ".\n";
    
    for (int i = 0; i < n; ++i) {
            std::cout << i << ": ";
            for (int neighbor : graph.getListaSasiedztwa()[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl; }
    
    int startIndex = przystankiIndex[poczatek];
    int endIndex = przystankiIndex[koniec];

    vector<int> path = graph.bfs(startIndex, endIndex);
    if (path.empty()) {
        cout << "NO ROUTE" << endl;
    } else {
        cout << "Najkrótsza ścieżka z " << poczatek << " do " << koniec << " to:\n";
        for (int i = 0; i < path.size(); i++) {
            cout << przystanki[path[i]];
            if (i < path.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}
