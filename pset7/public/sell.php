<?php

// configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["sell"]))
        {
            apologize("You must provide a valid stock symbol");
        }
        if (!query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]))
        {
            apologize("Sorry, but you don't own that stock");
        }
        $stock = lookup($_POST["sell"]);
        if ($stock === false)
        {
            apologize("Invalid symbol.");
        }
        else if ($stock["price"])
        {
            $shares = query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]);
            $sale = $stock["price"] * $shares[0]["shares"];
        }
        
        if (!query("SELECT * FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]))
        {
            apologize("Sorry, but you don't own that stock");
        }
        else
        {

            query("DELETE FROM portfolio WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["sell"]);
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $sale, $_SESSION["id"]);
            query("INSERT INTO log (id, date, transaction, symbol, name, shares, price) VALUES(?, ?, 'Sell', ?, ?, ?, ?)", $_SESSION["id"], date(DATE_RFC2822), $stock["symbol"], $stock["name"], $shares[0]["shares"], $stock["price"]); 
            redirect("log_controller.php");
        
        }
        


    }
    else
    {
        // else render form
        render("sell_form.php", ["title" => "Sell"]);
    }

?>
