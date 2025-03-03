#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Product {
public:
    string productId, name;
    double price;
    int stockQuantity;
    
    Product(string id, string n, double p, int qty) : productId(id), name(n), price(p), stockQuantity(qty) {}
};

class ShoppingCart {
private:
    vector<pair<Product, int>> items;

public:
    void addProduct(Product& product, int quantity) {
        if (product.stockQuantity >= quantity) {
            product.stockQuantity -= quantity;
            bool found = false;
            for (auto& item : items) {
                if (item.first.productId == product.productId) {
                    item.second += quantity;
                    found = true;
                    break;
                }
            }
            if (!found) {
                items.push_back(make_pair(product, quantity));
            }
            cout << "Product added successfully!\n";
        } else {
            cout << "Insufficient stock!\n";
        }
    }
    
    void viewCart() {
        if (items.empty()) {
            cout << "Shopping cart is empty.\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (auto& item : items) {
            cout << left << setw(15) << item.first.productId << setw(15) << item.first.name
                 << setw(10) << item.first.price << item.second << endl;
        }
    }
    
    double checkout() {
        double totalPrice = 0;
        for (auto& item : items) {
            totalPrice += item.first.price * item.second;
        }
        items.clear();
        cout << "You have successfully checked out the products!\n";
        return totalPrice;
    }
};

class Order {
public:
    int orderId;
    double totalAmount;
    vector<pair<Product, int>> orderItems;
    
    Order(int id, double amount, vector<pair<Product, int>> items) : orderId(id), totalAmount(amount), orderItems(items) {}
    
    void displayOrder() {
        cout << "\nOrder ID: " << orderId << "\nTotal Amount: " << totalAmount << "\nOrder Details:\n";
        cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (auto& item : orderItems) {
            cout << left << setw(15) << item.first.productId << setw(15) << item.first.name
                 << setw(10) << item.first.price << item.second << endl;
        }
    }
};

vector<Product> products = {
    Product("P001", "Paper", 20, 10),
    Product("P002", "Pencil", 10, 20),
    Product("P003", "Notebook", 50, 15)
};
vector<Order> orders;
ShoppingCart cart;

void viewProducts() {
    cout << "\nAvailable Products:\n";
    cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Stock" << endl;
    for (auto& p : products) {
        cout << left << setw(15) << p.productId << setw(15) << p.name << setw(10) << p.price << p.stockQuantity << endl;
    }
    string productId;
    while (true) {
        cout << "Enter the Product ID to add to cart (or 'exit' to return): ";
        cin >> productId;
        if (productId == "exit") break;
        int quantity;
        cout << "Enter quantity: ";
        cin >> quantity;
        auto it = find_if(products.begin(), products.end(), [&](Product& p) { return p.productId == productId; });
        if (it != products.end()) {
            cart.addProduct(*it, quantity);
        } else {
            cout << "Invalid Product ID!\n";
        }
    }
}

void viewOrders() {
    if (orders.empty()) {
        cout << "No orders placed yet.\n";
        return;
    }
    for (auto& order : orders) {
        order.displayOrder();
        cout << "\n";
    }
}

int main() {
    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\n";
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: viewProducts(); break;
            case 2: cart.viewCart();
                if (!cart.checkout()) break;
                orders.emplace_back(orders.size() + 1, cart.checkout(), vector<pair<Product, int>>());
                break;
            case 3: viewOrders(); break;
            case 4: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Please try again.\n";
        }
    }
}