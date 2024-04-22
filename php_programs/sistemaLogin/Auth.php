<?php
class Auth 
{

    public static function login($email, $senha) 
    {
        $usuario = Usuario::encontrarPorEmail($email);

        if ($usuario && $usuario->verificarSenha($senha)) 
        {
            session_start();
            $_SESSION['usuario_id'] = $usuario->getId();
            return true;
        }
        return false;
    }

    public static function estaAutenticado() 
    {
        return isset($_SESSION['usuario_id']);
    }

    public static function getUsuarioId() 
    {
        if (self::estaAutenticado()) 
        {
            return htmlspecialchars($_SESSION['usuario_id']);
        }
        return null;
    }

    public static function logout() 
    {
        session_start();
        session_destroy();
    }
}
?>
