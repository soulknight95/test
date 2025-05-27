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
    double discountPercent; // Phần trăm giảm giá, ví dụ: 10.0 là giảm 10%


public:
    Product(string barcode, string name, double price, int stock, double discountPercent = 0.0)
        : barcode(barcode), name(name), price(price), stock(stock), discountPercent(discountPercent) {}
    // Getter
    string getBarcode() const { return barcode; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    double getDiscountPercent() const { return discountPercent; }
    // Setter
    void setName(const string& newName) { name = newName; }
    void setPrice(double newPrice) { price = newPrice; }
    void setStock(int newStock) { stock = newStock; }
    void reduceStock(int quantity) { stock -= quantity; }
    void setDiscountPercent(double percent) { discountPercent = percent; }

};
class KhachHang {
private:
    string id;
    string name;
    string phone;

public:
    KhachHang(string id, string name, string phone)
        : id(id), name(name), phone(phone) {}

    string getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }

    void setName(const string& newName) { name = newName; }
    void setPhone(const string& newPhone) { phone = newPhone; }

    void display() const {
        cout << "ID: " << id << ", Ten: " << name << ", SDT: " << phone << endl;
    }
};

// Cấu trúc SaleItem để lưu sản phẩm trong đơn hàng
struct SaleItem {
    Product* product;
    int quantity;
    SaleItem(Product* _product, int _quantity) : product(_product), quantity(_quantity) {}
};
// Lớp Supermarket để quản lý hệ thống
class Supermarket {
private:
    vector<Product> products;
    vector<SaleItem> order;
    const string productFile = "products1.txt";
    const string receiptFile = "receipt1.txt";
public:
// Lưu sản phẩm vào file
    void saveToFile() {
        ofstream outFile(productFile);
        for (const auto& p : products) {
            outFile << p.getBarcode() << "," << p.getName() << "," << p.getPrice() << "," << p.getStock() << "," << p.getDiscountPercent() << endl;
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
            double price, discountPercent;
            int stock;
            size_t pos = 0;

            barcode = line.substr(0, pos = line.find(","));     line.erase(0, pos + 1);
            name = line.substr(0, pos = line.find(","));        line.erase(0, pos + 1);
            price = stod(line.substr(0, pos = line.find(","))); line.erase(0, pos + 1);
            stock = stoi(line.substr(0, pos = line.find(","))); line.erase(0, pos + 1);
            discountPercent = stod(line);

            products.push_back(Product(barcode, name, price, stock, discountPercent));
        }
        inFile.close();
    }
    vector<Product>& getProducts() {
        return products;
    }

    // Giả lập in hóa đơn (thay vì dùng máy in thật)
    void printReceipt() {
        ofstream outFile(receiptFile, ios::app);
        double totalBeforeDiscount = 0;
        double totalAfterDiscount = 0;
        time_t now = time(0);
        string timestamp = ctime(&now);

        outFile << "        === HOA DON BAN HANG ===\n";
        outFile << "Thoi gian: " << timestamp;
        outFile << left << setw(20) << "San pham" 
                << setw(10) << "So luong" 
                << setw(15) << "Don gia" 
                << setw(10) << "Giam" 
                << setw(15) << "Thanh tien" << endl;
        outFile << "------------------------------------------------------------------\n";

        for (const auto& item : order) {
            double price = item.product->getPrice();
            double discount = item.product->getDiscountPercent();
            double discountedPrice = price * (1 - discount / 100.0);
            double itemTotal = discountedPrice * item.quantity;
            totalAfterDiscount += itemTotal;
            totalBeforeDiscount += price * item.quantity;

            outFile << left << setw(20) << item.product->getName()
                    << setw(10) << item.quantity
                    << setw(15) << price
                    << setw(10) << (to_string(discount) + "%")
                    << setw(15) << itemTotal << endl;
        }

        outFile << "------------------------------------------------------------------\n";
        outFile << "Tong tien truoc giam: " << totalBeforeDiscount << " VND\n";
        if (totalBeforeDiscount > totalAfterDiscount) {
            outFile << "Giam gia: " << (totalBeforeDiscount - totalAfterDiscount) << " VND\n";
        }
        outFile << "Tong cong: " << totalAfterDiscount << " VND\n";
        outFile << "Cam on quy khach!\n\n";
        outFile.close();

        cout << "Da in hoa don vao " << receiptFile << endl;
    }


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
// Thêm sản phẩm vào đơn hàng qua mã vạch
    void addToOrder(string barcode, int quantity) {
        for (auto& p : products) {
            if (p.getBarcode() == barcode) {
                int quantityInOrder = 0;
                // Tính tổng số lượng sản phẩm này đã có trong đơn 
                for (const auto& item : order) {
                    if (item.product == &p) {
                        quantityInOrder += item.quantity;
                    }
                }
                // Kiểm tra nếu đủ hàng tồn kho
                if (p.getStock() >= quantityInOrder + quantity) {
                    // Nếu đã có sản phẩm trong đơn thì tăng số lượng
                    for (auto& item : order) {
                        if (item.product == &p) {
                            item.quantity += quantity;
                            cout << "Da cap nhat so luong trong don hang." << endl;
                            return;
                        }
                    }
                     // Nếu chưa có thì thêm mới vào đơn 
                    order.push_back(SaleItem(&p, quantity));
                    cout << "Da them " << quantity << " " << p.getName() << " vao don hang." << endl;
                } else {
                    cout << "Khong du hang trong kho! Chi con lai " << (p.getStock() - quantityInOrder) << " san pham." << endl;
                }
                return;
            }
        }
        cout << "Khong tim thay san pham voi ma vach nay!" << endl;
    }
// Xóa sản phẩm khỏi đơn hàng
    void removeFromOrder(string barcode) {
        for (auto it = order.begin(); it != order.end(); ++it) {
            if (it->product->getBarcode() == barcode) {
                order.erase(it);
                cout << "Da xoa san pham khoi don hang." << endl;
                return;
            }
        }
        cout << "San pham khong co trong don hang!" << endl;
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
        if (order.empty()) {
            cout << "Don hang trong!" << endl;
            return;
        }
        // Cập nhật tồn kho 
        for (auto& item : order) {
            item.product->reduceStock(item.quantity);
        }
        saveToFile();
        // In hóa đơn: 
        printReceipt();
        //xóa don hàng 
        order.clear();
        cout << "Thanh toan thanh cong!" << endl;
        // Kiểm tra tồn kho 
        checkLowStock();
    }
// Hiện thị đơn hàng 
    void displayOrder() {
        double total = 0;
        if (order.empty()) {
            cout << "Don hang trong!" << endl;
            return;
        }
        cout << left << setw(20) << "San pham" << setw(10) << "So luong" << setw(15) << "Don gia" << endl;
        for (const auto& item : order) {
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
    // Tìm kiếm sản phẩm theo mã vạch
void searchProductByBarcode(const string& barcode) {
    for (const auto& p : products) {
        if (p.getBarcode() == barcode) {
            cout << "\n=== Thong tin san pham ===\n";
            cout << "Ma vach: " << p.getBarcode() << endl;
            cout << "Ten: " << p.getName() << endl;
            cout << "Gia: " << p.getPrice() << " VND" << endl;
            cout << "Ton kho: " << p.getStock() << endl;
            return;
        }
    }
    cout << "Khong tim thay san pham voi ma vach nay!\n";
}

};

void menu() {
    Supermarket sm;
    int choice;
    while (true) {
        cout << "\n=== QUẢN LÝ SIÊU THỊ ===" << endl;
        cout << "1. Quản lý sản phẩm" << endl;
        cout << "2. Bán hàng" << endl;
        cout << "3. Hóa đơn & thanh toán" << endl;
        cout << "4. Tìm kiếm & giảm giá" << endl;
        cout << "0. Thoát" << endl;
        cout << "Chọn: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1: {
                int sub;
                do {
                    cout << "\n=== QUẢN LÝ SẢN PHẨM ===" << endl;
                    cout << "1. Thêm sản phẩm" << endl;
                    cout << "2. Sửa sản phẩm" << endl;
                    cout << "3. Xóa sản phẩm" << endl;
                    cout << "4. Hiển thị danh sách sản phẩm" << endl;
                    cout << "0. Quay lại" << endl;
                    cout << "Chọn: ";
                    cin >> sub;
                    cin.ignore();
                    switch (sub) {
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
                        case 2: {
                            string barcode;
                            cout << "Nhap ma vach can sua: ";
                            getline(cin, barcode);
                            sm.editProduct(barcode);
                            break;
                        }
                        case 3: {
                            string barcode;
                            cout << "Nhap ma vach can xoa: ";
                            getline(cin, barcode);
                            sm.deleteProduct(barcode);
                            break;
                        }
                        case 4:
                            sm.displayProducts();
                            break;
                        case 0: break;
                        default: cout << "Lua chon khong hop le!\n";
                    }
                } while (sub != 0);
                break;
            }

            case 2: {
                int sub;
                do {
                    cout << "\n=== BÁN HÀNG ===" << endl;
                    cout << "1. Quét mã vạch để thêm vào đơn hàng" << endl;
                    cout << "2. Xóa sản phẩm khỏi đơn hàng" << endl;
                    cout << "3. Hiển thị đơn hàng hiện tại" << endl;
                    cout << "0. Quay lại" << endl;
                    cout << "Chọn: ";
                    cin >> sub;
                    cin.ignore();
                    switch (sub) {
                        case 1: {
                            string barcode = sm.scanBarcode();
                            int quantity;
                            cout << "Nhap so luong: "; cin >> quantity;
                            cin.ignore();
                            sm.addToOrder(barcode, quantity);
                            break;
                        }
                        case 2: {
                            string barcode;
                            cout << "Nhap ma vach can xoa khoi don hang: ";
                            getline(cin, barcode);
                            sm.removeFromOrder(barcode);
                            break;
                        }
                        case 3:
                            sm.displayOrder();
                            break;
                        case 0: break;
                        default: cout << "Lua chon khong hop le!\n";
                    }
                } while (sub != 0);
                break;
            }

            case 3: {
                cout << "\n=== THANH TOÁN ===\n";
                sm.checkout();
                break;
            }

            case 4: {
                int sub;
                do {
                    cout << "\n=== TÌM KIẾM & GIẢM GIÁ ===" << endl;
                    cout << "1. Tìm kiếm sản phẩm theo mã vạch" << endl;
                    cout << "2. Áp dụng voucher giảm giá cho sản phẩm" << endl;
                    cout << "0. Quay lại" << endl;
                    cout << "Chọn: ";
                    cin >> sub;
                    cin.ignore();
                    switch (sub) {
                        case 1: {
                            string barcode;
                            cout << "Nhap ma vach can tim: ";
                            getline(cin, barcode);
                            sm.searchProductByBarcode(barcode);
                            break;
                        }
                        case 2: {
                            string barcode;
                            double percent;
                            cout << "Nhap ma vach san pham: ";
                            getline(cin, barcode);
                            cout << "Nhap phan tram giam gia: ";
                            cin >> percent;
                            cin.ignore();
                            for (auto& p : sm.getProducts()) {
                                if (p.getBarcode() == barcode) {
                                    p.setDiscountPercent(percent);
                                    sm.saveToFile();
                                    cout << "Da ap dung voucher " << percent << "% cho san pham.\n";
                                    break;
                                }
                            }
                            break;
                        }
                        case 0: break;
                        default: cout << "Lua chon khong hop le!\n";
                    }
                } while (sub != 0);
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
