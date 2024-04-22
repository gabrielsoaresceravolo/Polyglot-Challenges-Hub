#include <stdio.h>

// Função para adição
float adicao(float num1, float num2) 
{
    return num1 + num2;
}

// Função para subtração
float subtracao(float num1, float num2) 
{
    return num1 - num2;
}

// Função para multiplicação
float multiplicacao(float num1, float num2) 
{
    return num1 * num2;
}

// Função para divisão
float divisao(float num1, float num2) 
{
    if (num2 != 0)
        return num1 / num2;
    else 
    {
        printf("Erro: Divisão por zero!\n");
        return 0;
    }
}

// =====================================================================================================================

int main() 
{
    float num1, num2;
    char operador;

    // Solicitar ao usuário para inserir a operação
    printf("Digite a operacao (+, -, *, /): ");
    scanf("%c", &operador);

    // Solicitar ao usuário para inserir os números
    printf("Digite dois numeros: ");
    scanf("%f %f", &num1, &num2);

    // Realizar a operação com base no operador inserido
    switch (operador) 
    {
        case '+':
            printf("Resultado: %.2f\n", adicao(num1, num2));
            break;
        case '-':
            printf("Resultado: %.2f\n", subtracao(num1, num2));
            break;
        case '*':
            printf("Resultado: %.2f\n", multiplicacao(num1, num2));
            break;
        case '/':
            printf("Resultado: %.2f\n", divisao(num1, num2));
            break;
        default:
            printf("Operador invalido!\n");
            break;
    }
    return 0;
}
