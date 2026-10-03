#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

 class Song {
     string title;
     string author;
     string performer;
     int length;
 public:
     Song(string title = " ", string author = " ", string performer = " ", int length = 0) {
         this->title = title;
         this->author = author;
         this->performer = performer;
         this->length = length;
     }

     friend istream& operator>> (istream& in, Song& song) {
         getline(in, song.title);
         getline(in, song.author);
         getline(in, song.performer);
         in>>song.length;
         in.ignore();
         return in;
     }

     void print(ofstream& out) {
         //Song title: Usni na usni, Author: Grigor Koprov, Interpreted by: Toshe Proeski, 215 sek.
         out<<"Song title: "<<title<<", Author: "<<author<<", Interpreted by: "<<performer<<", "<<length<<" sek."<<endl;
     }

     bool issame (Song& o) {
         return author == o.author && title == o.title && o.performer == performer;
     }

     bool sameauthor (string a) {
         return author == a;
     }

 };

class Festival {
    string festivalname;
    string city;
    string date;
    Song* tracklist;
    int n;
public:
    Festival(string festivalname = " ", string city = " ", string date = " ", Song* tracklist = nullptr, int n = 0) {
        this->festivalname = festivalname;
        this->city = city;
        this->date = date;
        this->n = n;
        this->tracklist = new Song[n];
        for(int i = 0; i < n; i++) {
            this->tracklist[i] = tracklist[i];
        }
    }

~Festival() {
        delete[]this->tracklist;
    }

    Festival& operator=(const Festival& other) {
        if(this != &other) {
            delete[]this->tracklist;
            this->festivalname = other.festivalname;
            this->city = other.city;
            this->date = other.date;
            this->n = other.n;
            this->tracklist = new Song[n];
            for(int i = 0; i < n; i++) {
                this->tracklist[i] = other.tracklist[i];
            }
        }
        return *this;
    }

    Festival(const Festival& other) {
        this->festivalname = other.festivalname;
        this->city = other.city;
        this->date = other.date;
        this->n = other.n;
        this->tracklist = new Song[n];
        for(int i = 0; i < n; i++) {
            this->tracklist[i] = other.tracklist[i];
        }
    }

    Festival& operator-= (Song& s) {
        if (n == 0) {
            cout<<"Trying to delete from an empty list!"<<endl;
            return *this;
        }
        for(int i = 0; i < n; i++) {
            if(tracklist[i].issame(s)) {
                for(int j = i; j < n - 1; j++) {
                    tracklist[j] = tracklist[j + 1];
                }
                i--;
                n--;
            }
        }
        return *this;
    }

    void print(ofstream& out) {
        out<<"Festival: "<<festivalname<<" - "<<city<<", "<<date<<endl;
        for(int i = 0; i < n; i++) {
            tracklist[i].print(out);
        }
    }

    friend istream& operator>>(istream& in, Festival& o) {
        getline(in, o.festivalname);
        getline(in, o.city);
        getline(in, o.date);
        in>>o.n;
        in.ignore();
        o.tracklist = new Song[o.n];

        for(int i = 0; i < o.n; i++) {
            in>>o.tracklist[i];
        }
        return in;
    }

    Festival notFromAuthor(string author) {

        for(int i = 0; i < n; i++) {
            if(tracklist[i].sameauthor(author)) {
                for(int j = i; j < n-1; j++) {
                    tracklist[j] = tracklist[j + 1];
                }
                i--;
                n--;
            }
        }
        return *this;
    }


};


void wtf() {
    ofstream fout("vlezna.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();

    Festival festival;
    //TODO your code here
    //TODO Read the data from the file and store them in `festival`
    ifstream fin("vlezna.txt");
    fin>>festival;
    fin.close();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    string author;
    getline(cin, author);
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files izlezna1.txt and izlezna2.txt after this line

    ofstream fout("izlezna1.txt");
    festival.print(fout);
    fout.close();


    ofstream fout2("izlezna2.txt");
    Song s;
    festival-=s;
    festival.notFromAuthor(author);
    festival.print(fout2);
    fout2.close();
    //DO NOT MODIFY THE CODE BELLOW

    cout << "All the data for the festival:" << endl;
    rff("izlezna1.txt");
    cout << "Songs NOT from the author " << author << ": " << endl;
    rff("izlezna2.txt");


    return 0;
}