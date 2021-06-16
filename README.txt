Implementarea a durat cumulat apx 20 de ore, plus minus 3h. Textul a fost plasat intr-o lista dublu
inlantuita, pe mai multe niveluri. 

Nivelul 1 este cel basic pt o lista de acest tip, iar al doilea nivel sare de pe o linie pe o alta. 
Am, deci, doi pointeri, line_up si line_down. 

In stiva, fiecare comanda memoreaza pozitia la care a facut modificari si pozitiile de inceput si 
sfarsit ale secventei modificate. In cazul in care se taie ceva din text, o functie decupeaza acea 
parte si nu o dezaloca decat la save (asa ar trebui cel putin, ca in practica valgrindul nu e chiar 
de acord). 

Astfel, toate functiile se rezuma la a decupa secvente si a le lipi la loc, deci doua procese principale.

Am ales sa structurez programul pe mai multe fisiere sursa si headere, pentru ca deja am trecut de 600-700
de linii si ar fi fost incomod sa dau scroll.

Nu am mai dezalocat lista pentru ca imi iau timeout-uri, nu mi-e clar de ce, locatiile respective nu au
fost dezalocate inainte sau ceva..