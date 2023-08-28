//NAME : YEONSU PARK
//ID   :128899218
//EMAIL: ypark91@myseneca.ca
#include "Workstation.h"
namespace sdds {
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    Workstation::Workstation(const std::string& str) : Station(str) {}
    void Workstation::fill(std::ostream& os) {
        if (!m_orders.empty()) {
            m_orders.front().fillItem(*this, os);
        }
    }
    bool Workstation::attemptToMoveOrder() {
        bool moved{};
        if (!m_orders.empty()) {
            if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {
                if (!m_pNextStation) {
                    if (m_orders.front().isOrderFilled()) {
                        g_completed.push_back(std::move(m_orders.front()));
                    }
                    else {
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                else {
                    *m_pNextStation += std::move(m_orders.front());
                }
                m_orders.pop_front();
                moved = true;
            }
        }
        return moved;
    }


    void Workstation::setNextStation(Workstation* station) { m_pNextStation = station; }
    Workstation* Workstation::getNextStation() const { return m_pNextStation; }
    void Workstation::display(std::ostream& os) const {
        os << (this)->getItemName() << " --> ";
        (m_pNextStation) ?
            (os << m_pNextStation->getItemName()) :
            (os << "End of Line");
        os << "\n";
    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }
}