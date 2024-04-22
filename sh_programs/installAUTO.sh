#!/bin/bash

# Função para exibir mensagem de erro e sair do script
exibir_erro() 
{
    echo "Erro: $1"
    exit 1
}

# Verificar se o usuário possui permissões de superusuário
verificar_privilegios() 
{
    if [ "$(id -u)" != "0" ]; then
        exibir_erro "Este script precisa ser executado com privilégios de superusuário (root)."
    fi
}

# Verificar se o sistema é compatível (este exemplo é para distribuições Linux baseadas em Debian)
verificar_compatibilidade() 
{
    if ! command -v apt &> /dev/null; then
        exibir_erro "Este script é compatível apenas com sistemas Linux baseados em Debian."
    fi
}

# Função para instalar o Apache
instalar_apache() 
{
    echo "Instalando Apache..."
    apt update && apt install apache2 -y
    systemctl start apache2
    systemctl enable apache2
    echo "Apache instalado e iniciado com sucesso."
}

# Função para instalar o MySQL
instalar_mysql() 
{
    echo "Instalando MySQL..."
    apt install mysql-server -y
    systemctl start mysql
    systemctl enable mysql
    echo "MySQL instalado e iniciado com sucesso."
}

# Função para instalar o PHP
instalar_php() 
{
    echo "Instalando PHP..."
    apt install php libapache2-mod-php php-mysql -y
    echo "PHP instalado com sucesso."
}

# Função principal de instalação
instalacao() 
{
    verificar_privilegios
    verificar_compatibilidade

    instalar_apache
    instalar_mysql
    instalar_php
    
    echo "Instalação concluída."
}

# Iniciar a instalação
instalacao
