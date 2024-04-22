#!/bin/bash

LOG_FILE="system_monitor.log"
EMAIL="gabriel.ceravolo26@gmail.com"

enviar_alerta() 
{
    local assunto=$1
    local mensagem=$2
    echo "$(date +"%Y-%m-%d %H:%M:%S") - ALERTA: $mensagem" | tee -a "$LOG_FILE"
    echo -e "Subject:$assunto\n\n$mensagem" | sendmail "$EMAIL"
}

iniciar_monitoramento() 
{
    echo "Iniciando monitoramento..."
    while true; do
        
        cpu_usage=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
        cpu_threshold=80

        if (( $(echo "$cpu_usage > $cpu_threshold" | bc -l) )); then
            enviar_alerta "Alerta de CPU" "Uso de CPU acima de $cpu_threshold% - Uso atual: $cpu_usage%"
        fi

        memoria_total=$(free | grep Mem | awk '{print $2}')
        memoria_usada=$(free | grep Mem | awk '{print $3}')
        memoria_usada_percentual=$(echo "scale=2; $memoria_usada / $memoria_total * 100" | bc)
        memoria_threshold=80

        if (( $(echo "$memoria_usada_percentual > $memoria_threshold" | bc -l) )); then
            enviar_alerta "Alerta de Memória" "Uso de memória acima de $memoria_threshold% - Uso atual: $memoria_usada_percentual%"
        fi

        disco_usado_percentual=$(df | grep "/$" | awk '{print $5}' | sed 's/%//')
        disco_threshold=80

        if (( $disco_usado_percentual > $disco_threshold )); then
            enviar_alerta "Alerta de Disco" "Uso de disco acima de $disco_threshold% - Uso atual: $disco_usado_percentual%"
        fi

        sleep 60
    done
}

parar_monitoramento() 
{
    echo "Parando monitoramento..."
    pid=$(pgrep -f "$0")
    if [ -n "$pid" ]; then
        kill "$pid"
        echo "Monitoramento interrompido."
    else
        echo "Monitoramento não está em execução."
    fi
}

# Menu principal
while true; do
    echo "Escolha uma opção:"
    echo "1. Iniciar monitoramento"
    echo "2. Parar monitoramento"
    echo "3. Sair"

    read opcao

    case $opcao in
        1) iniciar_monitoramento ;;
        2) parar_monitoramento ;;
        3) echo "Saindo..."; exit ;;
        *) echo "Opção inválida. Por favor, escolha novamente." ;;
    esac
done
