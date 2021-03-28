//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Ondrej Kriz <xkrizo05@stud.fit.vutbr.cz>
// $Date:       $2021-01-04
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find a GetHead
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "double-linked list", ktera bude splnovat dodane testy 
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue()
{
    m_pHead = nullptr;
}

PriorityQueue::~PriorityQueue()
{
    Element_t* current = m_pHead;
    while (current != nullptr) {
        Element_t* next = current->pNext;
        delete current;
        current = next;
    }
    m_pHead = nullptr;
}

void PriorityQueue::Insert(int value)
{
    if (m_pHead == nullptr) { //empty queue
        m_pHead = new Element_t{.pNext = nullptr, .value = value};
    }
    else {
        Element_t *current = m_pHead;
        if (m_pHead->value < value) {
            m_pHead = new Element_t{.pNext = current, .value = value};
        }
        else {
            Element_t *lastptr = current;
            while (current->value > value) {
                if (current->pNext == nullptr) {
                    Element_t *element;
                    element = new Element_t{.pNext = nullptr, .value = value};
                    current->pNext = element;
                    return;
                }
                lastptr = current;
                current = current->pNext;
            }
            Element_t *element;
            element = new Element_t{.pNext = current, .value = value};
            lastptr->pNext = element;
        }
    }
}

bool PriorityQueue::Remove(int value)
{
    if (m_pHead == nullptr) //list empty
        return false;

    if (m_pHead->value == value) { //deleting first node
        Element_t *current = m_pHead;
        m_pHead = m_pHead->pNext;
        delete(current);
        return true;
    }

    Element_t *current = m_pHead;
    Element_t *lastptr;

    while (current->value != value) {
        if (current->pNext == nullptr)
            return false;
        lastptr = current;
        current = current->pNext;
    }
    lastptr->pNext = current->pNext;
    delete(current);
    return true;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    if (m_pHead == nullptr)
        return nullptr;

    Element_t *current = m_pHead;
    while (current->value != value) {
        if (current->pNext == nullptr)
            return nullptr;
        current = current->pNext;
    }
    return current;
}

size_t PriorityQueue::Length()
{
    int counter = 0;
    if (m_pHead == nullptr)
        return counter;
    Element_t *current = m_pHead;
    counter++;
    while (current->pNext != nullptr) {
        current = current->pNext;
        counter++;
    }
	return counter;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
