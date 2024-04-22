<?php
class Database 
{
    private $host = "LOCALHOST";
    private $usuario = "ROOT";
    private $senha = "PASSWORLD";
    private $banco = "DATA-BASE-TEST";

    // Método para obter uma conexão com o banco de dados
    public function getConnection() 
    {
        $conn = new mysqli($this->host, $this->usuario, $this->senha, $this->banco);

        // Verificar erros na conexão
        if ($conn->connect_error) 
        {
            die("Erro na conexão com o banco de dados: " . $conn->connect_error);
        }

        return $conn;
    }
}
?>
