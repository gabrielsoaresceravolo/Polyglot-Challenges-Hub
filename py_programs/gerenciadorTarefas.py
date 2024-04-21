import os
import pickle

class GerenciadorTarefas:
    def __init__(self):
        self.tarefas = []

    def adicionar_tarefa(self, tarefa):
        self.tarefas.append({"descricao": tarefa, "concluida": False})
        print("Tarefa adicionada com sucesso.")

    def remover_tarefa(self, indice):
        if indice >= 0 and indice < len(self.tarefas):
            tarefa_removida = self.tarefas.pop(indice)
            print(f"Tarefa '{tarefa_removida['descricao']}' removida com sucesso.")
        else:
            print("Índice de tarefa inválido.")

    def listar_tarefas(self):
        if self.tarefas:
            print("Lista de tarefas:")
            for i, tarefa in enumerate(self.tarefas):
                print(f"{i + 1}. [{ 'X' if tarefa['concluida'] else ' ' }] {tarefa['descricao']}")
        else:
            print("Não há tarefas na lista.")

    def marcar_como_concluida(self, indice):
        if indice >= 0 and indice < len(self.tarefas):
            self.tarefas[indice]['concluida'] = True
            print("Tarefa marcada como concluída.")
        else:
            print("Índice de tarefa inválido.")

    def editar_tarefa(self, indice, nova_descricao):
        if indice >= 0 and indice < len(self.tarefas):
            self.tarefas[indice]['descricao'] = nova_descricao
            print("Tarefa editada com sucesso.")
        else:
            print("Índice de tarefa inválido.")

    def salvar_tarefas(self, nome_arquivo):
        with open(nome_arquivo, 'wb') as file:
            pickle.dump(self.tarefas, file)
        print("Tarefas salvas com sucesso.")

    def carregar_tarefas(self, nome_arquivo):
        if os.path.exists(nome_arquivo):
            with open(nome_arquivo, 'rb') as file:
                self.tarefas = pickle.load(file)
            print("Tarefas carregadas com sucesso.")
        else:
            print("O arquivo de tarefas não existe.")

def menu():
    print("\n=---===---= Sistema de Gerenciamento de Tarefas =---===---=")
    print("1. Adicionar Tarefa")
    print("2. Remover Tarefa")
    print("3. Listar Tarefas")
    print("4. Marcar Tarefa como Concluída")
    print("5. Editar Tarefa")
    print("6. Salvar Tarefas")
    print("7. Carregar Tarefas")
    print("8. Sair")

def main():
    gerenciador = GerenciadorTarefas()

    while True:
        menu()
        opcao = input("Escolha uma opção: ")

        if opcao == '1':
            tarefa = input("Digite a nova tarefa: ")
            gerenciador.adicionar_tarefa(tarefa)
        elif opcao == '2':
            gerenciador.listar_tarefas()
            indice = int(input("Digite o índice da tarefa a ser removida: ")) - 1
            gerenciador.remover_tarefa(indice)
        elif opcao == '3':
            gerenciador.listar_tarefas()
        elif opcao == '4':
            gerenciador.listar_tarefas()
            indice = int(input("Digite o índice da tarefa a ser marcada como concluída: ")) - 1
            gerenciador.marcar_como_concluida(indice)
        elif opcao == '5':
            gerenciador.listar_tarefas()
            indice = int(input("Digite o índice da tarefa a ser editada: ")) - 1
            nova_descricao = input("Digite a nova descrição da tarefa: ")
            gerenciador.editar_tarefa(indice, nova_descricao)
        elif opcao == '6':
            nome_arquivo = input("Digite o nome do arquivo para salvar as tarefas: ")
            gerenciador.salvar_tarefas(nome_arquivo)
        elif opcao == '7':
            nome_arquivo = input("Digite o nome do arquivo para carregar as tarefas: ")
            gerenciador.carregar_tarefas(nome_arquivo)
        elif opcao == '8':
            print("Saindo do sistema...")
            break
        else:
            print("Opção inválida. Tente novamente.")

if __name__ == "__main__":
    main()
