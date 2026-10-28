#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

class InsuranceCompany;

class Client
{
    std::string id;
    std::string name;
    int age;
    InsuranceCompany* company;   // nullptr when not registered in any company

public:
    Client(const std::string& id, const std::string& name, int age);
    // Creates a client with given parameters

    Client(const Client& c);
    // Copy constructor — company pointer is NOT copied (copy starts unregistered)

    int compare_id(const std::string& x) const;
    // Compares current id with given id
    // Returns 0 if equal, -1 if smaller, 1 if greater

    const std::string& get_id() const;
    // Returns client id

    const std::string& get_name() const;
    // Returns client name

    int get_age() const;
    // Returns age of client

    int& ref_age();
    // Returns reference to age

    void set_company(InsuranceCompany* company);
    // Sets the owning company pointer (called by InsuranceCompany)

    const InsuranceCompany* get_company() const;
    // Returns pointer to the company this client is registered in,
    // or nullptr if the client is not registered anywhere

    bool is_registered() const;
    // Returns true if this client is currently registered in a company

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
    // Outputs one client
};

#endif
