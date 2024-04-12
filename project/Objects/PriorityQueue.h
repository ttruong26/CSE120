#ifndef PRIORTYQUEUE_H
#define PRIORTYQUEUE_H

#include <queue>

using namespace std;

template <typename T, typename priority_t>
struct PriorityQueue
{
    typedef pair<priority_t, T> PQElement;
    priority_queue<PQElement, vector<PQElement>, greater<PQElement>> elements;

    inline bool empty() const { return elements.empty(); }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    inline T get()
    {
        T best_item = elements.top().second;
        elements.pop();
        return best_item;
    }
};

#endif // PRIORTYQUEUE_H