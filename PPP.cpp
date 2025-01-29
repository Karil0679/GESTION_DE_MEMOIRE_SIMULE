#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// Structure pour représenter un bloc mémoire
struct MemBlock {
    int start; // Indice de début du bloc dans le tableau
    int size;  // Taille du bloc
    bool allocated; // Indique si le bloc est alloué ou libre
};

// Variables globales
vector<char> memory(1000, 0); // Tableau de 1000 cases
vector<MemBlock> allocatedBlocks;

// Fonction pour afficher l'état de la mémoire
void displayMemory() {
    cout << "n==== Etat de la Memoire ====" << endl;
    cout << "----------------------------------" << endl;
     cout << setw(10) << "Idx" << ": "
           << setw(10) << "start" << " | "
           << setw(10) << "size"  << " | "
           << setw(10) << "Etat" << endl;
        
    for (int i = 0; i < allocatedBlocks.size(); ++i) {
      cout << setw(10) << i << ": ";
        cout << setw(10) << allocatedBlocks[i].start << " | "
             << setw(10) << allocatedBlocks[i].size  << " | "
             << setw(10) << (allocatedBlocks[i].allocated ? "Occupe" : "Libre") << endl;
        }

    cout << "----------------------------------" << endl;
}

// Fonction pour allouer un bloc mémoire (first-fit)
int sim_malloc(int size) {
  
  for (int i = 0; i < allocatedBlocks.size() ; ++i) {
      
        if (!allocatedBlocks[i].allocated && allocatedBlocks[i].size >= size) {
          
             // Split du bloc si nécessaire
             if (allocatedBlocks[i].size > size) {
               MemBlock newBlock = {allocatedBlocks[i].start + size, allocatedBlocks[i].size - size, false};
               allocatedBlocks[i].size = size;
               allocatedBlocks.insert(allocatedBlocks.begin()+i+1, newBlock );
             }

            allocatedBlocks[i].allocated = true;
            return allocatedBlocks[i].start;  // Retourne l'indice de début du bloc
        }
    }
  
  // si aucun bloc libre n'est trouvé, on essaye d'allouer à partir de la mémoire inutilisée
    int nextStart = 0;
    if (!allocatedBlocks.empty()){
        nextStart = allocatedBlocks.back().start+ allocatedBlocks.back().size;
     }

    if (nextStart + size <= 1000){
        MemBlock newBlock = {nextStart, size, true};
         allocatedBlocks.push_back(newBlock);
         return nextStart;
    }
    return -1; // Retourne -1 si pas de bloc disponible

}

// Fonction pour libérer un bloc mémoire
void sim_free(int ptr) {
     for (int i = 0; i < allocatedBlocks.size(); ++i) {
        if (allocatedBlocks[i].allocated && allocatedBlocks[i].start == ptr) {
            allocatedBlocks[i].allocated = false;
            return;
        }
    }
}

int main() {
   
    //Initialisation d'un seul bloc mémoire pour la taille totale
      MemBlock initialBlock = {0,1000, false};
     allocatedBlocks.push_back(initialBlock);
    
    int choice, size, ptr;
    do {
        cout << "n==== Menu ====" << endl;
        cout << "1. Allouer memoire" << endl;
        cout << "2. Liberer memoire" << endl;
        cout << "3. Afficher memoire" << endl;
        cout << "0. Quitter" << endl;
        cout << "Choix : ";
        cin >> choice;

        switch (choice) {
            case 1:
            cout << "Entrez la taille a allouer : ";
            cin >> size;
            ptr = sim_malloc(size);
            if (ptr != -1) {
                cout << "Memoire allouee a partir de l'adresse : " << ptr << endl;
            } else {
                cout << "Erreur: Pas de memoire disponible" << endl;
            }
            break;
        case 2:
            cout << "Entrez l'adresse a liberer : ";
            cin >> ptr;
             sim_free(ptr);
            cout << "Memoire liberee" << endl;
            break;
        case 3:
              displayMemory();
            break;
        case 0:
            cout << "Fin du programme" << endl;
            break;
        default:
            cout << "Choix invalide" << endl;
        }
    } while (choice != 0);
    return 0;
}