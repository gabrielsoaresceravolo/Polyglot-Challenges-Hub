#!/bin/bash

# Função para realizar a tarefa
realizar_tarefa() 
{
    # Coloque aqui o código da tarefa a ser realizada
    echo "Tarefa realizada em $(date +%F_%H-%M-%S)"
}

# Verifica se o usuário tem permissão para escrever no arquivo de log
verificar_permissoes_log() 
{
    log_file="/caminho/do/arquivo/de/log.txt"
    if [ ! -w "$log_file" ]; then
        echo "Você não tem permissão para escrever no arquivo de log em $log_file"
        exit 1
    fi
}

# Registra a execução no arquivo de log
registrar_log() 
{
    log_file="/caminho/do/arquivo/de/log.txt"
    echo "$(date +%F_%H-%M-%S) - Tarefa automatizada" >> "$log_file"
}

# Verifica se o cron está instalado
verificar_cron() 
{
    if ! command -v cron &> /dev/null; then
        echo "O cron não está instalado neste sistema."
        exit 1
    fi
}

# Adiciona a tarefa ao cron
agendar_tarefa_cron() 
{
    # Solicitar ao usuário o agendamento personalizado
    read -p "Deseja agendar a tarefa para execução diária? [S/n]: " resposta
    resposta=${resposta:-S}  # Se a resposta estiver vazia, definir como "S" por padrão

    if [[ "$resposta" =~ ^[Ss]$ ]]; then
        # Agende a tarefa para ser executada todos os dias às 3 da manhã
        (crontab -l ; echo "0 3 * * * $(pwd)/$0 realizar_tarefa") | crontab -
        echo "Tarefa agendada com sucesso para execução diária às 3 da manhã."
    else
        echo "Tarefa não agendada."
    fi
}

# Main
verificar_permissoes_log
verificar_cro
