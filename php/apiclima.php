<?php

$token="9411af434f1da79b75ff8f3164fd19f7";
$city="cordoba";
$lang="sp";
$units="metric";
$url= "https://api.openweathermap.org/data/2.5/weather?q=$city&appid=$token&units=$units&lang=$lang"; //Aca armo la url

$response = file_get_contents($url); //con este traigo la info de la url
$data = json_decode($response); //Aca convierte el JSON en variable PHP

if ($data->cod === 200) { //Corrobora que la pagina no tienen error
    $temperature = $data->main->temp; //Traigo las variables que deseo y las muestro
    echo "Córdoba $temperature °C"; //Muestro
} else {
    echo "No se pudo obtener la temperatura actual.";
}






?>
