#include <iostream>
#include <vector>
#include <string>
#include <compare>
#include <stdexcept>

using namespace std;

class Zahtjev {
private:
    string imeZahtjeva;
    int prioritet;

public:
    Zahtjev() {}

    Zahtjev(string i, int p) : imeZahtjeva(i), prioritet(p) {}

    friend ostream& operator <<(ostream& ispis, const Zahtjev& z) {
        ispis << z.imeZahtjeva << "(" << z.prioritet << ")";
        return ispis;
    }

    strong_ordering operator <=>(const Zahtjev& z) {
        if(prioritet < z.prioritet) return strong_ordering::less;
        if(prioritet == z.prioritet) return strong_ordering::equal;
        return strong_ordering::greater;
    }

    void povecajPrioritet(int vrijednost) {
        prioritet += vrijednost;
    }
};

template<typename T>
class Heap {
private:
    T* niz;
    size_t alociranaVelicina;
    size_t velicina;

    inline int roditelj(int dijete) { return (dijete-1) / 2; }
    inline int dijete(int roditelj) { return 2*roditelj+1; }

    void propagirajNavise(int p) {
        while(p > 0) {
            int r = roditelj(p);

            if(niz[r] < niz[p]) break;

            swap(niz[r], niz[p]);
            p = r;
        }
    }

    void propagirajNanize(int p) {
        while(true) {
            int d = dijete(p);

            if(d >= velicina) break;

            if(d + 1 < velicina && niz[d] > niz[d + 1]) d++;

            if(niz[d] > niz[p]) break;

            swap(niz[d], niz[p]);
            p = d;
        }
    }
public:
    Heap() {
        alociranaVelicina = 7;
        velicina = 0;
        niz = new T[alociranaVelicina];
    }

    void dodajBezOcuvanjaSvojstvaHeapa(const T& el) {
        if(velicina == alociranaVelicina) {
            alociranaVelicina *= 2;
            T* noviNiz = new T[alociranaVelicina];
            for(int i = 0; i < velicina; i++) noviNiz[i] = niz[i];
            delete[] niz;
            niz = noviNiz;
        }

        niz[velicina++] = el;
    }

    void dodaj(const T& el) {
        dodajBezOcuvanjaSvojstvaHeapa(el);
        propagirajNavise(velicina-1);
    }

    T obrisiMin() {
        if(velicina == 0) throw runtime_error("Prazan je heap");

        auto M = niz[0];

        niz[0] = niz[--velicina];
        propagirajNanize(0);

        return M;
    }

    friend ostream& operator <<(ostream& ispis, const Heap& h) {
        int elementNaNivou = 0;
        int brojElemenataNaNivou = 1;

        for(int i = 0; i < h.velicina; i++) {
            ispis << h.niz[i];
            elementNaNivou++;

            if(elementNaNivou == brojElemenataNaNivou) {
                brojElemenataNaNivou *=2;
                elementNaNivou = 0;
                ispis << endl;
            } else {
                ispis << " ";
            }
        }
        return ispis;
    }

    void heapify() {
        for(int i = (velicina-1)/2; i >= 0; i--) propagirajNanize(i);
    }

    void povecajPrioritet(int p, int vr) {
        niz[p].povecajPrioritet(vr);

        if(vr > 0) {
            propagirajNanize(p);
        } else {
            propagirajNavise(p);
        }
    }
};

void testHeap() {
    Heap<Zahtjev> h;
    h.dodaj(Zahtjev("Aleksandar", 10));
    h.dodaj(Zahtjev("A", 20));
    h.dodaj(Zahtjev("B", 5));
    h.dodaj(Zahtjev("C", 8));
    h.dodaj(Zahtjev("D", 16));
    h.dodaj(Zahtjev("E", 33));
    h.dodaj(Zahtjev("F", 2));
    h.dodaj(Zahtjev("G", 15));
    h.dodaj(Zahtjev("H", 1));

    cout << h;
}
