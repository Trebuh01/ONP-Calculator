#include <iostream>
#include "Vector.h"
#include "String.h"
#include "Stack.h"

using namespace std;

Vector<String> divideIntoTokens(const String& str) {
    Vector<String> tokens;
    String currentToken = "";
    for (size_t i = 0; i < str.size(); ++i) {
        if (isdigit(str[i]) || (str[i] == 'M' && (str.substr(i, 3) == "MIN" || str.substr(i, 3) == "MAX"))) {
            if (str[i] == 'M') {
                
                if(str[i+2] == 'X')currentToken = "X";
                else currentToken = "M";
                
                tokens.push(currentToken);
                i += 2; 
                currentToken = ""; 
            }
            else {
              
                currentToken = currentToken + str[i];
            }
        }
        else {
            if (!currentToken.empty()) {
                tokens.push(currentToken);
                currentToken = ""; 
            }
            if (str[i] != ' ') {
               
                char opStr[2] = { str[i], '\0' }; 
                tokens.push(String(opStr));
            }
        }
    }
    if (!currentToken.empty()) {
        tokens.push(currentToken);
    }
    return tokens;
}
bool checkIfOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == 'N' || c == 'I' || c== 'M' || c =='X';
}

int determineOperatorPriority(char op) {
    switch (op) {
    case '+': case '-': return 1;
    case '*': case '/': return 2;
    case 'N': 
    case 'I': 
    case 'M': 
        return 3;
    default: return 0;
    }
}
void incrementLastOperator(Vector<int>& parametry) {
    if (!parametry.size()) {
        throw std::runtime_error("Vector is empty");
    }
    int ile = parametry.get(parametry.size() - 1);
    ile++;
    parametry.pop();
    parametry.push(ile);
}

String convertInfixToPostfix(const String& infix) {
    Stack<char> operators;
    String postfix = "";
    Vector<String> tokens = divideIntoTokens(infix);

    Vector<int> parametry;
    bool czy_dodawac = true;
    for (int i = 0; i < tokens.size(); ++i) {
        String token = tokens[i];
        if (isdigit(token[0])) { 
            postfix = postfix + token + " ";
            if (parametry.size()&& czy_dodawac&& !operators.isEmpty() && operators.top() != '+' && operators.top() != '-' && operators.top() != '/' && operators.top() != '*') {
                
                incrementLastOperator(parametry);
            }

        }
        else if (token == "(") {
            operators.push('(');
            if (i > 0 && (tokens[i - 1] == "F" )) {    
                if (parametry.size()&&czy_dodawac) {
                    incrementLastOperator(parametry);
                }
                czy_dodawac = false;
            }
            if (i > 0 && (tokens[i - 1] == "M" || tokens[i - 1] == "X")) {
                if (parametry.size()) {
                    if (!operators.isEmpty() && operators.top() == '(')
                    {
                        char nawias = operators.pop();
                        char znak = operators.pop();
                        char znak2 = operators.pop();
                        if (!operators.isEmpty() && operators.top() != 'I'&&znak2!='-' && znak2 != '+' && znak2 != '/' && znak2 != '*')
                        {
                            incrementLastOperator(parametry);
                        }
                        operators.push(znak2);
                        operators.push(znak);
                        operators.push(nawias);
                    }
                    
                }
                parametry.push(0);
                czy_dodawac = true;
            }
            char nawias = operators.pop();
            if (!operators.isEmpty() && ( operators.top() == '-' || operators.top() == '*' || operators.top() == '/' || operators.top() == '+'))czy_dodawac = false;
            operators.push(nawias);
        }
        else if (token == ",") {
            while (!operators.isEmpty() && operators.top() == 'N')
            {
                postfix = postfix + "N ";
                operators.pop();
            }
            while (!operators.isEmpty() && (operators.top() == '+'|| operators.top() == '-' || operators.top() == '/' || operators.top() == '*'))
            {
                postfix = postfix + operators.top() + " ";
                operators.pop();
            }
            

        }
        else if (token == ")") {
            while (!operators.isEmpty() && operators.top() != '(') {
                if (operators.top() == 'I') {
                    postfix = postfix + "IF ";
                    operators.pop(); 
                    czy_dodawac = true;

                }
                else if (operators.top() == 'M' || operators.top() == 'X') {
                    int count = parametry.get(parametry.size() - 1);
                    parametry.pop();
                    String countString = String::to_string(count);
                    postfix = postfix + (operators.top() == 'M' ? "MIN" : "MAX") + countString + " ";
                    operators.pop();
                }
                else {
                    postfix = postfix + operators.top() + " ";
                    operators.pop();
                    
                }
            }
            operators.pop(); // Usuwamy '(' ze stosu
            if (!operators.isEmpty() && operators.top() == 'N')
            {
                postfix = postfix + "N ";
                operators.pop();
            }
            else if (!operators.isEmpty() && operators.top() == 'I') {
                postfix = postfix + "IF ";
                operators.pop();
                czy_dodawac = true;
                
                if (!operators.isEmpty() && operators.top() == 'N')
                {
                    postfix = postfix + "N ";
                    operators.pop();
                }
                if (!operators.isEmpty() && operators.top() == '(')
                {
                    operators.pop();
                    if (!operators.isEmpty() && operators.top() == 'I')czy_dodawac = false;
                    operators.push('(');
                }
            }
            else if (!operators.isEmpty() && (operators.top() == 'M' || operators.top() == 'X')) {
                int count = parametry.get(parametry.size() - 1);
                parametry.pop();
                String countString = String::to_string(count);
                postfix = postfix + (operators.top() == 'M' ? "MIN" : "MAX") + countString + " ";
                operators.pop();
                if (!operators.isEmpty() && operators.top() == '(') {
                    operators.pop();  
                    if (!operators.isEmpty() && operators.top() == 'I') czy_dodawac = false;
                    operators.push('(');  
                }
            }
            else if (!operators.isEmpty() && operators.top() == '(')
            {
                char nawias = operators.pop();
                if (!operators.isEmpty() && operators.top() == 'X')
                {
                    if (i < tokens.size() - 1 && tokens[i + 1] == ',' )czy_dodawac = true;
                }
                operators.push(nawias);
            }
           
        }
        else if (checkIfOperator(token[0])) {
            while (!operators.isEmpty() && determineOperatorPriority(operators.top()) >= determineOperatorPriority(token[0])&&token[0]!='I' && token[0] != 'M' && token[0] != 'X') {
                if (operators.top() == 'I') {
                    postfix = postfix + "IF ";
                    operators.pop();
                    czy_dodawac = true;
                }
                else {
                    if (operators.top() == 'N' && token[0] == 'N')break;
                    postfix = postfix + operators.top() + " ";
                    operators.pop();
                }
            }
            operators.push(token[0]);
        }
    }

    // Opróżniamy stos operatorów
    while (!operators.isEmpty()) {
        if (operators.top() == 'I') {
            postfix = postfix + "IF ";
            operators.pop();
            
        }
        else if (operators.top() == 'M' || operators.top() == 'X') {
            int count = parametry.get(parametry.size() - 1);
            parametry.pop();
            String countString = String::to_string(count);
            postfix = postfix + operators.top() == 'M' ? "MIN" : "MAX";
            postfix = postfix + countString + " ";
        }
        else {
            postfix = postfix + operators.top() + " ";
            operators.pop();
        }
    }

    return postfix;
}

void calculatePostfixValue(const String& postfix) {
    Stack<int> stack;
    Vector<String> tokens = divideIntoTokens(postfix);
    for (int i = 0; i < tokens.size(); ++i) {
        String token = tokens[i];
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            stack.push(token.to_int());
        }
        else if (token == "N")
        {
            if (stack.isEmpty()) {
                cout << "ERROR: Stack is empty for negation" << endl;
                return;
            }
            
            cout << "N ";
            stack.print();
            cout << endl;
            int a = stack.pop();
            stack.push(-a);
        }
        else if (token == "I") {
            if (stack.size() < 3) {
                cout << "ERROR: Not enough operands for IF operation" << endl;
                return;
            }
            cout << "IF ";
            stack.print();
            int c = stack.pop();
            int b = stack.pop();
            int a = stack.pop();

            stack.push(a > 0 ? b : c);
            cout << endl;
        }
        else if (token == "X"|| token == "M") {
            ++i;
            String dlugosc = tokens[i];

            if (stack.size() < dlugosc.to_int()) {
                cout << "ERROR: Not enough operands for " << (token == "X" ? "MAX" : "MIN") << " operation" << endl;
                return;
            }
            cout << (token == "X" ? "MAX" : "MIN") << dlugosc << " ";
            stack.print();
            cout << endl;
            int result;
            if (token == "X")
            {
                result = 0;
                for (int j = 0; j < dlugosc.to_int(); ++j)
                {
                    int val = stack.pop();
                    if (val > result) {
                        result = val;
                    }
                }
            }
            if (token == "M")
            {
                result = INT_MAX;
                for (int j = 0; j < dlugosc.to_int(); ++j)
                {
                    int val = stack.pop();
                    if (val < result) {
                        result = val;
                    }
                }
            }


            stack.push(result); 
            
            
        }
        else if (checkIfOperator(token[0])) {
            if (stack.size() < 2) { 
                cout << "ERROR: Not enough operands for operation " << token[0] << endl;
                return;
            }
            int b = stack.pop();
            int a = stack.pop();
            cout << token[0] << " " << b << " " << a<< " ";
            stack.print();
            cout << endl;
            int result;
            switch (token[0]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/':
                if (b == 0) {
                    cout << "ERROR" << endl;
                    return;
                }
                result = a / b; break;
            }
            stack.push(result);
        }
    }

    if (!stack.isEmpty()) cout << stack.top() << endl;
}

int main() {
    int n;
    cin >> n;
    cin.ignore(); 

    for (int i = 0; i < n; ++i) {
        char expressionBuffer[1000000]; 
        int index = 0; 

        
        while (cin.get(expressionBuffer[index]) && expressionBuffer[index] != '.' && index < 999999) {
            if (expressionBuffer[index] != '\n') { 
                ++index;
            }
        }
        expressionBuffer[index] = '\0'; 

        
        String expression(expressionBuffer);

        try {
            String postfix = convertInfixToPostfix(expression);
            cout << postfix << endl;
            calculatePostfixValue(postfix);
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }

        cin.ignore(10000, '\n'); 
    }

    return 0;
}
