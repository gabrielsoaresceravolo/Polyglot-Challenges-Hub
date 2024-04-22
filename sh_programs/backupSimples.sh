#!/bin/bash

exibir_erro() 
{
    echo "Erro: $1"
    exit 1
}

if [ $# -ne 2 ]; then
    exibir_erro "Uso: $0 <diretório_origem> <diretório_destino>"
fi

origem="$1"
destino="$2"

if [ ! -d "$origem" ]; then
    exibir_erro "Diretório de origem não encontrado ou não é um diretório válido."
fi

if [ ! -d "$destino" ]; then
    mkdir -p "$destino" || exibir_erro "Não foi possível criar o diretório de destino."
fi

if [ ! -w "$destino" ]; then
    exibir_erro "Você não tem permissão para escrever no diretório de destino."
fi

cp -r "$origem"/* "$destino" || exibir_erro "Falha ao copiar arquivos para o diretório de destino."
echo "Backup concluído em $(date +%F_%H-%M-%S)"
