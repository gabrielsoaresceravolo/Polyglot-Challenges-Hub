#!/bin/bash

realizar_tarefa() 
{
    echo "Iniciando a tarefa..."
    ls C:\Users\Gabriel\Desktop\tasks
    echo "Tarefa realizada em $(date +%F_%H-%M-%S)"
}

verificar_permissoes_log() 
{
    log_file="/caminho/do/arquivo/de/log.txt"
    if [ ! -w "$log_file" ]; then
        echo "Você não tem permissão para escrever no arquivo de log em $log_file"
        exit 1
    fi
}

registrar_log() 
{
    log_file="/caminho/do/arquivo/de/log.txt"
    echo "$(date +%F_%H-%M-%S) - Tarefa automatizada" >> "$log_file"
}

verificar_cron() 
{
    if ! command -v cron &> /dev/null; then
        echo "O cron não está instalado neste sistema."
        exit 1
    fi
}

agendar_tarefa_cron() 
{
    read -p "Deseja agendar a tarefa para execução diária? [S/n]: " resposta
    resposta=${resposta:-S}

    if [[ "$resposta" =~ ^[Ss]$ ]]; then
        (crontab -l ; echo "0 3 * * * $(pwd)/$0 realizar_tarefa") | crontab -
        echo "Tarefa agendada com sucesso para execução diária às 3 da manhã."
    else
        echo "Tarefa não agendada."
    fi
}

verificar_permissoes_log
verificar_cro
