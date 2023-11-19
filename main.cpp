#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Product {
private:
    int productID;
    string name;
    float price;
    int quantityInStock;

public:
    Product(const int& id, string& name, float& price, int& quantity)
            : productID(id), name(name), price(price), quantityInStock(quantity) {}

    int getID() const {
        return this->productID;
    }

    string getName() const {
        return this->name;
    }

    void setName(const string& name) {
        this->name = name;
    }

    float getPrice() const {
        return this->price;
    }

    void setPrice(float& price) {
        this->price = price;
    }

    int getQuantityInStock() const {
        return this->quantityInStock;
    }

    void setQuantityInStock(int& quantity) {
        this->quantityInStock = quantity;
    }

    float totalCost() const {
        return this->price * this->quantityInStock;
    }
};

class Electronics : public Product {
private:
    string brand;
    string model;
    float powerConsumption;

public:
    Electronics(const int& id, string& name, float& price, int& quantity, string& brand, string& model, float& power)
            : Product(id, name, price, quantity), brand(brand), model(model), powerConsumption(power) {}

    void displayPowerConsumption() const {
        cout << "Power consumption: " << this->powerConsumption << " Watts" << endl;
    }
};

class Books : public Product {
private:
    string author;
    string genre;
    string ISBN;

public:
    Books(const int& id, string& name, float& price, int& quantity, string& author, string& genre, string& isbn)
            : Product(id, name, price, quantity), author(author), genre(genre), ISBN(isbn) {}

    void displayAuthor() const {
        cout << "Author: " << this->author << endl;
    }
};

class Clothing : public Product {
private:
    string size;
    string color;
    string material;

public:
    Clothing(const int& id, string& name, float& price, int& quantity, string& size, string& color, string& material)
            : Product(id, name, price, quantity), size(size), color(color), material(material) {}

    void displaySize() const {
        cout << "Size: " << this->size << endl;
    }
};

class Order {
private:
    int orderID;
    string customer;
    vector<Product> products;
    float totalCost;
    string orderStatus;

public:
    Order(const int& id, string& customer)
            : orderID(id), customer(customer), totalCost(0), orderStatus("-") {}

    void addProduct(const Product& product) {
        this->products.push_back(product);
        this->totalCost += product.totalCost();
    }

    void changeOrderStatus(const string& status) {
        this->orderStatus = status;
    }

    float calculateTotalCost() const{
        return this->totalCost;
    }

};

class ProductCatalog {
private:
    vector<Product> products;

public:
    ProductCatalog() = default;

    void addProduct(Product& product) {
        this->products.push_back(product);
    }

    void updateProductDetails(const int& id, string& name, float& price, int& quantity) {
        for (auto& product : products) {
            if (product.getID() == id) {
                product.setName(name);
                product.setPrice(price);
                product.setQuantityInStock(quantity);
                break;
            }
        }
    }

    void removeProduct(Product& removeProduct) {
        for (auto iterator = products.begin(); iterator != products.end(); ++iterator) {
            if (iterator->getID() == removeProduct.getID()) {
                products.erase(iterator);
                break;
            }
        }
    }

    void viewProducts() const {
        for (const auto& product : products) {
            cout << "Product ID: " << product.getID() << ", Name: " << product.getName()
                 << ", Price: " << product.getPrice() << "$, Quantity: " << product.getQuantityInStock() << endl;
        }
    }
};

class Inventory {
private:
    vector<Product> products;
    int lowStockThreshold;

public:
    Inventory(const int& threshold) : lowStockThreshold(threshold){}

    void manageStockLevels(const Product& product, int& quantity) {
        bool found = false;
        for (auto& product1 : products) {
            if (product1.getID() == product.getID()) {
                product1.setQuantityInStock(quantity);
                found = true;
                break;
            }
        }
        if (!found) {
            Product newProduct = product;
            newProduct.setQuantityInStock(quantity);
            products.push_back(newProduct);
        }
    }

    void notifyLowStock() const {
        for (const auto& product : products) {
            if (product.getQuantityInStock() < lowStockThreshold) {
                cout << "The product " << product.getName() << " with productID " << product.getID() << " low in stock." << endl;
            }
        }
    }

    vector<Product> needRestocking() const{
        vector<Product> lowStockProducts;
        for (const auto& product : products) {
            if (product.getQuantityInStock() < lowStockThreshold) {
                lowStockProducts.push_back(product);
            }
        }
        return lowStockProducts;
    }

};

class ConfigReader {
public:
    ConfigReader()= default;

    ProductCatalog readConfiguration(const string& filePath) {
        ifstream file(filePath);
        ProductCatalog catalog;
        string line;
        string type, name, brand, model, author, genre, isbn, size, color, material;
        int quantity;
        float price, power;
        int nextID = 123;

        if (!file.is_open()) {
            cout << "Unable to open the file. Try again." << endl;
            return catalog;
        }

        while (getline(file, line)){
            stringstream ss(line);
            getline(ss, type, ',');

            if (type == "Electronics") {
                ss.ignore(1, ',');
                getline(ss, name, ',');
                ss >> price;
                ss.ignore(1, ',');
                ss >> quantity;
                ss.ignore(1, ',');
                getline(ss, brand, ',');
                ss.ignore(1, ',');
                getline(ss, model, ',');
                ss.ignore(1, ',');
                ss >> power;
                Electronics electronic(nextID++, name, price, quantity, brand, model, power);
                catalog.addProduct(electronic);
            }
            else if (type == "Books") {
                ss.ignore(1, ',');
                getline(ss, name, ',');
                ss >> price;
                ss.ignore(1, ',');
                ss >> quantity;
                ss.ignore(1, ',');
                getline(ss, author, ',');
                ss.ignore(1, ',');
                getline(ss, genre, ',');
                ss.ignore(1, ',');
                getline(ss, isbn);
                Books book(nextID++, name, price, quantity, author, genre, isbn);
                catalog.addProduct(book);
            }
            else if (type == "Clothing") {
                ss.ignore(1, ',');
                getline(ss, name, ',');
                ss >> price;
                ss.ignore(1, ',');
                ss >> quantity;
                ss.ignore(1, ',');
                getline(ss, size, ',');
                ss.ignore(1, ',');
                getline(ss, color, ',');
                ss.ignore(1, ',');
                getline(ss, material);
                Clothing clothing(nextID++, name, price, quantity, size, color, material);
                catalog.addProduct(clothing);
            }
        }

        return catalog;
    }
};

int main() {
    ConfigReader reader;
    ProductCatalog  catalog = reader.readConfiguration("C:\\Users\\svobo\\OneDrive\\Desktop\\Yarrochka\\OOPD\\second\\data.txt");
    catalog.viewProducts();

    return 0;
}
