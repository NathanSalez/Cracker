//
// Created by nsalez on 25/11/18.
//

#ifndef CRACKER_BRUTEFORCESIMPLE_H
#define CRACKER_BRUTEFORCESIMPLE_H

#include <vector>
#include <cmath>    // pour la fonction pow() utilisée pour avoir le nombre de possibilités.

//#define __BRUTEFORCE_SIMPLE_DEBUG__
//#define __BRUTEFORCE_SIMPLE_COUNT_DEBUG

#include "Cracker.h"

namespace hack {

    /**
     * Types d'ensemble utilisés par la classe Bruteforce :
     * - letter : lowLetter + upLetter
     * - lowLetter : [a-z]
     * - upLetter : [A-Z]
     * - number : [0-9]
     * - alphanumeric : letter + number
     */
    enum class typeSet
    {
        begin,
        lowLetter,
        upLetter,
        letter,
        number,
        alphanumeric,
        end
    };


    /**
     * Services de la classe :
     * Trouver un mot de passe correspondant à une chaîne chiffrée donnée, à l'aide de la méthode classique d'une attaque par force brute.
     */
    class BruteforceSimple : public Cracker
    {

    private :

        /**
         * Un node est un noeud de l'arbre de décision à parcourir. Il est défini par son caractère
         */
        struct node
        {
            char car;       //Le caractère du noeud à afficher dans la chaîne des permutations.
            size_t index;   //L'index du noeud dans l'ensemble charSet (pour le noeud le plus à gauche, vaut 0)
            size_t profondeur;  // profondeur du noeud (vaut 1 pour les descendants directs de la racine)
        };

        struct DecisionTree
        {
            std::vector<node> s;

            /**
             * Convertit un vecteur de node en une chaine de caractères
             */
            void nodesToString(std::string & s);

        };

        const size_t minLength; /**< La taille minimum du mot de passe à forcer, variable en fonction du contexte. */
        const size_t maxLength; /**< La taille maximum du mot de passe à forcer, variable en fonction du contexte. */
        std::vector<char> charSet; /**< L'ensemble de caractères, qui délimite les possibilités du mot de passe. */
        DecisionTree stackNodes; /**< pile symbolisant l'arbre de décision à parcourir. */

        /**
         * Remplit l'attribut charSet en fonction du type t donné.
         */
        void buildSet(typeSet t);

        /**
         * Utilisé dans la méthode run, remonte au noeud père.
         */
        inline
        void backToFatherNode()
        {
            stackNodes.s.pop_back();
        }


        /**
         * Utilisé dans la méthode run, passe au 1er noeud fils.
         */
        inline
        void goToFirstSonNode()
        {
            stackNodes.s.push_back( {this->charSet.front(),0, (stackNodes.s.back().profondeur+1) } ) ;

        }


        /**
         * Utilisé dans la méthode run, renvoie true si le noeud courant est terminal.
         */
        inline
        bool finalNode()
        {
            return stackNodes.s.size() == this->maxLength;
        }


        /**
         * Utilisé dans la méthode run, renvoie true si la recherche est terminée (càd si on a atteint la racine de l'arbre)
         */
        inline
        bool searchEnded()
        {
            return ( stackNodes.s.empty() );
        }


        /**
         * Utilisé dans la méthode run, renvoie true si le noeud courant n'a plus de frère
         */
        inline
        bool noMoreBrotherNode()
        {
            // return stackNodes.s.back().car == this->charSet.back();
            return this->stackNodes.s.back().index == this->charSet.size() - 1;
        }


        /**
         * Utilisé dans la méthode run, passe au noeud frère suivant.
         * Incrémente l'index par conséquent.
         */
        void goToFollowingBrotherNode()
        {

            if( stackNodes.s.back().index >= this->charSet.size())
                exit(3);    // lancer une exception.

            size_t nextIndex = stackNodes.s.back().index +1;
            node brother = {this->charSet[nextIndex], nextIndex, stackNodes.s.back().profondeur};
#ifdef __BRUTEFORCE_DEBUG__
            std::clog << "  Passer au frère suivant - Index actuel : " << stackNodes.s.back().index << std::endl;
            std::clog << "  On passe au frère suivant : de la lettre '" << this->charSet[stackNodes.s.back().index] << "' à la lettre '" << this->charSet[stackNodes.s.back().index+1] << "'" << std::endl;
#endif
            stackNodes.s.pop_back();
            stackNodes.s.push_back( brother );
        }


        /**
         * Utilisé dans la méthode run, renvoie true si on est au même niveau ou à un niveau en dessous d'un noeud de départ
         * @return
         */
        inline
        bool upToStartNode()
        {
            return this->stackNodes.s.back().profondeur >= this->minLength;
        }


    public:

        /**
         * Constructeur par données de la classe.
         * Utile lorsqu'on veut utiliser un ensemble peu commun.
         * Lance une exception si maxSize ou minSize invalide.
         */
        BruteforceSimple(std::string const& p, size_t maxSize, std::vector<char> const& set,size_t minSize = 1);


        /**
         * Autre constructeur par données de la classe.
         * Utile pour la méthode simple.
         * Lance une exception si maxSize nulle ou t est invalide.
         */
        BruteforceSimple(std::string const& p, size_t maxSize, typeSet t,size_t minSize = 1);


        /**
         * Méthode de craquage de mot de passe.
         * Cherche le mot de passe correspondant à password en testant toutes les permutations possibles.
         * S'il le trouve, l'attribut passwordFound devient égal à true.
         */
        void run();

        /**
         * Retourne le nombre de possibilités associés à l'ensemble de caractères et à la longueur maximale d'un mdp.
         */
        size_t getNumberPossibilities() const;


        ~BruteforceSimple() = default;


    };
}


#endif //CRACKER_BRUTEFORCESIMPLE_H
