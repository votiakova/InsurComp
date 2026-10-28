#ifndef INSURANCE_COMPANY_H
#define INSURANCE_COMPANY_H

#include "Client.h"
#include "ClaimList.h"

class InsuranceCompany
{
private:
    struct ClientItem
    {
        Client* client;   
        ClaimList* claims;   
        ClientItem* next;     

        ClientItem();
        // Creates item with null pointers

        ClientItem(const ClientItem& other);
        // Copy constructor
    };

    std::string name;   // Name of the insurance company
    ClientItem* head;   // Pointer to the first element of the list

    void clear_list();
    void copy_from(const InsuranceCompany& other);

public:
    InsuranceCompany(const std::string& name);
    // Creates empty company with given name

    ~InsuranceCompany();
    // Destructor

    InsuranceCompany(const InsuranceCompany& other);
    // Copy constructor

    InsuranceCompany& operator=(const InsuranceCompany& other);
    // Assignment operator

    bool add_client(Client* client);
    // Returns false if client is nullptr or already registered in a company

    bool remove_client(const std::string& id);
    // Removes client by id together with all their medical claims
    // Returns false if not found

    Client* find_client(const std::string& id) const;
    // Searches by id
    // Returns pointer if found, nullptr otherwise

    ClaimList* find_claims(const std::string& id) const;
    // Returns pointer to the claim list of given client
    // Returns nullptr if client not found

    bool file_claim(const std::string& client_id,
                    const std::string& number,
                    const std::string& procedure,
                    double amount);
    // Files a new medical claim for an existing client (status = PENDING)
    // Returns false if client does not exist or claim number is duplicated

    bool cancel_claim(const std::string& client_id,
                      const std::string& number);
    // Removes a medical claim from a client
    // Returns false if client or claim not found

    bool approve_claim(const std::string& client_id,
                       const std::string& number);
    // Marks a claim as APPROVED
    // Returns false if client or claim not found

    bool reject_claim(const std::string& client_id,
                      const std::string& number);
    // Marks a claim as REJECTED
    // Returns false if client or claim not found

    void print_all() const;

    void warning(int age_limit) const;
    // Prints clients older than given age limit (senior clients)

    double total_payouts() const;
    // Returns sum of all APPROVED claim amounts across the company

    friend std::ostream& operator<<(std::ostream& os,
                                    const InsuranceCompany& company);
    // Outputs whole company
};

#endif
