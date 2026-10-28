#ifndef CLAIM_H
#define CLAIM_H

#include <iostream>
#include <string>

// Valid status values: PENDING  /  APPROVED  /  REJECTED
// A new claim is always created with status PENDING.
// Only the company may change status to APPROVED or REJECTED.

class Claim
{
    std::string number;     // Claim number
    std::string procedure;  // Description of the medical procedure
    double amount;     // Amount of money requested
    std::string status;     // PENDING / APPROVED / REJECTED

public:
    Claim(const std::string& number, const std::string& procedure, double amount);
    // Creates a new claim with given data
    // Status is set to PENDING by default

    Claim(const Claim& c);
    // Copy constructor

    int compare_number(const std::string& x) const;
    // Compares current number with given number

    const std::string& get_number()    const;
    // Returns claim number

    const std::string& get_procedure() const;
    // Returns procedure name

    double get_amount() const;
    // Returns amount of money requested

    const std::string& get_status() const;
    // Returns status of claim

    void approve();
    // Sets status to APPROVED

    void reject();
    // Sets status to REJECTED

    bool is_approved() const;
    // Returns true if status is APPROVED

    double& ref_amount();
    // Returns reference to amount

    friend std::ostream& operator<<(std::ostream& os, const Claim& c);
    // Outputs one claim
};

#endif
