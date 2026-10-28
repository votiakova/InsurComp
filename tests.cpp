#include <iostream>
#include "Client.h"
#include "Claim.h"
#include "ClaimList.h"
#include "InsuranceCompany.h"

int main()
{
    InsuranceCompany company("Health Insurance");
    InsuranceCompany company2("Second Insurance");

    // Create clients separately
    Client* c1 = new Client("12345678901", "Jan Kowalski", 35);
    Client* c2 = new Client("98765432101", "Anna Nowak", 28);
    Client* c3 = new Client("55555555555", "Piotr Wisniewski", 67);

    // --- Registration ---

    // Test 1: Add c1 successfully
    bool added = company.add_client(c1);
    if (added)
        std::cout << "OK: Client 12345678901 added successfully" << std::endl;
    else
        std::cout << "FAIL: Client 12345678901 should be added" << std::endl;

    company.add_client(c2);
    company.add_client(c3);

    // Test 2: Find c2 — correct name
    Client* found = company.find_client("98765432101");
    if (found != nullptr && found->get_name() == "Anna Nowak")
        std::cout << "OK: Client 98765432101 found with correct name" << std::endl;
    else
        std::cout << "FAIL: Client 98765432101 not found or wrong name" << std::endl;

    // --- Claims ---

    // Test 3: File claim CLM001 for existing client
    bool filed = company.file_claim("12345678901", "CLM001", "X-ray scan", 250.0);
    if (filed)
        std::cout << "OK: Claim CLM001 filed for client 12345678901" << std::endl;
    else
        std::cout << "FAIL: Claim CLM001 should be filed" << std::endl;

    company.file_claim("12345678901", "CLM002", "Dental cleaning", 180.0);
    company.file_claim("98765432101", "CLM003", "Cardiology consult", 350.0);
    company.file_claim("55555555555", "CLM004", "Hip replacement", 4500.0);

    // Test 4: Approve CLM001
    bool approved = company.approve_claim("12345678901", "CLM001");
    if (approved)
        std::cout << "OK: Claim CLM001 approved successfully" << std::endl;
    else
        std::cout << "FAIL: Claim CLM001 should be approved" << std::endl;

    company.approve_claim("98765432101", "CLM003");
    company.approve_claim("55555555555", "CLM004");

    // Test 5: Reject CLM002
    bool rejected = company.reject_claim("12345678901", "CLM002");
    if (rejected)
        std::cout << "OK: Claim CLM002 rejected successfully" << std::endl;
    else
        std::cout << "FAIL: Claim CLM002 should be rejected" << std::endl;

    // Test 6: Total payouts — CLM001 (250) + CLM003 (350) + CLM004 (4500) = 5100
    double payouts = company.total_payouts();
    if (payouts == 5100.0)
        std::cout << "OK: Total payouts = 5100.0 as expected" << std::endl;
    else
        std::cout << "FAIL: Total payouts should be 5100.0, got " << payouts << std::endl;

    // Test 7: Cancel CLM002
    bool cancelled = company.cancel_claim("12345678901", "CLM002");
    if (cancelled)
        std::cout << "OK: Claim CLM002 cancelled successfully" << std::endl;
    else
        std::cout << "FAIL: Claim CLM002 should be cancelled" << std::endl;

    // Test 8: Approve cancelled claim must fail
    bool approve_cancelled = company.approve_claim("12345678901", "CLM002");
    if (!approve_cancelled)
        std::cout << "OK: Cancelled claim cannot be approved" << std::endl;
    else
        std::cout << "FAIL: Cancelled claim should no longer exist" << std::endl;

    // --- Removing ---

    // Test 9: Remove c3
    bool removed = company.remove_client("55555555555");
    if (removed)
        std::cout << "OK: Client 55555555555 removed successfully" << std::endl;
    else
        std::cout << "FAIL: Client 55555555555 should be removed" << std::endl;

    // Test 10: Removed client no longer found
    Client* removed_client = company.find_client("55555555555");
    if (removed_client == nullptr)
        std::cout << "OK: Removed client no longer exists" << std::endl;
    else
        std::cout << "FAIL: Removed client still exists" << std::endl;

    // --- Two-way relationship ---

    // Test 11: c1 is marked as registered
    if (c1->is_registered())
        std::cout << "OK: c1 is registered in a company" << std::endl;
    else
        std::cout << "FAIL: c1 should be registered" << std::endl;

    // Test 12: Cannot add an already-registered client to a second company
    bool double_add = company2.add_client(c1);
    if (!double_add)
        std::cout << "OK: Registered client was not added to a second company" << std::endl;
    else
        std::cout << "FAIL: Registered client must not be accepted by another company" << std::endl;

    // Test 13: Cannot add nullptr
    bool null_add = company.add_client(nullptr);
    if (!null_add)
        std::cout << "OK: nullptr client was rejected" << std::endl;
    else
        std::cout << "FAIL: nullptr client should not be added" << std::endl;

    // --- Error cases ---

    // Test 14: Remove non-existent client
    bool bad_remove = company.remove_client("00000000000");
    if (!bad_remove)
        std::cout << "OK: Removing non-existent client returned false" << std::endl;
    else
        std::cout << "FAIL: Should return false for non-existent client" << std::endl;

    // Test 15: Find non-existent client
    Client* not_found = company.find_client("11111111111");
    if (not_found == nullptr)
        std::cout << "OK: Non-existent client returned nullptr" << std::endl;
    else
        std::cout << "FAIL: Should return nullptr" << std::endl;

    // Test 16: File claim for non-existent client
    bool bad_file = company.file_claim("22222222222", "CLM999", "MRI scan", 800.0);
    if (!bad_file)
        std::cout << "OK: Filing claim for non-existent client returned false" << std::endl;
    else
        std::cout << "FAIL: Should return false for non-existent client" << std::endl;

    // Test 17: File duplicate claim number
    bool dup_claim = company.file_claim("12345678901", "CLM001", "Eye exam", 120.0);
    if (!dup_claim)
        std::cout << "OK: Duplicate claim CLM001 was not filed" << std::endl;
    else
        std::cout << "FAIL: Duplicate claim should not be filed" << std::endl;

    // --- Company copy ---

    // Test 18: Copying a company creates independent deep copies of clients
    InsuranceCompany copy_company = company;
    Client* c1_in_copy = copy_company.find_client("12345678901");
    if (c1_in_copy != nullptr && c1_in_copy != c1 && c1->is_registered())
        std::cout << "OK: Company copy has independent client objects; original still registered" << std::endl;
    else
        std::cout << "FAIL: Company copy did not produce a correct independent copy" << std::endl;

    return 0;
}
