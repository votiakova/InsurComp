#include "ClaimList.h"
#include <iostream>

// ClaimItem

ClaimList::ClaimItem::ClaimItem()
    : claim(nullptr), next(nullptr)
{
}

ClaimList::ClaimItem::ClaimItem(const ClaimItem& other)
    : claim(other.claim ? new Claim(*other.claim) : nullptr),
      next(nullptr)
{
}

// private helpers

void ClaimList::clear_list()
{
    // Frees all claim nodes and their Claim objects.
    // Used by the destructor and assignment operator to avoid duplicate cleanup code.
    ClaimItem* current = head;
    while (current != nullptr)
    {
        ClaimItem* tmp = current->next;
        delete current->claim;
        delete current;
        current = tmp;
    }
    head = nullptr;
}

void ClaimList::copy_from(const ClaimList& other)
{
    ClaimItem* src  = other.head;
    ClaimItem* tail = nullptr;

    while (src != nullptr)
    {
        ClaimItem* node = new ClaimItem(*src);   // deep-copies the Claim object

        if (tail == nullptr)
            head = node;
        else
            tail->next = node;

        tail = node;
        src  = src->next;
    }
}

// constructors / destructor 

ClaimList::ClaimList()
    : head(nullptr)
{
}

ClaimList::~ClaimList()
{
    clear_list();   // destructor delegates to the dedicated method
}

ClaimList::ClaimList(const ClaimList& other)
    : head(nullptr)
{
    copy_from(other);
}

ClaimList& ClaimList::operator=(const ClaimList& other)
{
    if (this != &other)
    {
        clear_list();       // release current content via dedicated method
        copy_from(other);
    }
    return *this;
}

// public interface 

bool ClaimList::add_claim(const std::string& number,
                          const std::string& procedure,
                          double amount)
{
    if (find_claim(number) != nullptr)
        return false;   // duplicate claim number inside this client

    ClaimItem* node = new ClaimItem();
    node->claim = new Claim(number, procedure, amount);

    node->next = head;
    head = node;
    return true;
}

bool ClaimList::remove_claim(const std::string& number)
{
    ClaimItem* prev = nullptr;
    ClaimItem* current = head;

    while (current != nullptr)
    {
        if (current->claim->compare_number(number) == 0)
        {
            if (prev == nullptr)
                head = current->next;
            else
                prev->next = current->next; 
            delete current->claim;
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

Claim* ClaimList::find_claim(const std::string& number) const
{
    ClaimItem* current = head;
    while (current != nullptr)
    {
        if (current->claim->compare_number(number) == 0)
            return current->claim;
        current = current->next;
    }
    return nullptr;
}

bool ClaimList::approve_claim(const std::string& number)
{
    Claim* c = find_claim(number);
    if (c == nullptr)
        return false;
    c->approve();
    return true;
}

bool ClaimList::reject_claim(const std::string& number)
{
    Claim* c = find_claim(number);
    if (c == nullptr)
        return false;
    c->reject();
    return true;
}

void ClaimList::print_all() const
{
    if (head == nullptr)
    {
        std::cout << "(no medical claims)" << std::endl;
        return;
    }
    ClaimItem* current = head;
    while (current != nullptr)
    {
        std::cout << *current->claim << std::endl;
        current = current->next;
    }
}

double ClaimList::approved_total() const
{
    double total = 0.0;
    ClaimItem* current = head;
    while (current != nullptr)
    {
        if (current->claim->is_approved())
            total += current->claim->get_amount();
        current = current->next;
    }
    return total;
}

std::ostream& operator<<(std::ostream& os, const ClaimList& list)
{
    ClaimList::ClaimItem* current = list.head;
    while (current != nullptr)
    {
        os << *current->claim << "\n";
        current = current->next;
    }
    return os;
}
