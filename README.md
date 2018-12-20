# SyntezaUkladowCyfrowychNaMUX

**Temat:** Algorytm realizujący podaną funkcję logiczną przy użyciu multiplekserów MUX 4:1

**Multiplekser**  (w skrócie MUX) – [układ kombinacyjny](https://pl.wikipedia.org/wiki/Uk%C5%82ad_kombinacyjny), najczęściej [cyfrowy](https://pl.wikipedia.org/wiki/Uk%C5%82ad_cyfrowy), służący do wyboru jednego z kilku dostępnych sygnałów wejściowych i przekazania go na wyjście. Posiada k wejść informacyjnych, n wejść adresowych i jedno wyjście y.

**Opis programu:** Program wczytuje dane z wcześniej przygotowanego pliku lub generuje je na podstawie informacji podanych przez użytkownika. W tym drugim przypadku program prosi użytkownika o podanie liczby wejść (n=|X|) oraz liczbę stanów określonych (1 \&lt;= p \&lt;= 2^n). Układ jest opisany za pomocą macierzy binarnych X i Y (z niepełną określonością). Wczytany lub wygenerowany układ zostaje wypisany na ekran (lub do pliku), po czym program rozpoczyna syntezę UK(X,Y) na MUX 4:1 (k=2). Zostaje wybranych k zmiennych adresowych dla 2^L UK(X,Y) poziomu L. Następnie ustalane są kolejno wartości wszystkich kombinacji wartości k zmiennych adresowych, dla których zdekomponowany zostaje każdy UK(X,Y) poziomu L na 2^(L+1) UK(X,Y) poziomu L+1. Program sprawdza czy dany UK poziomu L+1 umożliwia bezpośrednie wyznaczenie kombinacyjnej zależności Y z X w postaci wartości stałej (0 lub 1) lub pojedynczej zmiennej prostej lub zanegowanej - jeżeli tak, to program przypisuje tę wartość/zmienną na odpowiednie wejście MUX, natomiast w przeciwnym wypadku, gdy jest możliwa przynajmniej jedna dalsza dekompozycja, kontynuuje ją w sposób rekurencyjny. Na koniec program wyprowadza rozwiązanie do pliku i/lub na ekran.

**(Pseudokod na odwrocie kartki)**

**Napotkane problemy: 1.** Reprezentacja macierzowa układu kombinacyjnego zapisana, za pomocą tablic w języku programowania c++ **2.** Określenie i wygenerowanie podanej ilości wejść wraz z różnymi stanami określonymi. **3.** Tworzenie podmacierzy (dla UK wyższego poziomu) oraz przekazywanie ich za pomocą funkcji rekurencyjnych **4.** Wypisanie na ekran i do pliku wyników dekompozycji na każdym poziomie wraz z odpowiednim oznaczeniem multiplekserów.

**Przykładowy wynik programu:**

Program dokonuje syntezy układu kombinacyjnego UK(X,Y) oraz realizuje podaną funkcję logiczną przy użyciu multiplekserów MUX4:1.

Gdzie wypisać wyniki? 1 - na ekran 2 - do pliku **1**

**(Przykład 1)** Skąd pobrać dane? 1-wygeneruj losowe 2-wczytaj z pliku **2**

Wczytałem z pliku następujący UK(X,Y):

   x1x2x3x4x5        y

X=| 1 0 1 0 1 |  Y=| 1 |

  | 1 1 0 0 0 |    | 1 |

  | 0 1 1 1 0 |    | 0 |

  | 1 1 1 0 1 |    | 1 |

  | 0 0 1 1 1 |    | 1 |

  | 1 0 1 1 0 |    | 0 |

  | 0 1 0 0 1 |    | 0 |

  | 1 1 1 1 1 |    | 1 |

  | 1 1 0 1 1 |    | 0 |

Objaśnienie formatu: MUXi oznacza MUX poziomu L, którego wyjście podane jest na wejście o numerze dziesiętnym MUX poziomu L-1, 0 \&lt;= i \&lt;= 2^(k\*L)-1.

Symbol ~ oznacza zaprzeczenie (negacje).

Rozpoczynam syntezę UK(X,Y) jak wyżej na MUX 4:1 (k=2).

Wynik: (Przykład 1)

Dekompozycja UK na MUX:

--------------

L=0

A=x1x2

MUX0(00)=1

MUX0(01)=0

MUX0(10)=~x4

MUX0(11)=MUX3

--------------

L=1

A=x3x4

MUX3(00)=1

MUX3(01)=0

MUX3(10)=1

MUX3(11)=1

--------------

 ![](data:image/*;base64,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)

**(Przykład 2)**Skąd pobrać dane? 1-wygeneruj losowe 2-wczytaj z pliku **1**

Podaj liczbę wejść n=|X|= **6**

Podaj liczbę stanów określonych (1 \&lt;= p \&lt;= 64) p= **12**

Wygenerowałem następujący UK(X,Y) **--------------\&gt;**

Rozpoczynam syntezę UK(X,Y) jak wyżej na MUX 4:1 (k=2)  Wynik:

Dekompozycja UK na MUX:

 ![](data:image/*;base64,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)

 ![](data:image/*;base64,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)

**Pseudokod:**

**Wypisz na ekran:**&quot;Program Program dokonuje syntezy układu kombinacyjnego UK(X,Y) oraz realizuje podaną funkcję logiczną przy użyciu multiplekserów MUX4:1. \n&quot;

**Wypisz na ekran:**&quot;Skąd pobrać dane? 1-wygeneruj losowe 2-wczytaj z pliku \n&quot;

**Utwórz dwuwymiarową tablicę**  **X**  **oraz jednowymiarową tablicę**  **Y** **(macierze)**

**Jeżeli użytkownik wpisał**  **1**** , **** wczytaj dane z pliku - w przeciwnym wypadku:**

        **Wypisz na ekran:**&quot;Liczba wyjść m=|Y|=1 Podaj liczbę wejść n=|X|=&quot;

        **Utwórz zmienną**  **n**  **i przypisz do niej wartość podaną przez użytkownika.**

**        Wypisz na ekran:**&quot;Podaj liczbę stanów określonych (1 \&lt;= p \&lt;= &quot; **\&lt;\&lt; 2^**** n **** \&lt;\&lt;**&quot;) p=&quot;

        **Utwórz zmienną**  **p**  **i przypisz do niej wartość podaną przez użytkownika.**

**        Wygeneruj wartości wejścia (stany określone) oraz wyjścia układu kombinacyjnego UK(X,Y)**

**Wczytane lub wygenerowane dane zapisz odpowiednio w tablicach/macierzach**  **X**  **i**  **Y**

**Zdefiniuj zmienną**  **L**  **oraz nadaj jej wartość początkową**  **0** (int L = 0;)

**Wybierz 2 zmienne (k=2) adresowe dla 2^****L **** UK( ****X**** , ****Y**** ) poziomu **** L ****.**

**Wykonaj funkcję dekomponuj(****X ****,**** Y,L****)**

//...

**Funkcja**  **dekomponuj**** (wejścia, wyjścia, poziom):**

**        Wykonuj kolejno dla wszystkich kombinacji wartości 2 zmiennych adresowych:**

**                Zdekomponuj dany UK(****X ****,**** Y****) poziomu**  **L** **na UK(****X2 ****,**** Y2****) poziomu**  **L+1**

**               ** **Sprawdź czy UK(****X2 ****,**** Y2****) poziomu**  **L+1**  **umożliwia bezpośrednio wyznaczenie kombinacyjnej                         zależności**  **Y2**  **z**  **X2** **w postaci wartości stałej (0 lub 1) lub pojedynczej zmiennej prostej lub                         zanegowanej z macierzy**  **X2****.**

**                        Jeżeli tak, to przypisz tę wartość/zmienną na odpowiednim wejściu MUX poziomu**  **L****.**

**                W przeciwnym wypadku, jeżeli dalsza dekompozycja jest możliwa, to wykonaj rekurencyjnie                         funkcję dekomponuj(****X2 ****,**** Y2,L+1****)**

//...dalszy ciąg głównej funkcji programu:

**Wyprowadź na ekran wyjście w przykładowym formacie:**

**       ** MUXi oznacza MUX poziomu L, którego wyjście podane jest na wejście o numerze dziesiętnym MUX poziomu L-1, 0 \&lt;= i \&lt;= 2^(2\*L)-1. Symbol ~ oznacza zaprzeczenie (negację).

**               **

**Wnioski:** Na podstawie analizy wyników zwracanych przez program i obliczeń wykonanych poza nim, można stwierdzić, iż program działa i prawidłowo generuje układ kombinacyjny UK(X,Y) dla podanych przez użytkownika danych, a następnie dokonuje jego syntezy na MUX 4:1 (k=2) korzystając z uogólnionego Tw. Shannona o dekompozycji logicznej. Czas generacji wydłuża się wraz ze wzrostem podanych przez użytkownika wartości - niska jednak złożoność sprzętowa wynika z niepełnej określoności UK.

**Literatura:**

- pl.wikipedia.org/wiki/Multiplekser
- Kokosiński Zbigniew : Synteza układów kombinacyjnych na multiplekserach i demultiplekserach, ICACIT 2015, Kiev, Ukraine
- Łuba T. : Synteza układów logicznych, Oficyna Wydawnicza PW, Warszawa 2005.
