#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <stack>

// Enumeração para os tipos de token
enum class TokenType 
{
    OPERATOR,
    NUMBER,
    LEFT_PAREN,
    RIGHT_PAREN
};

// Estrutura para representar um token
struct Token 
{
    TokenType type;
    std::string value;
};

// Função para verificar se um caractere é um operador
bool isOperator(char c) 
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Função para tokenizar uma expressão
std::vector<Token> tokenize(const std::string& expression) 
{
    std::vector<Token> tokens;
    std::istringstream iss(expression);
    std::string token;
    while (iss >> token) 
    {
        if (isOperator(token[0])) 
        {
            tokens.push_back({TokenType::OPERATOR, token});
        } 
        else if (token == "(") 
        {
            tokens.push_back({TokenType::LEFT_PAREN, token});
        } 
        else if (token == ")") 
        {
            tokens.push_back({TokenType::RIGHT_PAREN, token});
        } 
        else 
        {
            tokens.push_back({TokenType::NUMBER, token});
        }
    }
    return tokens;
}

// Função para converter a expressão de infix para postfix
std::vector<Token> infixToPostfix(const std::vector<Token>& infixTokens) 
{
    std::vector<Token> postfix;
    std::stack<Token> operatorStack;

    for (const auto& token : infixTokens) 
    {
        if (token.type == TokenType::NUMBER) 
        {
            postfix.push_back(token);
        } else if (token.type == TokenType::OPERATOR) 
        {
            while (!operatorStack.empty() && 
                   operatorStack.top().type == TokenType::OPERATOR &&
                   ((token.value == "+" || token.value == "-") &&
                   (operatorStack.top().value == "*" || operatorStack.top().value == "/"))) 
                   {
                postfix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (token.type == TokenType::LEFT_PAREN) 
        {
            operatorStack.push(token);
        } else if (token.type == TokenType::RIGHT_PAREN) 
        {
            while (!operatorStack.empty() && operatorStack.top().type != TokenType::LEFT_PAREN) 
            {
                postfix.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.pop(); // Remove o '('
        }
    }

    while (!operatorStack.empty()) 
    {
        postfix.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return postfix;
}

// Função para compilar uma expressão aritmética para código de máquina
std::string compile(const std::string& expression) 
{
    std::vector<Token> infixTokens = tokenize(expression);
    std::vector<Token> postfixTokens = infixToPostfix(infixTokens);

    std::map<std::string, std::string> opcode = 
    {
        {"+", "ADD"},
        {"-", "SUB"},
        {"*", "MUL"},
        {"/", "DIV"}
    };

    std::string machineCode;
    for (const auto& token : postfixTokens) 
    {
        if (token.type == TokenType::OPERATOR) 
        {
            machineCode += opcode[token.value] + " ";
        } else if (token.type == TokenType::NUMBER) 
        {
            machineCode += "PUSH " + token.value + " ";
        }
    }
    machineCode += "PRINT";
    return machineCode;
}

int main() 
{
    std::string expression;
    std::cout << "Digite uma expressao aritmetica (ex: 2 + (3 * 4)): ";
    std::getline(std::cin, expression);

    std::string machineCode = compile(expression);
    std::cout << "Codigo de maquina gerado: " << machineCode << std::endl;

    return 0;
}
