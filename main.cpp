#include <crow.h>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <iostream>

// Function to load data from a text file
std::unordered_map<std::string, std::string> load_data(const std::string& filename) {
    std::unordered_map<std::string, std::string> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, ':') && std::getline(iss, value)) {
            data[key] = value;
        }
    }
    return data;
}

// Function to save data to a text file
void save_data(const std::unordered_map<std::string, std::string>& data, const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& pair : data) {
        file << pair.first << ":" << pair.second << "\n";
    }
}

int main() {
    crow::SimpleApp app;

    // Load data from files
    auto users = load_data("users.txt");
    auto profiles = load_data("profiles.txt");

    // Serve the HTML file
    CROW_ROUTE(app, "/")([](){
        std::ifstream file("index.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    });

    // Login route
    CROW_ROUTE(app, "/login").methods("POST"_method)([&users](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        if (users.find(username) != users.end() && users[username] == password) {
            return crow::response("Login successful!");
        } else {
            return crow::response(403, "Invalid username or password");
        }
    });

    // Registration route
    CROW_ROUTE(app, "/register").methods("POST"_method)([&users](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::string username = x["username"].s();
        std::string password = x["password"].s();

        if (users.find(username) != users.end()) {
            return crow::response(409, "User already exists");
        } else {
            users[username] = password;
            save_data(users, "users.txt");
            return crow::response("Registration successful!");
        }
    });

    // Profile update route
    CROW_ROUTE(app, "/update_profile").methods("POST"_method)([&profiles](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        std::string username = x["username"].s();
        std::string profile_data = x["age"].s() + "," + x["gender"].s() + "," + x["weight"].s() + "," + x["height"].s() + "," + x["fitness_goals"].s() + "," + x["health_conditions"].s();

        profiles[username] = profile_data;
        save_data(profiles, "profiles.txt");
        return crow::response("Profile updated!");
    });

    // Start the server on port 18080
    app.port(18080).multithreaded().run();
}
