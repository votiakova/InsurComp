#include "Client.h"

Client::Client(const std::string& id, const std::string& name, int age)
    : id(id), name(name), age(age), company(nullptr)
{
}

Client::Client(const Client& c)
    : id(c.id), name(c.name), age(c.age), company(nullptr)
{
}

int Client::compare_id(const std::string& x) const
{
    if (id < x) return -1;
    if (id > x) return  1;
    return 0;
}

const std::string& Client::get_id() const
{
    return id;
}

const std::string& Client::get_name() const
{
    return name;
}

int Client::get_age() const
{
    return age;
}

int& Client::ref_age()
{
    return age;
}

void Client::set_company(InsuranceCompany* c)
{
    company = c;
}

const InsuranceCompany* Client::get_company() const
{
    return company;
}

bool Client::is_registered() const
{
    return company != nullptr;
}

std::ostream& operator<<(std::ostream& os, const Client& c)
{
    os << "Client ID: " << c.id
       << " | Name: " << c.name
       << " | Age: " << c.age << "]";
    return os;
}
