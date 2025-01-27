#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure pour le bloc memoire
struct MemBlock {
    int start; // Indice de début du bloc dans le tableau
    int size;  // Taille du bloc
    bool allocated; // Indique si le bloc est alloué ou libre
};

// VARIABLE GLOBAL
vector<MemBlock> memory;
int memorySize;


// Fonction pour afficher l'état de la mémoire
void displayMemory() {
    cout << "\n==== Etat de la Memoire ====" << endl;
    cout << "------------------------------" << endl;
    for (int i = 0; i < memory.size(); ++i) {
        cout << setw(1000) << i << ": ";
      cout << setw(1000) << memory[i].start << " | "
           << setw(1000) << memory[i].size  << " | "
           << setw(1000) << (memory[i].allocated ? "Occupe" : "Libre") << endl;
       }

    cout << "----------------------------------" << endl;
}

// Fonction pour allouer un bloc mémoire (first-fit)
int sim_malloc(int size) {
    for (int i = 0; i < memory.size(); ++i) {
        if (!memory[i].allocated && memory[i].size >= size) {
          
           // Split du bloc si nécessaire
             if (memory[i].size > size) {
               MemBlock newBlock = {memory[i].start + size, memory[i].size - size, false};
               memory[i].size = size; 
               memory.insert(memory.begin()+i+1, newBlock );
             }

            memory[i].allocated = true;
            return memory[i].start;  // Retourne l'indice de début du bloc
        }
    }
    return -1; // Retourne -1 si pas de bloc disponible
}

// Fonction pour libérer un bloc mémoire
void sim_free(int ptr) {
    for (int i = 0; i < memory.size(); ++i) {
        if (memory[i].allocated && memory[i].start == ptr) {
            memory[i].allocated = false;
            return;
        }
    }
}

int main() {

    int maxAllocatedMemory;
    
     cout << "Entrez la taille de la memoire: ";
        cin >> memorySize;
    
   memory.push_back({0,memorySize,false});

    int choice, size, ptr;
    do {
        cout << "\n==== Menu ====" << endl;
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
