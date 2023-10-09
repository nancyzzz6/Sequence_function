//
//  Sequence.hpp
//  32p2
//
//  Created by Nancy Zhao on 4/24/23.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = std::string;

class Sequence
{
    
    public:
        Sequence();
        ~Sequence();
        bool empty() const;
        int size() const;
        Sequence(const Sequence& other);
        Sequence& operator=(const Sequence& rhs);
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& other);
   private:
    
        struct Node
        {
            ItemType m_value;
            Node* m_next;
            Node* m_pre;
        };
        int m_size;
        Node* m_head;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
