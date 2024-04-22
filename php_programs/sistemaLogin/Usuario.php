<?php
class Usuario 
{
    private $nome;
    private $email;
    private $senha;

    // Método construtor
    public function __construct($nome, $email, $senha) 
    {
        $this->nome = $nome;
        $this->email = $email;
        $this->senha = password_hash($senha, PASSWORD_DEFAULT); // Hash da senha
    }

    // Método para salvar um novo usuário no banco de dados
    public function salvar() 
    {
        // Conectar ao banco de dados
        $db = new Database();
        $conn = $db->getConnection();

        // Preparar a consulta SQL
        $query = "INSERT INTO usuarios (nome, email, senha) VALUES (?, ?, ?)";
        $stmt = $conn->prepare($query);
        $stmt->bind_param("sss", $this->nome, $this->email, $this->senha);

        // Executar a consulta
        if ($stmt->execute()) 
        {
            return true;
        } 
        else 
        {
            return false;
        }
    }

    // Método estático para encontrar um usuário pelo e-mail
    public static function encontrarPorEmail($email) 
    {
        // Conectar ao banco de dados
        $db = new Database();
        $conn = $db->getConnection();

        // Preparar a consulta SQL
        $query = "SELECT * FROM usuarios WHERE email = ?";
        $stmt = $conn->prepare($query);
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $result = $stmt->get_result();

        // Retornar o usuário encontrado
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

    // Método para verificar a senha do usuário
    public function verificarSenha($senha) 
    {
        return password_verify($senha, $this->senha);
    }
}
?>
