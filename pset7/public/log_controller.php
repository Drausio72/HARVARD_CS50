<?php

// configuration
    require("../includes/config.php");
    
    date_default_timezone_set('UTC');
    
    $positions = [];     
    $rows = query("SELECT * FROM log WHERE id = ?", $_SESSION["id"]);
    $cash = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
       foreach ($rows as $row)
       {
        $positions[] = [
            "date" => $row["date"],
            "transaction" => $row["transaction"],
            "symbol" => $row["symbol"],
            "name" => $row["name"],
            "shares" => $row["shares"],
            "price" => $row["price"]
        ];
        }
        
        render("log.php", ["cash" => $cash[0]["cash"],"positions" => $positions, "title" => "Transaction Log"]);
    
?>
