#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <map>
#include <vector>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

bool isBalanced(const string& expression) {
    stack<char> s;
    for (char ch : expression) {
        if (ch == '(') s.push(ch);
        else if (ch == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

void infixToPostfix(const string& expression, string& postfix) {
    stack<char> s;
    for (char ch : expression) {
        if (isdigit(ch)) {
            postfix += ch;
        } else if (ch == '(') {
            s.push(ch);
        } else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // pop '('
        } else { // operator
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top();
                s.pop();
            }
            s.push(ch);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
}

int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0');
        } else { // operator
            int right = s.top(); s.pop();
            int left = s.top(); s.pop();
            switch (ch) {
                case '+': s.push(left + right); break;
                case '-': s.push(left - right); break;
                case '*': s.push(left * right); break;
                case '/': s.push(left / right); break;
            }
        }
    }
    return s.top();
}

int main() {
    string expression;
    char cont;

    do {
        cout << "請輸入運算式：";
        getline(cin, expression);

        if (!isBalanced(expression)) {
            cout << expression << " 運算式的括號不對稱，無法繼續運算" << endl;
            continue;
        }

        cout << expression << " 運算式的左右括號對稱" << endl;

        string postfix;
        infixToPostfix(expression, postfix);
        cout << expression << " 運算式的後序表式法為： " << postfix << endl;

        int result = evaluatePostfix(postfix);
        cout << expression << " 運算式的運算結果為： " << result << endl;

        cout << "是否繼續測試？(Y/N)：";
        cin >> cont;
        cin.ignore(); // 清除輸入緩衝區
    } while (cont == 'Y' || cont == 'y');

    return 0;
}
