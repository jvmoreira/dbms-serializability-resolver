// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

class Transaction {
public:
    //Construtor
    Transaction(Operation* op) { this->id = op->getId(); this->addOp(op); }

    //Getters e Setters
    unsigned int getId() { return this->id; }
    void addOp(Operation* op) { operations.push_back(op); }
    vector<Operation*>::iterator opList() { return this->operations.begin(); }
    vector<Operation*>::iterator listEnd() { return this->operations.end(); }
    vector<Operation*> getOperations() { return this->operations; }
    void printOperations() { // === REMOVER ===
        for(vector<Operation*>::iterator op = this->opList(); op != this->listEnd(); ++op)
            (*op)->printOperation();
    }
private:
    unsigned int id;
    vector<Operation*> operations;
};