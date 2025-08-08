#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class Vote { YES, NO, EMPTY };

struct MP {
    string name;
    string party_name;
    Vote vote;

    MP(string n, string p) : name(n), party_name(p), vote(Vote::EMPTY) {}
};

class Party {
private:
    string name;
    Vote strategy;
    vector<MP> members;

public:
    Party(string n, Vote s) : name(n), strategy(s) {}

    void add_member(string member_name) {
        members.emplace_back(member_name, name);
    }

    void vote_all() {
        for (auto& member : members) {
            member.vote = strategy;
        }
    }

    vector<MP>& get_members() {
        return members;
    }

    string get_name() const {
        return name;
    }
};

class Bill {
private:
    string title;
    vector<MP> voters;
    int yes_count = 0;
    int no_count = 0;
    int empty_count = 0;

public:
    Bill(string t) : title(t) {}

    void conduct_vote(vector<Party>& parties) {
        yes_count = 0; no_count = 0; empty_count = 0; 
        voters.clear();
        for (auto& party : parties) {
            party.vote_all();
            for (auto& member : party.get_members()) {
                voters.push_back(member);
                if (member.vote == Vote::YES) {
                    yes_count++;
                }
                else if (member.vote == Vote::NO) {
                    no_count++;
                }
                else {
                    empty_count++;
                }
            }
        }
    }

    void print_result() const {
        cout << "Bill: " << title << "\n";
        cout << "YES: " << yes_count << "\n";
        cout << "NO: " << no_count << "\n";
        cout << "EMPTY: " << empty_count << "\n";

        if (yes_count > no_count)
            cout << ">> Bill PASSED!\n";
        else
            cout << ">> Bill REJECTED!\n";
    }
};


void add_party(vector<Party>& parties);
void add_mp(vector<Party>& parties);
void propose_bill(vector<Bill>& bills);
void vote_bills(vector<Bill>& bills, vector<Party>& parties);
void show_results(const vector<Bill>& bills);

int main() {
    vector<Party> parties;
    vector<Bill> bills;

    bool running = true;
    while (running) {
        cout << "\n--- Parliament Simulator Menu ---\n";
        cout << "1. Add new party\n";
        cout << "2. Add MP to a party\n";
        cout << "3. Propose a new bill\n";
        cout << "4. Vote on all bills\n";
        cout << "5. Show bill results\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            add_party(parties);
            break;
        case 2:
            add_mp(parties);
            break;
        case 3:
            propose_bill(bills);
            break;
        case 4:
            vote_bills(bills, parties);
            break;
        case 5:
            show_results(bills);
            break;
        case 6:
            running = false;
            cout << "Exiting Parliament Simulator. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}



void add_party(vector<Party>& parties) {
    cout << "Enter party name: ";
    string name;
    cin.ignore(); 
    getline(cin, name);

    cout << "Select voting strategy (1=YES, 2=NO, 3=EMPTY): ";
    int strat;
    cin >> strat;

    Vote strategy;
    if (strat == 1) strategy = Vote::YES;
    else if (strat == 2) strategy = Vote::NO;
    else strategy = Vote::EMPTY;

    parties.emplace_back(name, strategy);
    cout << "Party '" << name << "' added successfully.\n";
}

void add_mp(vector<Party>& parties) {
    if (parties.empty()) {
        cout << "No parties available. Add a party first.\n";
        return;
    }

    cout << "Select party to add MP:\n";
    for (size_t i = 0; i < parties.size(); ++i) {
        cout << i + 1 << ". " << parties[i].get_name() << "\n";
    }
    cout << "Enter party number: ";
    int pindex;
    cin >> pindex;

    if (pindex < 1 || pindex >(int)parties.size()) {
        cout << "Invalid party number.\n";
        return;
    }

    cout << "Enter MP name: ";
    string mpname;
    cin.ignore();
    getline(cin, mpname);

    parties[pindex - 1].add_member(mpname);
    cout << "MP '" << mpname << "' added to party '" << parties[pindex - 1].get_name() << "'.\n";
}

void propose_bill(vector<Bill>& bills) {
    cout << "Enter bill title: ";
    string title;
    cin.ignore();
    getline(cin, title);

    bills.emplace_back(title);
    cout << "Bill '" << title << "' proposed successfully.\n";
}

void vote_bills(vector<Bill>& bills, vector<Party>& parties) {
    if (bills.empty()) {
        cout << "No bills to vote on.\n";
        return;
    }
    if (parties.empty()) {
        cout << "No parties to vote.\n";
        return;
    }

    for (auto& bill : bills) {
        bill.conduct_vote(parties);
    }
    cout << "Voting completed on all bills.\n";
}

void show_results(const vector<Bill>& bills) {
    if (bills.empty()) {
        cout << "No bills to show results for.\n";
        return;
    }

    for (const auto& bill : bills) {
        bill.print_result();
        cout << "\n";
    }
}
