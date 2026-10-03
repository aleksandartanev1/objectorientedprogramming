#include<iostream>
#include<cstring>

using namespace std;

class ExistingGame{
private:
  char msg[256];

public:
  ExistingGame(char msg_txt[]){
    strncpy(this->msg, msg_txt, 255);
    this->msg[255] = '\0';
  }

  void message(){
    std::cout<<this->msg<<std::endl;
  }
};

class Game {
protected:
  char name[101];
  float price;
  bool boughtondiscount;
public:
  Game(char *name = (char*)" ", float price = 0, bool boughtondiscount = false) {
    strcpy(this->name, name);
    this->price = price;
    this->boughtondiscount = boughtondiscount;
  }

  friend ostream& operator<<(ostream& out, Game& g) {
    out<<"Game: "<<g.name<<", regular price: $"<<g.price;
    if(g.boughtondiscount) {
      out<<", bought on sale"<<endl;
    }
    return out;
  }

  friend istream& operator>>(istream& in, Game& g) {
    in.get();
    in.getline(g.name, 101);
    in>>g.price>>g.boughtondiscount;
    in.ignore();
    return in;
  }

  bool operator==(const Game &g) const {
    return strcmp(name, g.name) == 0;
  }

  float get_price() {
    return price;
  }

  virtual ~Game() {};
};

class SubscriptionGame : public Game {
  float subscription;
  int month;
  int y;
public:
  SubscriptionGame(char *name = (char*)" ", float price = 0, bool boughtondiscount = false, float subscription = 0, int month = 0, int y = 0) : Game(name, price, boughtondiscount) {
    this->subscription = subscription;
    this->month = month;
    this->y = y;
  }

  friend ostream& operator<<(ostream& out, SubscriptionGame& g) {
    //Game: PUBG, regular price: $100, bought on sale, monthly fee: $5, purchased: 5-2018
    out<<"Game: "<<g.name<<", regular price: $"<<g.price;
    if(g.boughtondiscount) {
      out<<", bought on sale";
    }
    out<<", monthly fee: $"<<g.subscription<<", purchased: "<<g.month<<"-"<<g.y<<endl;
    return out;
  }

  friend istream& operator>>(istream& in, SubscriptionGame& g) {
    in.get();
    in.getline(g.name, 101);
    in>>g.price>>g.boughtondiscount>>g.subscription>>g.month>>g.y;
    in.ignore();
    return in;
  }

  bool operator==(const SubscriptionGame &g) const {
    return strcmp(name, g.name) == 0;
  }
};

class User {
private:
  void obj_copy(const User * orig, User * cpy){
    strcpy(cpy->username, orig->username);
    cpy->num_games = orig->num_games;

    cpy->games = new Game*[cpy->num_games];

    for (int i=0; i< cpy->num_games; ++i){
      cpy->games[i] = new Game(*(orig->games[i]));
    }
  }

protected:
  char username[100];
  Game ** games;
  int num_games;
public:
  User (char const * const un="") {
    strncpy(this->username, un, 99);
    this->username[99] = '\0';
    games = 0;
    num_games = 0;
  }

  User (const User& orig){
    obj_copy(&orig,this);
  }

  ~User(){
    for (int i=0; i < this->num_games; ++i){
      delete this->games[i];
    }
    delete [] games;
  }

  User& operator=(User & orig){
    if (&orig != this){

      for (int i=0; i < this->num_games; ++i){
        delete orig.games[i];
      }

      delete [] orig.games;

      obj_copy(&orig, this);
    }
    return *this;
  }

  User& operator+=(Game&g){

    Game ** new_games = new Game*[this->num_games+1];

    for (int i=0; i < (this->num_games); ++i) {
      if ( (*(this->games[i])) == g){
          throw ExistingGame("The game is already in the collection");
        }

        new_games[i] = games[i];
    }

    for (int i=0; i < (this->num_games); ++i) {
      new_games[i] = games[i];
    }

    SubscriptionGame * sg = dynamic_cast< SubscriptionGame* >(&g);

    if(sg){

      new_games[num_games] = new SubscriptionGame(*sg);
    }
    else {
      //cout<<"Game"<<endl;
      new_games[num_games] = new Game(g);
    }

    delete [] this->games;
    this->games = new_games;
    this->num_games++;

    //cout<<"User: "<< this->username<<endl;

//    for (int i=0; i<this->num_games;++i){
//        cout<< *(this->games[i]);
//    }

    return *this;
  }


//  User& operator+=(SubscriptionGame&g){

//    Game ** new_games = new Game*[this->num_games+1];

//    cout<<this->num_games<<std::endl;

//    for (int i=0; i < (this->num_games); ++i) {
//      new_games[i] = games[i];
//    }

//    SubscriptionGame * sg = dynamic_cast< SubscriptionGame* >(&g);

//    if(sg){
//      cout<<"Game"<<endl;
//      new_games[num_games] = new SubscriptionGame(*sg);
//    }
//    else {
//      cout<<"SubGame"<<endl;
//      new_games[num_games] = new Game(g);
//    }



//    this->num_games++;
//    cout<<"User: "<< this->username<<endl;

//    for (int i=0; i<this->num_games;++i){
//        cout<< *(this->games[i]);
//    }

//  }


  Game& get_game(int i){
        return (*(this->games[i]));
  }

  float total_spent(){
    float sum = 0.0f;
    for (int i=0; i<this->num_games; ++i){
        sum += games[i]->get_price();
      }
    return sum;
  }

  char const * const get_username(){
    return this->username;
  }

  int get_games_number(){
    return this->num_games;
  }

};

ostream & operator<<(ostream & o, User& u) {

  o<<"\nUser: "<<u.get_username()<<"\n";

  for (int i=0; i < u.get_games_number(); ++i){
      Game * g;
      SubscriptionGame * sg;
      g = &(u.get_game(i));

      sg = dynamic_cast<SubscriptionGame *> (g);

      if (sg){
        cout<<"- "<<(*sg);
      }
      else {
        cout<<"- "<<(*g);
      }
      cout<<"\n";
  }
  return o;
}



int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }

  else if (test_case_num == 5) {
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);


        u+=(*g);
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;
  }

    //    cout<<"\nUser: "<<u.get_username()<<"\n";

    //    for (int i=0; i < u.get_games_number(); ++i){
    //        Game * g;
    //        SubscriptionGame * sg;
    //        g = &(u.get_game(i));

    //        sg = dynamic_cast<SubscriptionGame *> (g);

    //        if (sg){
    //          cout<<"- "<<(*sg);
    //        }
    //        else {
    //          cout<<"- "<<(*g);
    //        }
    //        cout<<"\n";
    //    }



//   else if (test_case_num == 6){
//       cout<<"Testing exception ExistingGame for User"<<std::endl;
//       cin.get();
//       cin.getline(username,100);
//       User u(username);
//
//       int num_user_games;
//       int game_type;
//       cin >>num_user_games;
//
//       for (int i=0; i<num_user_games; ++i){
//
//           cin >> game_type;
//
//           Game *g;
//           // 1 - Game, 2 - SubscriptionGame
//           if (game_type == 1){
//             cin.get();
//             cin.getline(game_name, 100);
//
//             cin>>game_price>>game_on_sale;
//             g = new Game(game_name, game_price, game_on_sale);
//           }
//           else if (game_type == 2){
//             cin.get();
//             cin.getline(game_name, 100);
//
//             cin>>game_price>>game_on_sale;
//
//             cin>>sub_game_monthly_fee;
//             cin>>sub_game_month>>sub_game_year;
//             g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
//           }
//
//           //cout<<(*g);
//
//           try {
//             u+=(*g);
//           }
//           catch(ExistingGame &ex){
//             ex.message();
//           }
//         }
//
//       cout<<u;
//
// //      for (int i=0; i < u.get_games_number(); ++i){
// //          Game * g;
// //          SubscriptionGame * sg;
// //          g = &(u.get_game(i));
//
// //          sg = dynamic_cast<SubscriptionGame *> (g);
//
// //          if (sg){
// //            cout<<"- "<<(*sg);
// //          }
// //          else {
// //            cout<<"- "<<(*g);
// //          }
// //          cout<<"\n";
// //      }
//   }
//   else if (test_case_num == 7){
//       cout<<"Testing total_spent method() for User"<<std::endl;
//       cin.get();
//       cin.getline(username,100);
//       User u(username);
//
//       int num_user_games;
//       int game_type;
//       cin >>num_user_games;
//
//       for (int i=0; i<num_user_games; ++i){
//
//           cin >> game_type;
//
//           Game *g;
//           // 1 - Game, 2 - SubscriptionGame
//           if (game_type == 1){
//             cin.get();
//             cin.getline(game_name, 100);
//
//             cin>>game_price>>game_on_sale;
//             g = new Game(game_name, game_price, game_on_sale);
//           }
//           else if (game_type == 2){
//             cin.get();
//             cin.getline(game_name, 100);
//
//             cin>>game_price>>game_on_sale;
//
//             cin>>sub_game_monthly_fee;
//             cin>>sub_game_month>>sub_game_year;
//             g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
//           }
//
//           //cout<<(*g);
//
//
//           u+=(*g);
//         }
//
//       cout<<u;
//
//       cout<<"Total money spent: $"<<u.total_spent()<<endl;
//   }
}
