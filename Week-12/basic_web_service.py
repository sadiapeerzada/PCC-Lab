"""Week 12, Problem 12.4: basic RESTful Flask web service."""
import os
from flask import Flask, jsonify, request

app = Flask(__name__)
app.config["MAX_CONTENT_LENGTH"] = 16 * 1024
items = []  # Demo-only in-memory storage, resets when the process restarts.


@app.get("/hello")
def hello():
    return jsonify(message="Hello, World!")


@app.get("/greet")
def greet():
    name = request.args.get("name", "User").strip()[:80] or "User"
    return jsonify(message=f"Hello, {name}!")


@app.get("/items")
def list_items():
    return jsonify(items=items)


@app.post("/items")
def add_item():
    body = request.get_json(silent=True)
    if not isinstance(body, dict) or not isinstance(body.get("name"), str):
        return jsonify(error="Provide JSON with a string 'name'"), 400
    name = body["name"].strip()
    if not (1 <= len(name) <= 80):
        return jsonify(error="Item name must be 1-80 characters"), 400
    items.append({"id": len(items) + 1, "name": name})
    return jsonify(items[-1]), 201


if __name__ == "__main__":
    app.run(host="127.0.0.1", port=int(os.environ.get("PORT", "5001")), debug=False)
