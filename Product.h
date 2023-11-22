#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;

class Product {
private:
    int productID;
    string name;
    float price;
    int quantityInStock;

public:
    Product(const int id, string& name, float price, int quantity);
    int getID() const;
    string getName() const;
    void setName(const string& name);
    float getPrice() const;
    void setPrice(float price);
    int getQuantityInStock() const;
    void setQuantityInStock(int quantity);
    float totalCost() const;
    virtual ~Product();
};

#endif
