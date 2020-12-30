#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <string>
#include <cstdlib>
#include <map>
#include <stdexcept>

using namespace std;

struct Calculator;

struct TokenBase {
    virtual void evaluate (Calculator *) = 0;
    virtual ~TokenBase() {}
};

template< class T >
struct Token : public TokenBase {
    T token_;

    void evaluate (Calculator  *c);

    Token (T t) : token_(t) {}
};

struct RPNExpression {
    std::vector< TokenBase* > stack;

    void push (TokenBase *t) { stack.push_back (t); }

    TokenBase* pop () {
        TokenBase *t = stack.front ();
        stack.erase (stack.begin ());
        return t;
    }

    bool empty () const { return stack.empty (); }
};

struct ShuntingYard {
    const std::string expr_;
    RPNExpression rpn_;
    std::stack< char > op_stack_;
    mutable std::map< char, int > op_precedence_;

    int precedence (char op) const { return op_precedence_[op]; }

    int stack_precedence () const {
        if (op_stack_.empty ()) { return -1; }
        return precedence (op_stack_.top ());
    }

    void handle_left_paren () { op_stack_.push ('('); }

    void handle_right_paren () {
        while ('(' != op_stack_.top ()) {
            rpn_.push (new Token< char >(op_stack_.top ()));
            op_stack_.pop ();
        }
        op_stack_.pop ();
    }

    void handle_op (char op) {
        while (! op_stack_.empty () &&
                precedence (op) <= stack_precedence ()) {
            rpn_.push (new Token< char >(op_stack_.top ()));
            op_stack_.pop ();
        }
        op_stack_.push(op);
    }

    RPNExpression convert(const std::string &infix) {
        const char * token = infix.c_str ();
        while (token && *token) {
            while (*token && isspace (*token)) { ++token; }
            if (! *token) { break; }
            if (isdigit (*token)) {
                char * next_token = 0;
                rpn_.push (new Token< double >(strtod (token, &next_token)));
                token = next_token;
            } else {
                char op = *token;
                switch (op) {
                    case '(':
                        handle_left_paren ();
                        break;
                    case ')':
                        handle_right_paren ();
                        break;
                    default:
                        handle_op (op);
                }
                ++token;
            }
        }
        while (! op_stack_.empty ()) {
            rpn_.push (new Token< char >(op_stack_.top ()));
            op_stack_.pop ();
        }
        return rpn_;
    }


    ShuntingYard (const std::string& infix) : expr_(infix) {
        op_precedence_['('] = -1;
        op_precedence_['+'] = 2; op_precedence_['-'] = 2;
        op_precedence_['*'] = 3; op_precedence_['/'] = 3;
        op_precedence_['^'] = 4;
    }

    RPNExpression to_rpn () { return convert (expr_); }

};

struct Calculator {
    std::stack< double > operands_;

    double pop () {
        if(operands_.size() < 1)
            throw exception();
        double d = operands_.top ();
        operands_.pop ();
        return d;
    }

    void push (double d) { operands_.push (d); }

    double result () const { return operands_.top (); }

    void flush () {
        while (! operands_.empty ()) { operands_.pop (); }
    }

    void consume(double value) { push (value); }

    void consume(char op) {
        switch (op) {
            case '+':
                push (pop () + pop ());
                break;
            case '*':
                push (pop () * pop ());
                break;
            case '-':
                {
                    double right = pop ();
                    push (pop () - right);
                }
                break;
            case '/':
                {
                    double right = pop ();
                    push (pop () / right);
                }
                break;
            case '^':
                {
                    double right = pop ();
                    push(pow(pop (), right));
                    break;
                }
            default:
                throw std::domain_error("Unknown Operator");
        }
    }


    double calculate (const std::string& expr) {
        ShuntingYard shunting(expr);
        RPNExpression rpn = shunting.to_rpn ();
        flush ();
        while (!rpn.empty ()) {
            TokenBase * token = rpn.pop ();
            token->evaluate (this);
            delete token;
        }
        return result ();
    }

};

template< class T >
void Token< T >::evaluate (Calculator * c) { c->consume (token_); }

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

bool norm(string& data){
    data.erase(std::remove_if(data.begin(),
    data.end(),[](unsigned char x){return std::isspace(x);}), data.end());
    
    if(data[0] == '-')
        data = '0' + data;
    if(data[0] == '+')
        data = data.substr(1);
    
    data = ReplaceAll(data, "pi", "3.14");
    data = ReplaceAll(data, "e", "2.71");
    
    while (true) {
        int type = 0;
        int cnt = 4;
        size_t posBegin = data.find("sin(");
        if(posBegin == string::npos){
            posBegin = data.find("cos(");
            type = 1;
            cnt = 4;
        }
        if(posBegin == string::npos){
           posBegin = data.find("tg(");
            type = 2;
            cnt = 3;
        }
        if(posBegin == string::npos){
           posBegin = data.find("ctg(");
            type = 3;
            cnt = 4;
        }
        if(posBegin == string::npos){
           posBegin = data.find("exp(");
            type = 4;
        }
        if(posBegin == string::npos){
           posBegin = data.find("sqrt(");
            type = 5;
            cnt = 5;
        }
        
        if(posBegin != string::npos){
            size_t posBr = data.find(")", posBegin);
            double value = stod(data.substr(posBegin + cnt, posBr));
            double res;
            if(type == 0)
                res = sin(value);
            else if(type == 1)
                res = cos(value);
            else if(type == 2)
                res = tan(value);
            else if(type == 3)
                res = 1 / tan(value);
            else if(type == 4)
                res = exp(value);
            else if(type == 5)
                res = sqrt(value);
            
            if (isnan(res))
                throw exception();
            string s = data.substr(0, posBegin) + to_string(res) + data.substr(posBr + 1);
            s = ReplaceAll(s, "+-", "-");
            data = s;
        }
        else
            break;
    }
    return true;
}

int main () {
    try{
       
        string data = "2 + cos(3) + sqrt(4) + 6 ^ 2 + pi - e";
        norm(data);
        Calculator c;
        std::cout << c.calculate (data) << std::endl;
    }
    catch(invalid_argument e){
        cout << "Incorrect format" << endl;
    }
    catch(std::exception e){
        cout << e.what();
        std::cout << "Error!" << std::endl;
    }
    return 0;
}
