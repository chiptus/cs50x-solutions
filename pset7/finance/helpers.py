import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def lookup(symbol):
    """Look up quote for symbol."""

    # Contact API
    try:
        response = requests.get(f"https://api.iextrading.com/1.0/stock/{urllib.parse.quote_plus(symbol)}/quote")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        quote = response.json()
        return {
            "name": quote["companyName"],
            "price": float(quote["latestPrice"]),
            "symbol": quote["symbol"]
        }
    except (KeyError, TypeError, ValueError):
        return None


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def get_user_total_cash(db, user_id):
    # check if user is able to buy
    rows = db.execute("SELECT cash FROM users WHERE id = :id",
                      id=session["user_id"])

    # Ensure user exists
    if len(rows) != 1:
        raise Error("User does not exist")
    
    return rows[0]["cash"]
    
        
def get_user_details(db, user_id):
    rows = db.execute("SELECT * FROM users WHERE id = :id",
                      id=session["user_id"])

    # Ensure user exists
    if len(rows) != 1:
        raise Error("User does not exist")
    
    return rows[0]
    
def get_user_stocks(db, user_id):
    # get total bought stocks for symbol
    # get total sold stocks for symbol
    # lookup current value of the symbols
    # return the difference
    
    stocks_query = """
            SELECT symbol, SUM(shares) as shares FROM transactions WHERE user_id = :user_id AND type = :type
           GROUP BY symbol
           """
    
    rows_bought = db.execute(stocks_query, user_id=user_id, type=0)
    rows_sold = db.execute(stocks_query, user_id=user_id, type=1)
    
    dict_bought = {x['symbol']: x['shares'] for x in rows_bought}
    dict_sold = {x['symbol']: x['shares'] for x in rows_sold}
    
    stocks = []
    sum = 0
    # Assumes that there are no negative number of shares
    for symbol, shares in dict_bought.items():
        sold_shares = dict_sold.get(symbol, 0)
        total_shares = shares - sold_shares
        if total_shares <= 0:
            continue
        current_price = lookup(symbol)['price']
        total_value = current_price * total_shares
        sum = sum + total_value
        stocks.append({'symbol': symbol, 'shares': total_shares, 'current_price': current_price, 'total_value': total_value})
        
    return stocks, sum
    
def get_symbols_owned(db, user_id):
    stocks,_ = get_user_stocks(db, user_id)
    return [stock['symbol'] for stock in stocks]
    

def get_shares_owned(db, user_id, symbol):
    stocks_query = """
            SELECT SUM(shares) as shares FROM transactions WHERE user_id = :user_id AND type = :type AND symbol = :symbol
           """
    
    rows_bought = db.execute(stocks_query, user_id=user_id, type=0, symbol=symbol)
    rows_sold = db.execute(stocks_query, user_id=user_id, type=1, symbol=symbol)
    
    print(rows_bought, rows_sold)
    
    bought = rows_bought[0]["shares"] if len(rows_bought) > 0 else 0
    if not bought:
        bought = 0
    
    sold = rows_sold[0]["shares"] if len(rows_sold) > 0 else 0
    if not sold:
        sold = 0
        
    return bought - sold