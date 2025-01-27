


#include <iostream>
using namespace std;

struct Bloc memoire[MEMOIRE_TAILLE];

void initialiserMemoire() {
    for (int i = 0; i < MEMOIRE_TAILLE; i++) {
        memoire[i].taille = 1;
        memoire[i].libre = true;
    }
}

void afficherMemoire() {
    cout << "Etat de la memoire :" << endl;
    for (int i = 0; i < MEMOIRE_TAILLE; i++) {
        if (memoire[i].libre) {
            cout << "L ";
        } else {
            cout << "O ";
        }
    }
    cout << endl;
}

void* malloc(int taille) 
{
    if (taille < BLOC_MIN) {
        taille = BLOC_MIN;
    }
    int blocsNecessaires = taille;
    int debut = -1;
    for (int i = 0; i <= MEMOIRE_TAILLE - blocsNecessaires; i++) {
        bool libre = true;
        for (int j = i; j < i + blocsNecessaires; j++) {
            if (!memoire[j].libre) {
                libre = false;
                break;
            }
        }
        if (libre) {
            debut = i;
            break;
        }
    }
    if (debut != -1) {
        for (int i = debut; i < debut + blocsNecessaires; i++) {
            memoire[i].libre = false;
        }
        return (void*)debut;
    } else {
        cout << "Erreur : pas assez de memoire disponible." << endl;
        return nullptr;
    }
}

void free(void* adresse, int taille) {
    if (taille < BLOC_MIN) {
        taille = BLOC_MIN;
    }
    int debut = (int)adresse;
    for (int i = debut; i < debut + taille; i++) {
        memoire[i].libre = true;
    }
}







