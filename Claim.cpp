#include "Claim.h"

Claim::Claim(const std::string& number, const std::string& procedure, double amount)
    : number(number), procedure(procedure), amount(amount), status("PENDING")
{
}

Claim::Claim(const Claim& c)
    : number(c.number), procedure(c.procedure), amount(c.amount), status(c.status)
{
}

int Claim::compare_number(const std::string& x) const
{
    if (number < x) return -1;
    if (number > x) return  1;
    return 0;
}

const std::string& Claim::get_number() const
{
    return number;
}

const std::string& Claim::get_procedure() const
{
    return procedure;
}

double Claim::get_amount() const
{
    return amount;
}

const std::string& Claim::get_status() const
{
    return status;
}

void Claim::approve()
{
    status = "APPROVED";
}

void Claim::reject()
{
    status = "REJECTED";
}

bool Claim::is_approved() const
{
    return status == "APPROVED";
}

double& Claim::ref_amount()
{
    return amount;
}

std::ostream& operator<<(std::ostream& os, const Claim& c)
{
    os << " Claim No: " << c.number
       << " | Procedure: " << c.procedure
       << " | Amount: " << c.amount << " PLN"
       << " | Status: " << c.status << "]";
    return os;
}
