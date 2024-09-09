from flask import Flask, request, jsonify, render_template, redirect, url_for
import sqlite3
import subprocess

app = Flask(__name__)
DATABASE = 'access_control.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('DROP TABLE IF EXISTS users')
        cursor.execute('DROP TABLE IF EXISTS rfid_tags')
        cursor.execute('DROP TABLE IF EXISTS access_logs')

        cursor.execute('''
            CREATE TABLE users (
                id TEXT PRIMARY KEY,
                name TEXT
            )
        ''')
        cursor.execute('''
            CREATE TABLE rfid_tags (
                tag_id TEXT PRIMARY KEY,
                user_id TEXT,
                FOREIGN KEY(user_id) REFERENCES users(id)
            )
        ''')
        cursor.execute('''
            CREATE TABLE access_logs (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp TEXT,
                tag_id TEXT,
                access_granted INTEGER
            )
        ''')
    conn.close()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/add_user', methods=['POST'])
def add_user():
    user_id = request.form.get('user_id')
    name = request.form.get('name')
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('INSERT OR IGNORE INTO users (id, name) VALUES (?, ?)', (user_id, name))
    return jsonify({"status": "success"})

@app.route('/add_tag', methods=['POST'])
def add_tag():
    tag_id = request.form.get('tag_id')
    user_id = request.form.get('user_id')
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('INSERT OR IGNORE INTO rfid_tags (tag_id, user_id) VALUES (?, ?)', (tag_id, user_id))
    return jsonify({"status": "success"})

@app.route('/logs', methods=['GET'])
def logs():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM access_logs ORDER BY timestamp DESC LIMIT 5')
        logs = cursor.fetchall()
    return jsonify(logs)

@app.route('/simulate', methods=['POST'])
def simulate():
    tag_id = request.json.get('tag_id')
    try:
        result = subprocess.run(['./rfid_simulation', tag_id], capture_output=True, text=True, check=True)
        access_granted = "Access Granted" in result.stdout
    except subprocess.CalledProcessError as e:
        return jsonify({
            "status": "error",
            "message": "Error simulating access",
            "details": str(e),
            "stdout": e.stdout,
            "stderr": e.stderr
        }), 500
    except Exception as e:
        return jsonify({
            "status": "error",
            "message": "Unexpected error",
            "details": str(e)
        }), 500

    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('INSERT INTO access_logs (timestamp, tag_id, access_granted) VALUES (datetime("now"), ?, ?)', (tag_id, int(access_granted)))
        cursor.execute('DELETE FROM access_logs WHERE id NOT IN (SELECT id FROM access_logs ORDER BY timestamp DESC LIMIT 5)')
    
    if access_granted:
        return jsonify({"status": "success", "access_granted": access_granted, "redirect_url": url_for('house')})
    else:
        return jsonify({"status": "success", "access_granted": access_granted})

@app.route('/house')
def house():
    return render_template('house.html')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)
