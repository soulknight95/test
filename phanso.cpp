#include<iostream>
using namespace std;
class phanso{
    private:
        int tu, mau;
    public:
        phanso(){
            tu = 0 ; mau = 1;
        }
        phanso(int a, int b){
            this -> tu= a;
            this -> mau= b;
        }
    void tong (phanso s1, phanso s2); 
    void tich (phanso s1, phanso s2);
    void nhap ();
    void xuat(); 
    void rutgon();
    int UCLN(int a , int b);
};

void phanso:: tong(phanso s1, phanso s2){
    if (s1.mau == s2.mau ){
        tu = s1.tu + s2.tu;
        mau = s1.mau ;}
    else {
        tu = (s1.tu*s2.mau + s2.tu*s1.mau);
        mau = s1.mau*s2.mau;
    }
        cout << "tong  2 phan so: "; 
}
void phanso:: tich(phanso s1 , phanso s2){
    tu = s1.tu * s2.tu;
    mau = s1.mau * s2.mau;
    cout << "tich 2 phan so: ";
}
int phanso::UCLN(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}
void phanso::rutgon() {
    int ucln = UCLN(abs(tu), abs(mau));
    tu /= ucln;
    mau /= ucln;
    if (mau < 0) { // giữ mẫu dương
        tu = -tu;
        mau = -mau;
    }
}
void phanso:: nhap(){
    cout << "nhap phan so : "; cin >> tu >> mau;
}
void phanso :: xuat(){
    rutgon();
    if (tu == mau){
        cout << 1<<endl;
    }
    else{cout << tu << "/"<< mau<< endl;}
}
int main(){
    phanso s1; s1.nhap();
    phanso s2; s2.nhap();

    phanso s3;
    s3.tong(s1,s2); s3.xuat();
    s3.tich(s1,s2); s3.xuat();
    return 0;
}


