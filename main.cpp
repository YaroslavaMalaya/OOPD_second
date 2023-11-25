#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "Product.h"
using namespace std;

class Electronics : public Product {
private:
    string brand;
    string model;
    float powerConsumption;

public:
    Electronics(const int id, string& name, float price, int quantity, string& brand, string& model, float power)
            : Product(id, name, price, quantity), brand(move(brand)), model(move(model)), powerConsumption(move(power)) {}

    void displayDetails() const override {
        cout << "Product ID: " << this->getID() << ", Name: " << this->getName() << ", Price: " << this->getPrice()
             << "$, Quantity: " << this->getQuantityInStock() << ", Brand: " << this->brand << ", Model: " << this->model
             << ", Power: " << this->powerConsumption << " Watts" << endl;
    }

    string getBrand() const {
        return this->brand;
    }

    string getModel() const {
        return this->model;
    }

};

class Books : public Product {
private:
    string author;
    string genre;
    string ISBN;

public:
    Books(const int id, string& name, float price, int quantity, string& author, string& genre, string& isbn)
            : Product(id, name, price, quantity), author(move(author)), genre(move(genre)), ISBN(move(isbn)) {}

    void displayDetails() const override {
        cout << "Product ID: " << this->getID() << ", Name: " << this->getName() << ", Price: " << this->getPrice()
             << "$, Quantity: " << this->getQuantityInStock() << ", Author: " << this->author << ", Genre: "
             << this->genre<< ", ISBN: " << this->ISBN << endl;
    }

    string getAuthor() const {
        return this->author;
    }

    string getGenre() const {
        return this->genre;
    }

};

class Clothing : public Product {
private:
    string size;
    string color;
    string material;

public:
    Clothing(const int id, string& name, float price, int quantity, string& size, string& color, string& material)
            : Product(id, name, price, quantity), size(move(size)), color(move(color)), material(move(material)) {}

    void displayDetails() const override {
        cout << "Product ID: " << this->getID() << ", Name: " << this->getName() << ", Price: " << this->getPrice()
             << "$, Quantity: " << this->getQuantityInStock() << ", Size: " << this->size << ", Color: "
             << this->color << ", Material: " << this->material << endl;
    }

    string getSize() const {
        return this->size;
    }

    string getColor() const {
        return this->color;
    }

};

class Order {
private:
    int orderID;
    string customer;
    vector<Product*> products;
    float totalCost;
    string orderStatus;

public:
    Order(const int id, string customer) : orderID(move(id)), customer(move(customer)), totalCost(0.0), orderStatus("-"){}

    int getID() const {
        return this->orderID;
    }

    void addProduct(Product& product) {
        this->totalCost += product.getPrice();
        this->products.push_back(&product);
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
    vector<unique_ptr<Product>> products;

public:
    ProductCatalog() = default;

    void addProduct(unique_ptr<Product>& product) {
        this->products.push_back(move(product));
    }

    vector<unique_ptr<Product>>& getProducts() {
        return this->products;
    }

    void updateProductDetails(const int id, string& name, float price, int quantity) {
        for (auto& product : products) {
            if (product->getID() == id) {
                product->setName(name);
                product->setPrice(price);
                product->setQuantityInStock(quantity);
                break;
            }
        }
    }

    void changeQuantityProduct(Product& removeProduct) {
        for (auto iterator = products.begin(); iterator != products.end(); ++iterator) {
            if ((*iterator)->getID() == removeProduct.getID()) {
                cout << removeProduct.getQuantityInStock() << endl;
                int q  = removeProduct.getQuantityInStock() - 1;
                (*iterator)->setQuantityInStock(q);
                break;
            }
        }
    }

    void viewProducts() const {
        for (const auto& product : products) {
            cout << "Product ID: " << product->getID() << ", Name: " << product->getName()
                 << ", Price: " << product->getPrice() << "$, Quantity: " << product->getQuantityInStock() << endl;
        }
    }

    void viewCertainProduct(const string& criteria) {
        stringstream ss(criteria);
        string category, attribute;
        getline(ss, category, ' ');
        getline(ss, attribute);

        for (const auto& product : products) {
            if (category == "Electronics") {
                const auto* electronics = dynamic_cast<const Electronics*>(product.get());
                if (electronics && (attribute.empty() || electronics->getName() == attribute ||
                                    electronics->getModel() == attribute || electronics->getBrand() == attribute)) {
                    electronics->displayDetails();
                }
            } else if (category == "Books" ) {
                const auto *book = dynamic_cast<const Books *>(product.get());
                if (book && (attribute.empty() || book->getName() == attribute || book->getAuthor() == attribute
                             || book->getGenre() == attribute)) {
                    book->displayDetails();
                }
            } else if (category == "Clothing") {
                const auto* clothing = dynamic_cast<const Clothing*>(product.get());
                if (clothing &&( attribute.empty() || clothing->getName() == attribute || clothing->getColor() == attribute
                                 || clothing->getSize() == attribute)) {
                    clothing->displayDetails();
                }
            }}

    }
};

class Inventory {
private:
    vector<Product*> products;
    int lowStockThreshold;

public:
    Inventory(const int& threshold) : lowStockThreshold(threshold){}

    void manageStockLevels(Product& product) {
        bool found = false;
        for (const auto& product1 : products) {
            if (product1->getID() == product.getID()) {
                cout << product1->getQuantityInStock() << endl;
                int q = product1->getQuantityInStock() - 1;
                product1->setQuantityInStock(q);
                found = true;
                break;
            }
        }
        if (!found) {
            products.push_back(&product);
        }
    }

    void notifyLowStock() const {
        bool found = false;
        for (const auto& product : products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                found = true;
                cout << "The product " << product->getName() << " with productID " << product->getID() << " low in stock." << endl;
            }
        }
        if (!found){
            cout << "No restocking required" << endl;
        }
    }

    vector<Product*> needRestocking() {
        vector<Product*> lowStockProducts;
        for (const auto& product : products) {
            if (product->getQuantityInStock() < lowStockThreshold) {
                lowStockProducts.push_back(product);
            }
        }
        return lowStockProducts;
    }

};

class Customer {
private:
    string name;
    vector<Product*> shoppingCart;
    vector<Order> orders;

public:
    Customer(const string& name) : name(name) {}

    void addToCart(Product& product) {
        this->shoppingCart.push_back(&product);
    }

    string getName() const{
        return this->name;
    }

    void checkout(const int& id) {
        if (this->shoppingCart.empty()) {
            cout << "Shopping cart is empty!" << endl;
            return;
        }

        Order newOrder(id, name);
        for (auto& product : this->shoppingCart) {
            newOrder.addProduct(*product);
        }

        newOrder.changeOrderStatus("in process");
        this->orders.push_back(move(newOrder));
        this->shoppingCart.clear();
        cout << "The order received!" << endl;
        cout << "Confirmation order ID: " << id << endl;
    }

    void viewOrderHistory() const {
        if (this->orders.empty()) {
            cout << "No order history available." << endl;
            return;
        }

        cout << "Order history for " << this->name << ":\n";
        for (const auto& order : this->orders) {
            cout << "Order ID: " << order.getID() << " Total Cost: " << order.calculateTotalCost() << endl;
        }
    }

    vector<Product*>& getShoppingCart() {
        return this->shoppingCart;
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
                auto electronic = make_unique<Electronics>(nextID++, name, price, quantity, brand, model, power);
                catalog.addProduct((unique_ptr<Product> &) move(electronic));
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
                auto book = make_unique<Books>(nextID++, name, price, quantity, author, genre, isbn);
                catalog.addProduct((unique_ptr<Product> &) move(book));
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
                auto clothing = make_unique<Clothing>(nextID++, name, price, quantity, size, color, material);
                catalog.addProduct((unique_ptr<Product> &) move(clothing));
            }
        }

        return catalog;
    }
};

class Shopping {
private:
    ProductCatalog catalog;
    Inventory inventory;
    vector<unique_ptr<Customer>> customers;
    int orderId = 1;

    void loadCatalog(const string& filePath) {
        ConfigReader reader;
        catalog = reader.readConfiguration(move(filePath));
    }

public:
    Shopping(string& catalogFilePath, int lowStockThreshold) : inventory(move(lowStockThreshold)) {
        loadCatalog(catalogFilePath);
        for (auto& product : catalog.getProducts()) {
            inventory.manageStockLevels(*product);
        }
    }

    void showAll() {
        catalog.viewProducts();
    }

    void showCertain(string& criteria) {
        catalog.viewCertainProduct(criteria);
    }

    void addProduct() {
        string customerName;
        int productId;
        cout << "Enter your name and the product ID: " << endl;
        cin >> customerName >> productId;

        unique_ptr<Customer>* existingCustomer = nullptr;
        for (auto& customer : customers) {
            if (customer->getName() == customerName) {
                existingCustomer = &customer;
                break;
            }
        }

        if (!existingCustomer) {
            customers.push_back(make_unique<Customer>(customerName));
            existingCustomer = &customers.back();
        }

        bool productAdded = false;
        for (auto& product : catalog.getProducts()) {
            if (product->getID() == productId) {
                (*existingCustomer)->addToCart(*product);
                cout << "The product added to your cart successfully!" << endl;
                productAdded = true;
                break;
            }
        }

        if (!productAdded) {
            cout << "Product ID not found." << endl;
        }

        cin.ignore();
    }

    void showCart(){
        string customerName;
        cout << "Enter your name: " << endl;
        cin >> customerName;

        bool found = false;
        for (auto& customer : customers) {
            if (customer->getName() == customerName){
                found = true;
                for (auto& product : customer->getShoppingCart())
                {
                    cout << "Product ID: " << product->getID() << ", Name: " << product->getName() << ", Price: $" << product->getPrice() << endl;
                }
                break;
            }
        }
        if (!found){
            cout << "Incorrect customer name." << endl;
        }
        cin.ignore();
    }

    void checkout() {
        string customerName;
        cout << "Enter your name: " << endl;
        cin >> customerName;

        bool found = false;
        for (auto& customer : customers) {
            if (customer->getName() == customerName){
                found = true;
                for (auto product : customer->getShoppingCart())
                {
                    inventory.manageStockLevels(*product);
                }
                customer->checkout(orderId);
                orderId++;
                break;
            }
        }
        if (!found){
            cout << "Incorrect customer name." << endl;
        }

        cout << "\n------ Notification ------" << endl;
        inventory.notifyLowStock();
        cout << "-----------------------------------" << endl;
        cin.ignore();
    }

    void viewOrderHistory() {
        string customerName;
        cout << "Enter your name: " << endl;
        cin >> customerName;

        bool found = false;
        for (auto& customer : customers) {
            if (customer->getName() == customerName){
                found = true;
                customer->viewOrderHistory();
                break;
            }
        }
        if (!found){
            cout << "Incorrect customer name." << endl;
        }
        cin.ignore();
    }

    void needRestocking() {
        auto productsToRestock = inventory.needRestocking();
        if (productsToRestock.empty()) {
            cout << "No items need restocking." << endl;
        } else {
            cout << "Items that need to be restocked: " << endl;
            for (const auto& product : productsToRestock) {
                cout << "Product ID: " << product->getID()
                     << ", Name: " << product->getName()
                     << ", Current Stock: " << product->getQuantityInStock()
                     << endl;
            }
        }
    }
};

class ConsoleLogic{
private:
    Shopping shop;
    bool isRunning;

public:
    ConsoleLogic(string& filePath, int lowInStock) : shop(filePath, move(lowInStock)), isRunning(true) {};

    void run() {
        string command;
        while (isRunning) {
            cout << "\nAll commands:\n"
                 << " -show all;\n"
                 << " -show 'category attribute';\n"
                 << " -add a product;\n"
                 << " -check the cart;\n"
                 << " -checkout;\n"
                 << " -view order history;\n"
                 << " -need restocking;\n"
                 << " -exit;\n"
                 << "Enter command: " << endl;
            getline(cin, command);

            if (command == "show all") {
                shop.showAll();
            } else if (command.rfind("show ", 0) == 0) {
                std::string criteria = command.substr(5);
                shop.showCertain(criteria);
            } else if (command == "add a product") {
                shop.addProduct();
            } else if (command == "check the cart") {
                shop.showCart();
            } else if (command == "checkout") {
                shop.checkout();
            } else if (command == "view order history") {
                shop.viewOrderHistory();
            } else if (command == "need restocking") {
                shop.needRestocking();
            } else if (command == "exit") {
                isRunning = false;
            } else {
                cout << "Invalid command." << endl;
            }
        }
    }
};

int main() {
    string path = "/Users/Yarrochka/Mine/Study/OOPD/second/data.txt";
    // string path = "C:\\Users\\svobo\\OneDrive\\Desktop\\Yarrochka\\OOPD\\second\\data.txt";
    ConsoleLogic console(path, 6);
    console.run();

    return 0;
}