import statistics

def calcular_media(tipo, quantidade):
    numeros = []
    for i in range(quantidade):
        while True:
            try:
                entrada = float(input(f"Digite o {i+1}º número: "))
                numeros.append(entrada)
                break
            except ValueError:
                print("Por favor, digite um número válido.")

    if tipo == 'aritmetica':
        media = statistics.mean(numeros)
    elif tipo == 'geometrica':
        media = statistics.geometric_mean(numeros)
    elif tipo == 'harmonica':
        media = statistics.harmonic_mean(numeros)

    print(f"A média {tipo} dos números inseridos é: {media:.2f}")

if __name__ == "__main__":
    print("Calculadora de Média")
    while True:
        tipo_media = input("Escolha o tipo de média (aritmética, geométrica ou harmônica): ").lower()
        if tipo_media not in ['aritmetica', 'geométrica', 'harmônica']:
            print("Tipo de média inválido. Por favor, tente novamente.")
        else:
            break
    
    while True:
        try:
            quantidade = int(input("Quantos números você deseja inserir? "))
            if quantidade <= 0:
                print("Por favor, insira um número positivo.")
            else:
                break
        except ValueError:
            print("Por favor, insira um número válido.")

    calcular_media(tipo_media, quantidade)
