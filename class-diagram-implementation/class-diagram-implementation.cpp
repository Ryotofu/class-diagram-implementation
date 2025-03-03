#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

const int MAX_PRODUCTS = 10;
const int MAX_ORDERS = 10;
const int MAX_CART_ITEMS = 10;

class Product {
public:
    string productId, name;
    double price;
    int stockQuantity;
    
    Product() {}
    Product(string id, string n, double p, int qty) : productId(id), name(n), price(p), stockQuantity(qty) {}
};

class ShoppingCart {
private:
    Product items[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int itemCount;

public:
    ShoppingCart() : itemCount(0) {}

    void addProduct(Product& product, int quantity) {
        if (product.stockQuantity >= quantity) {
            product.stockQuantity -= quantity;
            for (int i = 0; i < itemCount; i++) {
                if (items[i].productId == product.productId) {
                    quantities[i] += quantity;
                    cout << "Product added successfully!\n";
                    return;
                }
            }
            if (itemCount < MAX_CART_ITEMS) {
                items[itemCount] = product;
                quantities[itemCount] = quantity;
                itemCount++;
                cout << "Product added successfully!\n";
            } else {
                cout << "Cart is full!\n";
            }
        } else {
            cout << "Insufficient stock!\n";
        }
    }
    
    void viewCart() {
        if (itemCount == 0) {
            cout << "Shopping cart is empty.\n";
            return;
        }
        cout << "\nShopping Cart:\n";
        cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(15) << items[i].productId << setw(15) << items[i].name
                 << setw(10) << items[i].price << quantities[i] << endl;
        }
    }
    
    double checkout() {
        double totalPrice = 0;
        for (int i = 0; i < itemCount; i++) {
            totalPrice += items[i].price * quantities[i];
        }
        itemCount = 0;
        cout << "You have successfully checked out the products!\n";
        return totalPrice;
    }

    Product* getItems() { return items; }
    int* getQuantities() { return quantities; }
    int getItemCount() { return itemCount; }
};

class Order {
public:
    int orderId;
    double totalAmount;
    Product orderItems[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int itemCount;
    
    Order() {}
    Order(int id, double amount, Product items[], int qty[], int count) : orderId(id), totalAmount(amount), itemCount(count) {
        for (int i = 0; i < count; i++) {
            orderItems[i] = items[i];
            quantities[i] = qty[i];
        }
    }
    
    void displayOrder() {
        cout << "\nOrder ID: " << orderId << "\nTotal Amount: " << totalAmount << "\nOrder Details:\n";
        cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Quantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(15) << orderItems[i].productId << setw(15) << orderItems[i].name
                 << setw(10) << orderItems[i].price << quantities[i] << endl;
        }
    }
};

Product products[MAX_PRODUCTS] = {
    Product("P001", "Paper", 20, 10),
    Product("P002", "Pencil", 10, 20),
    Product("P003", "Notebook", 50, 15)
};
int productCount = 3;
Order orders[MAX_ORDERS];
int orderCount = 0;
ShoppingCart cart;

void viewProducts() {
    cout << "\nAvailable Products:\n";
    cout << left << setw(15) << "Product ID" << setw(15) << "Name" << setw(10) << "Price" << "Stock" << endl;
    for (int i = 0; i < productCount; i++) {
        cout << left << setw(15) << products[i].productId << setw(15) << products[i].name << setw(10) << products[i].price << products[i].stockQuantity << endl;
    }
    string productId;
    while (true) {
        cout << "Enter the Product ID to add to cart (or 'exit' to return): ";
        cin >> productId;
        if (productId == "exit") break;
        int quantity;
        cout << "Enter quantity: ";
        cin >> quantity;
        bool found = false;
        for (int i = 0; i < productCount; i++) {
            if (products[i].productId == productId) {
                cart.addProduct(products[i], quantity);
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Invalid Product ID!\n";
        }
        char choice;
        cout << "Do you want to add another product? (Y/N): ";
        cin >> choice;
        if (choice == 'N' || choice == 'n') break;
    }
}

void viewOrders() {
    if (orderCount == 0) {
        cout << "No orders placed yet.\n";
        return;
    }
    for (int i = 0; i < orderCount; i++) {
        orders[i].displayOrder();
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
            case 2: 
                cart.viewCart();
                char confirm;
                cout << "Do you want to check out all the products? (Y/N): ";
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    if (orderCount < MAX_ORDERS) {
                        double total = cart.checkout();
                        if (total > 0) {
                            orders[orderCount] = Order(orderCount + 1, total, cart.getItems(), cart.getQuantities(), cart.getItemCount());
                            orderCount++;
                        }
                    }
                }
                break;
            case 3: viewOrders(); break;
            case 4: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice. Please try again.\n";
        }
    }
}