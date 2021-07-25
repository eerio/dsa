/**
 * This module implements a generic stack
 */
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<cassert>
#include<map>

template <typename T>
class Stack {
  private:
    std::vector<T> storage;

  public:
    Stack()
      : storage {}
    {}

    void push(T elem) {
      this->storage.push_back(elem);
    }

    T pop() {
      T back = storage.back();
      this->storage.pop_back();
      return back;
    }

    bool empty() {
      return this->storage.empty();
    }

    void print() {
      for (T elem: this->storage) std::cout << elem << ' ';
    }
};

enum Operation {
  ADD,
  SUB,
  MUL,
  DIV,
  NEG,
  SQRT,
  POW
};

std::map<std::string, Operation> op_representations = {
  {"+", ADD},
  {"-", SUB},
  {"*", MUL},
  {"/", DIV},
  {"~", NEG},
  {"sqrt", SQRT},
  {"**", POW}
};



int my_sqrt(int x) {
  int low=0, high=x, mid;
  
  while (low < high - 1) {
    mid = (low + high) / 2;
    // std::cout << "low, mid, high" << low << ' '<< ' ' << mid << ' ' << high << std::endl;
    if (mid * mid < x) {
      low = mid;
    } else if (mid * mid == x) {
      return mid;
    } else {
      high = mid;
    }
  }

  return low;
}

int my_pow(int base, int exp) {
  if (exp == 0) return 1;

  if (exp % 2 == 0) {
    return my_pow(base * base, exp / 2);
  } else {
    return base * my_pow(base, exp - 1);
  }
}

enum ExpType {
  OPERATION,
  ARGUMENT
};

struct Expression {
  ExpType exp_type;

  union {
    Operation op;
    int arg;
  } exp;
};

std::ostream& operator<<(std::ostream &os, const Expression e) {
  os << "Expression: (" << (int)e.exp_type << ", " << (int)e.exp.arg << ")";
  return os;
}

void red_add(Stack<int> &stack) { stack.push(stack.pop() + stack.pop()); }
void red_sub(Stack<int> &stack) { stack.push(stack.pop() - stack.pop()); }
void red_mul(Stack<int> &stack) { stack.push(stack.pop() * stack.pop()); }
void red_div(Stack<int> &stack) { stack.push(stack.pop() / stack.pop()); }
void red_neg(Stack<int> &stack) { stack.push(-stack.pop()); }
void red_sqrt(Stack<int> &stack) { stack.push(my_sqrt(stack.pop())); }
void red_pow(Stack<int> &stack) {
  int exponent = stack.pop();
  int base = stack.pop();
  stack.push(my_pow(base, exponent)); 
}
typedef void (*prefix_reduce_fun)(Stack<int>&);

std::map<Operation, prefix_reduce_fun> reduce_functions = {
  {Operation::ADD, red_add},
  {Operation::SUB, red_sub},
  {Operation::MUL, red_mul},
  {Operation::DIV, red_div},
  {Operation::NEG, red_neg},
  {Operation::SQRT, red_sqrt},
  {Operation::POW, red_pow},
};


Expression parse_expression(std::string token) {
  Expression expression;
  if (op_representations.find(token) == op_representations.end()) {
    expression.exp_type = ExpType::ARGUMENT;
    expression.exp.arg = std::stoi(token);
  } else {
    expression.exp_type = ExpType::OPERATION;
    expression.exp.op = op_representations[token];
  }

  return expression;
}

int prefix_reduce(Stack<Expression> stack) {
  Expression top;
  
  Stack<int> aux;

  while (!stack.empty()) {
    top = stack.pop();
    if (top.exp_type == ExpType::ARGUMENT) {
      aux.push(top.exp.arg);
    } else {
      reduce_functions[top.exp.op](aux);
    }
  }

  return aux.pop();
}

int main() {
  std::cout << "Hello!" << std::endl;
  
  Stack<Expression> expressions;
  
  std::string input, token;;
  std::getline(std::cin, input);
  std::istringstream stream(input);
  while(stream >> token) expressions.push(parse_expression(token));

  // expressions.print();
  int result = prefix_reduce(expressions);

  // assert(!expressions.empty());
  // Expression result = expressions.pop();
  // assert(expressions.empty());
  // assert(!result.is_op);

  std::cout << result << std::endl;
}

