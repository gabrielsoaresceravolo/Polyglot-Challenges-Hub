#!/bin/bash

exibir_erro() 
{
    echo "Erro: $1"
    exit 1
}

verificar_privilegios() 
{
    if [ "$(id -u)" != "0" ]; then
        exibir_erro "Este script precisa ser executado com privilégios de superusuário (root)."
    fi
}

verificar_compatibilidade() 
{
    if ! command -v apt &> /dev/null; then
        exibir_erro "Este script é compatível apenas com sistemas Linux baseados em Debian."
    fi
}

instalar_apache() 
{
    echo "Instalando Apache..."
    apt update && apt install apache2 -y
    systemctl start apache2
    systemctl enable apache2
    echo "Apache instalado e iniciado com sucesso."
}

instalar_mysql() 
{
    echo "Instalando MySQL..."
    apt install mysql-server -y
    systemctl start mysql
    systemctl enable mysql
    echo "MySQL instalado e iniciado com sucesso."
}

instalar_php() 
{
    echo "Instalando PHP..."
    apt install php libapache2-mod-php php-mysql -y
    echo "PHP instalado com sucesso."
}

instalacao() 
{
    verificar_privilegios
    verificar_compatibilidade

    instalar_apache
    instalar_mysql
    instalar_php
    
    echo "Instalação concluída."
}

instalacao
