
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <utility>
#include <iostream>
using namespace std;


class LFUCache {
    struct _ListItem {
        _ListItem(int f) { frequency = f; }

        int frequency;
        list<int> items;
    };

    struct _Item {
        _Item(list<_ListItem>::iterator p, list<int>::iterator s, int v) {
            parent = p;
            self = s;
            val = v;
        }
        list<_ListItem>::iterator parent;
        list<int>::iterator self;
        int val;
    };

public:
    LFUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        auto it = items_.find(key);
        if (items_.end() == it)
            return -1;

        _Item item = it->second;
        auto next_it = item.parent;
        ++next_it;
        int frequency = item.parent->frequency + 1;
        list<_ListItem>::iterator iter;
        if (freqencies_.end() != next_it && frequency == next_it->frequency) {
            iter = next_it;
        } else {
            iter = freqencies_.insert(next_it, _ListItem(frequency));
        }

        if (1 == item.parent->items.size())
            freqencies_.erase(item.parent);
        else
            item.parent->items.erase(item.self);

        it->second.parent = iter;
        it->second.self = iter->items.insert(iter->items.begin(), key);
        return it->second.val;
    }
    
    void put(int key, int value) {
        if (capacity_ <= 0)
            return;

        auto it_key = items_.find(key);
        if (it_key != items_.end()) {
            get(key);
            it_key->second.val = value;
            return;
        }
        
        if (items_.size() >= capacity_)
            evict_one();

        auto it = freqencies_.begin();
        if (freqencies_.empty() || it->frequency != 1) {
            freqencies_.insert(freqencies_.begin(), _ListItem(1));
            it = freqencies_.begin();
        }

        auto it_self = it->items.insert(it->items.begin(), key);
        items_.insert(make_pair(key, _Item(it, it_self, value)));
    }

    void evict_one() {
        auto it_begin = freqencies_.begin();
        int key = *it_begin->items.rbegin();
        auto it_item = items_.find(key);
        if (it_begin->items.size() == 1) {
            freqencies_.erase(it_begin);
        } else {
            it_begin->items.erase(it_item->second.self);
        }

        items_.erase(it_item);
    }

private:
    int capacity_;
    unordered_map<int, _Item> items_;
    list<_ListItem> freqencies_;
};


int main()
{
    LFUCache cache(2);
    cache.put(3, 1);
    cache.put(2, 1);
    cache.put(2, 2);
    cache.put(4, 4);
    cout << cache.get(2) << endl;

    return 0;
}
