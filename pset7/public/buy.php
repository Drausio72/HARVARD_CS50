<?php

// configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (preg_match("/^\d+$/", $_POST["amount"]) === false || empty($_POST["amount"]))
        {
            apologize("You must provide a valid amount"); 
        }
        
        $buy_upper = strtoupper($_POST["buy"]);
        
        $stock = lookup($buy_upper);
           
        if (empty($_POST["buy"]) || $stock === false)
        {
            apologize("You must provide a valid stock symbol");
        }     


        $balances = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
            
        $cost = $stock["price"] * $_POST["amount"];
            
        if ($cost > $balances[0]["cash"])
       {
            apologize("Sorry, not enough balance for this transaction");
       }
       
       
    
       query("INSERT INTO portfolio (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock["symbol"], $_POST["amount"]);
       query("UPDATE users SET cash = cash - ? WHERE id = ?", $cost, $_SESSION["id"]);
       query("INSERT INTO log (id, date, transaction, symbol, name, shares, price) VALUES(?, ?, 'Buy', ?, ?, ?, ?)", $_SESSION["id"], date(DATE_RFC2822), $stock["symbol"], $stock["name"], $_POST["amount"], $stock["price"]); 
        

       redirect("log_controller.php");
    } 
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Buy"]);
    }

?>
