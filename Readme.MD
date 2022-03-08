# Projekt č. 1 – Práca s dynamickým poľom
Napíšte program, ktorý bude pracovať so záznamami zapísanými v súbore
**OrganizacnePodujatia.txt** obsahujúci záznamy o plánovaných seminároch. Program bude
vykonávať príkazy načítané zo štandardného vstupu. Každý príkaz bude predstavovať malé
písmeno nasledované koncom riadku:
● **v** - po aktivovaní program zistí, či txt súbor už bol otvorený. Ak súbor ešte nebol
otvorený pokúsi sa ho otvoriť. V prípade, ak sa súbor nepodarí otvoriť program
vypíše správu Neotvoreny subor. Správa je nasledovaná znakom konca riadku. V
prípade úspešného otvorenia txt súboru (resp. txt súbor už bol otvorený - tzn. že
príkaz ‘v’ už bol predtým stlačený), program zisti, či už boli vytvorené dynamické
polia (bol už stlačený prikaz ‘n’). Ak ano, tak program vypíše na obrazovku jednotlivé
záznamy z dynamických polí inak program vypíše jednotlivé záznamy zo súboru.
Jedntlivé vypisované záznamy budú oddelené prázdnym riadkom, jednotlivé položky
záznamu budú pomenované a každá bude umiestnená v samostatnom riadku. Výpis
bude vyzerať nasledovne:
Nazov prispevku: (medzera) max. 150 znakový reťazec, ktorý obsahuje písmená
a medzery
Mena autorov:(medzera) meno a priezvisko autorov clanku, max. 100 znakový
reťazec, ktorý obsahuje písmená a medzery, autori sú oddelení znakom #
Typ prezentovania:(medzera) 2 znaky - písmená z množiny {PD, UD, PP, UP}
Cas prezentovania: (medzera) 4 znaky (1-2 znak reprezentuje hodinu 08-19h,
3-4 znak reprezentuje minuty 00-59)
Datum:(medzera) osemmiestne celé číslo v tvare rrrrmmdd 20201030
(30.10.2020)
(prázdny riadok)
Txt súbor bude obsahovať iba hodnoty, nie typy (názvy) položiek.
● **o** – po aktivovaní program načíta dátum (vo formáte rrrrmmdd) a vypíše zoznam
príspevkov s rovnakým dátumom, zoradené podľa časového harmonogramu a typu
prezentovania, kde UP a UD bude predstavovať jeden zoznam a PP a PD bude
predstavovať druhý zoznam časovo zoradený. Tento príkaz vypíše zoznam na
obrazovku aj v prípade, že príkaz 'n' nebol aktivovaný (t.j. dynamické polia pre
jednotlivé položky zo vstupného súboru ešte nie sú vytvorené), ale príkaz 'v' áno (iba
príkaz 'v' má možnosť otvoriť txt súbor).
Ukážka vstupu:
20200405
Ukážka výstupu:
1030 UD Jana Mrkvickova Cloud computing
1120 UP Jozko Mrkvicka Deep learning
1140 UP Jozko Mrkvicka Spracovanie obrazu
1520 UP Jan Oriesok Metody inspirovane prirodou
1200 PP Jozko Mrkvicka Spracovanie obrazu
1520 PD Jana Oriesokova Metody inspirovane prirodou (2)
● **n** – po aktivovaní spočíta počet záznamov v súbore, dynamicky vytvorí polia pre
jednotlivé položky (tzn. jedno pole pre “Nazov prispevku”, druhe pole pre “mena
autorov”, atd.). Zapíše ich v takom poradí, v akom sú v súbore. Ak už boli polia
predtým vytvorené, sú najprv dealokované a potom sa vytvoria nové. Po úspešnom
načítaní hodnôt sa vypíše hláška Nacitane data. Ak súbor nie je otvorený (t.j. ešte
nebol vykonaný príkaz ‘v’), táto voľba nič nezmení a vypíše správu Neotvoreny
subor.
Ukážka vstupu:
Ukážka výstupu:
Nacitane data.
● **s** – po aktivovaní program načíta dátum(vo formáte rrrrmmdd) a typ prezentovania
(vo formáte {PD, UD, PP, UP}), program vypíše položky “cas prezentovania”,
“Prezenter” a “Nazov príspevku” z dynamicky alokovaných polí na obrazovku, ktoré
zodpovedajú načítanému vstupu. Ak dynamické polia nie sú vytvorené, vypíše
správu Polia nie su vytvorene. Správa je nasledovaná znakom konca riadku. Ak pre
daný vstup neexistuje žiadny záznam, vypíše sa správa Pre dany vstup neexistuju
zaznamy.
Ukážka vstupu:
20200405 UP
Ukážka výstupu:
1120 Jozko Mrkvicka Deep learning
1030 Jana Mrkvickova Cloud computing
1520 Jan Oriesok Metody inspirovane prirodou
1140 Jozko Mrkvicka Spracovanie obrazu
● **h** – po aktivovaní program vypíše histogram pre typ prezentovania a hodinu v
2-hodinovom intervale (t.j. podľa položky cas prezentovania ... viď ukážka výstupu).
Ak dynamické polia nie sú vytvorené, vypíše správu Polia nie su vytvorene. Správa
je nasledovaná znakom konca riadku.
Ukážka výstupu:
hodina UP UD PP PD
08:00 - 09:59 : 0 0 0 0
10:00 - 11:59 : 3 1 0 0
12:00 - 13:59 : 0 0 1 0
14:00 - 15:59 : 0 0 0 1
...
18:00 - 19:59 : 0 0 0 0
● **z** – po aktivovaní program načíta nazov prispevku a záznam/y s rovnakým názvom
vymaže z dynamických polí. Po vymazaní program vypíše hlášku, koľko záznamov
sa vymazalo (napr. Vymazalo sa : 5 zaznamov !). Vykonajte aj úpravu veľkosti
jednotlivých dynamických polí. Ak polia nie sú vytvorené, vypíše správu Polia nie su
vytvorene. Správa je nasledovaná znakom konca riadku.
Ukážka vstupu:
Spracovanie obrazu
Ukážka výstupu:
Vymazalo sa : 2 zaznamov !
● **p** – po aktivovaní program načíta všetky údaje z klávesnice a pridá záznam do
dynamických polí na koniec. Po pridaní program vypíše hlášku Zaznam sa podarilo
pridat. Ak polia nie sú vytvorené, vypíše správu Polia nie su vytvorene a nepridá
sa zadaný záznam na koniec. Správa je nasledovaná znakom konca riadku.
Ukážka vstupu:
Zaklady proceduralneho programovania 2
Jan Zelenka
UP
0800
20200405
Ukážka výstupu:
Zaznam sa podarilo pridat.
● **k** – po aktivovaní sa korektne dealokujú dynamické polia, ak boli predtým vytvorené;
ak je vstupný súbor otvorený, tak bude uzavretý a následne sa program ukončí. Pri
tejto voľbe program negeneruje žiaden výstup.
Nedodržanie presného formátu výpisu bude mať za následok zníženie hodnotenia.
Používajte funkcie, t.j. každý príkaz (okrem k) sa vykoná vo vlastnej funkcii, pričom použite
prenos argumentov, nie globálne premenné. Nepoužívajte štruktúry. Nereprezentujte celý
vstupný súbor pomocou jedného viacrozmerného dynamického poľa. Dynamicky alokované
pole vytvorte pomocou funkcie malloc (alebo iných funkcií na dynamickú alokáciu pamäte).
Môžete použiť reťazce a pole reťazcov. Zdrojový kód píšte prehľadne, dôležité riadky
okomentujte.
Pracujte samostatne, odovzdané zdrojové kódy budú porovnávané. Zistená
podobnosť bude riešená na disciplinárnej komisii.
##Hodnotenie: (max. 15b, min. 4b)
● príkazy v, s,p - každý v samostatnej funkcii 3*1.5b,
● príkazy n, z, h - každý v samostatnej funkcii 3*2b,
● príkaz o v samostatnej funkcii 1*3b,
● funkcia main (súčasťou je korektná implementácie príkazu k) 1.5b,
Príklad súboru OrganizacnePodujatia.txt (vstupný súbor neobsahuje znaky s diakritikou)
Deep learning
Jozko Mrkvicka
UP
1120
20200405
Cloud computing
Jana Mrkvickova#Jozko Mrkvicka
UD
1030
20200405
Metody inspirovane prirodou
Jan Oriesok#Jozko Mrkvicka
UP
1520
20200405
Spracovanie obrazu
Jozko Mrkvicka
UP
1140
20200405
Spracovanie obrazu
Jozko Mrkvicka
PP
1200
20200405
Metody inspirovane prirodou (2)
Jana Oriesokova#Jan Oriesok#Jozko Mrkvicka
PD
1520
20200405