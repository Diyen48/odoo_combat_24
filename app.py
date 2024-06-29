from flask import Flask, request, jsonify

app = Flask(_name_)

# File paths for data storage
USERS_FILE = 'users.txt'

# Helper functions for file handling
def read_file(filename):
    data = {}
    try:
        with open(filename, 'r') as f:
            for line in f:
                if line.strip():
                    key, value = line.strip().split(':', 1)
                    data[key.strip()] = value.strip()
    except FileNotFoundError:
        pass  # Handle file not found error
    return data

def write_file(filename, data):
    with open(filename, 'w') as f:
        for key, value in data.items():
            f.write(f"{key}:{value}\n")

# Read initial data from text files
users = read_file(USERS_FILE)

# Routes
@app.route('/')
def index():
    return 'Welcome to Level Up Your Fitness!'

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    password = data.get('password')

    if username in users:
        return 'User already exists', 409
    else:
        users[username] = password
        write_file(USERS_FILE, users)  # Update users.txt
        return 'Registration successful!'

if _name_ == '_main_':
    app.run(debug=True)
