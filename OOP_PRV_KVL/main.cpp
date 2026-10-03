#include <iostream>
#include<cstring>
using namespace std;

class ztring {
private:
    char *content;

public:
    ztring (char *cptr = "") {
        this->content = new char [strlen(cptr)+1];
        strcpy(this->content, cptr);
    }

    ztring (const ztring &other) {
        this->content = new char[strlen(other.content) +1];
        strcpy(this->content, other.content);
    }

~ztring() {
        delete [] content;
    }
    ztring & operator= (const ztring &s ) {
        if (this==&s) {
            delete [] content;
            this->content = new char [strlen(s.content) + 1];
            strcpy(this->content, s.content);
        }
    }
};



int main() {

}
