<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Formulário de Contato</title>
    <!-- Bootstrap CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet">
</head>
<body>
    <div class="container">
        <h2 class="mt-5">Formulário de Contato</h2>
        <form action="enviar_email.php" method="post">
            <div class="mb-3">
                <label for="nome" class="form-label">Nome:</label>
                <input type="text" class="form-control" id="nome" name="nome" required>
            </div>
            <div class="mb-3">
                <label for="email" class="form-label">E-mail:</label>
                <input type="email" class="form-control" id="email" name="email" required>
            </div>
            <div class="mb-3">
                <label for="mensagem" class="form-label">Mensagem:</label>
                <textarea class="form-control" id="mensagem" name="mensagem" rows="5" required></textarea>
            </div>
            <button type="submit" class="btn btn-primary">Enviar</button>
        </form>
    </div>
    <!-- Bootstrap JS -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js"></script>
</body>
</html>

<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") 
{
    function limparEntrada($entrada) 
    {
        return htmlspecialchars(strip_tags(trim($entrada)), ENT_QUOTES, 'UTF-8');
    }

    $nome = limparEntrada($_POST['nome']);
    $email = limparEntrada($_POST['email']);
    $mensagem = limparEntrada($_POST['mensagem']);

    try 
    {
        $pdo = new PDO('mysql: 
                                host=localhost; 
                                dbname=NAME DATA BASE', 
                                'root', 
                                'passworld');

        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        $stmt = $pdo->prepare("INSERT INTO mensagens (nome, email, mensagem) VALUES (:nome, :email, :mensagem)");
        
        $stmt->execute(array(
            ':nome' => $nome,
            ':email' => $email,
            ':mensagem' => $mensagem
        ));
        
        echo "Mensagem enviada com sucesso!";
    } 
    catch(PDOException $e) 
    {
        echo "Erro ao enviar a mensagem.";
    }
} 
else 
{
    header("Location: formulario_contato.html");
    exit;
}
?>