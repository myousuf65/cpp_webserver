#include <iostream>
#include "crow.h"
#include "nlohmann/json.hpp"
#include <map>
#include <jwt-cpp/jwt.h>


using std::cout , std::endl, std::string, std::vector, std::map;

class Student{

public:
    std::string firstName;
    std::string lastName;
    std::string emailAddress;
    uint32_t phoneNumber;

    Student(std::string firstName, std::string lastName, std::string emailAddress, uint32_t phoneNumber){
        this->firstName = firstName;
        this->lastName = lastName;
        this->emailAddress = emailAddress;
        this->phoneNumber = phoneNumber;
    }
};

class User{

public:
    std::string username;
    std::string password;

    User(const std::string &username, const std::string &password){
        this->username = username;
        this->password = password;
    }

};

std::vector<User> users;
std::map<std::string, Student> studentInfo;
using json = nlohmann::json;

void handlePost(const crow::request& req, crow::response& res)
{
    // Parse the JSON payload
    json payload = json::parse(req.body);

    // Extract first name and last name from the payload
    string key = payload["u:id"];
    string firstName = payload["first_name"];
    string lastName = payload["last_name"];
    string emailAddress = payload["email_address"];
    uint32_t phone = payload["phone"];

    std::cout<<firstName<<" "<<lastName<<std::endl;


    studentInfo.try_emplace(key, Student(firstName, lastName , emailAddress, phone ));
    // Set the response
    res.code = 200;
    res.write("POST request processed successfully");
    res.end();
}

void handleGet(const crow::request& req, crow::response& res) {
    // Create a JSON object with student information
    json responseJson;

    responseJson["All Students"] = json::array(); //declare json array

    for (const auto &pair: studentInfo) {

        //json for single student
        json student;
        student["first_name"] = pair.second.firstName;
        student["last_name"] = pair.second.lastName;
        student["email_address"] = pair.second.emailAddress;
        student["phone_number"] = pair.second.phoneNumber;

        //push single student into array
        responseJson[pair.first].push_back(student);
    }

    // Set the response content type to JSON
    res.add_header("Content-Type", "application/json");
    // Send the JSON response to the client
    res.write(responseJson.dump());
    // Set the response code
    res.code = 200;
    // End the response
    res.end();
}

void handlePut(const crow::request& request, crow::response& response){

    //get json from the request
    json payload = json::parse(request.body);

    //initialize the variable with the provided key
    std::string key = payload["u:id"];

    //retreive address of the pair in map
    Student& updatedRecord = studentInfo.at(key);

    if(payload.contains("first_name")){
        updatedRecord.firstName = payload["first_name"];
    }
    if(payload.contains("last_name")){
        updatedRecord.lastName = payload["last_name"];
    }
    if(payload.contains("email_address")){
        updatedRecord.emailAddress = payload["email_address"];
    }
    if(payload.contains("phone_number")){
        updatedRecord.phoneNumber = payload["phone_number"];
    }


    json updatedstudentJson;
    updatedstudentJson["first_name"] = studentInfo.find(key)->second.firstName;
    updatedstudentJson["last_name"] = studentInfo.find(key)->second.lastName;
    updatedstudentJson["emai_address"] = studentInfo.find(key)->second.emailAddress;
    updatedstudentJson["phone_number"] = studentInfo.find(key)->second.phoneNumber;

    // Set the response content type to JSON
    response.add_header("Content-Type", "application/json");
    // Send the JSON response to the client
    response.write(updatedstudentJson.dump());
    // Set the response code
    response.code = 200;
    // End the response
    response.end();

}


void handleDelete(crow::request& request,crow::response& response){

    //get json from the request
    json payload = json::parse(request.body);

    //initialize the variable with the provided key
    std::string key = payload["u:id"];


    auto deleteRecord = studentInfo.at(key);

    studentInfo.erase(key);

    json deleteJson;
    deleteJson["first_name"] = deleteRecord.firstName;
    deleteJson["last_name"] =  deleteRecord.lastName;
    deleteJson["email_address"] = deleteRecord.emailAddress;
    deleteJson["phone_number"] = deleteRecord.phoneNumber;


    // Set the response content type to JSON
    response.add_header("Content-Type", "application/json");
    // Send the JSON response to the client
    response.write("successfully deleted : " + deleteJson.dump());
    // Set the response code
    response.code = 200;
    // End the response
    response.end();
}

void handleLogin(crow::request& request,crow::response& response){


    json payload = json::parse(request.body);

    string username = payload["username"];
    string password = payload["password"];
    string email = payload["email"];

    users.push_back(User(username, password));

    for(auto& user: users){
        cout<<user.username << " , "<< user.password <<endl;
    }

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point expiry = now + std::chrono::hours(1);

    auto token = jwt::create()
            .set_issuer("auth0")
            .set_type("JWS")
            .set_expires_at(expiry)
            .set_payload_claim("username", jwt::claim(username ))
            .set_payload_claim("email", jwt::claim(email))
            .sign(jwt::algorithm::hs256{"OFY4Spw2k2A4IQAUW7CE4mkrt5itGp0Y"});


//    cout<<token<<endl;

    response.add_header("Content-Type", "application/json");
//     Send the JSON response to the client
    response.write("jwt token : " + token);
    // Set the response code
    response.code = 200;
    // End the response
    response.end();

}

void handleGetLogin(crow::request& request,crow::response& response){
    for(auto& user : users){
        cout<<user.username<<" , "<<user.password<<" , "<<endl;
    }

    response.write("printed");
    response.code = 200;
    response.end();
}


int main()
{
    //controller
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api/post").methods("POST"_method)(handlePost);

    CROW_ROUTE(app, "/api/get").methods("GET"_method)(handleGet);

    CROW_ROUTE(app, "/api/put").methods("PUT"_method)(handlePut);

    CROW_ROUTE(app, "/api/delete").methods("DELETE"_method)(handleDelete);

    CROW_ROUTE(app, "/api/login").methods("POST"_method)(handleLogin);

    CROW_ROUTE(app, "/api/get/login").methods("GET"_method)(handleGetLogin);



    app.port(8080).multithreaded().run();

    return 0;
}
