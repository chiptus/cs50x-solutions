import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, g
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, get_user_total_cash, \
    get_user_details, get_user_stocks, get_symbols_owned, get_shares_owned, two_decimals


# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True
app.jinja_env.filters['two_decimals'] = two_decimals
# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    # get user data
    user = get_user_details(db, user_id)
    # get user stocks (grouped by symbol - sum of bought stocks - sum of sold stocks by symbol)
    stocks, total_value = get_user_stocks(db, user_id)
    return render_template("index.html", stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # get symbol
        symbol = request.form.get("symbol")

        # make sure symbol is provided
        if not symbol:
            return apology("must provide symbol")

        # make sure shares is provided and is a positive integer
        shares = request.form.get("shares")

        if not shares:
            return apology("must provide number of shares")

        try:
            shares = int(shares)
        except:
            return apology("shares must be an integer: " + str(type(shares)))

        if shares <= 0:
            return apology("shares must be a positive integer")

        # lookup symbol's price
        quote = lookup(symbol)

        # if doesn't exist render apology
        if not quote:
            return apology(f"symbol {symbol} does not exist")

        user_id = session.get("user_id")

        # get user amount of cash
        total_cash = get_user_total_cash(db, user_id)
        stock_price = quote["price"]
        total_price = stock_price * shares
        if total_cash < total_price:
            return apology("sorry, you don't have enough funds")

        # add transaction to table
        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, type) VALUES (:user_id, :symbol, :price, :shares, 0)",
                   user_id=user_id,
                   symbol=symbol,
                   price=stock_price,
                   shares=shares
                   )
        # substract total_price from user's cash
        db.execute("UPDATE users SET cash = :cash WHERE id = :user_id",
                   cash=total_cash - total_price,
                   user_id=user_id)

        session['balance'] = session['balance'] - total_price
        session['stock_balance'] = session['stock_balance'] + total_price

        # return index
        return redirect("/")
    return render_template("buy.html", symbol=request.args.get('symbol', default=''))


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    stocks = db.execute(
        "SELECT * from transactions WHERE user_id = :user_id", user_id=session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        user = rows[0]
        session["user_id"] = user["id"]
        session['balance'] = user["cash"]
        _, session['stock_balance'] = get_user_stocks(db, user["id"])
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # get stock's symbol `input[name='symbol']
        symbol = request.form.get("symbol")
        # return apology if missing
        if not symbol:
            return apology("Symbol is required")

        # look up for the value of the symbol

        quote = lookup(symbol)
        if not quote:
            # return apology if symbol doesn't exist
            return apology(f"Symbol {symbol} does not exist")

        # return quoted.html with symbol and value
        return render_template("quoted.html", company=quote['name'], symbol=symbol, price=f"{quote['price']:0.2f}")

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        username = request.form.get("username")

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 400)
        password = request.form.get("password")

        # Ensure confirmation was submitted
        if not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Check if user exists
        existing_user_query = db.execute(
            "SELECT id FROM users WHERE username = :username", username=username)
        is_user_exists = len(existing_user_query) > 0
        if is_user_exists:
            return apology("User with this username already exists", 400)

        if password != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Store user into `users`
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                             username=username,
                             hash=generate_password_hash(password))

        session["user_id"] = user_id

        session['balance'] = 10000
        session['stock_balance'] = 0

        return redirect("/")
    # on GET
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":

        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Failed to select a stock")

        shares_owned = get_shares_owned(db, user_id, symbol)

        if shares_owned <= 0:
            return apology("You don't own any shares of this stock")

        shares = request.form.get("shares")

        if not shares:
            return apology("must provide number of shares")

        try:
            shares = int(shares)
        except:
            return apology("shares must be an integer: " + str(type(shares)))

        if shares <= 0:
            return apology("shares must be a positive integer")

        if shares > shares_owned:
            return apology("You don't own enough shares of this stock")

        quote = lookup(symbol)

        if not quote:
            return apology("Symbol does not exist")

        stock_price = quote["price"]
        total_price = stock_price * shares

        db.execute("INSERT INTO transactions (user_id, symbol, price, shares, type) VALUES (:user_id, :symbol, :price, :shares, 1)",
                   user_id=user_id,
                   symbol=symbol,
                   price=stock_price,
                   shares=shares
                   )

        db.execute("""
            UPDATE users
            SET cash = cash + :total_price
            WHERE id = :user_id
        """, user_id=user_id, total_price=total_price)

        session['balance'] = session['balance'] + total_price
        session['stock_balance'] = session['stock_balance'] - total_price

        return redirect("/")

    return render_template("sell.html", symbols=get_symbols_owned(db, user_id), selected_symbol=request.args.get('symbol', default=''))


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
