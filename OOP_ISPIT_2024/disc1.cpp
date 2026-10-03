//
// Created by aleks on 6/16/2025.
//
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;
class Date{
private:
 int d, m, y;
public:
 Date(){}
 Date(int dd, int mm, int yy){
 d = dd;
 m = mm;
 y = mm;
 }
 ~Date(){}
 bool compare(Date &date){
 return y == date.y && m == date.m && d == date.d;

 }
 friend ostream &operator<<(ostream &out, Date & f){
 out<< f.d << "/" << f.m << "/" << f.y;
 return out;
 }
 friend istream &operator>>(istream &in, Date & f){
 in >> f.d;
 in >> f.m;
 in >> f.y;
 return in;
 }
 void read(ifstream& in){
 in >> d >> m >> y;
 in.ignore();
 }


};


class Call{
private:
 string dialedNumber;
 int duration;
 Date date;
public:
 Call(){}
 Call(const string & num, int dur, Date d){
 dialedNumber = num;
 duration = dur;
 date = d;
 }
 ~Call(){}

 void read(ifstream& in)
 {
 date.read(in);
 getline(in, dialedNumber);
 in >> duration;
 in.ignore();
 }
 friend ostream &operator<<(ostream &out, Call & f){
 out<<"Dialed number: "<<f.dialedNumber<<f.duration<<" sec, "<< f.date << endl;
 return out;
 }
 Date getDate(){
 return date;
 }
};


class Log{
private:
 Call *calls;
 int n;
public:
 Log(){
 calls = nullptr;
 n = 0;
 }
 Log(Call *c, int num){
 n = num;
 calls = new Call[n];
 for(int i = 0; i < n; i++){
 calls[i] = c[i];
 }
 }
 Log(const Log &l){
 n = l.n;
 calls = new Call[n];
 for(int i = 0; i < n; i++){
 calls[i] = l.calls[i];
 }
 }
 ~Log(){
 delete [] calls;
 }
 void read(ifstream& in){
 in>>n;
 in.ignore();
 calls = new Call[n];
 for(int i = 0; i < n; i++)
 {
 calls[i].read(in);
 }
 }
 friend ostream &operator<<(ostream &out, Log & f){
 for(int i = 0; i < f.n; i++)
 out<< f.calls[i];
 return out;
 }
 Log daily(Date d){
 int c = 0;
 Call *tmp = new Call[n];
 for(int i = 0; i < n; i++){
 if(calls[i].getDate().compare(d)){
 tmp[c++] = calls[i];
 }
 }
 Log log(tmp, c);
 return log;
 }
};
void wtf() {
 ofstream fout("prva.txt");
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
 //TODO your code here
 ifstream fin("prva.txt");
 ofstream fout("vtora.txt");
 ofstream fout2("treta.txt");
 Log log;
 log.read(fin);
 fin.close();
 fout<<log;
 fout.close();
 //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
 Date d;
 cin >> d;
 //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT
 //TODO Save the results in the files vtora.txt and treta.txt
 Log log1 = log.daily(d);
 fout2 << log1;
 fout2.close();
 //DO NOT MODIFY THE CODE BELLOW
 cout << "All the data for the log:" << endl;
 rff("vtora.txt");
 cout << "Calls on date " << d << endl;
 rff("treta.txt");
 return 0;
}