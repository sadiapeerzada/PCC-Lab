"""Week 12, Problem 12.3: simple registration/login/protected API.
Demonstration only. Uses hashed passwords and signed session cookies.
For production use managed identity and a persistent managed database.
"""
import os
import secrets
import sqlite3
from pathlib import Path
from flask import Flask, jsonify, request, session
from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)
app.config.update(
    SECRET_KEY=os.environ.get("SECRET_KEY") or secrets.token_hex(32),
    SESSION_COOKIE_HTTPONLY=True,
    SESSION_COOKIE_SAMESITE="Lax",
    SESSION_COOKIE_SECURE=os.environ.get("APP_ENV") == "production",
    MAX_CONTENT_LENGTH=16 * 1024,
)
DB = Path(os.environ.get("AUTH_DB", "users.db"))


def connect_db():
    db = sqlite3.connect(DB)
    db.row_factory = sqlite3.Row
    db.execute("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password_hash TEXT NOT NULL)")
    db.commit()
    return db


def credentials():
    data = request.get_json(silent=True)
    if not isinstance(data, dict):
        return None, None, "Expected a JSON object"
    username = data.get("username")
    password = data.get("password")
    if not isinstance(username, str) or not (3 <= len(username) <= 40):
        return None, None, "Username must be 3-40 characters"
    if not isinstance(password, str) or not (8 <= len(password) <= 128):
        return None, None, "Password must be 8-128 characters"
    return username, password, None


@app.post("/register")
def register():
    username, password, error = credentials()
    if error:
        return jsonify(error=error), 400
    with connect_db() as db:
        try:
            db.execute("INSERT INTO users(username, password_hash) VALUES(?, ?)",
                       (username, generate_password_hash(password)))
            db.commit()
        except sqlite3.IntegrityError:
            return jsonify(error="Username already exists"), 409
    return jsonify(message="Registered successfully"), 201


@app.post("/login")
def login():
    username, password, error = credentials()
    if error:
        return jsonify(error=error), 400
    with connect_db() as db:
        user = db.execute("SELECT password_hash FROM users WHERE username=?", (username,)).fetchone()
    if user is None or not check_password_hash(user["password_hash"], password):
        return jsonify(error="Invalid credentials"), 401
    session.clear()
    session["username"] = username
    return jsonify(message="Login successful"), 200


@app.get("/protected")
def protected():
    username = session.get("username")
    if not username:
        return jsonify(error="Login required"), 401
    return jsonify(message=f"Welcome, {username}!"), 200


@app.post("/logout")
def logout():
    session.clear()
    return jsonify(message="Logged out"), 200


if __name__ == "__main__":
    # Development only; place behind HTTPS reverse proxy for cloud deployment.
    app.run(host="127.0.0.1", port=5000, debug=False)
