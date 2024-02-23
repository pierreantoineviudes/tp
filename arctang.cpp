#define taille_tableau 1000000L
#define MAX_THREADS 15

#include <thread>
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

double somme_globale = 0.0;

void somme_une_tranche(double tab[], int deb_inclu, int fin_exlue, long &somme_globale)
{
    double somme_locale = 0.00000000;
    cout << "some localce : " << somme_locale << endl;
    for (int i = deb_inclu; i < fin_exlue; i++)
    {
        somme_locale += tab[i];
        // cout << "tab[i]" << tab[i] << endl;
        // cout << "somme_locale update  : " << somme_locale << endl;
    }
    somme_globale += somme_locale / taille_tableau;
    cout << "comme locale ! " << somme_locale / taille_tableau << endl;
}

int main()
{
    double tab[taille_tableau];
    for (int i = 0; i < taille_tableau; i++)
    {
        double term = 1.0 + pow((i + 0.5) / taille_tableau, 2);
        tab[i] = 4.0 / term;
        // cout << "4.0 / term : " << 4.0 / term << endl;
    }

    for (int nb_threads = 1; nb_threads < MAX_THREADS; nb_threads++)
    {
        thread lds[nb_threads];
        long somme_globale = 0;
        int size_tranche = ceil(taille_tableau * 1.0 / nb_threads);
        auto start = chrono::high_resolution_clock::now();
        int taille_deja_fait = 0;
        for (int k = 0; k < nb_threads - 1; k++, taille_deja_fait += size_tranche)
        {
            lds[k] = thread(somme_une_tranche, tab, k * size_tranche, (k + 1) * size_tranche, ref(somme_globale));
        }
        lds[nb_threads - 1] = thread(somme_une_tranche, tab, (nb_threads - 1) * size_tranche, taille_tableau, ref(somme_globale));
        for (auto &tache_bis : lds)
            tache_bis.join();
        auto end = chrono::high_resolution_clock::now();
        auto diff = end - start;
        auto diff_sec = chrono::duration_cast<chrono::nanoseconds>(diff);

        cout << "Temps moyen pour " << nb_threads << "threads = " << diff_sec.count() / 1000000.0 << "ms";
        cout << "La somme de " << taille_tableau << "valeurs : " << somme_globale << endl;
    }

    cout << "(Controle : la somme devrait etre ";
    cout << M_PI << ")\n";
    return 0;
}