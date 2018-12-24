//
// Created by nsalez on 25/11/18.
//

#include "BruteforceSimple.h"

namespace hack
{

    BruteforceSimple::BruteforceSimple( std::string const& p, size_t maxSize, std::vector<char> const& set, size_t minSize) : Bruteforce(p), minLength(minSize), maxLength(maxSize)
    {

        if( maxSize <= 0 || minSize <= 0 || maxSize < minSize )
            exit(4);

        if(!set.empty())
        {
            this->charSet.resize(set.size());
            std::copy(set.begin(), set.end(), this->charSet.begin());
        }
        else
            this->buildSet(typeSet::number);

    }


    BruteforceSimple::BruteforceSimple(std::string const& p, size_t maxSize, typeSet t, size_t minSize) : Bruteforce(p), minLength(minSize), maxLength(maxSize)
    {
        if( maxSize <= 0 || minSize <= 0 || maxSize < minSize )
            exit(4);

        this->buildSet(t);
    }


    void BruteforceSimple::buildSet(typeSet t)
    {
        if (t == typeSet::begin || t == typeSet::end)
            exit(2);    // lancer une exception

        if (t == typeSet::letter || t == typeSet::alphanumeric || t == typeSet::lowLetter || t == typeSet::upLetter)
        {
            for (char c = 'a'; c <= 'z'; c++) {
                if( t != typeSet::upLetter)
                    this->charSet.push_back(c); // on ajoute la lettre minuscule..
                if( t != typeSet::lowLetter )
                    this->charSet.push_back(c - ' ');   //.. mais aussi la lettre majuscule correspondante.
            }
        }

        if (t == typeSet::number || t == typeSet::alphanumeric)
        {
            for (char c = '0'; c <= '9'; c++) {
                this->charSet.push_back(c);
            }
        }


    }


    size_t BruteforceSimple::getNumberPossibilities() const
    {
        size_t n = this->charSet.size();        // n est la raison de la suite géométrique associée à l'ensemble des possibilités.
        if( n != 1)
            return static_cast<size_t>( pow(n,this->minLength)*( pow(n,this->maxLength-this->minLength+1) - 1 )/(n-1) );
        else
            return this->maxLength-this->minLength+1;
    }


    void BruteforceSimple::DecisionTree::nodesToString(std::string & s)
    {
        s.clear();
        for( auto c : this->s)
            s.push_back(c.car);
    }



    void BruteforceSimple::run()
    {
        this->start = std::chrono::system_clock::now();
        //std::vector<node> p;    // pile symbolisant l'arbre de décision à parcourir.
        std::string sTest;
#ifdef __BRUTEFORCE_SIMPLE_DEBUG__
        std::clog << "Solution à trouver : " << this->password << std::endl;
#endif

        // 0 : passer de la racine au 1er fils.
        this->stackNodes.s.push_back( {this->charSet.front(),0,1} );
#ifdef __BRUTEFORCE_SIMPLE_DEBUG__
        std::clog << "On descend dans l'arbre - profondeur = " << this->stackNodes.s.back().profondeur << std::endl;
#endif
        do {
            while( !this->finalNode() )
            {
                this->stackNodes.nodesToString(sTest);
                if( this->upToStartNode() && trySolution(sTest) )
                {
                    // 1a : on sauvegarde la solution et on arrête la recherche
                    this->end = std::chrono::system_clock::now();
                    this->solution = sTest;
                    this->passwordFound = true;
                    return;
                }
                else
                {
                    // 1b : on passe au premier fils de ce noeud.
                    this->goToFirstSonNode();
#ifdef __BRUTEFORCE_SIMPLE_DEBUG__
                    std::clog << "On descend dans l'arbre - profondeur = " << this->stackNodes.s.back().profondeur << std::endl;
#endif
                }
            }


            // 2 : si le noeud terminal est solution alors on effectue la manipulation 1a.
            this->stackNodes.nodesToString(sTest);
            if( trySolution(sTest) )
            {
                this->end = std::chrono::system_clock::now();
                this->solution = sTest;
                this->passwordFound = true;
                return;
            }


            // 3 : Tant que le noeud courant n'a pas de frère, et qu'on est pas à la racine, on remonte au père.
            while( this->noMoreBrotherNode() && !this->searchEnded() )
            {
                this->backToFatherNode();
            }


            // 4 : Si le noeud courant n'est pas la racine, on passe au frère suivant.
            if( !this->searchEnded() )
            {
                this->goToFollowingBrotherNode();
            }
        }while( !this->searchEnded());
        this->end = std::chrono::system_clock::now();
    }
}
