#!/bin/bash

# Arquivo de log
LOG_FILE="system_monitor.log"

# Função para enviar alerta
enviar_alerta() 
{
    echo "$(date +"%Y-%m-%d %H:%M:%S") - ALERTA: $1" | tee -a "$LOG_FILE"
    # Aqui você pode implementar a lógica para enviar um e-mail, SMS, ou outra forma de alerta
}

# Função para iniciar o monitoramento
iniciar_monitoramento() 
{
    echo "Iniciando monitoramento..."
    while true; do
        # Coletar informações de CPU
        cpu_usage=$(top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1}')
        cpu_threshold=80 # Porcentagem de uso de CPU para alerta

        if (( $(echo "$cpu_usage > $cpu_threshold" | bc -l) )); then
            enviar_alerta "Uso de CPU acima de $cpu_threshold% - Uso atual: $cpu_usage%"
        fi

        # Coletar informações de memória
        memoria_total=$(free | grep Mem | awk '{print $2}')
        memoria_usada=$(free | grep Mem | awk '{print $3}')
        memoria_usada_percentual=$(echo "scale=2; $memoria_usada / $memoria_total * 100" | bc)
        memoria_threshold=80 # Porcentagem de uso de memória para alerta

        if (( $(echo "$memoria_usada_percentual > $memoria_threshold" | bc -l) )); then
            enviar_alerta "Uso de memória acima de $memoria_threshold% - Uso atual: $memoria_usada_percentual%"
        fi

        # Coletar informações de disco
        disco_usado_percentual=$(df | grep "/$" | awk '{print $5}' | sed 's/%//')
        disco_threshold=80 # Porcentagem de uso de disco para alerta

        if (( $disco_usado_percentual > $disco_threshold )); then
            enviar_alerta "Uso de disco acima de $disco_threshold% - Uso atual: $disco_usado_percentual%"
        fi

        # Intervalo de tempo entre as verificações (em segundos)
        sleep 60 # Verificar a cada 60 segundos, por exemplo
    done
}

# Função para parar o monitoramento
parar_monitoramento() 
{
    echo "Parando monitoramento..."
    # Encontrar o PID do processo do script de monitoramento
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
