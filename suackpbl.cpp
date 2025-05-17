#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
using namespace std;

// Lớp Product để quản lý sản phẩm
class Product {
private:
    string barcode; // Mã vạch
    string name; // Tên sp
    double price; // giá sp
    int stock;  // tồn kho

public:
    Product(string _barcode, string _name, double _price, int _stock)
        : barcode(_barcode), name(_name), price(_price), stock(_stock) {} 
// Khai báo ngắn gọn hơn thay vì dùng this:
//     Product(string barcode, string name, double price, int stock) {
//     this->barcode = barcode;
//     this->name = name;
//     this->price = price;
//     this->stock = stock;
// }
    // Getter
    string getBarcode() const { return barcode; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    // Setter
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setStock(int newStock) { stock = newStock; }
    void reduceStock(int quantity) { stock -= quantity; }
};
// Cấu trúc SaleItem để lưu sản phẩm trong giỏ hàng
struct SaleItem {
    Product* product;
    int quantity;
    SaleItem(Product* _product, int _quantity) : product(_product), quantity(_quantity) {}
};
// Lớp Supermarket để quản lý hệ thống
class Supermarket {
private:
    vector<Product> products;
    vector<SaleItem> cart;
    const string productFile = "products1.txt";
    const string receiptFile = "receipt1.txt";
// Lưu sản phẩm vào file
    void saveToFile() {
        ofstream outFile(productFile);
        for (const auto& p : products) {
            outFile << p.getBarcode() << "," << p.getName() << "," << p.getPrice() << "," << p.getStock() << endl;
        }
        outFile.close();
    }
// Đọc sản phẩm từ file
    void loadFromFile() {
        ifstream inFile(productFile);
        products.clear();
        string line;
        while (getline(inFile, line)) {
            string barcode, name;
            double price;
            int stock;
            size_t pos = 0;
            barcode = line.substr(0, pos = line.find(","));
            line.erase(0, pos + 1);
            name = line.substr(0, pos = line.find(","));
            line.erase(0, pos + 1);
            price = stod(line.substr(0, pos = line.find(",")));
            line.erase(0, pos + 1);
            stock = stoi(line);
            products.push_back(Product(barcode, name, price, stock));
        }
        inFile.close();
    }
    // Giả lập in hóa đơn (thay vì dùng máy in thật)
    void printReceipt() {
        ofstream outFile(receiptFile, ios::app);
        double total = 0;
        time_t now = time(0);
        string timestamp = ctime(&now);

        outFile << "        === HOA DON BAN HANG ===\n";
        outFile << "Thoi gian: " << timestamp;
        outFile << left << setw(20) << "San pham" << setw(10) << "So luong" << setw(15) << "Don gia" << setw(15) << "Thanh tien" << endl;
        outFile << "-------------------------------------------------------\n";

        for (const auto& item : cart) {
            double itemTotal = item.product->getPrice() * item.quantity;
            total += itemTotal;
            outFile << left << setw(20) << item.product->getName() << setw(10) << item.quantity 
                    << setw(15) << item.product->getPrice() << setw(15) << itemTotal << endl;
        }

        outFile << "-------------------------------------------------------\n";
        outFile << "Tong cong: " << total << " VND\n";
        outFile << "Cam on quy khach!\n\n";
        outFile.close();

        cout << "Da in hoa don vao " << receiptFile << endl;
    }

public:
    Supermarket() {
        loadFromFile(); // Tải dữ liệu khi khởi tạo
    }
// Thêm sản phẩm 
    void addProduct(string barcode, string name, double price, int stock) {
        for (const auto& p : products) {
            if (p.getBarcode() == barcode) {
                cout << "Ma vach da ton tai!" << endl;
                return;
            }
        }
        products.push_back(Product(barcode, name, price, stock));
        saveToFile();
        cout << "Them san pham thanh cong!" << endl;
    }
 // Giả lập quét mã vạch
    string scanBarcode() {
        string barcode;
        cout << "Quet ma vach (nhap ma): ";
        getline(cin, barcode);
        return barcode;
    }
// Thêm sản phẩm vào giỏ hàng qua mã vạch
    void addToCart(string barcode, int quantity) {
        for (auto& p : products) {
            if (p.getBarcode() == barcode) {
                int quantityInCart = 0;
                // Tính tổng số lượng sản phẩm này đã có trong giỏ
                for (const auto& item : cart) {
                    if (item.product == &p) {
                        quantityInCart += item.quantity;
                    }
                }
                // Kiểm tra nếu đủ hàng tồn kho
                if (p.getStock() >= quantityInCart + quantity) {
                    // Nếu đã có sản phẩm trong giỏ thì tăng số lượng
                    for (auto& item : cart) {
                        if (item.product == &p) {
                            item.quantity += quantity;
                            cout << "Da cap nhat so luong trong gio hang." << endl;
                            return;
                        }
                    }
                     // Nếu chưa có thì thêm mới vào giỏ
                    cart.push_back(SaleItem(&p, quantity));
                    cout << "Da them " << quantity << " " << p.getName() << " vao gio hang." << endl;
                } else {
                    cout << "Khong du hang trong kho! Chi con lai " << (p.getStock() - quantityInCart) << " san pham." << endl;
                }
                return;
            }
        }
        cout << "Khong tim thay san pham voi ma vach nay!" << endl;
    }
// Xóa sản phẩm khỏi giỏ hàng
    void removeFromCart(string barcode) {
        for (auto it = cart.begin(); it != cart.end(); ++it) {
            if (it->product->getBarcode() == barcode) {
                cart.erase(it);
                cout << "Da xoa san pham khoi gio hang." << endl;
                return;
            }
        }
        cout << "San pham khong co trong gio hang!" << endl;
    }
//Sửa sản phẩm 
    void editProduct(string barcode) {
        for (auto& p : products) {
            if (p.getBarcode() == barcode) {
                cout << "Dang sua san pham: " << p.getName() << endl;
                cout << "Nhap ten moi (hoac nhan Enter de giu nguyen): ";
                string newName;
                getline(cin, newName);
                if (!newName.empty()) p.setName(newName);

                cout << "Nhap gia moi (hoac 0  de giu nguyen): ";
                double newPrice;
                cin >> newPrice;
                if (newPrice >= 1) p.setPrice(newPrice);

                cout << "Nhap ton kho moi (hoac 0  de giu nguyen): ";
                int newStock;
                cin >> newStock;
                cin.ignore();
                if (newStock >= 1) p.setStock(newStock);

                saveToFile();
                cout << "Cap nhat san pham thanh cong!" << endl;
                return;
            }
        }
        cout << "Khong tim thay san pham voi ma vach nay!" << endl;
    }
// Xóa sản phẩm 
    void deleteProduct(string barcode) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getBarcode() == barcode) {
                cout << "Ban co chac muon xoa " << it->getName() << "? (y/n): ";
                char confirm;
                cin >> confirm;
                cin.ignore();
                if (confirm == 'y' || confirm == 'Y') {
                    products.erase(it);
                    saveToFile();
                    cout << "Da xoa san pham." << endl;
                } else {
                    cout << "Huy xoa." << endl;
                }
                return;
            }
        }
        cout << "Khong tim thay san pham voi ma vach nay!" << endl;
    }
//Thanh toán và in hóa đơn 
    void checkout() {
        if (cart.empty()) {
            cout << "Gio hang trong!" << endl;
            return;
        }
        // Cập nhật tồn kho 
        for (auto& item : cart) {
            item.product->reduceStock(item.quantity);
        }
        saveToFile();
        // In hóa đơn: 
        printReceipt();
        //xóa giỏ hàng 
        cart.clear();
        cout << "Thanh toan thanh cong!" << endl;
        // Kiểm tra tồn kho 
        checkLowStock();
    }
// Hiện thị giỏ hàng 
    void displayCart() {
        double total = 0;
        if (cart.empty()) {
            cout << "Gio hang trong!" << endl;
            return;
        }
        cout << left << setw(20) << "San pham" << setw(10) << "So luong" << setw(15) << "Don gia" << endl;
        for (const auto& item : cart) {
            double itemTotal = item.product->getPrice() * item.quantity;
            total += itemTotal;
            cout << left << setw(20) << item.product->getName() << setw(10) << item.quantity
                 << setw(15) << item.product->getPrice() << endl;
        }
        cout << "----------------------------------------\n";
        cout << "Tong cong: " << total << " VND\n";
    }
//Tự động sắp xếp các sản phẩm theo mã vach 
    void sortProducts(){
            for (int i=0 ; i< products.size(); i++ ){
                for(int j= i+1; j< products.size(); j++){
                    if( products[i].getBarcode() > products[j].getBarcode()){
                        swap(products[i] , products[j]);
                    }
                }
            }
        }
    // Hiển thị danh sách sản phẩm
    void displayProducts() {
        sortProducts();
        cout << left << setw(15) << "Ma vach" << setw(20) << "Ten" << setw(15) << "Gia (VND)" << setw(10) << "Ton kho" << endl;
        for (const auto& p : products) {
            cout << left << setw(15) << p.getBarcode() << setw(20) << p.getName() << setw(15) << p.getPrice() << setw(10) << p.getStock() << endl;
        }
        // Kiểm tra tồn kho 
        checkLowStock();
    }
// Hàm kiểm tra tồn kho (dưới 10sp --> cảnh báo)
    void checkLowStock(int threshold = 10) {
        bool found = false;
        for (const auto& p : products) {
            if (p.getStock() <= threshold) {
                cout << "\n*** Canh bao san pham sap het hang (ton kho <= " << threshold << ") ***\n";
                cout << " - " << p.getName() << " (Ma: " << p.getBarcode() << ") chi con " << p.getStock() << " san pham.\n";
                found = true;
            }
        }
        if (!found) {
            cout << "Tat ca san pham deu con nhieu hang.\n";
        }
    }
};

void menu() {
    Supermarket sm;
    int choice;
    while (true) {
        cout << "\n=== Quan ly sieu thi ===" << endl;
        cout << "1. Them san pham" << endl;
        cout << "2. Hien thi san pham" << endl;
        cout << "3. Quet ma vach de ban hang" << endl;
        cout << "4. Hien thi gio hang" << endl;
        cout << "5. Thanh toan va in hoa don" << endl;
        cout << "6. Xoa san pham khoi gio hang" << endl;
        cout << "7. Sua thong tin san pham" << endl;
        cout << "8. Xoa san pham" << endl;
        cout << "9. Thoat" << endl;
        cout << "Chon: ";
        cin >> choice;
        cin.ignore();

        if (choice == 9) break;

        switch (choice) {
            case 1: {
                string barcode, name;
                double price;
                int stock;
                cout << "Nhap ma vach: "; getline(cin, barcode);
                cout << "Nhap ten san pham: "; getline(cin, name);
                cout << "Nhap gia: "; cin >> price;
                cout << "Nhap ton kho: "; cin >> stock;
                cin.ignore();
                sm.addProduct(barcode, name, price, stock);
                break;
            }
            case 2: sm.displayProducts(); break;
            case 3: {
                string barcode = sm.scanBarcode();
                int quantity;
                cout << "Nhap so luong: "; cin >> quantity;
                cin.ignore();
                sm.addToCart(barcode, quantity);
                break;
            }
            case 4: sm.displayCart(); break;
            case 5: sm.checkout(); break;
            case 6: {
                string barcode;
                cout << "Nhap ma vach san pham can xoa: ";
                getline(cin, barcode);
                sm.removeFromCart(barcode);
                break;
            }
            case 7: {
                string barcode;
                cout << "Nhap ma vach san pham can sua: ";
                getline(cin, barcode);
                sm.editProduct(barcode);
                break;
            }
            case 8: {
                string barcode;
                cout << "Nhap ma vach san pham can xoa: ";
                getline(cin, barcode);
                sm.deleteProduct(barcode);
                break;
            }
            default:
                cout << "Lua chon khong hop le!" << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
