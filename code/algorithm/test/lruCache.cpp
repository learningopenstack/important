template <typename k, typename v>
class LRUCache{
    public:
    LRUCache(int capacity):cap(capacity){
        }

    v get(k key){
            auto it = m.find(key);
            if (it != m.end()){
                        put(key, m[key]->second);
                        return m[key]->second;
                    }
            return;
        }

    void put(k key, v value){
            auto it = m.find(key);
            if(it != m.end()) { //更新
                        l.erase(m[key]);
                    } else if(l.size() >= cap){
                                m.erase(l.back().first);
                                l.pop_back();
                            }
            l.push_front(make_pair(key, value));
            m[key] = l.begin();
        }

    private:
    int cap;
    list<pair<k, v>> l;
    unordered_map<k, list<pair<k, v>>::iterator> m;
};
