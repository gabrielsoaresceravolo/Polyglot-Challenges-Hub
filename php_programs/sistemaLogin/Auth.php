<?php
class Auth 
{
    // Método para fazer login
    public static function login($email, $senha) 
    {
        $usuario = Usuario::encontrarPorEmail($email);

        // Verificar se o usuário foi encontrado e se a senha está correta
        if ($usuario && $usuario->verificarSenha($senha)) 
        {
            // Iniciar a sessão e armazenar o ID do usuário
            session_start();
            $_SESSION['usuario_id'] = $usuario->getId();
            return true;
        }
        return false;
    }

    // Método para verificar se o usuário está autenticado
    public static function estaAutenticado() 
    {
        return isset($_SESSION['usuario_id']);
    }

    // Método para obter o ID do usuário autenticado
    public static function getUsuarioId() 
    {
        if (self::estaAutenticado()) 
        {
            return htmlspecialchars($_SESSION['usuario_id']);
        }
        return null;
    }

    // Método para fazer logout
    public static function logout() 
    {
        // Destruir a sessão
        session_start();
        session_destroy();
    }
}
?>
