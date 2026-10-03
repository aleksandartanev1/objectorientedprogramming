/*Од стандарден влез се читаат податоци за непознат број студенти (не повеќе од 100).
 *Податоците се внесуваат така што во секој ред се состои од:

името
презимето
бројот на индекс (формат xxyzzzz)
четири броја (поени од секоја задача)
со произволен број празни места или табулатори меѓу нив.

Да се напише програма која ќе испечати список на студенти, каде во секој ред ќе има: презиме, име, број на индекс,
вкупен број на бодови сортиран според бројот на бодови. При тоа имињата и презимињата да се напишат со голема почетна буква.

*/

#include<iostream>
using namespace std;


struct studenti {

 char ime[50];
 char prezime[50];
 int indeks;
 int total;

 void print () {
  cout<<ime<<endl;
  cout<<prezime<<endl;
  cout<<indeks<<endl;
  cout<<total<<endl;
 }
};

void normalize (char *name, bool alluppercase = false) {
 *name = toupper(*name);
 ++name;
 while(*name) {
  if(alluppercase) {
   *name = toupper(*name);
  } else {
   *name = tolower(*name);
  }
  ++name;
 }
}
void read(studenti &s) {
 cin >> s.ime;
 cin >> s.prezime;
 normalize(s.ime);
 normalize(s.prezime);
 cin >> s.indeks;
 int a, b, c, d;
 cin >> a >> b >> c >> d;
 s.total = a + b + c + d;
}

void sort(studenti s[], int n) {
 for(int i = 0; i < n; ++i) {
  for(int j = 0; j < n - 1; ++j) {
   if(s[j].total < s[j + 1].total) {
    studenti tmp = s[j];
    s[j] = s[j + 1];
    s[j + 1] = tmp;
   }
  }
 }
}

int main () {
 studenti s[100];
 int n;
 cin >> n;
 for(int i = 0; i < n; ++i) {
  read(s[i]);
 }
 sort(s, n);
 cout << "======== ORDERED ========" << endl;
 //read(s);
 for(int i = 0; i < n; ++i) {
  s[i].print();
  //print(s[i]);
 }

 return 0;
}
