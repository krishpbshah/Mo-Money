#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TODO
Transaction::Transaction( std::string ticker_symbol, unsigned int day_date, unsigned int
month_date, unsigned year_date, bool buy_sell_trans, unsigned int number_shares,
double trans_amount ){
  symbol = ticker_symbol;
  day = day_date;
  month = month_date;
  year = year_date;
  if (buy_sell_trans){
    trans_type = "Buy";

  }
  else{
    trans_type = "Sell";
  }
  shares = number_shares;
  amount = trans_amount;
  trans_id = assigned_trans_id;
  assigned_trans_id++;






}



Transaction::~Transaction(){
  symbol = "";
  day = 0;
  month = 0;
  year = 0;
  shares = 0;
  amount = 0;
  trans_id = 0;





}
// TODO

// Overloaded < operator.
// TODO
bool Transaction:: operator<( Transaction const &other ){
  if (year < other.year){
    return true;
  }
  else{
    if ((year == other.year)&&(month<other.month)){
      return true;
    }
    else{
      if ((year == other.year)&&(month==other.month)&&(day<other.day)){
        return true;
      }
      else{
        if ((year == other.year)&&(month==other.month)&&(day==other.day)&&(trans_id<other.get_trans_id())){
        return true;
      }
        
      
      
    }
  }
  return false;
  }
}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TODO
History::History(){
  p_head = nullptr;

}


// Destructor
// TODO
History::~History(){
  while (p_head != nullptr){
    Transaction *temp = p_head;
    p_head = p_head ->get_next();
    delete temp;
    temp = nullptr;

  }
  
  
}

// insert(...): Insert transaction into linked list.
// TODO
void History::insert(Transaction *p_new_trans){
   if (p_head == nullptr){
        p_head = p_new_trans;
        p_new_trans->set_next(nullptr);

    } else {
        Transaction *ptr = p_head;
        while(ptr->get_next() != nullptr){
            ptr = ptr->get_next();
        }
        
        ptr->set_next(p_new_trans);
        p_new_trans->set_next(nullptr);

        
    }
  




  
  
  
}

// read_history(...): Read the transaction history from file.
// TODO
void History::read_history(){
  ece150::open_file();
  while (ece150::next_trans_entry()) {
    std::string symbol = ece150::get_trans_symbol();
    unsigned int day = ece150::get_trans_day();
    unsigned int month = ece150::get_trans_month();
    unsigned int year = ece150::get_trans_year();
    bool buy_sell = ece150::get_trans_type();
    unsigned int shares = ece150::get_trans_shares();
    double amount = ece150::get_trans_amount();
        
    Transaction *new_transaction = new Transaction(symbol, day, month, year, buy_sell, shares, amount);
    insert(new_transaction);
    }
  ece150::close_file();

  
}

// print() Print the transaction history.
// TODO
void History::print(){
 
  Transaction *ptr = p_head; 
  
   
  std::cout << "========== BEGIN TRANSACTION HISTORY ==========" << std::endl;
  

    
  while (ptr != nullptr) {
    ptr->print(); 
    ptr = ptr->get_next(); 
  }

  std::cout << "========== END TRANSACTION HISTORY ==========" << std::endl;
}



// sort_by_date(): Sort the linked list by trade date.
// TODO


void History::sort_by_date() {
    if (p_head == nullptr || p_head->get_next() == nullptr) {
        return; // No need to sort if there are 0 or 1 elements
    }

    Transaction *current = p_head;
    p_head = p_head->get_next();
    current->set_next(nullptr);

    while (p_head != nullptr) {
        Transaction *temp = p_head;
        p_head = p_head->get_next();
        temp->set_next(nullptr);

        if (*temp < *current) {
            temp->set_next(current);
            current = temp;
        } else {
            Transaction *traverse = current;

            while (traverse->get_next() != nullptr) {
                if (!(*temp < *(traverse->get_next()))) {
                    traverse = traverse->get_next();
                } else {
                    break;
                }
            }

            temp->set_next(traverse->get_next());
            traverse->set_next(temp);
        }
    }

    p_head = current;
}

void History::update_acb_cgl() {
    if (p_head == nullptr) {
        return;
    }

    double acb = 0.0;
    double total_cgl = 0.0; // Accumulator for total cgl
    unsigned int total_shares = 0; // Total shares

    Transaction *ptr = p_head;

    while (ptr != nullptr) {
        if (ptr->get_trans_type()) {
            // Buy transaction
            acb += ptr->get_amount();
            total_shares += ptr->get_shares();
            ptr->set_acb(acb);
            ptr->set_share_balance(total_shares);
        } else {
            // Sell transaction
            if (ptr->get_share_balance() >= ptr->get_shares()) {
                double proceeds = ptr->get_amount() * ptr->get_shares();
                double avg_acb_per_share = acb / total_shares;
                double cgl = proceeds - ptr->get_shares() * avg_acb_per_share;
                
                total_cgl += cgl;
                acb -= ptr->get_shares() * avg_acb_per_share;
                total_shares -= ptr->get_shares();

                ptr->set_acb(acb);
                ptr->set_share_balance(total_shares);
                ptr->set_cgl(cgl);
            }
        }
        ptr = ptr->get_next();
    }
}




// compute_cgl(): )Compute the ACB, and CGL.
// TODO
double History::compute_cgl(unsigned int year) {
    double cgl = 0.0;
    Transaction *ptr = p_head;

    while (ptr != nullptr) {
        if (ptr->get_year() == year && ptr->get_cgl() != 0.0) {
            cgl += ptr->get_cgl();
        }
        ptr = ptr->get_next();
    }

    return cgl;
}



// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }



