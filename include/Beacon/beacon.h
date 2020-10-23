#ifndef BEACON_H
#define BEACON_H

#include <functional>
#include <vector>

namespace Beacon
{
    template<class... PARAMS>
    class Event
    {
    private:
        typedef std::function<void(PARAMS...)> ListenerType;

        std::vector<std::pair<unsigned short, ListenerType>> m_listeners;
        unsigned short m_nextID = 0;
    public:
        ListenerType firstListener = nullptr;
        ListenerType lastListener = nullptr;

        unsigned short addListener(ListenerType a_listener)
        {
            this->m_listeners.emplace_back(std::pair<unsigned short, ListenerType>(this->m_nextID, a_listener));
            return this->m_nextID++;
        }

        void removeListener(unsigned short a_id)
        {
            unsigned short i = 0;
            for (std::pair<unsigned short, ListenerType> combo : this->m_listeners)
            {
                if (combo.first == a_id)
                {
                    std::swap(this->m_listeners[i], this->m_listeners.back());
                    this->m_listeners.pop_back();
                    return;
                }

                i++;
            }
        }

        void call(PARAMS... params) const
        {
            if (this->firstListener != nullptr)
                this->firstListener(params...);
            for (std::pair<unsigned short, ListenerType> combo : this->m_listeners)
            {
                combo.second(params...);
            }
            if (this->lastListener != nullptr)
                this->lastListener(params...);
        }
    };
}

#endif
