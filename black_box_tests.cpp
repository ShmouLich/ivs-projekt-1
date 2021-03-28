//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>
#include "iostream"

#include "gtest/gtest.h"

#include "red_black_tree.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        for(int i = 0; i < 11; ++i)
            tree.InsertNode(values[i]);
    }

    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp() {
        int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        for(int i = 0; i < 11; ++i)
            tree.InsertNode(values[i]);
    }

    BinaryTree tree;
};

TEST_F(NonEmptyTree, FindNode) {

    std::vector<Node_t *> nodeVector {};
    tree.GetLeafNodes(nodeVector);
    for (auto node : nodeVector){
        std::cout << node->color << "\n";
    }

    tree.InsertNode(0);
    EXPECT_TRUE(tree.FindNode(0));

    tree.DeleteNode(0);
    EXPECT_FALSE(tree.FindNode(0));

    EXPECT_NO_FATAL_FAILURE(tree.FindNode(rand()%10));
}

TEST_F(NonEmptyTree, InsertNode) {

    EXPECT_FALSE(tree.InsertNode(tree.GetRoot()->key).first);

    tree.DeleteNode(0);
    EXPECT_TRUE(tree.InsertNode(0).first);
    EXPECT_FALSE(tree.InsertNode(0).first);

    std::vector<Node_t *> nodeVector {};
    tree.GetAllNodes(nodeVector);
    EXPECT_FALSE(tree.InsertNode(nodeVector[0]->key).first);
}

TEST_F(NonEmptyTree, DeleteNode) {

    int tmp = tree.GetRoot()->key;

    if (tree.GetRoot()->pLeft != nullptr)
        EXPECT_TRUE(tree.DeleteNode(tree.GetRoot()->pLeft->key));

    if (tree.GetRoot()->pRight != nullptr)
        EXPECT_TRUE(tree.DeleteNode(tree.GetRoot()->pRight->key));

    EXPECT_TRUE(tree.DeleteNode(tmp));
    EXPECT_FALSE(tree.DeleteNode(tmp));
}

TEST_F(EmptyTree, FindNode) {

    EXPECT_EQ(tree.FindNode(0), nullptr);

    tree.InsertNode(5);
    EXPECT_NO_THROW(tree.FindNode(5));
}

TEST_F(EmptyTree, InsertNode) {

    auto result = tree.InsertNode(5);
    EXPECT_TRUE(result.first);

    EXPECT_EQ(result.second->key, 5);
    EXPECT_EQ(result.second->pParent, nullptr);

    auto result2 = tree.InsertNode(5);
    EXPECT_EQ(result2.second, result.second);

}

TEST_F(EmptyTree, DeleteNode) {

    EXPECT_FALSE(tree.DeleteNode(0));

    tree.InsertNode(5);
    EXPECT_TRUE(tree.DeleteNode(5));
}

TEST_F(TreeAxioms, Axiom1) { //leafnodes black

    std::vector<Node_t *> nodeVector {};
    tree.GetLeafNodes(nodeVector);
    for (auto leaf : nodeVector) {
        EXPECT_EQ(leaf->color, 1); //1 = black, 0 = red
    }
}

TEST_F(TreeAxioms, Axiom2) { //if n. red => potomci black

    auto currentNode = tree.GetRoot();

    while((currentNode = currentNode->pRight) != nullptr) { //root je vzdy black

        if (!currentNode->color) {
            EXPECT_EQ(currentNode->pRight->color, 1);
            EXPECT_EQ(currentNode->pLeft->color, 1);
        }
    }

    currentNode = tree.GetRoot();

    while((currentNode = currentNode->pLeft) != nullptr) { //root je vzdy black

        if (!currentNode->color) { //color == 0
            EXPECT_EQ(currentNode->pRight->color, 1);
            EXPECT_EQ(currentNode->pLeft->color, 1);
        }
    }
}

TEST_F(TreeAxioms, Axiom3) { //every path root-leaf contains the same amount of black nodes
    //pro zjednoduseni pujdeme pouze po levych a pravych potomcich rootu
    //v minimalni podobe by mel strom 2 prvky, z nichz jeden bude cerveny

    int leftcounter, rightcounter;
    leftcounter = rightcounter = 0;
    auto currentNode = tree.GetRoot();

    while((currentNode = currentNode->pRight) != nullptr) { //root je vzdy black

        if (currentNode->color) {
            rightcounter++;
        }
    }

    currentNode = tree.GetRoot();

    while((currentNode = currentNode->pLeft) != nullptr) { //root je vzdy black

        if (currentNode->color) {
            leftcounter++;
        }
    }

    std::cout << rightcounter << "\n"; //pokud je counter 0, asi je neco spatne
    EXPECT_EQ(leftcounter, rightcounter);
}

/*** Konec souboru black_box_tests.cpp ***/
