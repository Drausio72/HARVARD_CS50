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
</center>

            </div>

            <div id="middle">


<table class="table table-striped">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>

    <?php foreach ($positions as $position): ?>

    <tr>
        <td><?= $position["symbol"] ?></td>
        <td><?= $position["name"] ?></td>
        <td><?= $position["shares"] ?></td>
        <td><?= "$" . number_format($position["price"],2) ?></td>
        <td><?= "$" . number_format($position["total"],2) ?></td>
    </tr>

    <?php endforeach ?>
    <tr>
        <td colspan="3">TOTAL INVESTED</td>
        <td colspan="7"><?= "$" . number_format($gross,2) ?></td>
    </tr>
    <tr>
        <td colspan="3">ACCOUNT BALANCE</td>
        <td colspan="7"><?= "$" . number_format($cash,2) ?></td>
    </tr>

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
    <a href="logout.php">Log Out</a>
</div>


