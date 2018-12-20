#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

bool czydopliku = false;
ofstream wynik;

string stringi[10][500];
std::stringstream ss;

void ccout(string str){
    if(czydopliku) wynik << str;
    cout << str;
}

void wypisz(int **b, int *y, int p, int n, int lvl = 0){
    int help = lvl;
    int c = 0;
    int d = 0;
    while(help--) ccout("\t");
    help = lvl;
    ccout("   ");
    for (int i = 1; i <= n; i++){
        ss.str( std::string() ); ss.clear();
        ss << "x" << i;
        ccout(ss.str());
    }
    ccout("       y\n");
    for (int i = 0; i < p; i++){
        while(help--) ccout("\t");
        help = lvl;
        if(i==0) ccout("X=| "); else ccout("  | ");
        for (int j = 0; j < n; j++){
            if(i%2!=0){
                ss.str( std::string() ); ss.clear();
                ss << b[c][j] << " ";
                ccout(ss.str());
            }else{
                ss.str( std::string() ); ss.clear();
                ss << b[p-1-d][j] << " ";
                ccout(ss.str());
            }
        }
        if(i==0) ccout("| Y=| "); else ccout("|   | ");
        if(i%2!=0){
            ss.str( std::string() ); ss.clear();
            ss << y[c] << " |" << endl;
            ccout(ss.str());
        }else{
            ss.str( std::string() ); ss.clear();
            ss << y[p-1-d] << " |" << endl;
            ccout(ss.str());
        }

        if(i%2!=0){
            c++;
        }
        else{
            d++;
        }
    }
}

int bintodec(string bin){
    int dec = 0;
    for(int i = 0; i<bin.length(); i++){
        if(bin[bin.length()-1-i]=='1'){
            dec += pow(2,i);
        }
    }
    return dec;
}

void dekomponuj(int **b, int *y, int p, int n, int lvl, string wejscie = ""){
    int x1 = 0;
    int x2 = 0;
    int ktstr = -1;
    int decc = 0;
    while(stringi[lvl][++ktstr]!=".");
    if(wejscie!="") decc = bintodec(wejscie);

    int help = lvl;
    if(n-2==0){
        for(int i = 0; i < p; i++){
            //while(help--) cout << "\t"; help = lvl;
            //cout << "MUX" << lvl << "(" << b[i][0] << b[i][1] << ")=" << y[i] << endl;
            ss.str( std::string() ); ss.clear();
            ss << decc << "(" << b[i][0] << b[i][1] << ")=" << y[i] << "\0";
            stringi[lvl][ktstr++] = ss.str();
        }

        return;
    }

    do{
        int i = 0;
        //int bc[p][n-2];
        int** bc = new int*[p];
        for(int i = 0; i < p; i++)
        bc[i] = new int[20];

        //int yc[p];
        int *yc = new int[p];
        for (int k = 0; k < p; k++){
            if(b[k][0]==x1 && b[k][1]==x2){
                for (int j = 2; j < n; j++){
                    bc[i][j-2] = b[k][j];
                    yc[i] = y[k];
                }
                i++;
            }
        }

        if(i==0){
            x2++;
            if( x2==2 ){
                x1++;
                x2=0;
            }
            if(x1==2) break; else continue;
        }
        //cout << endl;
        /*while(help--) cout << "\t"; help = lvl;
        cout << "Dla x1x2=" << x1 << x2 << endl;
        wypisz(bc,yc,i,n-2,lvl);
        cout << endl;*/

        int cyfra = yc[0];
        bool czyYtakiesame = true;
        bool czydekomponowacdalej = true;
        for (int j = 1; j < i; j++){
            if(yc[j]!=cyfra) czyYtakiesame = false;
        }
        if(czyYtakiesame || i==1){
            //while(help--) cout << "\t"; help = lvl;
            //cout << "MUX" << lvl << "(" << x1 << x2 << ")=" << cyfra << endl;
            ss.str( std::string() ); ss.clear();
            ss << decc << "(" << x1 << x2 << ")=" << cyfra << "\0";
            stringi[lvl][ktstr++] = ss.str();
            czydekomponowacdalej=false;
        }else{
            bool czyXtakiesame = true;
            bool czyXzaprzeczenie = true;
            int np = i;
            for (int i = 0; i < n-2; i++){
                czyXtakiesame = true;
                for (int j = 0; j < np; j++){
                    if(bc[j][i]!=yc[j]) czyXtakiesame = false;
                }
                if(czyXtakiesame){
                    //while(help--) cout << "\t"; help = lvl;
                    //cout << "MUX" << lvl << "(" << x1 << x2 << ")=x" << i+1+2*(lvl+1) << endl;
                    ss.str( std::string() ); ss.clear();
                    ss << decc << "(" << x1 << x2 << ")=x" << i+1+2*(lvl+1) << "\0";
                    stringi[lvl][ktstr++] = ss.str();
                    czydekomponowacdalej = false;
                    break;
                }
                czyXzaprzeczenie = true;
                for (int j = 0; j < np; j++){
                    if(bc[j][i]==yc[j]) czyXzaprzeczenie = false;
                }
                if(czyXzaprzeczenie){
                    //while(help--) cout << "\t"; help = lvl;
                    //cout << "MUX" << lvl << "(" << x1 << x2 << ")=x" << i+1+2*(lvl+1) << endl;
                    ss.str( std::string() ); ss.clear();
                    ss << decc << "(" << x1 << x2 << ")=~x" << i+1+2*(lvl+1) << "\0";
                    stringi[lvl][ktstr++] = ss.str();
                    czydekomponowacdalej = false;
                    break;
                }
            }
        }

        if(czydekomponowacdalej){
            //while(help--) cout << "\t"; help = lvl;
            //cout << "MUX" << lvl << "(" << x1 << x2 << ")=MUX" << lvl+1 << ": (Mozliwa dalsza dekompozycja)" << endl;
            ss.str( std::string() ); ss.clear();
            ss << wejscie << x1 << x2;
            string wejscie2 = ss.str();
            ss.str( std::string() ); ss.clear();
            int decc2 = bintodec(wejscie2);
            ss << decc << "(" << x1 << x2 << ")=MUX" << decc2 << "\0";
            stringi[lvl][ktstr++] = ss.str();
            dekomponuj(bc,yc,i,n-2,lvl+1,wejscie2);
        }

        delete [] yc;
        for ( int i(0); i < p; ++i )
        delete [] bc[i];
        delete [] bc;

        x2++;
        if( x2==2 ){
            x1++;
            x2=0;
        }
    }while(x1!=2);
}

int main()
{
    cout << "Program dokonuje syntezy ukladu kombinacyjnego UK(X,Y) oraz realizuje podana funkcje logiczna przy uzyciu multiplekserow MUX4:1." << endl;
    wynik.open("wynik.txt");
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 500; j++){
            stringi[i][j] = ".";
        }
    }

    srand( time( NULL ) );
    int n = 0;
    int p = 0;
    int maxx = 0;
    bool czyZpliku = false;
    while(1){
        cout << "Gdzie wypisac wyniki? 1 - na ekran 2 - do pliku" << endl;
        cin >> n;
        if(n==2) czydopliku = true;
        n = 0;

        cout << "Skad pobrac dane? 1-wygeneruj losowe 2-wczytaj z pliku" << endl;
        cin >> n;
        if(n==2){
            czyZpliku = true;
            ifstream dane;
            dane.open("dane.txt");
            char znak = '0';
            int ktwiersz = 0;
            int ktkolumna = 0;
            n=0;
            while(dane >> znak){
                if(znak == ':'){
                    if(n==0) n = ktkolumna;
                    ktkolumna = 0;
                    continue;
                }else if(znak == ';'){
                    ktwiersz++;
                    continue;
                }else{
                    ktkolumna++;
                }
            }
            p = ktwiersz;
            ktwiersz = 0;
        }else{
            cout << "Liczba wyjsc m=|Y|=1" << endl;
            cout << "Podaj liczbe wejsc n=|X|=";
            cin >> n;
            if(n<1 || n>11){
                cout << "Podano bledne dane. Musisz wybrac z przedzialu (1 <= n <= 10)" << endl;
                continue;
            }
            maxx = pow(2,n);
            cout << "Podaj liczbe stanow okreslonych (1 <= p <= " << maxx << ") p=";
            cin >> p;
            if(p<1 || p>maxx || p>600){
                if(p>600) cout << "Przykro mi, ale program nie obsluguje p wiekszego niz 600 z powodu potrzebnych zbyt duzych tablic" << endl;
                cout << "Podano bledne dane. Sprobuj jeszcze raz." << endl;
                continue;
            }
            cout << endl;
        }
        break;
    }

    int a[n];
    int** b = new int*[p];
        for(int i = 0; i < p; i++)
        b[i] = new int[20];
    //int y[p];
    int *y = new int[p];

    if(!czyZpliku){
        //pseudogenerowanie UK vv
        int cokt = maxx/p;
        //cout << "cokt: " << cokt << endl;
        int kt = cokt;
        for (int i = 0; i < p; i++){
            y[i] = ( std::rand() % 2 );
        }
        for (int i = 0; i < n; i++){
            a[i] = 0;
        }
        for (int i = 0; i < p; i++){
            for (int j = 0; j < n; j++){
                b[i][j] = 0;
            }
        }
        a[n-1]--;
        for(int j = 1, ktp = 0; ktp!=p ; j++){
            a[n-1]++;
            for(int i = 1; n-i-1>=0 ; ){
                if( a[n-i] > 1 ){
                    a[n-i-1]++;
                    a[n-i] = 0;
                    i++;
                } else break;
            }
            if(kt == j-(maxx-p*cokt)/2){
                kt+=cokt;
                for (int k = 0; k < n; k++){
                    b[ktp][k] = a[k];
                }
                ktp++;
            }
        }
        //cout << "p = " << p << endl;
        //cout << "0%2" << 0%2 << endl;

        //pseudo generowanie UK ^^

        cout << "Wygenerowalem nastepujacy UK(X,Y): " << endl;
        wypisz(b,y,p,n);
    }else{
        ifstream dane;
        dane.open("dane.txt");
        char znak = '0';
        bool czyX = true;
        int ktwiersz = 0;
        int ktkolumna = 0;
        while(dane >> znak){
            //cout << znak << " ";
            //if(znak == ';') cout << endl;

            if(znak == ':'){
                czyX = false;
                ktkolumna = 0;
                continue;
            }else if(znak == ';'){
                czyX = true;
                ktwiersz++;
                continue;
            }
            if(czyX){
                if(znak == '1'){
                    b[ktwiersz][ktkolumna] = 1;
                    //cout << "b[" << ktwiersz << "][" << ktkolumna << "] = 1;" << endl;
                }
                else{
                    b[ktwiersz][ktkolumna] = 0;
                    //cout << "b[" << ktwiersz << "][" << ktkolumna << "] = 0;" << endl;
                }
                ktkolumna++;
            }else{
                if(znak == '1')
                    y[ktwiersz] = 1;
                else
                    y[ktwiersz] = 0;
            }
        }
        //cout << "ktwiersz: " << ktwiersz << endl;
        //cout << "n: " << n << endl;
        ktwiersz = 0;
        cout << "Wczytalem z pliku nastepujacy UK(X,Y): " << endl;
        wypisz(b,y,p,n);
    }

    dekomponuj(b, y, p , n, 0);

    cout << endl;
    if(!czydopliku) cout << "Rozpoczynam synteze UK(X,Y) jak wyzej na MUX 4:1 (k=2). Wynik:" << endl;
    else{
        cout << "Wynik znajdziesz w pliku wynik.txt oraz ponizej:" << endl;
        ccout("Rozpoczynam synteze UK(X,Y) jak wyzej na MUX 4:1 (k=2). Wynik:\n");
    }
    ccout("Dekompozycja UK na MUX: \n");
    ccout("--------------\n");
    for(int i = 0; i < 10; i++){
        if(stringi[i][0]==".") break;
        ss.str( std::string() ); ss.clear();
        ss << "L=" << i << endl;
        ccout(ss.str());
        ss.str( std::string() ); ss.clear();
        ss << "A=x" << i*2+1 << "x" << i*2+2 << endl;
        ccout(ss.str());
        for (int j = 0; j < 100; j++){
            if(stringi[i][j]==".") break; else{
                ss.str( std::string() ); ss.clear();
                ss << "MUX" << stringi[i][j] << endl;
                ccout(ss.str());
            }
        }
        ccout("--------------\n");
    }
    ccout("\n");
    ccout("Objasnienie formatu: MUXi oznacza MUX poziomu L, ktorego wyjscie podane jest na wejscie o numerze dziesietnym MUX poziomu L-1, 0 <= i <= 2^(k*L)-1.\n");
    ccout("Symbol ~ oznacza zaprzeczenie (negacje).\n");
    wynik.close();
    cin >> n;

    return 0;
}
