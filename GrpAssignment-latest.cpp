#include <iostream>
#include <vector>
#include <string>
#include <ctime> 
#include <cstdlib> 
#include <limits> 
#include <algorithm> 

using namespace std;


struct Product {
    string name;
    int quantity;

    Product(const string& n, int q) : name(n), quantity(q) {}
};


class Order {
private:
    string orderID;
    string customerID;
    vector<Product> productList;
    time_t orderDate; 
    string status;

public:
    
    Order(const string& id, const string& custID, const vector<Product>& products, const time_t& date)
        : orderID(id), customerID(custID), productList(products), orderDate(date), status("Processing") {}

    
    string getOrderID() const { return orderID; }
    string getCustomerID() const { return customerID; }
    vector<Product> getProductList() const { return productList; }
    time_t getOrderDate() const { return orderDate; }
    string getStatus() const { return status; }

    
    bool isOrderOlderThan7Days() const {
        time_t currentTime = time(nullptr); 
        return (currentTime - orderDate) > (7 * 24 * 60 * 60); 
    }

    
    void updateStatusIfOlderThan7Days() {
        if (isOrderOlderThan7Days() && status != "Shipped") {
            status = "Shipped";
            cout << "Order status updated to Shipped automatically." << endl;
        }
    }

    
    void editCustomerID(const string& newCustomerID) {
        customerID = newCustomerID;
        cout << "Customer ID updated successfully." << endl;
    }

    
    void editProductList(const vector<Product>& newProductList) {
        productList = newProductList;
        cout << "Product list updated successfully." << endl;
    }

    
    void editStatus(const string& newStatus) {
        status = newStatus;
        cout << "Status updated successfully." << endl;
    }
};


void addOrder(vector<Order>& orders, const Order& newOrder) {
	for (const auto& order : orders) {
        if (order.getOrderID() == newOrder.getOrderID()) {
            cout << "Order ID already exists. Cannot add duplicate order." << endl;
            return; 
        }
    }
    orders.push_back(newOrder);
}


vector<Order>::iterator findOrder(vector<Order>& orders, const string& orderID) {
    for (auto it = orders.begin(); it != orders.end(); ++it) {
        if (it->getOrderID() == orderID)
            return it;
    }
    return orders.end();
}


void deleteOrder(vector<Order>& orders, const string& orderID) {
    auto it = findOrder(orders, orderID);
    if (it != orders.end()) {
        orders.erase(it);
        cout << "Order deleted successfully." << endl;
    } else {
        cout << "Order not found." << endl;
    }
}


void editOrder(vector<Order>& orders, const string& orderID) {
    auto it = findOrder(orders, orderID);
    if (it != orders.end()) {
        Order& order = *it;
        cout << "Editing Order ID: " << orderID << endl;

       
        cout << "What would you like to edit?" << endl;
        cout << "[1] Customer ID" << endl;
        cout << "[2] Product List" << endl;
        cout << "[3] Status" << endl;

        int option;
        cout << "Enter option: ";
        cin >> option;

        switch (option) {
            case 1: { 
                string newCustomerID;
                cout << "Enter new Customer ID: ";
                cin >> newCustomerID;
                order.editCustomerID(newCustomerID);
                break;
            }
            case 2: { 
                int numProducts;
                cout << "Enter new number of products: ";
                cin >> numProducts;

                vector<Product> newProducts;
                cout << "Enter product details (name quantity):" << endl;
                for (int i = 0; i < numProducts; ++i) {
                    string productName;
                    int quantity;
                    cin >> productName >> quantity;
                    newProducts.emplace_back(productName, quantity);
                }

                order.editProductList(newProducts);
                break;
            }
            case 3: { 
                string newStatus;
                cout << "Enter new Status: ";
                cin >> newStatus;
                order.editStatus(newStatus);
                break;
            }
            default:
                cout << "Invalid option." << endl;
        }
    } else {
        cout << "Order not found." << endl;
    }
}


bool compareOrderByID(const Order& order1, const Order& order2) {
    return order1.getOrderID() < order2.getOrderID();
}


void sortOrdersByID(vector<Order>& orders) {
    std::sort(orders.begin(), orders.end(), compareOrderByID);
}


void displayOrder(const Order& order) {
    cout << "Order ID: " << order.getOrderID() << endl;
    cout << "Customer ID: " << order.getCustomerID() << endl;
    cout << "Product List:" << endl;
    for (const auto& product : order.getProductList()) {
        cout << "=> " << product.name << "= " << product.quantity << endl;
    }
    cout << "Status: " << order.getStatus() << endl;
    cout << "---------------------------" << endl;
}


void displayOrders(const vector<Order>& orders) {
    cout << "List of Orders:" << endl;
    cout << endl;
    for (const auto& order : orders) {
        displayOrder(order);
    }
}

int main() {
    vector<Order> orders;

    
    L2: cout << "========================================" << endl;
    cout << "  E-Commerce Order Tracking System " << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "======================" << endl;
    cout << "     Our Services :" << endl;
    cout << "======================" << endl;
    cout << "[1] ADD AN ORDER " << endl;
    cout << "[2] DELETE AN ORDER " << endl;
    cout << "[3] SEARCH AN ORDER " << endl;
    cout << "[4] EDIT AN ORDER " << endl;
    cout << "[5] SORT ORDERS BY ID " << endl;
    cout << "[6] VIEW ALL ORDERS " << endl;
    cout << "[7] Exit " << endl;
    cout << "======================" << endl;
    cout << endl;
    int option;

    while (true) {
        L1: cout << "\nPlease enter an option to Continue :";
        if (cin >> option) {
            if (option >= 1 && option <= 7) {
                break;
            } else {
                cout << "Invalid option. Please enter a number from 1 to 7..." << endl;
            }
        } else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You are not allowed to enter letters. ";
        }
    }

    switch (option) {
        case 1: { 
            L3: cout << "Enter Order ID: ";
			string orderId;
			cin >> orderId;

			bool orderExists = false;
			for (const auto& order : orders) 
			{
    			if (order.getOrderID() == orderId)
				{
        			cout << "Order ID already exists. Cannot add duplicate order." << endl;
        			orderExists = true;
        			break;
    			}
			}	

			if (!orderExists) 
			{
    			cout << "Enter Customer ID: ";
    			string customerId;
    			cin >> customerId;

    			cout << "Enter number of products: ";
    			int numProducts;
    			cin >> numProducts;

    			vector<Product> products;

    			for (int i = 0; i < numProducts; ++i) 
			{
        		string productName;
        		int quantity;
        		cout << "Enter product " << (i + 1) << " (name & quantity) :" << endl;
        		cin >> productName >> quantity;
        		products.emplace_back(productName, quantity);
    		}	

    		time_t orderDate = time(nullptr);
    		Order order(orderId, customerId, products, orderDate);

    		addOrder(orders, order);

    		order.updateStatusIfOlderThan7Days();

    		cout << "Order Added Successfully." << endl;
    		cout << "Order Status: " << order.getStatus() << endl;
			}

			L4: cout << "Do you want to add another order? [Y/N]";
            char dis;
            cin >> dis;
            if (dis == 'Y' || dis == 'y') { 
                cout << endl;
                goto L3;
            } else if (dis == 'N' || dis == 'n') {
                std::system("cls"); 
                goto L2; 
            } else {
                cout << "Invalid selection.";
                goto L4;
            }
            break;
        } 

        case 2: { 
            L5: cout << "Enter Order ID to Delete: ";
            string orderId;
            cin >> orderId;

            deleteOrder(orders, orderId);

            L6: cout << "Do you want to delete another order? [Y/N]";
            char dis;
            cin >> dis;
            if (dis == 'Y' || dis == 'y') { 
                goto L5;
            } else if (dis == 'N' || dis == 'n') {
                std::system("cls"); 
                goto L2; 
            } else {
                cout << "Invalid selection.";
                goto L6;
            }
            break;
        } 

        case 3: { 
            L7: cout << "Enter Order ID to Search: ";
            string orderId;
            cin >> orderId;

            auto it = findOrder(orders, orderId);
            if (it != orders.end()) {
                cout << "Order found:" << endl;
                displayOrder(*it);
            } else {
                cout << "Order not found." << endl;
            }

            L8: cout << "Do you want to search another order? [Y/N]";
            char dis;
            cin >> dis;
            if (dis == 'Y' || dis == 'y') { 
                goto L7;
            } else if (dis == 'N' || dis == 'n') {
                std::system("cls"); 
                goto L2;
            } else {
                cout << "Invalid selection.";
                goto L8;
            }
            break;
        } 

        case 4: { 
            L9: cout << "Enter Order ID to Edit: ";
            string orderId;
            cin >> orderId;

            editOrder(orders, orderId);

            L10: cout << "Do you want to edit another order? [Y/N]";
            char dis;
            cin >> dis;
            if (dis == 'Y' || dis == 'y') { 
                goto L9;
            } else if (dis == 'N' || dis == 'n') {
                std::system("cls"); 
                goto L2; 
            } else {
                cout << "Invalid selection.";
                goto L10;
            }
            break;
        } 

        case 5: {
            sortOrdersByID(orders);
            cout << "Orders sorted by ID." << endl;

           /* 
            if (orders.empty()) {
                cout << "No orders to display." << endl;
            } else {
                displayOrders(orders);4
            }

            
            */
            goto L1;
            break;
        } 
        
        
        case 6:{
        	if (orders.empty()) {
                cout << "No orders to display." << endl;
            } else {
                displayOrders(orders);
            }

            goto L1;
			break;
		}

        case 7: {
            return 0;
            break;
        }
    } 

} 
