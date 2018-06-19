<?php

    // configuration
    require("../includes/config.php"); 
    
    $rows = query("SELECT * FROM portfolio WHERE id = ?", $_SESSION["id"]);
    $users_cash = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    $cash = $users_cash[0]["cash"];
    $gross = 0;

    
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
    
    if ($stock !== false)
    {
        $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"],
            "total" => ($stock["price"] * $row["shares"])
        ];
    }
        $gross += ($stock["price"] * $row["shares"]);
    }
    
    

    // render portfolio
    render("portfolio.php", ["cash" => $cash, "gross" => $gross, "positions" => $positions, "title" => "Portfolio"]);

?>
