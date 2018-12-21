<?php
$conn=mysqli_connect("localhost","root","mario34","simpleboard");

$query="select m.name,a.date,a.time,a.act from attendance a,member m where a.id=m.id order by a.date desc, a.time desc limit 0,20";

if($result=mysqli_query($conn,$query)){
    $row_num=mysqli_num_rows($result);

    echo "<table border=\"1\">";
  	echo "<tr>";
            echo "<th >이름</th>";
             echo "<th >날짜</th>";
             echo "<th >시간</th>";
             echo "<th >구분</th>";
        echo "</tr>";
        for($i = 0; $i < $row_num; $i++) {
            $row = mysqli_fetch_array($result);
            echo "<tr>";
		echo "<td> $row[0] </td>";
		echo "<td> $row[1] </td>";
		echo "<td> $row[2] </td>";
		echo "<td> $row[3] </td>";
            echo "</tr>";
        }
    echo "</table>";

    //$sql = "INSERT INTO board(seq, author, title, content) VALUES(10, 'aaaaaaa', 'aaaaaa','aaaaaaa')";
 
    //$result = mysqli_query($conn,$sql);
}

else{
    echo "fail";
}
?>
