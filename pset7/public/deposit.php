<?php

// configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
           
        if (empty($_POST["amount"]))
        {
            apologize("You must provide a valid amount");
        }     
            
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["amount"], $_SESSION["id"]); 
        
        congratulate("You just deposited $" . $_POST["amount"] . " dollars.");
            
    }
    else
    {
        // else render form
        render("deposit_form.php", ["title" => "Deposit"]);
    }

?>
