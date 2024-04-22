#!/bin/bash

# Função para renomear um arquivo
renomear_arquivo() 
{
    echo "Digite o nome do arquivo que deseja renomear:"
    read arquivo_antigo
    echo "Digite o novo nome para o arquivo:"
    read arquivo_novo

    if [ -e "$arquivo_antigo" ]; then
        mv "$arquivo_antigo" "$arquivo_novo"
        echo "Arquivo renomeado com sucesso!"
    else
        echo "O arquivo '$arquivo_antigo' não existe."
    fi
}

# Função para mover um arquivo para um diretório específico
mover_arquivo() 
{
    echo "Digite o nome do arquivo que deseja mover:"
    read arquivo
    echo "Digite o diretório de destino:"
    read destino

    if [ -e "$arquivo" ]; then
        if [ -d "$destino" ]; then
            mv "$arquivo" "$destino"
            echo "Arquivo movido para $destino."
        else
            echo "O diretório '$destino' não existe."
        fi
    else
        echo "O arquivo '$arquivo' não existe."
    fi
}

# Função para excluir um arquivo
excluir_arquivo() 
{
    echo "Digite o nome do arquivo que deseja excluir:"
    read arquivo

    if [ -e "$arquivo" ]; then
        echo "Tem certeza de que deseja excluir o arquivo '$arquivo'? (S/N)"
        read confirmacao
        if [ "$confirmacao" == "S" ] || [ "$confirmacao" == "s" ]; then
            rm "$arquivo"
            echo "Arquivo '$arquivo' excluído com sucesso."
        else
            echo "Operação de exclusão cancelada."
        fi
    else
        echo "O arquivo '$arquivo' não existe."
    fi
}

# Função para listar o conteúdo de um diretório
listar_conteudo() 
{
    echo "Digite o caminho do diretório que deseja listar (ou '.' para o diretório atual):"
    read diretorio

    if [ -d "$diretorio" ]; then
        echo "Conteúdo do diretório '$diretorio':"
        ls -l "$diretorio"
    else
        echo "O diretório '$diretorio' não existe."
    fi
}

# Menu principal
while true; do
    echo "Escolha uma opção:"
    echo "1. Renomear arquivo"
    echo "2. Mover arquivo"
    echo "3. Excluir arquivo"
    echo "4. Listar conteúdo de um diretório"
    echo "5. Sair"

    read opcao

    case $opcao in
        1) renomear_arquivo ;;
        2) mover_arquivo ;;
        3) excluir_arquivo ;;
        4) listar_conteudo ;;
        5) echo "Saindo..."; exit ;;
        *) echo "Opção inválida. Por favor, escolha novamente." ;;
    esac
done
