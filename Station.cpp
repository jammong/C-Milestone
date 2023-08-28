#include "Station.h"
#include "Utilities.h"


namespace sdds {
    Station::Station(const std::string str) {
        Utilities utils{};
        size_t next_pos{ 0 };
        bool more = true;
        m_item = utils.extractToken(str, next_pos, more);
        m_serial = std::stoi(utils.extractToken(str, next_pos, more));
        m_quantity = std::stoi(utils.extractToken(str, next_pos, more));
        m_widthField = std::max(m_widthField, utils.getFieldWidth());
        m_description = utils.extractToken(str, next_pos, more);
        m_id = ++id_generator;
    }
    const std::string& Station::getItemName() const {
        return m_item;
    }
    size_t Station::getNextSerialNumber() {
        return m_serial++; 
    
    }
    size_t Station::getQuantity() const {
        return m_quantity;
    }
    void Station::updateQuantity() {
        (m_quantity > 0) ? m_quantity -= 1 : m_quantity;
    }
    void Station::display(std::ostream& os, bool full) const {
        os << std::setfill('0') << std::right << std::setw(3) << m_id << " | ";
        os << std::setw(m_widthField + 1) << std::left << std::setfill(' ') << m_item << " | ";
        os << std::setw(6) << std::right << std::setfill('0') << m_serial << " | ";
        if (full) {
            os << std::setfill(' ') << std::setw(4) << std::right << m_quantity << " | ";
            os << std::left << m_description;
        }
        os << std::endl;
    }
}