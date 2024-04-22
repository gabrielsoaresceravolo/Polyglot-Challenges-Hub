<?php
class Usuario 
{
    private $nome;
    private $email;
    private $senha;

    public function __construct($nome, $email, $senha) 
    {
        $this->nome = $nome;
        $this->email = $email;
        $this->senha = password_hash($senha, PASSWORD_DEFAULT); // Hash da senha
    }

    public function salvar() 
    {
        $db = new Database();
        $conn = $db->getConnection();

        $query = "INSERT INTO usuarios (nome, email, senha) VALUES (?, ?, ?)";
        $stmt = $conn->prepare($query);
        $stmt->bind_param("sss", $this->nome, $this->email, $this->senha);

        if ($stmt->execute()) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }

    public static function encontrarPorEmail($email) 
    {
        $db = new Database();
        $conn = $db->getConnection();

        $query = "SELECT * FROM usuarios WHERE email = ?";
        $stmt = $conn->prepare($query);
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $result = $stmt->get_result();

        if ($result->num_rows == 1) 
        {
            $row = $result->fetch_assoc();
            return new Usuario(htmlspecialchars($row['nome']), htmlspecialchars($row['email']), $row['senha']);
        } 
        else 
        {
            return null;
        }
    }

    public function verificarSenha($senha) 
    {
        return password_verify($senha, $this->senha);
    }
}
?>
