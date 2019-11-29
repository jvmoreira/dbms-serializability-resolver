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
#include "Operation.h"
#include "Transaction.h"
#include "Schedule.h"

using namespace std;

#define READ 'R'
#define WRITE 'W'
#define COMMIT 'C'

// ===================================================
// ====== Tester =============================

class Tester {
public:
    Tester() { this->currentGraph = new Graph(); }
    bool isActive(unsigned int id);
    vector<Schedule*> getSchedules() const{ return schedules; }
    vector<Operation*> getSerialOperations();
    vector<Operation*>::iterator findOperationByTS(unsigned int TS);
    Transaction* findTransactionById(unsigned int id);
    void newOp(Operation* op);
private:
    vector<Schedule*> schedules;
    vector<Operation*> operations;
    vector<Transaction*> transactions;
    vector<unsigned int> activeTransactionsIds;
    vector<unsigned int> finalizedTransactionsIds;
    Graph *currentGraph;
};
