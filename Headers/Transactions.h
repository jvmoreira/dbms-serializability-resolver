// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

#include "Graph.h"

using namespace std;

#define READ 'R'
#define WRITE 'W'
#define COMMIT 'C'

// ===================================================
// ====== Operation ==================================

class Operation {
    unsigned int id;
    unsigned int transactionId;
    char action;
    char attribute;
    unsigned int timestamp;
public:
    Operation(string operationDef);
    unsigned int getId() { return this->transactionId; }
    char getAction() { return this->action; }
    char getAttr() { return this->attribute; }
    unsigned int getTS() { return this->timestamp; }
    bool after(Operation T) { return this->getTS() > T.getTS(); }
    void printOperation() { // === REMOVER ===
        cout << "Ordem: " << getTS() << " | " << "T" << getId() << ' ' << getAction() << "(" << getAttr() << ")" << endl;
    }
};

class Transaction {
    unsigned int id;
    vector<Operation*> operations;
public:
    Transaction(Operation* op) { this->id = op->getId(); this->addOp(op); }
    unsigned int getId() { return this->id; }
    void addOp(Operation* op) { operations.push_back(op); }
    vector<Operation*>::iterator opList() { return this->operations.begin(); }
    vector<Operation*>::iterator listEnd() { return this->operations.end(); }
    vector<Operation*> getOperations() { return this->operations; }
    void printOperations() { // === REMOVER ===
        for(vector<Operation*>::iterator op = this->opList(); op != this->listEnd(); ++op)
            (*op)->printOperation();
    }
};


// ===================================================
// ====== Schedule ===================================

class Schedule {
    bool conflictSerial;
    bool viewEquivalent;
public:
    vector<unsigned int> transactionsIds;
    Schedule(vector<unsigned int> ids);
    void setConflictSerial(bool b) { this->conflictSerial = b; }
    void setViewEquivalent(bool b) { this->viewEquivalent = b; }
    string isConflictSerial() { return this->conflictSerial ? "SS" : "NS"; }
    string isViewEquivalent() { return this->viewEquivalent ? "SV" : "NV"; }
    void addTransaction(unsigned int id) { this->transactionsIds.push_back(id); }
    stringstream outputString();
};


// ===================================================
// ====== Tester =============================

class Tester {
    vector<Operation*> operations;
    vector<Transaction*> transactions;
    vector<unsigned int> activeTransactionsIds;
    vector<unsigned int> finalizedTransactionsIds;
    Graph *currentGraph;

public:
    vector<Schedule*> schedules;
    Tester() { this->currentGraph = new Graph(); }
    bool isActive(unsigned int id);
    Transaction* findTransactionById(unsigned int id);
    void newOp(Operation* op);
};
