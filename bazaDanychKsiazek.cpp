#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <limits>
#include <sstream>

struct Element {
    std::string tytul;
    std::string autor;
    void wypisz() const {
        std::cout << "Tytuł: " << tytul << "\n";
        std::cout << "Autor: " << autor << "\n";
        std::cout << "------------------------\n";
    }
};

class BazaDanych {
private:
    std::vector<Element> baza;

public:
    void dodajElement(const Element& element) {
        baza.push_back(element);
        std::cout << "Dodano element do bazy danych.\n";
    }
void usunElement(const std::string& tytul) {
    auto it = std::remove_if(baza.begin(), baza.end(), [&](const Element& e) {
        return e.tytul == tytul; 
    });

    if (it != baza.end()) {
        baza.erase(it, baza.end());
        baza.shrink_to_fit();  
        std::cout << "Usunięto element z bazy danych.\n";
    } else {
        std::cout << "Element o podanym tytule nie został znaleziony.\n";
    }
}


    void usunElementAutor(const std::string& autor) {
        auto it = std::remove_if(baza.begin(), baza.end(), [&](const Element& e) {
            return e.autor == autor;
        });

        if (it != baza.end()) {
            baza.erase(it, baza.end());
            baza.shrink_to_fit();
            std::cout << "Usunięto element z bazy danych.\n";
        } else {
            std::cout << "Element o podanym autorze nie został znaleziony.\n";
        }
    }

    void wyszukajElement(const std::string& szukane) const {
        std::cout << "Wyniki wyszukiwania:\n";
        for (const auto& element : baza) {
            if (zawieraPodciag(element.tytul, szukane) || zawieraPodciag(element.autor, szukane)) {
                element.wypisz();
            }
        }
    }

    void wypiszBaze() const {
        std::cout << "Baza danych:\n";
        for (const auto& element : baza) {
            element.wypisz();
        }
    }

    void zapiszDoPliku(const std::string& nazwaPliku) const {
        std::ofstream plik(nazwaPliku);

        if (plik.is_open()) {
            plik << "tytul,autor\n";

            for (const auto& element : baza) {
                plik << element.tytul << "," << element.autor << "\n";
            }

            std::cout << "Zapisano bazę danych do pliku.\n";
        } else {
            std::cerr << "Błąd podczas otwierania pliku do zapisu.\n";
        }
    }

    void odczytajZPliku(const std::string& nazwaPliku) {
    std::ifstream plik(nazwaPliku);

    if (plik.is_open()) {
        baza.clear();

        std::string naglowki;
        std::getline(plik, naglowki);

        if (naglowki != "tytul,autor") {
            std::cerr << "Błąd: Nieprawidłowy format pliku.\n";
            return;
        }

        std::string linia;
        while (std::getline(plik, linia)) {
            std::stringstream ss(linia);
            Element element;
            if (std::getline(ss, element.tytul, ',') && std::getline(ss, element.autor)) {
                if (!element.tytul.empty() && !element.autor.empty()) {
                    baza.push_back(element);
                    std::cout << "Wczytano: " << element.tytul << ", " << element.autor << "\n";
                }
            }
        }

        std::cout << "Odczytano bazę danych z pliku.\n";
    } else {
        std::cerr << "Błąd podczas otwierania pliku do odczytu.\n";
    }
}

    void wyczyscBazeDanych() {
        baza.clear();
        std::cout << "Baza danych została wyczyszczona.\n";
    }

private:

    bool zawieraPodciag(const std::string& tekst, const std::string& szukane) const {
        return std::search(tekst.begin(), tekst.end(), szukane.begin(), szukane.end(), 
                           [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }) != tekst.end();
    }
};

int main() {
    BazaDanych baza;
    baza.odczytajZPliku("baza_danych.txt");

    int wybor;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Dodaj element\n";
        std::cout << "2. Usuń element (po tytule)\n";
        std::cout << "3. Usuń element (po autorze)\n";
        std::cout << "4. Wyszukaj element\n";
        std::cout << "5. Wyświetl bazę danych\n";
        std::cout << "6. Zapisz bazę danych do pliku\n";
        std::cout << "7. Wyczyść bazę danych\n";
        std::cout << "0. Wyjście\n";
        std::cout << "Wybierz opcję: ";
        std::cin >> wybor;

        //ignorowanie znaku nowej linii w buforze
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (wybor) {
            case 1: {
                Element nowyElement;
                std::cout << "Podaj tytuł: ";
                std::getline(std::cin, nowyElement.tytul);
                std::cout << "Podaj autora: ";
                std::getline(std::cin, nowyElement.autor);

                baza.dodajElement(nowyElement);
                break;
            }
            case 2: {
                std::string tytulDoUsuniecia;
                std::cout << "Podaj tytułu do usunięcia: ";
                std::getline(std::cin, tytulDoUsuniecia);
                baza.usunElement(tytulDoUsuniecia);
                break;
            }
            case 3: {
                std::string autorDoUsuniecia;
                std::cout << "Podaj autora do usunięcia: ";
                std::getline(std::cin, autorDoUsuniecia);
                baza.usunElementAutor(autorDoUsuniecia);
                break;
            }
            case 4: {
                std::string szukane;
                std::cout << "Podaj część tytułu lub autora do wyszukania: ";
                std::getline(std::cin, szukane);
                baza.wyszukajElement(szukane);
                break;
            }
            case 5:
                baza.wypiszBaze();
                break;
            case 6:
                baza.zapiszDoPliku("baza_danych.txt");
                break;
            case 0:
                std::cout << "Koniec programu.\n";
                break;
            case 7:
                baza.wyczyscBazeDanych();
                break;
            default:
                std::cout << "Nieprawidłowa opcja. Wybierz ponownie.\n";
                break;
        }

    } while (wybor != 0);

    return 0;
}
