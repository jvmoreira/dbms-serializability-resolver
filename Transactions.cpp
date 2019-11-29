// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "Transactions.h"

// ===================================================
// ====== Operation ==================================

Operation::Operation(string operationDef) {
    stringstream definition(operationDef);
    string tokens[4], *token = tokens;
    while( getline(definition, *(token++), ' ') );
    (stringstream) tokens[0] >> timestamp;
    (stringstream) tokens[1] >> transactionId;
    action = *(tokens[2].c_str());
    attribute = *(tokens[3].c_str());
}



// ===================================================
// ====== Schedule ===================================

Schedule::Schedule(vector<unsigned int> ids) {
    // Cria schedule com os ids
    for(unsigned int i = 0; i < ids.size(); ++i)
        this->transactionsIds.push_back(ids[i]);
}

// ===================================================
// ====== Tester =====================================

// Verifica se existe uma transação ativa com determinado id
bool Tester::isActive(unsigned int id) {
    for(unsigned int i = 0; i < this->activeTransactionsIds.size(); ++i)
        if(this->activeTransactionsIds[i] == id)
            return true;
    return false;
}

// Encontra transação pelo id
Transaction* Tester::findTransactionById(unsigned int id) {
    for(unsigned int i = 0; i < this->transactions.size(); ++i) {
        if(this->transactions[i].getId() == id)
            return &(this->transactions[i]);
    }
    return 0;
};

// Função chamada ao receber uma nova operação
void Tester::newOp(Operation* op) {

    // Verifica se a transação já existe
    Transaction* T = this->findTransactionById(op->getId());
    // Caso exista, adiciona operação
    if(T) T->addOp(op);
    else { // Caso não exista, cria nova
        Transaction *T = new Transaction(op);
        this->transactions.push_back(*T);
        this->currentGraph->createNode(op->getId());
    }

    // Verifica se é diferente de commit
    if(op->getAction() != COMMIT) {
        // Se não for uma transação ativa, adiciona à lista
        if( !this->isActive( op->getId() ) ) {
            this->activeTransactionsIds.push_back(op->getId());
        }

        // Itera por todas as operações anteriores, verificando se há conflito
        for(unsigned int i = 0; i < this->operations.size(); ++i) {
            Operation *opIter = &(this->operations[i]);

            // Verifica se são transações diferentes e são os mesmos atributos
            if( (op->getId() != opIter->getId()) && (op->getAttr() == opIter->getAttr()) ) {
                // Verifica se algum dos dois é uma escrita
                if( (op->getAction() == WRITE) || opIter->getAction() == WRITE ) {
                    // Adiciona aresta de opIter para op
                    Node *opNode = this->currentGraph->findNode(op->getId());
                    this->currentGraph->findNode(opIter->getId())->addNode(opNode);
                    // cout << "Adiciona aresta de " << opIter->getId() << " para " << op->getId() << endl;
                }
            }
        }
        // Adiciona operação à lista de operações
        this->operations.push_back(*op);
    }
    // Caso seja um commit
    else {
        // Verifica se existe transação ativa com o id da operação
        if( !this->isActive( op->getId() ) ) return;


        // Remove id da transação da lista de ativas
        for(unsigned int i = 0; i < this->activeTransactionsIds.size(); ++i)
            if(this->activeTransactionsIds[i] == op->getId())
                this->activeTransactionsIds.erase( this->activeTransactionsIds.begin() + i );

        // Adiciona à lista de finalizadas
        this->finalizedTransactionsIds.push_back(op->getId());

        // No caso em que não há mais transações ativas, cria uma nova saída dizendo se é ou não serial
        if(this->activeTransactionsIds.size() < 1) {
            Schedule *s = new Schedule(this->finalizedTransactionsIds);
            // Verifica se há ciclo
            if(this->currentGraph->findCycle()) {
                s->setConflictSerial(true);
                // Se for serializável por conflito, então também é por visão
                s->setViewEquivalent(true);
            }
            else {
                s->setConflictSerial(false);
                s->setViewEquivalent(false);
            }

            // Adiciona à lista de saídas
            this->schedules.push_back(s);
            this->currentGraph = new Graph();
        }
    }
}
