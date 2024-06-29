function register() {
    const username = document.getElementById('reg_username').value;
    const password = document.getElementById('reg_password').value;
    fetch('/register', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, password })
    })
    .then(response => response.text())
    .then(data => {
        document.getElementById('reg_result').innerText = data;
    });
}

function login() {
    const username = document.getElementById('username').value;
    const password = document.getElementById('password').value;
    fetch('/login', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, password })
    })
    .then(response => response.text())
    .then(data => {
        document.getElementById('login_result').innerText = data;
    });
}

function updateProfile() {
    const username = document.getElementById('profile_username').value;
    const age = document.getElementById('age').value;
    const gender = document.getElementById('gender').value;
    const weight = document.getElementById('weight').value;
    const height = document.getElementById('height').value;
    const fitness_goals = document.getElementById('fitness_goals').value;
    const health_conditions = document.getElementById('health_conditions').value;
    fetch('/update_profile', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ username, age, gender, weight, height, fitness_goals, health_conditions })
    })
    .then(response => response.text())
    .then(data => {
        document.getElementById('profile_result').innerText = data;
    });
}
