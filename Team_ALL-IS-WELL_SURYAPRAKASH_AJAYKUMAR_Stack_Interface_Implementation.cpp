#include <iostream>
using namespace std;

template <typename T>
class Stack {
    private:
        T arr[100000];
        int stack_size;
        int curr_position;
   
    public:
        Stack() : stack_size(100000), curr_position(-1) { }

        T top_element() {
            if(curr_position >= 0)
                return arr[curr_position];
            else
                throw out_of_range("Stack is empty");
        }

        void push_element(T element) {
            if(curr_position < stack_size - 1){
                arr[++curr_position] = element;
            } else {
                cout << "Stack overflow" << endl;
            }
        }

        void pop_element() {
            if(curr_position >= 0){
                --curr_position;
            } else {
                cout << "Stack underflow" << endl;
            }
        }

        int current_size() {
            return curr_position + 1;
        }

        bool is_empty() {
            return curr_position == -1;
        }
};

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

char associativity(char c) {
    if (c == '^')
        return 'R'; 
    return 'L'; 
}

string infixToPostfix(string s) {
    Stack<char> ele_stack;
    string result;

    for (int i = 0; i < s.length(); i++) {
        char c = s[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;

        else if (c == '(')
            ele_stack.push_element('(');

        else if (c == ')') {
            while (!ele_stack.is_empty() && ele_stack.top_element() != '(') {
                result += ele_stack.top_element();
                ele_stack.pop_element();
            }
            ele_stack.pop_element();
        }

        else {
            while (!ele_stack.is_empty() && precedence(s[i]) < precedence(ele_stack.top_element()) ||
                !ele_stack.is_empty() && precedence(s[i]) == precedence(ele_stack.top_element()) &&
                associativity(s[i]) == 'L') {
                result += ele_stack.top_element();
                ele_stack.pop_element();
            }
            ele_stack.push_element(c);
        }
    }

    while (!ele_stack.is_empty()) {
        result += ele_stack.top_element();
        ele_stack.pop_element();
    }
    return result;
}

bool areBracketsBalanced(string expr) {
    Stack<int> encoding_stack;

    for (int i = 0; i < expr.size(); i++) {
        if (expr[i] == '(')
            encoding_stack.push_element(1);
        else if (expr[i] == '{')
            encoding_stack.push_element(2);
        else if (expr[i] == '[')
            encoding_stack.push_element(3);
        else if ((expr[i] == ')' && !encoding_stack.is_empty() && encoding_stack.top_element() == 1) ||
                 (expr[i] == '}' && !encoding_stack.is_empty() && encoding_stack.top_element() == 2) ||
                 (expr[i] == ']' && !encoding_stack.is_empty() && encoding_stack.top_element() == 3)) {
            encoding_stack.pop_element();
        } else {
            return false;
        }
    }

    return encoding_stack.is_empty();
}

int main() {
    string infix;
    cin >> infix;

    string postfix = infixToPostfix(infix);
    cout << "Postfix is " << postfix << endl;

    string expr;
    cin >> expr;

    if (areBracketsBalanced(expr)){
        cout << "The string " << expr << " is Balanced" << endl;
    }
    else{
        cout << "The string " << expr << " is Not Balanced" << endl;
    }

    return 0;
}




