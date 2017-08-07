
#include <list>
#include <unordered_map>
using namespace std;


class LRUCache {
    struct _Item {
        _Item(int v, list<int>::iterator it) {
            val = v;
            it_list = it;
        }
        int val;
        list<int>::iterator it_list;
    };
public:
    LRUCache(int capacity) {
        capacity_ = capacity;
    }
    
    int get(int key) {
        if (keys_.find(key) == keys_.end())
            return -1;

        _Item& item = keys_.find(key)->second;
        list_.erase(item.it_list);
        item.it_list = list_.insert(list_.begin(), key);
        return item.val;
    }
    
    void put(int key, int value) {
        if (capacity_ <= 0)
            return;

        auto it = keys_.find(key);
        if (it != keys_.end()) {
            get(key);
            it->second.val = value;
            return;
        }

        if (list_.size() >= capacity_) {
            int old_key = list_.back();
            keys_.erase(old_key);
            list_.pop_back();
        }
        
        list_.push_front(key);
        keys_.insert(make_pair(key, _Item(value, list_.begin())));
    }

private:
    int capacity_;
    list<int> list_;
    unordered_map<int, _Item> keys_;
};


int main()
{

    return 0;
}
