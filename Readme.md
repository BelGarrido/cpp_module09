# C++ — map & iterators

## 1. What is std::pair?

Every element stored in a map is a std::pair. It is a struct defined in the standard library with exactly two members:

| Member   | Type      | Meaning         |
|----------|-----------|-----------------|
| .first   | key type  | the map key     |
| .second  | value type| the mapped value|

You did not declare these names — the standard library did. They are hardcoded inside pair.

---

## 2. The -> operator

An iterator `it` behaves like a pointer to a pair. To access a member:

    it->first       // preferred — dereference + access in one step
    (*it).first     // same thing, more verbose

Use -> when you have an iterator or pointer. Use . when you have a direct object.

---

## 3. Iterating a map

    map<char, int> m;
    m['a'] = 10;
    m['b'] = 20;

    map<char,int>::iterator it;
    for(it = m.begin(); it != m.end(); ++it){
        cout << it->first << " => " << it->second << '\n';
    }

---

## 4. Iterating a map of vectors

Pseudocode first:

    start at the beginning of the map
    for each pair in the map:
        start at the begin() of the vector
        for each element in the vector:
            do something with the element iterator
        end when we reach end() of the vector
    move to the next pair
    end when we reach end() of the map

Real code:

    map<string, vector<int>> data;
    data["numbers"] = {10, 20, 30};

    map<string, vector<int>>::iterator eso;
    vector<int>::iterator it;

    for(eso = data.begin(); eso != data.end(); ++eso){
        for(it = eso->second.begin(); it != eso->second.end(); ++it){
            cout << eso->first << " => " << *it << '\n';
        }
    }

---

## 5. Key concepts learned

- std::pair — where .first and .second come from
- map iterator — points to a pair<key, value>
- vector iterator — points to a single element inside the vector
- -> vs * — dereference and access in one step
- nested loops — one for the map, one for the container inside
- pseudocode — structure your logic in plain English before coding