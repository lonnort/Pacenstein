# THGA: Styleguide
Dit is een kleine guide waarin beschreven staat hoe de code gestructureerd moet worden en opgemaakt voor consistency tussen files en verschillende programmateurs. Als je het oneens bent met een punt, laat het weten.

## Spacing en brackets
Basically, houdt het volgende aan en het komt goed:
```c++
void function(int i, std::string str) {
    if (i > 0) {
        str += toString(i);
    }
}
```

Voor single line if-statements, for-loops, enz. is het prima om geen brackets te gebruiken en alles op dezelfde regel te zetten. Doe dit nooit voor geneste if's en loop.
```c++
if (true) doSomething();
else doNoting();

// of onderstaande als je dat leesbaarder vindt.
if (true)
    doSomething();
else
    doNothing();

for (int i = 0; i < 5; i++) std::cout << i << ',';

void function() { doSomething(); }
```

## Comments en documentation
Probeer comments niet veel breder dan 100 characters te maken, de meeste IDE's hebben een ruler die je kunt aanzetten (of al aan hebben staan) op 80 of 100 characters.

Documentatie werkt met doxygen, en vereist dus doxygen compatible syntax. De voorkeur gaat uit naar het volgende:
```c++
/**
 * Stukje documentatie voor een functie
 * 
 * @param i Een integer.
 */
void function(int i);
```

## Naming
- Classes als `CamelCase` met een leading hoofletter.
- Variabelen en parameters volledig lower case met underscores: `variable_name`.
- Functies als `camelCase` zonder leading hoofletter.
- Constant variabelen en `#define` waarden in `FULL_CAPS_MET_UNDERSCORES`.
- Typedefs als volgt: `some_custom_type_t`, note de trailing `_t`.
- Reference markers direct achter het type: `int& i_ref`.

## This
Markeer members van een class met `this->` in de .cpp-files.
```c++
// f.hpp
class f {
private:
    int i;

public:
    f();
    void doSomething(int i);
}

// f.cpp
void f::doSomething(int i) {
    this->i = i;
}
```

## Pragma
Gebruik van `#pragma once` heeft de voorkeur over `#define` guards.

## Inline functions
Markeer een functie `inline` als hij minder dan 10 regels lang is en weinig/geen loops, switch statements en function calls bevat. Doorgaans zal dit efficientere code opleveren omdat het de compiler forceert de code te kopieeren ipv branching te gebruiken.

## Include order
De volgorde van includes is relevant, en het is verstandig om een specifieke volgorde aan te houden.
1. Gerelateerde headers van andere projecten; vb.: `<SFML/Graphics.hpp>`
2. C system headers; vb.: `<math.h>`
3. C++ standard library headers; vb.: `<iostream>`
4. Eigen headers; vb.: `"State.hpp"`

## Local variables
Definieer direct als er een definitie staat, gebruik ook vooral initializer lists voor array-like datastructuren, en probeer variabelen zo lokaal mogelijk te houden.
```c++
// fout
int i;
i = f();

// goed
int j = g();

// ook fout
std::vector<int> v;
v.push_back(1);
v.push_back(2);

// goed
std::vector<int> w = {1, 2};
```

Bedenk wel dat alles super lokaal houden soms niet de beste optie is.
```c++
// Dit is extreem inefficient, elke keer dat i omhoog gaat
// wordt de constructor en destructor van Foo aangeroepen.
for (int i = 0; i < 10000000; i++) {
    Foo f;
    f.doSomething(i);
}

// Dus we halen de definitie van f buiten de loop.
Foo f;
for (int i = 0; i < 10000000; i++) {
    f.doSomething(i);
}
```

## Pointers
Gebruik smart pointers, en niet c-style pointers.
