<?php

    //configuration
    require("../includes/config.php");
    
    //if form was submitted
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //TODO
        
        
        if (empty($_POST["username"]))
        {
            apologize("You must provide your username.");
        }
        else if (empty($_POST["password"]))
        {
            apologize("You must provide your password.");
        }
        else if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Your passwords do no match");
        }
        
        $rows = query("INSERT INTO users (username, hash, cash) VALUES (?, ?, 10000.00)", $_POST['username'], crypt($_POST['password']));

        $rows = query("SELECT * FROM users WHERE username = ?", $_POST["username"]);

        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's input against hash that's in database
            if (crypt($_POST["password"], $row["hash"]) == $row["hash"])
            {
                // remember that user's now logged in by storing user's ID in session
                $_SESSION["id"] = $row["id"];

                // redirect to portfolio
                redirect("/");
            }
        }
        
        if ($rows === false)
        {
            apologize("The username " . $_POST["username"] . " is already in use.");
        }
            
    }
    else
    {
        //else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
    
