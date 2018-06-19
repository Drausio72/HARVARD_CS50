<!DOCTYPE html>

<html>


    <body>

        <div class="container">

        <div id="top">
<center>    
<ul class="nav nav-pills">
    <li><a href="quote.php">Quote</a></li>
    <li><a href="buy.php">Buy</a></li>
    <li><a href="sell.php">Sell</a></li>
    <li><a href="log_controller.php">Transaction Log</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="sell" placeholder="Stock symbol to be sold" type="text"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell stock</button>
        </div>
    </fieldset>
</form>
<div>
    <a href="logout.php">Log Out</a>
</div>
