#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Product {
    std::string type;
    std::string name;
    int price;
};

bool compare(const Product& a, const Product& b);
void MySort(std::vector<Product>& product);

std::ostream& operator<<(std::ostream& os, const Product& p) {
    return os << "(" + p.type << ", " << p.name << ", " << p.price << ")";
}

int main() {
    std::vector<Product> products = {
        {"TypeA", "Name1", 30},
        {"TypeB", "Name2", 50},
        {"TypeC", "Name2", 90},
        {"TypeC", "Name1", 70},
        {"TypeA", "Name1", 20},
        {"TypeA", "Name2", 10},
        {"TypeC", "Name1", 50},
        {"TypeB", "Name2", 30},
        {"TypeB", "Name1", 20},
    };
    
    MySort(products);
    
    for (const auto& p : products) {
        std::cout << p << std::endl;
    }
}

bool compare(const Product& a, const Product& b) {
    if (a.type != b.type) {
        return a.type < b.type;
    }
    if (a.name != b.name) {
        return a.name < b.name;
    }
    
    return a.price < b.price;
}

void MySort(std::vector<Product>& product) {
    std::sort(product.begin(), product.end(), compare);
}
