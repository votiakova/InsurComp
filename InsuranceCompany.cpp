#include "InsuranceCompany.h"
#include <iostream>

// ClientItem

InsuranceCompany::ClientItem::ClientItem()
    : client(nullptr), claims(nullptr), next(nullptr)
{
}

InsuranceCompany::ClientItem::ClientItem(const ClientItem& other)
    : client(other.client ? new Client (*other.client) : nullptr),
      claims(other.claims ? new ClaimList (*other.claims) : nullptr),
      next(nullptr)
{
}

// private helpers

void InsuranceCompany::clear_list()
{
    // Frees all client nodes with their Client and ClaimList data.
    ClientItem* current = head;
    while (current != nullptr)
    {
        ClientItem* tmp = current->next;
        delete current->client;   // remove reference from Client side
        delete current->claims;   // remove reference from ClaimList side
        delete current;
        current = tmp;
    }
    head = nullptr;
}

void InsuranceCompany::copy_from(const InsuranceCompany& other)
{
    ClientItem* src = other.head;
    ClientItem* tail = nullptr;

    while (src != nullptr)
    {
        ClientItem* node = new ClientItem(*src);
        node->client->set_company(this);   // copied client belongs to the new company

        if (tail == nullptr)
            head = node;
        else
            tail->next = node;

        tail = node;
        src = src->next;
    }
}

// constructors / destructor 

InsuranceCompany::InsuranceCompany(const std::string& name)
    : name(name), head(nullptr)
{
}

InsuranceCompany::~InsuranceCompany()
{
    clear_list();   // destructor delegates to the dedicated method
}

InsuranceCompany::InsuranceCompany(const InsuranceCompany& other)
    : name(other.name), head(nullptr)
{
    copy_from(other);
}

InsuranceCompany& InsuranceCompany::operator=(const InsuranceCompany& other)
{
    if (this != &other)
    {
        clear_list();           // release current content via dedicated method
        name = other.name;
        copy_from(other);
    }
    return *this;
}

// public interface 

bool InsuranceCompany::add_client(Client* client)
{
    if (client == nullptr)
        return false;
    if (client->is_registered())
        return false;

    ClientItem* node = new ClientItem();
    node->client = client;
    node->claims = new ClaimList();
    node->next = head;
    head = node;
    client->set_company(this);
    return true;
}

bool InsuranceCompany::remove_client(const std::string& id)
{
    ClientItem* prev = nullptr;
    ClientItem* current = head;

    while (current != nullptr)
    {
        if (current->client->compare_id(id) == 0)
        {
            if (prev == nullptr)
                head = current->next;
            else
                prev->next = current->next;

            current->client->set_company(nullptr);
            delete current->client;
            delete current->claims;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

Client* InsuranceCompany::find_client(const std::string& id) const
{
    ClientItem* current = head;
    while (current != nullptr)
    {
        if (current->client->compare_id(id) == 0)
            return current->client;
        current = current->next;
    }
    return nullptr;
}

ClaimList* InsuranceCompany::find_claims(const std::string& id) const
{
    ClientItem* current = head;
    while (current != nullptr)
    {
        if (current->client->compare_id(id) == 0)
            return current->claims;
        current = current->next;
    }
    return nullptr;
}

bool InsuranceCompany::file_claim(const std::string& client_id,
                                  const std::string& number,
                                  const std::string& procedure,
                                  double amount)
{
    ClaimList* list = find_claims(client_id);
    if (list == nullptr)
        return false;   // client does not exist

    return list->add_claim(number, procedure, amount);
}

bool InsuranceCompany::cancel_claim(const std::string& client_id,
                                    const std::string& number)
{
    ClaimList* list = find_claims(client_id);
    if (list == nullptr)
        return false;   // client does not exist

    return list->remove_claim(number);
}

bool InsuranceCompany::approve_claim(const std::string& client_id,
                                     const std::string& number)
{
    ClaimList* list = find_claims(client_id);
    if (list == nullptr)
        return false;   // client does not exist

    return list->approve_claim(number);
}

bool InsuranceCompany::reject_claim(const std::string& client_id,
                                    const std::string& number)
{
    ClaimList* list = find_claims(client_id);
    if (list == nullptr)
        return false;   // client does not exist

    return list->reject_claim(number);
}

void InsuranceCompany::print_all() const
{
    if (head == nullptr)
    {
        std::cout << "(no clients registered)" << std::endl;
        return;
    }
    ClientItem* current = head;
    while (current != nullptr)
    {
        std::cout << *current->client << std::endl;
        current->claims->print_all();
        current = current->next;
    }
}

void InsuranceCompany::warning(int age_limit) const
{
    bool found = false;
    ClientItem* current = head;

    while (current != nullptr)
    {
        if (current->client->get_age() > age_limit)
        {
            std::cout << *current->client
                      << " | Approved payouts: "
                      << current->claims->approved_total()
                      << " PLN" << std::endl;
            found = true;
        }
        current = current->next;
    }
    if (!found)
        std::cout << "(no clients older than " << age_limit << ")" << std::endl;
}

double InsuranceCompany::total_payouts() const
{
    double total = 0.0;
    ClientItem* current = head;
    while (current != nullptr)
    {
        total  += current->claims->approved_total();
        current = current->next;
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const InsuranceCompany& company)
{
    os << "   " << company.name << "    \n";
    InsuranceCompany::ClientItem* current = company.head;
    while (current != nullptr)
    {
        os << *current->client << "\n"
           << *current->claims;
        current = current->next;
    }
    return os;
}
