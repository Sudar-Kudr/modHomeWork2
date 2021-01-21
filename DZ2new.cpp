#include <iostream>
#include <vector>
#include <string>
#include <cmath>

float build_sk (std::string str, int i) {
    bool flag = false;
    bool key = true;
    char symbol = ' ';
    float answer = 0;
    float b = 0;
    float x = 0;
    int k;
    
    if (str[i] == '-') {
        flag = true;
        i++;
    }
    float a = 0;
    
    if (str[i] == 'x') {
        if (key == true) {
            std::cout << "Введите х\n" ;
            std::cin >> x;
            key = false;
        }
        a = x;
        i++;
    }
    else if (str[i] == 'P') {
        a = M_PI;
        i++;
    }
    else if (str[i] == 'e') {
        a = M_E;
        i++;
    }
    else if (str[i] >= '0' && str[i] <= '9') {
        while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
            a = a * 10 + str[i] - '0';
            i++;
        }
    }
    else {
        std ::cout << "В выражении ошибка!\n";
        return -1000000;
    }
    if (i >= str.length() || str[i] == ')' ) {
        if (symbol == '+') {
            answer += a;
        }
        else if (symbol == '-') {
            answer -= a;
        }
        else {
            answer = a;
        }
        return answer;
    }
    if (str[i] == '.') {
        k = 1;
        i++;
        while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
            a = a + (str[i] - '0')/(pow(10,k));
            i++;
            k++;
        }
    }
    
    std::cout << x << " = x \n";
    if (flag == true) {
        a *= -1;
    }
    while (i < str.length() && str[i] != ')') {
    while (str[i] == '*' || str[i] == '/' || str[i] == '^') {
        if (str[i] == '/' && str[i+1] == '0' && x == 0) {
            std::cout << "Нельзя делить на ноль\n";
            return -1000000;
        }
        if (str[i] == '*') {
            if (str[i+1] == '(') {
                a = a * build_sk (str, i+2);
                while (str[i] != ')' && i < str.length()) {
                    i++;
                }
                i++;
                if (i >= str.length()) {
                    if (symbol == '+') {
                        answer += a;
                    }
                    else if (symbol == '-') {
                        answer -= a;
                    }
                    else {
                        answer = a;
                    }
                    return answer;
                }
            }
            else {
                i++;
                b = 0;
                if (str[i] == 'x') {
                    if (key == true) {
                        std::cout << "Введите х\n" ;
                        std::cin >> x;
                        key = false;
                    }
                    b = x;
                    i++;
                }
                else if (str[i] == 'P') {
                    b = M_PI;
                    i++;
                }
                else if (str[i] == 'e') {
                    b = M_E;
                    i++;
                }
                else if (str[i] >= '0' && str[i] <= '9'){
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                if (i >= str.length() || str[i] == ')' ) {
                    a = a * b;
                    if (symbol == '+') {
                           answer += a;
                       }
                       else if (symbol == '-') {
                           answer -= a;
                       }
                       else {
                           answer = a;
                       }
                    return answer;
                }
                if (str[i] == '.' && str[i+1] >= '0' && str[i+1] <= '9') {
                    k = 1;
                    i++;
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b + (str[i] - '0')/(pow(10,k));
                        i++;
                        k++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                a = a * b;
            }
        }
        else  if (str[i] == '/') {
            if (str[i+1] == '(') {
                a = a / build_sk (str, i+2);
                while (str[i] != ')' && i < str.length()) {
                    i++;
                }
                i++;
                if (i >= str.length()) {
                    if (symbol == '+') {
                        answer += a;
                    }
                    else if (symbol == '-') {
                        answer -= a;
                    }
                    else {
                        answer = a;
                    }
                    return answer;
                }
            }
            else {
                i++;
                b = 0;
                if (str[i] == 'x') {
                    if (key == true) {
                        std::cout << "Введите х\n" ;
                        std::cin >> x;
                        key = false;
                    }
                    b = x;
                    i++;
                }
                else if (str[i] == 'P') {
                    b = M_PI;
                    i++;
                }
                else if (str[i] == 'e') {
                    b = M_E;
                    i++;
                }
                else if (str[i] >= '0' && str[i] <= '9'){
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                if (i >= str.length() || str[i] == ')' ) {
                    a = a / b;
                    if (symbol == '+') {
                           answer += a;
                       }
                       else if (symbol == '-') {
                           answer -= a;
                       }
                       else {
                           answer = a;
                       }
                    return answer;
                }
                if (str[i] == '.' && str[i+1] >= '0' && str[i+1] <= '9') {
                    k = 1;
                    i++;
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b + (str[i] - '0')/(pow(10,k));
                        i++;
                        k++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                a = a / b;
            }
        }
        else if (str[i] == '^') {
            if (str[i+1] == '(') {
                a = pow(a,build_sk (str, i+2));
                while (str[i] != ')' && i < str.length()) {
                    i++;
                }
                i++;
                if (i >= str.length()) {
                    if (symbol == '+') {
                        answer += a;
                    }
                    else if (symbol == '-') {
                        answer -= a;
                    }
                    else {
                        answer = a;
                    }
                    return answer;
                }
            }
            else {
                i++;
                b = 0;
                if (str[i] == 'x') {
                    if (key == true) {
                        std::cout << "Введите х\n" ;
                        std::cin >> x;
                        key = false;
                    }
                    b = x;
                    i++;
                }
                else if (str[i] == 'P') {
                    b = M_PI;
                    i++;
                }
                else if (str[i] == 'e') {
                    b = M_E;
                    i++;
                }
                else if (str[i] >= '0' && str[i] <= '9'){
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                if (i >= str.length() || str[i] == ')' ) {
                    a =pow(a,b);
                    if (symbol == '+') {
                           answer += a;
                       }
                       else if (symbol == '-') {
                           answer -= a;
                       }
                       else {
                           answer = a;
                       }
                    return answer;
                }
                if (str[i] == '.' && str[i+1] >= '0' && str[i+1] <= '9') {
                    k = 1;
                    i++;
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b + (str[i] - '0')/(pow(10,k));
                        i++;
                        k++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                a = pow(a,b);
                
            }
        }
        
    }
    std::cout << a << "  4\n symbol = " << symbol << "\n" << "answer = " << answer << "\n";
    if (symbol == '+') {
        answer += a;
    }
    else if (symbol == '-') {
        answer -= a;
    }
    else {
        answer = a;
    }
    if (str[i] == ')' || i >= str.length()) {
        return answer;
    }
    symbol = str[i];
    a = 0;
    while (str[i] == '+' || str[i] == '-') {
        if (str[i] == '+') {
            if (str[i+1] == '(') {
                a = a + build_sk (str, i+2);
                while (str[i] != ')' && i < str.length()) {
                    i++;
                }
                i++;
                if (i >= str.length()) {
                    answer += a;
                    return answer;
                }
            }
            else {
                i++;
                b = 0;
                if (str[i] == 'x') {
                    if (key == true) {
                        std::cout << "Введите х\n" ;
                        std::cin >> x;
                        key = false;
                    }
                    b = x;
                    i++;
                }
                else if (str[i] == 'P') {
                    b = M_PI;
                    i++;
                }
                else if (str[i] == 'e') {
                    b = M_E;
                    i++;
                }
                else if (str[i] >= '0' && str[i] <= '9' ) {
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                    std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }

                if (i >= str.length() || str[i] == ')' ) {
                    a =a+b;
                    answer += a;
                    return answer;
                }
                if (str[i] == '.' && str[i+1] >= '0' && str[i+1] <= '9') {
                    k = 1;
                    i++;
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b + (str[i] - '0')/(pow(10,k));
                        i++;
                        k++;
                    }
                }
                else {
                  std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                
                if (str[i] != '*' && str[i] != '/' && str[i] != '^')  {
                    a = a + b;
                }
                else {
                    symbol = '+';
                }
            }
        }
        else  {
            if (str[i+1] == '(') {
                a = a - build_sk (str, i+2);
                while (str[i] != ')' && i < str.length()) {
                    i++;
                }
                i++;
                if (i >= str.length()) {
                    answer += a;
                    return answer;
                }
            }
            else {
                i++;
                b = 0;
                if (str[i] == 'x') {
                    if (key == true) {
                        std::cout << "Введите х\n" ;
                        std::cin >> x;
                        key = false;
                    }
                    b = x;
                    i++;
                }
                else if (str[i] == 'P') {
                    b = M_PI;
                    i++;
                }
                else if (str[i] == 'e') {
                    b = M_E;
                    i++;
                }
                else if (str[i] >= '0' && str[i] <= '9'){
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b * 10 + str[i] - '0';
                        i++;
                    }
                }
                else {
                  std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }

                if (i >= str.length() || str[i] == ')' ) {
                    a =a-b;
                    answer += a;
                    return answer;
                }
                if (str[i] == '.'&& str[i+1] >= '0' && str[i+1] <= '9') {
                    k = 1;
                    i++;
                    while(str[i] >= '0' && str[i] <= '9' && i < str.length() && str[i] != ')' ) {
                        b = b + (str[i] - '0')/(pow(10,k));
                        i++;
                        k++;
                    }
                }
                else {
                  std ::cout << "В выражении ошибка!\n";
                    return -1000000;
                }
                if (str[i] != '*' && str[i] != '/' && str[i] != '^')  {
                    a = a - b;
                }
                else {
                    symbol = '-';
                }
            }
        }
    }
    answer += a;
    a = b;
    //отлавливаем ошибки
        if (str[i] != '*' && str[i] != '/' && str[i] != '+' && str[i] != '-') {
            std ::cout << "В выражении ошибка!\n";
            return -1000000;
        }
    }
    return answer;
}

int main(){
    std::cout << "Пи = P\ne=e\nВведите\n";
    std::string str;
    std::cin >> str;
    float k = build_sk(str, 0); //всё выражение в скобках с начала
    if (k == -1000000) {
        std::cout << "нельзя посчитать\n";
    }
    else {
        std::cout << k;
    }
    
    return 0;
}
