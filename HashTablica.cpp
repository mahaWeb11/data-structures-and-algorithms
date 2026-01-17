#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <list>

using namespace std;

int prvi_sljedeci_prost_broj(int p) {
    auto r = p;
    while (true) {
        bool prost = true;
        auto korijen = int(sqrt(r));
        for (int i = 2; i <= korijen; i++) {
            if (r % i == 0) {
                prost = false;
                break;
            }
        }
        if (prost) return r;

        r += 2;
    }
}

template<typename K, typename V, class H>
class HashTablica {
private:
    enum class Status { S_SLOBODNO, S_ZAUZETO, S_OBRISANO };

    class Element {
    public:
        K kljuc;
        V vrijednost;
        Status status;

        Element() : status(Status::S_SLOBODNO) {}
    };

    vector<Element> tablica;
    size_t alociranaVelicina;
    size_t zauzetaVelicina;
    size_t brojPoredenja;
    H hasher;
public:
    HashTablica() {
        alociranaVelicina = 151;
        zauzetaVelicina = 0;
        brojPoredenja = 0;
        hasher = H{};
        tablica.resize(alociranaVelicina);
    }

    void dodaj(K kljuc, V vrijednost) {
        if(zauzetaVelicina / alociranaVelicina > 0.6) rehash();

        auto h = hasher(kljuc) % alociranaVelicina;

        while(true) {
            brojPoredenja++;
            if(tablica[h].status == Status::S_ZAUZETO) {
                h = (h +1) % alociranaVelicina;
                continue;
            }

            tablica[h].status = Status::S_ZAUZETO;
            tablica[h].kljuc = kljuc;
            tablica[h].vrijednost = vrijednost;
            zauzetaVelicina++;

            return;
        }
    }

    void rehash() {
        auto kopija = tablica;
        alociranaVelicina = prvi_sljedeci_prost_broj(2*alociranaVelicina+1);

        tablica = vector<Element>(alociranaVelicina);
        zauzetaVelicina = 0;
        brojPoredenja = 0;

        for(auto &x : kopija) {
            if(x.status == Status::S_ZAUZETO) dodaj(x.kljuc, x.vrijednost);
        }
    }

    void obrisi(K kljuc) {
        auto h = hasher(kljuc) % alociranaVelicina;

        while(true) {
            if(tablica[h].status == Status::S_SLOBODNO) throw runtime_error("Ne postoji taj element");

            if(tablica[h].status == Status::S_ZAUZETO && tablica[h].kljuc == kljuc) {
                tablica[h].status = Status::S_OBRISANO;
                zauzetaVelicina--;
                return;
            }

            h = (h + 1) % alociranaVelicina;
        }
    }

    V nadji(K kljuc) {
        auto h = hasher(kljuc) % alociranaVelicina;

        while(true) {
            if(tablica[h].status == Status::S_SLOBODNO) throw runtime_error("Ne postoji taj element");

            if(tablica[h].status == Status::S_ZAUZETO && tablica[h].kljuc == kljuc) {
                return tablica[h].vrijednost;
            }

            h = (h + 1) % alociranaVelicina;
        }
    }

    void test() {
        for(auto &x : tablica) {
            if(x.status == Status::S_SLOBODNO) {
                cout << " ";
            } else if(x.status == Status::S_ZAUZETO) {
                cout << "*";
            } else {
                cout << "#";
            }
        }
        cout << endl;
        cout << "Broj poredjenja: " << brojPoredenja << "\n";
    }
};

class MojHasher {
public:
    size_t operator()(string s) {
        int p1 = 37;
        int p2 = 151;

        size_t r = 0;
        for (auto c: s) {
            r = (r * p1 + c - 32) % p2;
        }

        return r;
    }
};

void testHash() {
    list<string> l;

    l.push_back("6133/M");
    l.push_back("257/IT-21");
    l.push_back("6174/M");
    l.push_back("199/IT-20");
    l.push_back("270/IT-21");
    l.push_back("5863/M");
    l.push_back("6073/M");
    l.push_back("341/IT-22");
    l.push_back("6061/M");
    l.push_back("6155/M");
    l.push_back("6116/M");
    l.push_back("406/IT-23");
    l.push_back("323/IT-22");
    l.push_back("131/IT-19");

    HashTablica<string, int, MojHasher> h;

    int broj = 0;

    for(auto index : l) {
        h.dodaj(index, ++broj);
    }

    h.test();
}
