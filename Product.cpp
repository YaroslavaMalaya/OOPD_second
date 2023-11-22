#include "Product.h"

Product::Product(const int id, string& name, float price, int quantity)
        : productID(move(id)), name(move(name)), price(move(price)), quantityInStock(move(quantity)) {}

int Product::getID() const {
    return this->productID;
}

string Product::getName() const {
    return this->name;
}

void Product::setName(const string& name) {
    this->name = name;
}

float Product::getPrice() const {
    return this->price;
}

void Product::setPrice(float price) {
    this->price = price;
}

int Product::getQuantityInStock() const {
    return this->quantityInStock;
}

void Product::setQuantityInStock(int quantity) {
    this->quantityInStock = quantity;
}

float Product::totalCost() const {
    return this->price * this->quantityInStock;
}

Product::~Product() = default;