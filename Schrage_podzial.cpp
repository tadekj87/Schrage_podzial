// Schrage_podzial.cpp Ten plik zawiera funkcję „main”.W nim rozpoczyna się i kończy wykonywanie programu.
// Grupa: WT 13: Junak Tadeusz, Karol Kędzia

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct strukturaZadania
{
    int r,p,q; // termin dostępności r (punkt), czas wykonania p (okres), czas dostarczenia q

	strukturaZadania(int a, int b, int c) 
	{
		r = a; p = b; q = c;
	}
};

struct kolejnoscR
{
	bool operator ()( const strukturaZadania& a, const strukturaZadania& b ) const
	{
		return a.r > b.r;
	}
};

struct kolejnoscQ
{
	bool operator ()( const strukturaZadania& a, const strukturaZadania& b ) const
	{
		return a.q < b.q;
	}
};

// zbiory G i N to kolejki priorytetowe

priority_queue<strukturaZadania, vector<strukturaZadania>, kolejnoscQ> zbiorG; // zbiór G jest porządkowany rosnąco po większej wartości "q"
priority_queue<strukturaZadania, vector<strukturaZadania>, kolejnoscR> zbiorN; // zbiór N jest porządkowany rosnąco po mniejszej wartości "r"

int main()
{
    fstream plik;
	plik.open("SCHRAGE3.dat",ios::in);
    int rozmiar=0;
    int r,p,q;
    int t, k, Cmax, duzaWartosc;

    duzaWartosc = 9999999999999999999;

	t = k = Cmax = 0;

    plik >> rozmiar;
 
	cout << "Kolejnosc: r p q" << endl;

	strukturaZadania l(0, 0, 0), e(0,0,duzaWartosc); // zadanie pomocnicze "e" i "l"

    for (int i=0; i<rozmiar; i++)
	{
        plik >> r;
        plik >> p;
        plik >> q;
        cout << r << "\t" << p << "\t" << q << endl;
        strukturaZadania zadanie(r,p,q); // każde zadanie ląduje 
        zbiorN.push(zadanie); // w zbiorze N
    }

	// algorytm

    while(zbiorG.empty()==false || zbiorN.empty()==false)
	{
        while (zbiorN.empty() == false && zbiorN.top().r <= t)
        {
            e = zbiorN.top();
            zbiorG.push(e); // zadanie "e" dodawane do zbioru G z "czubka" zbioru N
            zbiorN.pop(); // ściągnięcie "e" z czubka N

            if (e.q > l.q)
            {
                l.p = t - e.r;
                t = e.r;

                if (l.p > 0)
                {
                    zbiorG.push(l);
                }
            }
        }

        if (zbiorG.empty() == true)
		{
                t = zbiorN.top().r; // "t" jest równe najmniejszej wartości zbioru N
                continue;	// pomija się dalsze kroki i przechodzi do kolejnej pętli
		}

        e = zbiorG.top(); // "e" jest ściągane z czubka "G"
        zbiorG.pop();

        l = e;
        t=t+e.p;
  
		if (Cmax < t + e.q)
			Cmax = t + e.q;
    }

	// wyswietlenie rozmiaru i Cmax

	cout << endl << "Rozmiar to: "<< rozmiar << endl;
    cout << "Cmax to: " << Cmax << endl;

	system("PAUSE");

	return 0;
}


