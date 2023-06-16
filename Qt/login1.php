/*<?PHP
require_once "config2.php";
// $timezone = date_default_timezone_get();
// echo "The current server timezone is: " . $timezone; America/New_York
//$today = date("Y-m-d H:i:s");
echo $today;
if ( isset( $_GET[ 'user' ] ) ) {
    
    // Procese los datos de inicio de sesión
    $username = $_GET["user"];
    $password = $_GET["pass"];
    // ...
    $intentos;
    $ultimo_intento;
    date_default_timezone_set('America/Argentina/Buenos_Aires');
    

    $sql = "SELECT * FROM USUARIOS WHERE USUARIO = '$username'";
    $resultado = mysqli_query($DB_conn, $sql);
    // INGRESO UN NOMBRE CORRECTO PERO NO LA CONTRASENA
        // HAGO UN UPDATE EN CAMPO INTENTOS +1, HAGO UN UPDATE EN ULTIMO_INICIO = DATETIME
    // NO HAY USUARIO CORRECTO
    if (mysqli_num_rows($resultado) == 1) { // Existe usuario con ese username
        // Las credenciales son válidas
        // Mostrar los datos del usuario
        $fila = mysqli_fetch_assoc($resultado);
        $ultimo_inicio = $fila["ULTIMO_INICIO"];       
       
        $proximo_intento =strtotime($ultimo_inicio);
        $nueva_fecha = date('H:i:s', $proximo_intento + 300);
        //echo $nueva_fecha;
        $ultimo_intento = date("Y-m-d H:i:s");
        if ($fila["INTENTOS"] >= 3){
            // Si la diferencia de minutos entre la fecha actual y el ultimo intento es mayor a 5           
            $fecha_actual = new DateTime(); // Fecha actual
            $ultimo_inicio = new DateTime($ultimo_inicio); // Fecha obtenida de la base de datos como objeto DateTime
            $diferencia = $fecha_actual->diff($ultimo_inicio); // Diferencia entre las dos fechas
            $minutos = $diferencia->i; // Obtener los minutos de la diferencia
            //echo $minutos; // Imprimir la diferencia de minutos
            if($minutos < 5){
                echo $nueva_fecha . "!";
                exit;
            } else{
                $cod_usuario = $fila["COD_USUARIO"];
                if($fila["CONTRASENA"] == $password){
                    echo $fila["NOMBRE"] . "::";
                    echo $fila["APELLIDO"];  
                    $sql3 = "UPDATE USUARIOS SET INTENTOS = 0, ULTIMO_INICIO = '$ultimo_intento' WHERE COD_USUARIO = '$cod_usuario'"; 
                    mysqli_query($DB_conn, $sql3);
                }
                else {
                    $intentos = $fila["INTENTOS"] + 1 ;                      
                    $sql2 = "UPDATE USUARIOS SET INTENTOS = '$intentos', ULTIMO_INICIO = '$ultimo_intento' WHERE COD_USUARIO ='$cod_usuario' ";
                    mysqli_query($DB_conn, $sql2);
                }
            }
            
        } else{
            $cod_usuario = $fila["COD_USUARIO"];
         
            if($fila["CONTRASENA"] == $password){
                echo $cod_usuario ."::"; 
                $sql3 = "UPDATE USUARIOS SET INTENTOS = 0, ULTIMO_INICIO = '$ultimo_intento' WHERE COD_USUARIO = '$cod_usuario'"; 
            }
            else {
                $intentos = $fila["INTENTOS"] + 1 ;                      
                $sql2 = "UPDATE USUARIOS SET INTENTOS = '$intentos', ULTIMO_INICIO = '$ultimo_intento' WHERE COD_USUARIO ='$cod_usuario' ";
                mysqli_query($DB_conn, $sql2);
            }
        }        
    } else {

        // Las credenciales no son válidas, muestre un mensaje de error
        echo "Nombre de usuario o contraseña incorrectos";

    }
}

?>