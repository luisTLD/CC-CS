/*
// Caracteres especiais

'\a'    // alerta (sonoro)
'\n'    // nova linha
'\t'    // tabulacao  (justificar texto a esquerda)
'\v'    // tabulacao vertical
'\f'    // nova linha (FF=FormFeed)
'\r'    // retorno ao inicio da linha
'\b'    // backspace
'\0'    // caractere nulo (fim de sequencia de caracteres)
'\\'    // barra invertida
'\?'    // interrogacao
'\''    // apostrofo ("aspas simples")
'\"'    // aspas duplas
'\xhh'  // numero hexadecimal => '\xb'  = tab vertical
'\ooo'  // numero octal       => '\013' = tab vertical

// Formatos

"%i"    // inteiro
"%s"    // string
"%f"    // ponto-flutuante
"%ld"   // inteir longo
"%c"    // caractere
"%p"    // ponteiro
"%o"    // valor octal
"%d"    // valor decimal
"%x"    // valor hexadecimal
"%%"    // simbolo (%)
"%3d"   // inteiro com pelo menos 3 dígitos (justificar texto 'a direita)
"%6.2f" // ponto-flutuante com pelo menos 3 dígitos 'a esquerda e 2 'a direita
"%10s"  // alinhar cadeias de caracteres    (justificar texto 'a direita)

-----------------------------------------------------------
    Operadores / Prioridade        | Associatividade
-----------------------------------------------------------
 () [] -> .                        | esquerda para direita
 ! ~ ++ -- + = *(type)sizeof       | direita  para esquerda
 * / %                             | esquerda para direita
 + -                               | esquerda para direita
 << >>                             | esquerda para direita
 < <= > >=                         | esquerda para direita
 == !=                             | esquerda para direita
 &                                 | esquerda para direita
 ^                                 | esquerda para direita
 |                                 | esquerda para direita
 &&                                | esquerda para direita
 ||                                | esquerda para direita
 ?:                                | direita  para esquerda
 = += -= *= /= %= &= ^= |= <<= >>= | direita  para esquerda
 ,                                 | esquerda para direita
-----------------------------------------------------------
*/
