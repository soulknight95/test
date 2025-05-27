// tạo lớp điểm, nhập 3 điểm bất kỳ trong mặt phẳng, 
// tính chu vi, diện tích tam giác tạo ra từ 3 điểm đó
//(kiểm tra không phải tam giác thì nhập lại ).


#include<iostream>
#include<math.h>
using namespace std;

class Point{
    private:
        float x;
        float y;
    public: 
        Point(){
            x=0; y=0;
        }
        Point (float x, float y) : x(x), y(y){}
        float getX(){return x;}
        float getY(){return y;}
        
        void setX(float x){this ->x=x;}
        void setY(float y){this-> y=y;}

        void nhap(){
            cout << "Nhap diem x: "; cin>>x;
            cout << "Nhap diem y: "; cin >>y;
        }
        bool laTamGiac(Point s1, Point s2, Point s3) {
            float area = 0.5 * abs(s1.getX() * (s2.getY() - s3.getY()) +
                                s2.getX() * (s3.getY() - s1.getY()) +
                                s3.getX() * (s1.getY() - s2.getY()));
            return area != 0;
        }
        float dientich(Point s1, Point s2, Point s3){
            float area;
            area = (s1.getX()*(s2.getY() + s3.getY())
                        + s2.getX()*(s3.getY() + s1.getY()) 
                            + s3.getX()*(s1.getY() + s2.getY())) /2;
            return area;
        }
        float chuvi(Point s1, Point s2, Point s3){

            float chuvi;
            chuvi = sqrt(pow(s1.getX()-s2.getX(),2) + pow(s1.getY()-s2.getY(),2)) 
                    + sqrt(pow(s3.getX()-s2.getX(),2) + pow(s3.getY()-s2.getY(),2)) 
                        + sqrt(pow(s1.getX()-s3.getX(),2) + pow(s1.getY()-s3.getY(),2));

            return chuvi;      
        }
        void xuat(Point s1, Point s2, Point s3, float dientich, float chuvi){
            cout << "Ba diem vua nhap la: "<<endl;
            cout << s1.getX() << ";" << s1.getY()<<endl;
            cout << s2.getX() << ";" << s2.getY()<<endl;
            cout << s3.getX() << ";" << s3.getY()<<endl;
            cout << "Dien tich tam giac: "<< dientich << endl;
            cout << "Chu vi tam giac: "<< chuvi << endl;
        }
};
int main(){
    Point s1, s2, s3;
    cout<< "Diem thu nhat: \n";s1.nhap();
    cout<< "Diem thu hai: \n";s2.nhap();
    cout<< "Diem thu ba: \n";s3.nhap();
    Point s4;
        // Kiểm tra tam giác 
            do {
                cout<< "Diem thu nhat: \n"; s1.nhap();
                cout<< "Diem thu hai: \n"; s2.nhap();
                cout<< "Diem thu ba: \n"; s3.nhap();

            if (!s4.laTamGiac(s1, s2, s3)) {
                    cout << "Ba diem khong tao thanh tam giac. Vui long nhap lai!\n";
                }
            } while (!s4.laTamGiac(s1, s2, s3));
    
    s4.dientich(s1,s2,s3);
    s4.chuvi(s1,s2,s3);
    float dt= s4.dientich( s1, s2, s3);
    float cv = s4.chuvi( s1, s2, s3);
    s4.xuat(s1, s2, s3, dt, cv );
    return 0;
}

