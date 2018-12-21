<?php

	session_start();

	$method = $_POST[mtd];
	$value = $_POST[val];

	$aaa = exec("./srvapp/controler $method $value");
	echo "$aaa" ;

?>
