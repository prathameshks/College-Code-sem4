/*
Consider a scenario for Hospital to cater services to different kinds of
patients as Serious (top priority), b) non-serious (medium priority), c) General
Checkup (Least priority). Implement the priority queue to cater services to the
patients.
*/

#include <iostream>
using namespace std;
#define MAX 10

class pQueue {
   public:
    string arr[MAX];
    int priority[MAX];
    int rear, front;

    pQueue() {
        rear = -1;
        front = -1;
    }

    bool empty() {
        if (rear == -1 && front == -1) {
            return true;
        }
        return false;
    }

    bool is_full() { return rear == MAX - 1; }

    void enqueue(string s, int p) {
        if (is_full()) {
            cout << "Overflow" << endl;
            return;
        }
        if (empty()) {
            rear++;
            arr[rear] = s;
            priority[rear] = p;
            front = 0;
        }

        rear++;
        int i;
        for (i = rear - 1; i >= 0; i--) {
            if (priority[i] < p) {
                arr[i + 1] = arr[i];
                priority[i + 1] = priority[i];
            } else {
                break;
            }
        }
        arr[i + 1] = s;
        priority[i + 1] = p;
    }

    string dequeue() {
        if (empty()) {
            cout << "Queue is empty" << endl;
            return "";
        }
        string data = arr[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
        return data;
    }

    
    void display() {
        if (empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue is:" << endl;
        for (int i = front; i <= rear; i++) {
            cout << priority[i] << " : " << arr[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    // code here
    pQueue q;
    q.enqueue("A",0);
    // q.enqueue("B",0);
    // q.enqueue("C",2);
    // q.enqueue("D",1);
    // q.enqueue("E",2);
    q.enqueue("F",1);
    q.enqueue("G",0);
    q.display();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.display();
    return 0;
}