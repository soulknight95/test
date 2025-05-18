// #include <iostream>
// using namespace std;


// void date (int m, int y) {
// 	if ( m<13 && m>0){
// 		cout << "1-"<< m << "-"<< y << endl;
// 	}
//     else{
//         int x;
//         x=m%12; y+=(m/12);
//         cout << "1-"<< x << "-"<< y << endl;
//     }
// }

// void date ( int d, int m, int y){
// 	if ( m<13 && m>0 && d>0 && d<31){
// 		cout << d << "-" << m << "-"<< y << endl;
// 	}
//     else{
//         int x, z;
//         x=((d/30)+m)%12; y+=(((d/30)+m)/12); z=d%30;
//         cout << z << "-" << x << "-"<< y << endl;
        
//     }	
// }
// void date ( int d  ){
//     int day =(d %360)%30+1; int m = (d %360)/30; int y= d/360;
//     if (m==0){
//         m=m+1;
//     }
// 	cout <<day << "/" 
// 			<< m << "/" 
// 			<< d/360<< endl;
// }
// int main (){
// 	date( 7,2024);
// 	date(35,3,2025);
//     date(2024*12*30+2*30+22);
//     date(0);
//     date(1);
//     date(729097);
//     date (360);
//     date (3600);
    
    
// }





#include<iostream>

class Author{
    private:
        string name;
        string email;
    public:
        Author(string name, string email){
            this -> name = name;
            this -> email = email;
        }
        void setName(string name){this -> name = name;}
        void setEmail(string email){this -> email = email;}
        string getName(){return name;}
        string getEmail(){return email;}
};

class Book{
    private:
        string name;
        double price;
        vector <Author> authors;
    public:
        Book(string name, double price, vector <Author> authors){
            this -> name = name;
            this -> price = price;
            this -> authors = authors;
        }
        void setName(string name){this -> name = name;}
        string getName(){return name;}
        void setPrice(double price){this -> price = price;}
        double getPrice(){return price;}
        string getAuthorName(){return authors;}
};
int main() {
	vector<Author> authors;
	authors.push_back(Author("Viet", "VietCV@codelearn.io"));
	authors.push_back(Author("Tuan", "TuanLQ7@codelearn.io"));
	authors.push_back(Author("KienNT", "KienNT@codelearn.io"));

	Book book1("C++ for Beginners", authors, 210000);
	cout << book1.getAuthorNames();	
	return 0;
}