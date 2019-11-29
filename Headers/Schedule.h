// ====================================================
// >> UFPR 2019 - João Vitor Moreira - GRR20171621 <<
// >> UFPR 2019 - Igor Segalla Farias - GRR20176543 <<
// ====================================================

#pragma once

class Schedule {
public:
	//Construtor
    Schedule(vector<unsigned int> ids)
    {
        // Cria schedule com os ids
        for(unsigned int i = 0; i < ids.size(); ++i)
            this->transactionsIds.push_back(ids[i]);
    }

    //Getters e Setters
    void setConflictSerial(bool b) { this->conflictSerial = b; }
    void setViewEquivalent(bool b) { this->viewEquivalent = b; }
    string isConflictSerial() { return this->conflictSerial ? "SS" : "NS"; }
    string isViewEquivalent() { return this->viewEquivalent ? "SV" : "NV"; }
    vector<unsigned int> getTransactionIds() const{ return transactionsIds; }
    void addTransaction(unsigned int id) { this->transactionsIds.push_back(id); }
    stringstream outputString();

    vector<unsigned int> transactionsIds;
private:
	bool conflictSerial;
    bool viewEquivalent;
};