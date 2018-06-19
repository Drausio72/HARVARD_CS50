<?php

// configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must provide a valid stock symbol");
        }

        $stock = lookup($_POST["symbol"]);


        if ($stock === false)
        {
            apologize("Invalid symbol.");
        }
        else if ($stock["price"])
        {
            result($stock["symbol"], $stock["name"], $stock["price"]);
        }
        


    }
    else
    {
        // else render form
        render("quote_form.php", ["title" => "Quotes"]);
    }

?>
