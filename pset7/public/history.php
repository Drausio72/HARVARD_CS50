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
    <li><a href="history.php">History</a></li>
    <li><a href="logout.php"><strong>Log Out</strong></a></li>
</ul>
</center>

            </div>

            <div id="middle">


<table class="table table-striped">
    <thead>
        <tr>
            <th>Date</th>
            <th>Transaction</th>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>

    <tbody>

    <?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["date"] ?></td>
        <td><?= $position["transaction"] ?></td>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= $position["price"] ?></td>
    </tr>

    <?php endforeach ?>

    </tbody>

</table>
            </div>

            <div id="bottom">
                Copyright &#169; John Harvard
            </div>

        </div>

    </body>

</html>


    


<div>
    Your balance: $<?= $formatted_cash ?>
</div>

<div>
    <a href="logout.php">Log Out</a>
</div>


