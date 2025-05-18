// #include<iostream>
// #include<vector>
// using namespace std;

// class Card{
//     private: 
//         string nameBook;
//         string nameAuthor;
//         int numberBook;
//     public:
//         Card(){ 
//             nameBook = "";
//             nameAuthor = "";
//             numberBook = 0;
//         }
//         Card( string nameBook, string nameAuthor, int numberBook){
//             this -> nameBook = nameBook;
//             this -> nameAuthor = nameAuthor;
//             this -> numberBook = numberBook;
//         }
//         void display() const {
//             cout << " Name Book: "<< nameBook<< endl;
//             cout << " Name Author: "<< nameAuthor << endl;
//             cout << " Number Book: "<< numberBook << endl;
//         }
//         int getNumBook() const { return numberBook;}
        
//         static void sortCard( vector<Card> &cards){
//             for (int i=0 ; i< cards.size(); i++ ){
//                 for(int j= i+1; j< cards.size(); j++){
//                     if( cards[i].getNumBook() > cards[j].getNumBook()){
//                         swap(cards[i] , cards[j]);
//                     }
//                 }
//             }
//         }
// };int main() {
//     vector<Card> cards;
//     cards.push_back(Card("Book A", "Author A", 111));
//     cards.push_back(Card("Book B", "Author B", 444));
//     cards.push_back(Card("Book C", "Author C", 222));

//     cout << "Before sorting:\n";
//     for (const auto& card : cards) {// vòng lặp gọi ra các sách 
//         card.display();
//         cout << endl;
//     }

//     Card::sortCard(cards);

//     cout << "After sorting:\n";
//     for (const auto& card : cards) {
//         card.display();
//         cout << endl;
//     }

//     return 0;
// }


#include<iostream>
#include<vector>
using namespace std;

class Card{
    private:
        string nameBook;
        string nameAuthor;
        int numberBook;
    public:
        Card(){
            nameBook = "";
            nameAuthor= "";
            numberBook =0;
        }
        Card(string nameBook, string nameAuthor, int numberBook){
            this -> nameAuthor = nameAuthor;
            this -> nameBook = nameBook;
            this -> numberBook = numberBook;
        }
        int getNumBook(){return numberBook;}
        void display(){
            cout << "Name Book: "<< nameBook<< endl;
            cout << "Name Author: "<< nameAuthor<<endl;
            cout << "Number Book: "<< numberBook<< endl;
        }
        static void sortCards(vector<Card> &cards){
            for (int i=0 ; i < cards.size() ; i++){
                for(int j = i +1; j< cards.size()  ; j++){
                    if (cards[i].getNumBook() > cards[j].getNumBook()){
                        swap(cards[i], cards[j]);
                }}
            }
        }
};

int main(){
    vector<Card> cards;
    cards.push_back(Card("le huyen", "to nga", 20000));
    cards.push_back(Card("le huyen", "duy chien", 90000));
    cards.push_back(Card("le huyen", "thi yen", 8000));
    cards.push_back(Card("thuy vy", "huyen trang", 87998));
    

    Card:: sortCards(cards);
    for (auto &cards : cards){
        cards.display();
        cout<< endl;
    }

    return 0;
}