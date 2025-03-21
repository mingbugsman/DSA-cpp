#include <iostream>
#include <vector>
#include <limits>  
using namespace std;



// Ham doc so nguyen an toan
int readInt() {
    int x;
    while (!(cin >> x)) {
        cout << "Nhap khong hop le, vui long nhap mot so nguyen: ";
        cin.clear(); // xoa trang thai error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // bo qua cac ky tu con lai
    }
    return x;
}

//================== BAI 1. QUEUE ==================//

class NodeQueue {
public:
    int data;
    NodeQueue* next;
    NodeQueue(int data) : data(data), next(nullptr) {}
};

class LinkedListQueue {
private:
    NodeQueue* front;
    NodeQueue* rear;
    int count;
public:
    LinkedListQueue() : front(nullptr), rear(nullptr), count(0) {}

    void enqueue(int value) {
        NodeQueue* newNode = new NodeQueue(value);
        if(isEmpty()){
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
        cout << "Enqueue: " << value << "\n";
    }

    int dequeue() {
        if(isEmpty()){
            cout << "Queue rong. Khong the dequeue.\n";
            return -1;
        }
        NodeQueue* temp = front;
        int value = temp->data;
        front = front->next;
        if(front == nullptr)
            rear = nullptr;
        delete temp;
        count--;
        cout << "Dequeue: " << value << "\n";
        return value;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int size() {
        return count;
    }

    void clear() {
        while(!isEmpty()){
            dequeue();
        }
        cout << "Queue da duoc xoa.\n";
    }

    ~LinkedListQueue() {
        clear();
    }

};

// ----- Cai dat Mang cho Queue -----
class ArrayQueue {
private:
    vector<int> arr;
public:
    void enqueue(int value) {
        arr.push_back(value);
        cout << "Enqueue: " << value << "\n";
    }

    int dequeue() {
        if(isEmpty()){
            cout << "Queue rong. Khong the dequeue.\n";
            return -1;
        }
        int value = arr.front();
        arr.erase(arr.begin());
        cout << "Dequeue: " << value << "\n";
        return value;
    }

    bool isEmpty() {
        return arr.empty();
    }

    int size() {
        return arr.size();
    }

    void clear() {
        arr.clear();
        cout << "Queue da duoc xoa.\n";
    }
};

//================== BAI 2. STACK ==================//
// Dinh nghia phan so
class Fraction {
public:
    int num;
    int den;
    Fraction(int n = 0, int d = 1) : num(n), den(d) {
        if(den == 0) {
            cout << "Mau so khong duoc bang 0, tu dong dat thanh 1.\n";
            den = 1;
        }
    }
    void display() const {
        cout << num << "/" << den;
    }
};

// ----- Cai dat DSLK cho Stack -----
class NodeStack {
public:
    Fraction data;
    NodeStack* next;
    NodeStack(const Fraction &f) : data(f), next(nullptr) {}
};

class LinkedListStack {
private:
    NodeStack* top;
    int count;
public:
    LinkedListStack() : top(nullptr), count(0) {}

    void push(const Fraction &f) {
        NodeStack* newNode = new NodeStack(f);
        newNode->next = top;
        top = newNode;
        count++;
        cout << "Push: ";
        f.display();
        cout << "\n";
    }

    Fraction pop() {
        if(isEmpty()){
            cout << "Stack rong. Khong the pop.\n";
            return Fraction(0,1);
        }
        NodeStack* temp = top;
        Fraction value = top->data;
        top = top->next;
        delete temp;
        count--;
        cout << "Pop: ";
        value.display();
        cout << "\n";
        return value;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    int size() {
        return count;
    }

    void clear() {
        while(!isEmpty()){
            pop();
        }
        cout << "Stack da duoc xoa.\n";
    }

    ~LinkedListStack() {
        clear();
    }
};

// ----- Cai dat Mang cho Stack -----
class ArrayStack {
private:
    vector<Fraction> arr;
public:
    void push(const Fraction &f) {
        arr.push_back(f);
        cout << "Push: ";
        f.display();
        cout << "\n";
    }

    Fraction pop() {
        if(isEmpty()){
            cout << "Stack rong. Khong the pop.\n";
            return Fraction(0,1);
        }
        Fraction value = arr.back();
        arr.pop_back();
        cout << "Pop: ";
        value.display();
        cout << "\n";
        return value;
    }

    bool isEmpty() {
        return arr.empty();
    }

    int size() {
        return arr.size();
    }

    void clear() {
        arr.clear();
        cout << "Stack da duoc xoa.\n";
    }
};

void menuQueue() {
    int choice, value, implChoice;
    cout << "Chon cach cai dat Queue:\n";
    cout << "1. DSLK\n2. Mang\n";
    implChoice = readInt();
    
    if(implChoice == 1) {
        LinkedListQueue queue;
        do {
            cout << "\n--- Menu Queue (DSLK) ---\n";
            cout << "1. Enqueue\n2. Dequeue\n3. Kiem tra Queue rong\n4. Dem so luong phan tu\n5. Xoa tat ca phan tu\n0. Thoat\n";
            cout << "Chon: ";
            choice = readInt();
            switch(choice) {
                case 1:
                    cout << "Nhap so can enqueue: ";
                    value = readInt();
                    queue.enqueue(value);
                    break;
                case 2:
                    queue.dequeue();
                    break;
                case 3:
                    cout << (queue.isEmpty() ? "Queue rong.\n" : "Queue khong rong.\n");
                    break;
                case 4:
                    cout << "So phan tu hien co: " << queue.size() << "\n";
                    break;
                case 5:
                    queue.clear();
                    break;
                case 0:
                    cout << "Thoat Queue.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        } while(choice != 0);
    }
    else if(implChoice == 2) {
        ArrayQueue queue;
        do {
            cout << "\n--- Menu Queue (Mang) ---\n";
            cout << "1. Enqueue\n2. Dequeue\n3. Kiem tra Queue rong\n4. Dem so luong phan tu\n5. Xoa tat ca phan tu\n0. Thoat\n";
            cout << "Chon: ";
            choice = readInt();
            switch(choice) {
                case 1:
                    cout << "Nhap so can enqueue: ";
                    value = readInt();
                    queue.enqueue(value);
                    break;
                case 2:
                    queue.dequeue();
                    break;
                case 3:
                    cout << (queue.isEmpty() ? "Queue rong.\n" : "Queue khong rong.\n");
                    break;
                case 4:
                    cout << "So phan tu hien co: " << queue.size() << "\n";
                    break;
                case 5:
                    queue.clear();
                    break;
                case 0:
                    cout << "Thoat Queue.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        } while(choice != 0);
    }
    else {
        cout << "Lua chon khong hop le.\n";
    }
}

void menuStack() {
    int choice, num, den, implChoice;
    cout << "Chon cach cai dat Stack:\n";
    cout << "1. DSLK\n2. Mang\n";
    implChoice = readInt();
    
    if(implChoice == 1) {
        LinkedListStack stack;
        do {
            cout << "\n--- Menu Stack (DSLK) ---\n";
            cout << "1. Push\n2. Pop\n3. Kiem tra Stack rong\n4. Dem so luong phan tu\n5. Xoa tat ca phan tu\n0. Thoat\n";
            cout << "Chon: ";
            choice = readInt();
            switch(choice) {
                case 1:
                    cout << "Nhap tu so: ";
                    num = readInt();
                    cout << "Nhap mau so: ";
                    den = readInt();
                    stack.push(Fraction(num, den));
                    break;
                case 2:
                    stack.pop();
                    break;
                case 3:
                    cout << (stack.isEmpty() ? "Stack rong.\n" : "Stack khong rong.\n");
                    break;
                case 4:
                    cout << "So phan tu hien co: " << stack.size() << "\n";
                    break;
                case 5:
                    stack.clear();
                    break;
                case 0:
                    cout << "Thoat Stack.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        } while(choice != 0);
    }
    else if(implChoice == 2) {
        ArrayStack stack;
        do {
            cout << "\n--- Menu Stack (Mang) ---\n";
            cout << "1. Push\n2. Pop\n3. Kiem tra Stack rong\n4. Dem so luong phan tu\n5. Xoa tat ca phan tu\n0. Thoat\n";
            cout << "Chon: ";
            choice = readInt();
            switch(choice) {
                case 1:
                    cout << "Nhap tu so: ";
                    num = readInt();
                    cout << "Nhap mau so: ";
                    den = readInt();
                    stack.push(Fraction(num, den));
                    break;
                case 2:
                    stack.pop();
                    break;
                case 3:
                    cout << (stack.isEmpty() ? "Stack rong.\n" : "Stack khong rong.\n");
                    break;
                case 4:
                    cout << "So phan tu hien co: " << stack.size() << "\n";
                    break;
                case 5:
                    stack.clear();
                    break;
                case 0:
                    cout << "Thoat Stack.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le.\n";
            }
        } while(choice != 0);
    }
    else {
        cout << "Lua chon khong hop le.\n";
    }
}


int main() {
    int mainChoice;
    do {
        cout << "\n======= MENU CHINH =======\n";
        cout << "1. Queue (so nguyen)\n";
        cout << "2. Stack (phan so)\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        mainChoice = readInt();
        switch(mainChoice) {
            case 1:
                menuQueue();
                break;
            case 2:
                menuStack();
                break;
            case 0:
                cout << "Ket thuc chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le.\n";
        }
    } while(mainChoice != 0);
    
    return 0;
}
