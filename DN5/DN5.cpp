#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <ctime>


using namespace std;

int main() {

    // inicializiramo matriko A
    vector<vector<double>> A;

    // inicializiramo vektor b;
    vector<double> b;

    // podamo ime datoteke
    std::string filename = "./datoteka_A_b.txt";

    // preberemo datoteko
    std::ifstream infile;
    infile.open(filename);

    // preberemo prvo vrstico, v kateri imamo podano velikost matrike A 
    std::string string_first_line;
    std::getline(infile, string_first_line);

    // string_first_line je enak 'A: n=256'
    // vemo, da je delimiter pri '=', lahko zamenjamo npr. z ' '
    std::replace(string_first_line.begin(), string_first_line.end(), '=', ' ');

    // definiramo stringstream, s katerim je nekoliko lazje shranjevati
    // podatke iz string-a, ce so loceni z ' '
    std::istringstream iss(string_first_line);
    std::string nepomemben_del1; // sem bomo dali string 'A:' iz prve vrstice
    std::string nepomemben_del2; // sem bomo dali string 'n' iz prve vrstice
    int n; // sem bomo dali velikost matrike A

    // istringstream loci glede na ' ', trenutno imamo 'A: n 256'
    iss >> nepomemben_del1;
    iss >> nepomemben_del2;
    iss >> n;

    std::cout << "Velikost matrike A: " << n << "x" << n << std::endl;;

    // V naslednjih n vrsticah imamo elemente matrike A, zato naredimo
    // iteracijo, da preberemo in zafilamo matriko A
    for (int iiA = 0; iiA < n; iiA++)
    {
        // preberemo vrstico
        std::string line;
        std::getline(infile, line);
        // zamenjamo ';' s  ' ', saj istringstream loci glede na ' '
        std::replace(line.begin(), line.end(), ';', ' ');

        // z istringstream ponovno pretvorimo string
        std::istringstream iss_column(line);

        // definiramo nov vektor, da shranimo vrstico 
        vector<double> row;

        // sedaj lahko iteriramo po elementih v iss_column
        for (int column = 0; column < n; column++)
        {
            double element_a = 0;
            iss_column >> element_a;
            row.push_back(element_a);
        }

        // ko imamo vektor za vrstico, ga damo v A
        A.push_back(row);
    }

    // sedaj imamo sestavljeno matriko A. Naslednja vrstica je prazna,
    // zato jo samo preberemo in ne naredimo nicesar. Poglejte v
    // datoteko datoteka_A_b.txt
    std::string empty_line;
    std::getline(infile, empty_line);

    // prebrati moramo se vektor b
    std::string string_line_b;
    std::getline(infile, string_line_b);

    // lahko uporabimo podoben trik kot pri prvi vrstici
    std::replace(string_line_b.begin(), string_line_b.end(), '>', ' ');
    std::istringstream iss_b(string_line_b);
    int n_b; // sem bomo dali velikost vektorja b (ki je identicna velikosti A)

    iss_b >> nepomemben_del1;
    iss_b >> nepomemben_del2;
    iss_b >> n_b;

    std::cout << "Velikost vektorja b: " << n_b << std::endl;;

    // naredimo iteracijo po naslednjem n_b stevilu vrstic
    for (int iib = 0; iib < n_b; iib++)
    {
        // preberemo vrstico in shranimo element v vrstici v vektor b
        std::string line_b_element;
        std::getline(infile, line_b_element);
        std::istringstream iss_b_element(line_b_element);

        double b_element = 0;
        iss_b_element >> b_element;

        b.push_back(b_element);
    }

    // Sedaj imamo A in b. Lahko napisemo Gauss-Seidel metodo. Najprej
    // inicializiramo vektor resitve T, npr. na 100 stopinj.
    vector<double> T;
    for (int iiT = 0; iiT < n_b; iiT++)
    {
        T.push_back(100);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    for (int k = 0; k < 2000; ++k) {
        for (int i = 0; i < n; ++i) {

            double d = b[i];
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    d = d - A[i][j] * T[j];
                }
            }

            T[i] = d / A[i][i];
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_duration = end_time - start_time;
    std::cout << "Time of Gauss-Seidel: " << time_duration.count() << " seconds" << std::endl;

    // Za izpis maksimalne vrednosti
    double max_T = 0;
    for (int iiT = 0; iiT < n_b; iiT++)
    {
        cout << T[iiT] << endl;

        if (T[iiT] > max_T) {
            max_T = T[iiT];
        }
    }
    std::cout << "Serial Time: " << time_duration.count() << " seconds" << std::endl;
    cout << "Max. temperature: " << max_T << " degree C." << endl;



    return 0;
}
