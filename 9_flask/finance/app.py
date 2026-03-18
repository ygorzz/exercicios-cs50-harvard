import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Função de porcentagem registrada como filtro Jinja
def percentage(value):
    return f"{value:,.2f}%"
app.jinja_env.filters["percentage"] = percentage

# Configure session to use filesystem
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Agrupa por símbolo para mostrar o total de ações (compras - vendas)
    stocks = db.execute(
        "SELECT symbol, name, SUM(shares) as total_shares FROM purchase WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0",
        user_id
    )

    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    total_value = cash
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["price"] = quote["price"]
        stock["total"] = stock["price"] * stock["total_shares"]
        total_value += stock["total"]

    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(total_value))

@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Permite ao usuário adicionar saldo à conta"""
    user_id = session["user_id"]

    if request.method == "POST":
        amount = request.form.get("amount")

        # Validação simples do valor
        try:
            amount = float(amount)
            if amount <= 0:
                return apology("must provide a positive amount")
        except ValueError:
            return apology("amount must be a number")

        # Atualiza o saldo no banco de dados
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)

        # Opcional: Registrar no histórico como "DEPOSIT"
        db.execute("INSERT INTO purchase (user_id, symbol, name, shares, price, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, "CASH", "Deposit", 1, amount, "DEPOSIT")

        flash("Cash added successfully!")
        return redirect("/")

    else:
        # Busca o saldo atual para exibir na página
        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        current_cash = row[0]["cash"]
        return render_template("add_cash.html", current_cash=usd(current_cash))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol")

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol")

        try:
            shares = int(shares)
            if shares <= 0:
                return apology("shares must be positive")
        except ValueError:
            return apology("shares must be an integer")

        user_id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        cost = shares * stock["price"]
        if cash < cost:
            return apology("can't afford")

        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)
        db.execute("INSERT INTO purchase (user_id, symbol, name, shares, price, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], stock["name"], shares, stock["price"], "BUY")

        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT type, symbol, shares, price, timestamp FROM purchase WHERE user_id = ? ORDER BY timestamp DESC",
        session["user_id"]
    )
    return render_template("history.html", transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol")
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username")
        if not password or not confirmation:
            return apology("must provide password")
        if password != confirmation:
            return apology("passwords do not match")

        hash = generate_password_hash(password)
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("username already exists")

        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        owned = db.execute("SELECT SUM(shares) as total FROM purchase WHERE user_id = ? AND symbol = ?",
                          user_id, symbol)[0]["total"]

        if not symbol:
            return apology("must provide symbol")

        # Verifique se shares é um número positivo (você já fez o int(), mas garanta que > 0)
        if shares <= 0:
            return apology("shares must be positive")

        rows = db.execute("SELECT SUM(shares) as total FROM purchase WHERE user_id = ? AND symbol = ?",
                          user_id, symbol)

        if not rows or not rows[0]["total"] or shares > rows[0]["total"]:
            return apology("too many shares")
        if shares > owned:
            return apology("too many shares")

        stock = lookup(symbol)
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", shares * stock["price"], user_id)
        db.execute("INSERT INTO purchase (user_id, symbol, name, shares, price, type) VALUES (?, ?, ?, ?, ?, ?)",
                   user_id, stock["symbol"], stock["name"], -shares, stock["price"], "SELL")

        return redirect("/")
    else:
        stocks = db.execute("SELECT symbol FROM purchase WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", stocks=stocks)
