// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#include "Tester.h"

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
        if(this->transactions[i]->getId() == id)
            return this->transactions[i];
    }
    return 0;
};

vector<Operation*>::iterator Tester::findOperationByTS(unsigned int TS)
{
     for( auto it = operations.begin(); it != operations.end(); ++it )
        if( (*it)->getTS() == TS )
            return it;

     return operations.end();
}

vector<Operation*> Tester::getSerialOperations()
{
    vector<Operation*> serialOperations;

    // Deixa as operações em serial
    for( auto& T : this->transactions ) {
        for( auto& op : T->getOperations() )
            serialOperations.push_back(op);
    }

    return serialOperations;
}

// Função chamada ao receber uma nova operação
void Tester::newOp(Operation* op) {

    // Verifica se a transação já existe
    Transaction* T = this->findTransactionById(op->getId());
    // Caso exista, adiciona operação
    if(T) T->addOp(op);
    else { // Caso não exista, cria nova
        Transaction *T = new Transaction(op);
        this->transactions.push_back(T);
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
            Operation *opIter = this->operations[i];

            // Verifica se são transações diferentes e são os mesmos atributos
            if( (op->getId() != opIter->getId()) && (op->getAttr() == opIter->getAttr()) ) {
                // Verifica se algum dos dois é uma escrita
                if( (op->getAction() == WRITE) || opIter->getAction() == WRITE ) {
                    // Adiciona aresta de opIter para op
                    Node *opNode = this->currentGraph->findNode( op->getId() );
                    Node *opIterNode = this->currentGraph->findNode( opIter->getId() );
                    if( opNode && opIterNode ) {
                        opIterNode->addNode( opNode );
                    }
                }
            }
        }
        // Adiciona operação à lista de operações
        this->operations.push_back(op);
    }
    // Caso seja um commit
    else {
        // Verifica se existe transação ativa com o id da operação
        if( !this->isActive( op->getId() ) ) return;


        // Remove id da transação da lista de ativas
        for(unsigned int i = 0; i < this->activeTransactionsIds.size(); ++i)
            if(this->activeTransactionsIds[i] == op->getId())
            {
                this->activeTransactionsIds.erase( this->activeTransactionsIds.begin() + i );
                break;
            }

        // Adiciona à lista de finalizadas
        this->finalizedTransactionsIds.push_back(op->getId());

        // No caso em que não há mais transações ativas, cria uma nova saída dizendo se é ou não serial
        if(this->activeTransactionsIds.size() < 1) {
            Schedule *s = new Schedule(this->finalizedTransactionsIds);
            // Verifica se há ciclo
            if(!this->currentGraph->findCycle()) {
                // Se não há ciclo, então é serializável por conflito
                s->setConflictSerial(true);

                // Se for serializável por conflito, então também é por visão
                s->setViewEquivalent(true);
            }
            else {
                // Se houver ciclo, então não é serializável por conflito
                s->setConflictSerial(false);
                // Verifica se é serializável por equivalência de visão
                bool viewEquivalent = true;
                do {
                    // Cria lista de operações com transações em série
                    vector<Operation*> serialOperations = getSerialOperations();
                    bool breakLoop = false;

                    // Itera pelas operações em séries, buscando por operação de leitura
                    for( auto it = serialOperations.begin(); it != serialOperations.end(); ++it ) 
                    {
                        breakLoop = false;
                        auto op = *it;

                        // Verifica se duas operações realizam escrita sobre o mesmo atributo, e são operações diferentes
                        auto IsDiffOperation = [](auto op1, auto op2)
                        {
                            if( op2->getId() != op1->getId() && op2->getAttr() == op1->getAttr() && op2->getAction() == WRITE )
                                return true;

                            return false;
                        };

                        // Operação de leitura
                        if(op->getAction() == READ) 
                        {
                            // Busca operação correspondente na entrada original
                            auto originalIt = findOperationByTS( op->getTS() );

                            // Busca primeira escrita do mesmo atributo por transação diferente
                            for( auto reverseIt = originalIt; reverseIt != operations.begin()-1; --reverseIt ) 
                            {
                                //Verifica se a operação é de escrita sobre o mesmo atributo
                                if( IsDiffOperation( op, (*reverseIt) ) ) 
                                {
                                    // Busca pela escrita no mesmo atributo anterior à op em serialOperations
                                    bool writeFound = false;
                                    for( auto serialIt = it; serialIt != serialOperations.begin()-1; --serialIt ) 
                                    {
                                        // Verifica se a operação é de escrita sobre o mesmo atributo
                                        if( IsDiffOperation( op, (*serialIt) ) ) 
                                        {
                                            writeFound = true;

                                            if( (*serialIt)->getTS() != (*reverseIt)->getTS() ) 
                                            {
                                                breakLoop = true;
                                                break;
                                            }
                                        }
                                    }
                                    if(!writeFound) breakLoop = true;
                                }
                                if(breakLoop) break;
                            }
                            if(breakLoop) break;
                        }
                        if(breakLoop) break;
                    }

                    // Checa última escrita de cada atributo
                    if(breakLoop) {
                        viewEquivalent = false;
                        continue;
                    }

                    // Guarda o TS da ultima OP que escreveu em determinado atributo
                    unordered_map<char,unsigned int> lastWroteValue;
                    unordered_map<char,unsigned int> lastWroteValueSerial;

                    // Procura a OP primeiro nas operacoes original
                    for( const auto& op : operations )
                        if( op->getAction() == WRITE )
                            lastWroteValue[op->getAttr()] = op->getTS();

                    // Procura a OP primeiro nas novas operacoes
                    for( const auto& op : serialOperations )
                        if( op->getAction() == WRITE )
                            lastWroteValueSerial[op->getAttr()] = op->getTS();

                    // Itera pelos últimos valores escritos
                    for( const auto& p : lastWroteValue )
                        // Caso o último valor escrito no original for diferente do serial, não é equivalente
                        if( lastWroteValue[p.first] != lastWroteValueSerial[p.first] ) {
                            viewEquivalent = false;
                            continue;
                        }

                        // Geração das permutações das transações
                } while( next_permutation( transactions.begin(), transactions.end() ) );
                s->setViewEquivalent(viewEquivalent);
            }

            // Adiciona à lista de saídas
            this->schedules.push_back(s);

            // Limpa grafo e listas
            this->currentGraph->clear();
            this->operations.clear();
            this->transactions.clear();
            this->finalizedTransactionsIds.clear();
        }
    }
}
