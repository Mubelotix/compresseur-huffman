#include "codingTable.h"
#include <errno.h>

CT_CodingTable CT_new() {
    CT_CodingTable table;
    table.length = 0;
    return table;
}

bool CT_isEmpty(CT_CodingTable table) {
    return table.length == 0;
}

unsigned int CT_length(CT_CodingTable table) {
    return table.length;
}

bool CT_contains(CT_CodingTable table, B_Byte byte) {
    unsigned int converted_byte = B_byteToNatural(byte);
    for (unsigned int i = 0; i < table.length; i++) {
        if (B_byteToNatural(table.tab[i].byte) == converted_byte) {
            return 1;
        }
    }
    return 0;
}

// \begin{algorithme} 
//     \fonction{getBinaryCode}{table : CodingTable, byte : Byte}{BinaryCode}{contains(table,byte)}{i : \naturelNonNul}
//     {\affecter{i}{1}
//     \tantque{(i $\leq$ \champ{table}{length}) et (\champ{table}{tab[i]}{.byte} $\neq$ byte)}
//         {\affecter{i}{i + 1}}
//     \retourner{\champ{table}{tab[i]}{.code}}}   
// \end{algorithme}
// \vspace*{0.5cm}

// \begin{algorithme}
//     \procedure{add}{\paramEntreeSortie{table: CodingTable} \paramEntree{byte: Byte, code : BinaryCode} }{non contains(table,byte)}{}
//     {\affecter{\champ{table}{tab[\champ{table}{length+1}]}{.byte}}{byte}
//     \affecter{\champ{table}{tab[\champ{table}{length+1}+1]}{.code}}{code}}
// \end{algorithme}
// \vspace*{0.5cm}

// \begin{algorithme} 
//     \fonction{getByte}{table : CodingTable, code : BinaryCode}{Byte}{i : \naturelNonNul}{}
//     {\affecter{i}{1}
//     \tantque{(i $\leq$ \champ{table}{length}) et (\champ{table}{tab[i]}{.code} $\neq$ code)}
//         {\affecter{i}{i + 1} 
//         \affecter{present}{\champ{table}{tab[i]}{.byte}}}
//     \retourner{\champ{table}{tab[i]}{.byte}}}
// \end{algorithme}
