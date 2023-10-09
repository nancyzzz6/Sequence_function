//
//  Sequence.cpp
//  32p2
//
//  Created by Nancy Zhao on 4/24/23.
//

#include "Sequence.h"

//constructor
Sequence::Sequence()
{
    m_size = 0;
    m_head = new Node;
    m_head -> m_next = m_head;
    m_head -> m_pre = m_head;
}

//destructor
Sequence::~Sequence()
{
    // delete from dummy
    Node* p = m_head->m_next;
    delete m_head;
    for (int i = 0; i < m_size; i++)
    {
// delete every item in the list
        Node* temp = p;
        p = p->m_next;
        delete temp;
    }

}
bool Sequence::empty() const
{
    return m_size == 0;
}

int Sequence::size() const
{
    return m_size;
}


//copy constructor
Sequence::Sequence(const Sequence& other)
{
//    consider copy from an empty sequence
    m_size = 0;
    m_head = new Node;
    m_head -> m_next = m_head;
    m_head -> m_pre = m_head;
    
    for(int i = 0; i < other.size(); i++)
    {
        ItemType value;
        other.get(i, value);
        insert(i, value);
    }
}

//assignment constructor
Sequence& Sequence::operator=(const Sequence& rhs)
{
    if(&rhs == this)
        return *this;
    Sequence temp(rhs);
    swap(temp);
    return *this;
    
}

    
    
int Sequence::insert(int pos, const ItemType& value)
{
    //    pos not valid
    if(pos > m_size || pos < 0)
        return -1;
    //    must able to insert, so m_size ++
    m_size++;
    //    Create a temp p
    Node* p = m_head->m_next;
    //    Create a new Node
    Node* newGuy = new Node;
    newGuy->m_value = value;
    for (int i = 0; i < pos; i++)
    {
        p = p->m_next;
    }
       newGuy->m_next = p;
       newGuy->m_pre = p->m_pre;
       p->m_pre = newGuy;
       newGuy->m_pre->m_next = newGuy;
    return pos;
}

int Sequence::insert(const ItemType& value)
{

    Node* newGuy = new Node;
    newGuy->m_value = value;
    Node* temp = m_head->m_next;
    int pos = 0;
//    find the first place where value <= the value in the list
    for(Node* p = m_head->m_next; p != m_head && p->m_value < value; p = p->m_next)
    {
        temp = p->m_next;
        pos ++;
    }
    newGuy->m_next = temp;
    newGuy->m_pre = temp->m_pre;
    newGuy->m_pre->m_next = newGuy;
    newGuy->m_next->m_pre = newGuy;
    m_size++;
    return pos;
}


bool Sequence::erase(int pos)
{
//    pos not valid
    if (pos < 0 || pos >= size()||empty()==true)
        return false;
//    find the node at pos
    Node* p = m_head->m_next;
    for (int i = 0; i < pos; i++)
        p = p->m_next;
//    connect the two nodes next pos
    p->m_pre->m_next = p->m_next;
    p->m_next->m_pre = p->m_pre;
    delete p;
    m_size -- ;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    Node* p = m_head->m_next;
    for ( int i = 0; i < size(); i++)
    {
//        compare each node's m_value with value
        if (p->m_value == value)
        {
            p = p -> m_next;
            erase(i);
            i--;
            count++;
        }
        else
            p = p -> m_next;
    }
    return count;
}


bool Sequence::get(int pos, ItemType& value) const
{
//    consider only valid pos
    if(pos < 0 || pos >= size())
        return false;
    Node* p = m_head->m_next;
//    find Node at pos
    for(int i = 0; i < pos; i++)
        p = p -> m_next;
    value = p -> m_value;
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if(pos < 0 || pos >= size())
        return false;
    Node* p = m_head->m_next;
//    find Node at pos
    for(int i = 0; i < pos; i++)
        p = p -> m_next;
     p -> m_value = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    Node* p = m_head->m_next;
    for(int i = 0; i < size(); i++)
    {
//        return the first value in the sequence that equal to value
        if(p->m_value == value)
            return i;
        p = p->m_next;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
//    swap the size
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
//    swap the head ptr
    Node* tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;
    
}


int subsequence(const Sequence& seq1, const Sequence& seq2)
{
//    seq2 can't be subsequence of a shorter sequence
    if(seq2.size() > seq1.size()|| seq2.empty())
        return -1;
    
    ItemType seq1Value;
    ItemType seq2Value;

    for(int i = 0; i <= seq1.size()-seq2.size(); i++)
    {
        for(int j = 0; j < seq2.size(); j++)
        {
            seq1.get(i+j, seq1Value);
            seq2.get(j, seq2Value);
            if (seq1Value != seq2Value)//didn't math all terms in seq2
                break;
            if (j == seq2.size() - 1) //matched all terms in seq2
                return i;
        }
    }
    return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence s;
    ItemType seq1Value;
    ItemType seq2Value;
    result = s;
    int j = 0;
    int k = 0;
    for(int i = seq1.size()-1; i >= 0; i--)
    {
            seq1.get(i, seq1Value);
            result.insert(j, seq1Value);
        j++;
    }
    for(int i = seq2.size()-1; i >= 0; i--)
    {
            seq2.get(i, seq2Value);
            result.insert(k+seq1.size(), seq2Value);
            result.insert(k+seq1.size(), seq2Value);
    }
}
