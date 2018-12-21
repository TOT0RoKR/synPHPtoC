<?php
    
   // header('content-type: text/html; charset=utf-8'); 
    // 데이터베이스 접속 문자열. (db위치, 유저 이름, 비밀번호)
    $connect=mysqli_connect( "localhost","root","mario34","simpleboard");
   // mysqli_query("SET NAMES UTF8");
 
   
   // 세션 시작
   session_start();

   $id = $_POST[u_id];
   $act = $_POST[u_act]; 
   $date = date("Y-m-d");
   $time = date("H:i:s");

   echo "$id  $act \n";
   echo "$date  $time \n";
 
 
$query="select id from member where id='$id'";

if($result=mysqli_query($connect,$query)){
    $row_num=mysqli_num_rows($result);

    if($row_num > 0){

        $sql = "INSERT INTO attendance(id, date, time, act) VALUES('$id', '$date', '$time', '$act')";
 
        $result = mysqli_query($connect,$sql);
    }
    else {
        $result = 0;
    }
} 
else {
   $result = 0;
}
if(!$result)
     die("mysql query error");
else
     echo "insert success";
 
?>

