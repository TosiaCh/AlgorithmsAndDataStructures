#include <iostream>
#include <vector>
#include <list>
#include <map>

using namespace std;

void rekurencja(int v, map<int,bool>& visited , map<int,bool>& cykle, int& niszczenie, vector<list<int>>& listaSasiedztwa){
 
 
  if(cykle[v]==true){
      return;
   }
   if(visited[v]==true){
      niszczenie++;
      return;
   }


   visited[v]=true;
   for (int sasiad : listaSasiedztwa[v]){
      rekurencja(sasiad,visited,cykle,niszczenie,listaSasiedztwa);
   }

   for(int n = 0;n < listaSasiedztwa.size(); n++){
            if(visited[n]==true){
               cykle[n]=true;
            } }




}


int zniszcz(vector<list<int>>& listaSasiedztwa){

   int liczbaKrawedzi = listaSasiedztwa.size();
   map<int,bool> visited;
   map<int,bool> cykle;
   int niszczenie = 0;

   for (int i = 0; i < liczbaKrawedzi; ++i) {
        visited[i] = false; 
        cykle[i] = false; 
    }
    
    for(int i=0; i<liczbaKrawedzi; ++i){
      if(visited[i]!=true){
      rekurencja(i,visited,cykle,niszczenie,listaSasiedztwa);
    }}


    return niszczenie;
}

int main(){
   int n;
    cout << "Podaj liczbę sejfów: ";
    cin >> n;
    vector<list<int>> listaSasiedztwa(n);
    for (int i = 0; i < n; i++) {
        int m;
        cout << "Ile kluczy jest w " << i + 1 << " sejfie?: ";
        cin >> m;
        for (int j = 0; j < m; j++) {
            int klucz;
            cout << "Podaj klucz: ";
            cin >> klucz;
            listaSasiedztwa[i].push_back(klucz - 1);
        }
        cout << "Lista sąsiedztwa zawiera następujące klucze dla sejfów:" << endl;
        for (int i = 0; i < n; i++) {
        cout << "Sejf " << i + 1 << ": ";
        for (int klucz : listaSasiedztwa[i]) {
            cout << klucz << " ";
        }
        cout << endl;
    }
    }

    int sejfyDoZniszczenia = zniszcz(listaSasiedztwa);
    cout << "Należy zniszczyć " << sejfyDoZniszczenia << " sejfów" << endl;

    return 0;

}