<?PHP
$servername = "sql110.epizy.com"; // Reemplace "sqlxxx" con su Nombre de host de MySQL
$username = "epiz_34100138"; // Reemplace "your_username" con su nombre de usuario
$password = "pXwvTOXC0n"; // Reemplace "your_password" con su contraseña, se encuentra en InfinityFree->detalles de la cuenta
$dbname = "epiz_34100138_poo_ejercicio16";

$conn = mysqli_connect($servername, $username, $password, $dbname);

// Verificar conexión
if (!$conn) {
    die("Conexión fallida: " . mysqli_connect_error());
}
//echo "Conexión exitosa";
if ( isset( $_GET[ 'user' ] ) ) {
    
    // Procese los datos de inicio de sesión
    $username = $_GET["user"];
    $password = $_GET["pass"];
    // ...

    $sql = "SELECT * FROM USUARIOS WHERE usuario = '$username' AND clave = '$password'";
    $resultado = mysqli_query($conn, $sql);

    if (mysqli_num_rows($resultado) == 1) {
        // Las credenciales son válidas
        // Mostrar los datos del usuario
        $fila = mysqli_fetch_assoc($resultado);
        echo "Nombre: " . $fila["nombre"] . "<br>";
        echo "Apellido: " . $fila["apellido"] . "<br>";
        echo "Correo electrónico: " . $fila["mail"] . "<br>";
    } else {
        // Las credenciales no son válidas, muestre un mensaje de error
        echo "denegado";
    }
}

?>