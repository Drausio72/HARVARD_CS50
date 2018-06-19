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

<p class="lead text-danger">
    Sorry!
</p>
<p class="text-danger">
    <?= htmlspecialchars($message) ?>
</p>

<a href="javascript:history.go(-1);">Back</a>

<div>
    <a href="logout.php">Log Out</a>
</div>
