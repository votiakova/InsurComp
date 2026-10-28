#ifndef CLAIM_LIST_H
#define CLAIM_LIST_H

#include "Claim.h"

class ClaimList
{
private:
    struct ClaimItem
    {
        Claim* claim;   // Pointer to Claim object
        ClaimItem* next;    // Pointer to next element in list

        ClaimItem();
        // Creates item with null pointers

        ClaimItem(const ClaimItem& other);
        // Copy constructor — deep-copies the Claim object
    };

    ClaimItem* head;   // Pointer to first element of the list

    void clear_list();
    // Dedicated method: deletes every node and its Claim object.
    // Called by the destructor and the assignment operator so that
    // cleanup logic lives in exactly one place.

    void copy_from(const ClaimList& other);
    // Deep-copies all nodes from another list

public:
    ClaimList();
    // Creates empty list

    ~ClaimList();
    // Destructor — delegates entirely to clear_list()

    ClaimList(const ClaimList& other);
    // Copy constructor

    ClaimList& operator=(const ClaimList& other);
    // Assignment operator

    bool add_claim(const std::string& number,
                   const std::string& procedure,
                   double amount);
    // Adds a new claim with status PENDING
    // Returns false if a claim with the same number already exists

    bool remove_claim(const std::string& number);
    // Removes claim by number
    // Returns false if not found

    Claim* find_claim(const std::string& number) const;
    // Searches claim by number
    // Returns pointer if found, nullptr otherwise

    bool approve_claim(const std::string& number);
    // Marks claim as APPROVED
    // Returns false if not found

    bool reject_claim(const std::string& number);
    // Marks claim as REJECTED
    // Returns false if not found

    void print_all() const;
    // Prints all claims of this client

    double approved_total() const;
    // Returns sum of amounts of all APPROVED claims

    friend std::ostream& operator<<(std::ostream& os, const ClaimList& list);
    // Outputs whole list of claims
};

#endif
