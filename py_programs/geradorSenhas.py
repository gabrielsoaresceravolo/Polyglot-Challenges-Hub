import random
import string

class GeradorSenha:
    def __init__(self, tamanho=8):
        self.tamanho = tamanho

    def gerar_senha_baixa_seguranca(self):
        caracteres = string.ascii_letters + string.digits
        return ''.join(random.choice(caracteres) for _ in range(self.tamanho))

    def gerar_senha_media_seguranca(self):
        caracteres = string.ascii_letters + string.digits + string.punctuation
        return ''.join(random.choice(caracteres) for _ in range(self.tamanho))

    def gerar_senha_alta_seguranca(self):
        caracteres = string.ascii_letters + string.digits + string.punctuation
        senha = ''.join(random.choice(caracteres) for _ in range(self.tamanho))
        return ''.join(random.sample(senha, len(senha)))

    def gerar_senhas(self, quantidade=1, nivel='alta', incluir_caracteres_especiais=True):
        senhas = []
        for _ in range(quantidade):
            if nivel == 'baixa':
                senha = self.gerar_senha_baixa_seguranca()
            elif nivel == 'media':
                senha = self.gerar_senha_media_seguranca()
            elif nivel == 'alta':
                senha = self.gerar_senha_alta_seguranca()
            if not incluir_caracteres_especiais:
                senha = ''.join(c for c in senha if c.isalnum())
            senhas.append(senha)
        return senhas

if __name__ == "__main__":
    gerador = GeradorSenha()

    nivel_seguranca = input("Escolha o nível de segurança (baixa, média, alta): ").lower()
    quantidade_senhas = int(input("Quantas senhas deseja gerar? "))
    incluir_caracteres_especiais = input("Deseja incluir caracteres especiais? (s/n): ").lower() == 's'

    senhas_geradas = gerador.gerar_senhas(quantidade_senhas, nivel_seguranca, incluir_caracteres_especiais)
    print("Senhas geradas:")
    for senha in senhas_geradas:
        print(senha)
