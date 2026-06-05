-- Lab 1

10. S? se afi?eze numele, job-ul ?i data la care au început lucrul salaria?ii angaja?i între 20
Februarie 1987 ?i 1 Mai 1989. Rezultatul va fi ordonat cresc?tor dup? data de început.

SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN TO_DATE('17-02-1987', 'dd-mm-yyyy') AND TO_DATE('01-05-1989', 'dd-mm-yyyy')
ORDER BY hire_date;

15. S? se listeze numele tuturor angaja?ilor care au a treia liter? din nume ‘A’

SELECT last_name
FROM employees
WHERE UPPER(last_name) LIKE '__A%';

16. S? se listeze numele tuturor angajatilor care au cel pu?in 2 litere ‘L’ în nume ?i lucreaz? în
departamentul 30 sau managerul lor este 102

SELECT last_name
FROM employees
WHERE UPPER(last_name) LIKE '%L%L%'
AND (department_id = 30 OR manager_id = 102);

18. S? se afi?eze numele, salariul ?i comisionul pentru toti salaria?ii care câ?tig? comision.
S? se sorteze datele în ordine descresc?toare a salariilor ?i comisioanelor.

SELECT last_name, salary, commission_pct
FROM employees
WHERE commission_pct IS NOT NULL
ORDER BY salary DESC,
commission_pct DESC;

20. S? se afi?eze angaja?ii care au salariul între 5000 ?i 9000, iar prenumele (first_name) lor
începe cu litera a sau m. Verificarea se va face utilizând liter? mica. De asemenea, se
afi?eaz? doar acei angaja?i care au fost angaja?i într-un an impar, iar luna lor de angajare
coincide cu luna curent? (adic? luna în care ne afl?m în acest moment). Se vor afi?a:
numele concatenat cu spa?iu, concatenat cu prenumele, salariul si data angaj?rii. Coloana
pe care se afl? numele ?i prenumele se va numi Nume Complet. Rezultatele se vor ordona
descresc?tor, în func?ie de data angaj?rii. 

SELECT last_name || ' ' || first_name as "Nume complet", salary, hire_date
FROM employees
WHERE (LOWER(first_name) LIKE 'a%' OR LOWER(first_name) LIKE 'm%')
AND MOD(TO_CHAR(hire_date, 'YYYY'), 2) = 1
AND TO_CHAR(hire_date, 'MM') = TO_CHAR(SYSDATE, 'MM')
ORDER BY hire_date DESC;

21. Implementa?i query-ul care a generat urm?torul rezultat. Query-ul returneaz?, în total, 45
de rânduri. 

SELECT last_name, salary, job_id, TO_NUMBER(TO_CHAR(SYSDATE, 'YYYY'), '9999') - TO_NUMBER(TO_CHAR(hire_date, 'YYYY'), '9999') AS "Ani lucrati", TO_CHAR(hire_date, 'YYYY') AS "Anul angajarii"
FROM employees
WHERE lower(job_id) like '%clerk%'; 


-- LABORATOR 2 - SAPTAMANA 3

-- APLICARE FUNCTII

SELECT TO_CHAR(SYSDATE, 'DD/MM/YYYY')
FROM DUAL;

SELECT TO_DATE('18-MAR-2025','dd-mon-yyyy')
FROM DUAL;

/*
DIMENSIUNI:

Char -> Maximum size: 2000 bytes;
Varchar, Varchar2  -> Maximum size: 4000 bytes;
Number -> 999...(38 9's) x10125 maximum value
                  -999...(38 9's) x10125 minimum value (precizie: 38 de cifre);
                  
*/

SELECT LTRIM ('     info')
FROM DUAL;

SELECT RTRIM ('infoXXXX', 'X')  
FROM DUAL;

-- ANALIZATI CU ATENTIE URMATOARELE DOUA EXEMPLE!

SELECT TRIM (BOTH 'X' FROM 'XinfoXxX')
FROM DUAL;

SELECT RTRIM ('XinfoXxXabc', 'bacX')
FROM DUAL;

-- RULATI SI ANALIZATI EXEMPLELE:

SELECT TRANSLATE('$a$aaa','$a','b')
FROM DUAL;

SELECT TRANSLATE('$a$aaa','$a','bac')
FROM DUAL;

SELECT TRANSLATE('cerc','ce','d')
FROM DUAL;

SELECT TRANSLATE('$a$aaa','aa','bc')
FROM DUAL;

SELECT TRANSLATE('$a$aaa','ac','cd')
FROM DUAL;



-- CUM SE TESTEAZA URMATOAREA OPERATIE?

-- FORMA GENERALA: expr_date -/+ expr_number

SELECT '07-03-2023' + 3 -- gresit
FROM dual; 

SELECT TO_DATE('07-03-2023', 'DD-MM-YYYY') + 3
FROM dual; 

-- DE CE NU ESTE CORECTA VARIANTA ANTERIOARA? 

_____;


-- FORMA GENERALA: expr_date1 – expr_date2

SELECT SYSDATE - TO_DATE ('10-07-2000', 'DD-MM-YYYY')
FROM dual; 

-- CUM ROTUNJIM? 

SELECT ROUND(SYSDATE - TO_DATE ('10-07-2000', 'DD-MM-YYYY'))
FROM dual;


-- ANALIZATI:

SELECT NVL (1, 'a')
FROM dual; 


-- EXERCITII - FUNCTII PE SIRURI DE CARACTERE

1.	Scrie?i o cerere care are urm?torul rezultat pentru fiecare angajat: 

<prenume angajat> <nume angajat> castiga <salariu> lunar dar doreste 
<salariu de 3 ori mai mare>. Etichetati coloana “Salariu ideal”. 

Pentru concatenare, utiliza?i atât func?ia CONCAT cât ?i operatorul “||”.

SELECT concat(first_name,' ') || last_name || ' castiga ' || salary 
                              || ' lunar dar doreste ' || salary * 3 "Salariu ideal"
FROM employees;


2.	Scrie?i o cerere prin care s? se afi?eze prenumele salariatului 
cu prima litera majuscul? ?i toate celelalte litere minuscule, 
numele acestuia cu majuscule ?i lungimea numelui, 
pentru angaja?ii al c?ror nume începe cu J sau M sau care au a treia liter? din nume A. 
Rezultatul va fi ordonat descresc?tor dup? lungimea numelui. 
Se vor eticheta coloanele corespunz?tor. 
Se cer 2 solu?ii (cu operatorul LIKE ?i func?ia SUBSTR).

--LIKE
SELECT INITCAP(first_name) "Prenume", UPPER(last_name) "NUME", LENGTH(last_name) "Lungimea numelui"
FROM employees
WHERE UPPER(last_name) like 'J%' or upper(last_name) like 'M%' or upper(last_name) like '__A%'
ORDER BY LENGTH(last_name) desc;

--SUBSTR
--SUBSTR(string, start [,n])


3.	S? se afi?eze, pentru angaja?ii cu prenumele „Steven”, 
codul ?i numele acestora, precum ?i codul departamentului în care lucreaz?. 
C?utarea trebuie s? nu fie case-sensitive, iar eventualele blank-uri care preced 
sau urmeaz? numelui trebuie ignorate.

--Varianta 1:
SELECT employee_id, last_name, department_id
FROM employees
WHERE LTRIM(RTRIM(UPPER(first_name)))='STEVEN';

--Varianta 2:
SELECT employee_id, last_name, department_id
FROM employees
WHERE TRIM(BOTH FROM UPPER(first_name))='STEVEN';


4. S? se afi?eze pentru to?i angaja?ii al c?ror nume se termin? cu litera 'e', 
codul, numele, lungimea numelui ?i pozi?ia din nume în care apare 
prima data litera 'A'. 
Utiliza?i alias-uri corespunz?toare pentru coloane;

SELECT employee_id "Id Ang", last_name "Nume", length(last_name) "Lung Nume",
       instr(upper(last_name),'A',1,1) "Pozitie litera in nume"
FROM employees
WHERE substr(lower(last_name), -1) = 'e';



-- FUNCTII ARITMETICE

5.	S? se afi?eze detalii despre salaria?ii care au lucrat un num?r 
întreg de s?pt?mâni pân? la data curent?. 
Obs: Solu?ia necesit? rotunjirea diferen?ei celor dou? date calendaristice. 

SELECT *
FROM employees
WHERE (TO_DATE(TO_CHAR(SYSDATE, 'dd-mm-yyyy'), 'dd-mm-yyyy') - TO_DATE(TO_CHAR(hire_date, 'dd-mm-yyyy'), 'dd-mm-yyyy')) / 7 = (TO_DATE(TO_CHAR(SYSDATE, 'dd-mm-yyyy'), 'dd-mm-yyyy') - TO_DATE(TO_CHAR(hire_date, 'dd-mm-yyyy'), 'dd-mm-yyyy')) / 7;


6.	S? se afi?eze codul salariatului, numele, salariul, salariul m?rit cu 15%, 
exprimat cu dou? zecimale ?i num?rul de sute al salariului nou 
rotunjit la 2 zecimale. 
Eticheta?i ultimele dou? coloane “Salariu nou”, respectiv “Numar sute”. 
Se vor lua în considerare salaria?ii al c?ror salariu nu este divizibil cu 1000. 

SELECT employee_id, last_name, salary, 
       round(salary + 0.15 * salary, 2)  "Salariu Nou",  
       round((salary + 0.15 * salary) / 100, 2)  "Numar sute" 
FROM employees
WHERE MOD(salary, 1000) != 0;  


7.	S? se listeze numele ?i data angaj?rii salaria?ilor care câ?tig? comision. 
S? se eticheteze coloanele „Nume angajat”, „Data angajarii”. 
Utiliza?i func?ia RPAD pentru a determina ca data angaj?rii s? aib? 
lungimea de 20 de caractere.

SELECT last_name  AS "Nume angajat" , RPAD(to_char(hire_date),20,'X')  "Data angajarii"
FROM employees
WHERE  commission_pct IS NOT NULL;


-- FUNCTII SI OPERATII CU DATE CALENDARISTICE

8. S? se afi?eze data (numele lunii, ziua, anul, ora, minutul si secunda) 
de peste 30 zile.

SELECT TO_CHAR(SYSDATE + 30, 'MONTH DD YYYY HH24:MI:SS') "Data"
FROM DUAL;

9. S? se afi?eze num?rul de zile r?mase pân? la sfâr?itul anului.

SELECT to_date('31-12-2026','dd-mm-yyyy') - sysdate
FROM dual;

10. a) S? se afi?eze data de peste 12 ore.

SELECT TO_CHAR(SYSDATE + 12/24, 'DD/MM HH24:MI:SS') "Data"
FROM DUAL;

b) S? se afi?eze data de peste 5 minute
Obs: Cât reprezint? 5 minute dintr-o zi?


SELECT TO_CHAR(SYSDATE + 1 / 288, 'DD/MM HH24:MI:SS') "Data"
FROM DUAL;


11.	S? se afi?eze numele ?i prenumele angajatului (într-o singur? coloan?), 
data angaj?rii ?i data negocierii salariului, care este prima zi de Luni 
dup? 6 luni de serviciu. Eticheta?i aceast? coloan? “Negociere”.

SELECT concat(last_name, first_name), hire_date,
       NEXT_DAY(ADD_MONTHS(hire_date, 6), 'monday') "Negociere"
FROM employees;


12.	Pentru fiecare angajat s? se afi?eze numele ?i num?rul de luni 
de la data angaj?rii. Eticheta?i coloana “Luni lucrate”. 
S? se ordoneze rezultatul dup? num?rul de luni lucrate. 
Se va rotunji num?rul de luni la cel mai apropiat num?r întreg.

 -- prima varianta de ordonare

SELECT last_name, round(months_between(sysdate, hire_date)) "Luni lucrate"
FROM employees
ORDER BY MONTHS_BETWEEN(SYSDATE, hire_date);


-- a doua varianta de ordonare

SELECT last_name, round(months_between(sysdate, hire_date)) "Luni lucrate"
FROM employees
ORDER BY 2;


-- a treia varianta de ordonare

SELECT last_name, round(months_between(sysdate, hire_date)) "Luni lucrate"
FROM employees
ORDER BY "Luni lucrate";


-- FUNCTII DIVERSE

13.	S? se afi?eze numele angaja?ilor ?i comisionul. Dac? un angajat 
nu câ?tig? comision, s? se scrie “Fara comision”. Eticheta?i coloana “Comision”.

SELECT last_name, NVL(TO_CHAR(commission_pct, '.99'), 'Fara Comision') "Comision"
FROM employees; 


14.	S? se listeze numele, salariul ?i comisionul tuturor angaja?ilor 
al c?ror venit lunar (salariu + valoare comision) dep??e?te 10 000. 

SELECT  last_name, salary, commission_pct
FROM  employees 
WHERE  salary * (1 + NVL(commission_pct, 0)) > 10000;



-- LABORATOR 3
-- RECAPITULARE JOIN

-- Join-ul este opera?ia de reg?sire a datelor din dou? sau mai multe tabele, 
-- pe baza valorilor comune ale unor coloane. De obicei, aceste coloane reprezint? 
-- cheia primar?, respectiv cheia extern? a tabelelor. 
-- Reamintim c? pentru a realiza un join între n tabele
-- o sa fie nevoie de cel pu?in n – 1 condi?ii de join


--TIPURI DE JOIN:

-- NONEQUIJOIN – condi?ia de join con?ine al?i operatori decât operatorul de egalitate
--Exemplu Nonequijoin:

SELECT last_name, salary, grade_level, lowest_sal, highest_sal
FROM employees, job_grades
WHERE salary BETWEEN lowest_sal AND highest_sal;

SELECT * FROM job_grades;


-- INNER JOIN (equijoin, join simplu) 
-- corespunde situa?iei în care valorile de pe coloanele ce apar în condi?ia 
-- de join trebuie s? fie egale

--EXEMPLE (folosind atat join-ul in WHERE cat si cel din standardul SQL3):

-- VARIANTA 1 - Condi?ia de Join este scris? în clauza WHERE a instruc?iunii SELECT 

-- S? se afi?eze codul si numele angaja?ilor, dar si numele si codul departamentelor 
-- pentru to?i angaja?ii care lucreaz? în departamente.

SELECT employee_id, last_name, d.department_name, d.department_id
FROM employees e, departments d
WHERE e.department_id = d.department_id;

-- VARIANTA 2 - --JOIN SCRIS IN FROM (standardul SQL3) - folosind ON
SELECT employee_id, last_name, d.department_name, d.department_id
FROM employees e
JOIN departments d
ON e.department_id = d.department_id;
     

-- JOIN SCRIS IN FROM (standardul SQL3) - folosind USING
-- USING SE UTILIZEAZA dac? exist? coloane având acelasi nume
-- in acest caz coloanele referite nu trebuie sa contina calificatori 
-- adica sa nu fie precedate de nume de tabele sau alias-uri

SELECT employee_id, last_name, department_name, department_id
FROM employees JOIN departments USING(department_id);

-- Cele doua variante (join in where si join in from) sunt echivalente.


-- OUTER JOIN

-- S? se afi?eze codul angaja?ilor, numele acestora, numele departamentului si codul departamentului 
-- pentru to?i angaja?ii. 
-- S? se afi?eze toti angajatii, chiar dac? au sau nu departament (se vor afi?a atât angajatii care 
-- lucreaz? intr-un departament, cât ?i angajatii care nu au departament).

-- pentru a afisa si angajatii care nu au departament se utilizeaza 
-- simbolul (+) in partea deficitara de informatie

-- deficit de informatie -> angajati FARA departament 

SELECT employee_id, last_name, d.department_id, department_name
FROM employees e, departments d
WHERE e.department_id = d.department_id (+);


-- S? se afi?eze codul angaja?ilor, numele acestora, numele departamentului si codul departamentului 
-- pentru to?i angaja?ii. 
-- S? se afi?eze toate departamentele, chiar dac? au sau nu angaja?i (se vor afi?a atât departamentele în care 
-- lucreaz? angaja?i, cât ?i departamentele care nu au angaja?i).

-- deficit de informatie -> departamente FARA angajati 

SELECT employee_id, last_name, d.department_id, department_name
FROM employees e, departments d
WHERE e.department_id (+) = d.department_id;


-- In cazul standardului SQL3 se utilizeaza LEFT, RIGHT ?i FULL OUTER JOIN
-- DISCUTIE!


-- CROSS JOIN - produs cartezian
SELECT employee_id, last_name, e.department_id, department_name
FROM employees e CROSS JOIN departments d;


-- NATURAL JOIN 
SELECT last_name, job_id, job_title                       
FROM employees NATURAL JOIN jobs;   

SELECT last_name, e.job_id, job_title 
FROM employees e, jobs j 
WHERE e.job_id = j.job_id;

1. S? se listeze codurile ?i denumirile job-urilor care exist? în departamentul
30.

SELECT DISTINCT j.job_id, j.job_title
FROM employees e
JOIN jobs j
ON e.job_id = j.job_id
WHERE e.department_id = 30;

2. S? se afi?eze numele angajatului, numele departamentului ?i id-ul loca?iei
pentru to?i angaja?ii care câ?tig? comision

SELECT last_name, department_name, location_id
FROM employees e 
JOIN departments d
ON e.department_id = d.department_id
WHERE commission_pct IS NOT NULL;

3. S? se afi?eze numele angaja?ilor, titlul job-ului ?i denumirea
departamentului pentru to?i angaja?ii care lucreaz? în Oxford (coloana - city).

SELECT last_name, job_title, department_name
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
JOIN jobs j
ON e.job_id = j.job_id
JOIN locations l
ON l.location_id = d.location_id
WHERE UPPER(city) = 'OXFORD';

4. S? se afi?eze codul angajatului ?i numele acestuia, împreun? cu numele ?i
codul ?efului s?u direct. Se vor eticheta coloanele Cod Angajat, Nume
Angajat, Cod Manager, Nume Manager.

SELECT ang.employee_id "Cod angajat", ang.last_name "Nume angajat", sef.last_name "Nume sef", sef.employee_id "Cod sef"
FROM employees ang JOIN employees sef
ON ang.manager_id = sef.employee_id;

5. S? se modifice cererea anterioar? pentru a afi?a to?i salaria?ii, inclusiv cei care
nu au ?ef

SELECT ang.employee_id "Cod angajat", ang.last_name "Nume angajat", sef.last_name "Nume sef", sef.employee_id "Cod sef"
FROM employees ang LEFT JOIN employees sef
ON ang.manager_id = sef.employee_id;

6. Scrie?i o cerere care afi?eaz? numele angajatului, codul departamentului în
care acesta lucreaz? ?i numele colegilor s?i de departament. Se vor eticheta
coloanele corespunz?tor.

SELECT e.last_name "Nume ang", e.department_id "Dep ang", c.last_name "Coleg dep"
FROM employees e
JOIN employees c
ON e.department_id = c.department_id
WHERE e.employee_id != c.employee_id;

7. Crea?i o cerere prin care s? se afi?eze numele angajatilor, codul job-ului,
titlul job-ului, numele departamentului ?i salariul angaja?ilor. Se vor include
?i angaja?ii al c?ror departament nu este cunoscut.

SELECT e.last_name, e.job_id, j.job_title, d.department_name, e.salary
FROM employees e
LEFT JOIN departments d
ON e.department_id = d.department_id
JOIN jobs j
ON e.job_id = j.job_id;

8. S? se afi?eze numele ?i data angaj?rii pentru salaria?ii care au fost angaja?i
dup? salariatul cu numele (last_name) Gates

SELECT e.last_name, e.hire_date
FROM employees e JOIN employees g
ON upper(g.last_name) = 'GATES'
WHERE e.hire_date > g.hire_date;

9. Scrie?i o cerere pentru a afi?a numele salariatului, luna (în litere), anul
angaj?rii ?i valoarea comisionului pentru to?i salaria?ii din acela?i departament
cu Gates (last_name este Gates) – se verific? numele scris cu prima liter? mare
?i restul literelor mici, al c?ror nume con?ine litera “a”. Se va exclude Gates. Se
vor utiliza aliasuri pentru numele coloanelor din output. În cazul în care un
angajat nu câ?tig? comision, se va scrie în output, pe coloana respectiv?,
mesajul “Nu câ?tig? comision”. Rezultatul se va ordona alfabetic dup? numele
salaria?ilor. Output-ul este urm?torul:

SELECT e.last_name "Nume", TO_CHAR(e.hire_date, 'month') || ' - ' || TO_CHAR(e.hire_date, 'YYYY') "Luna si anul ang", NVL(TO_CHAR(e.commission_pct, '.99'), 'Nu castiga comision') "Comision"
FROM employees e
JOIN employees g
ON e.department_id = g.department_id
WHERE e.employee_id != g.employee_id AND INITCAP(g.last_name) = 'Gates' AND upper(e.last_name) like '%A%' 
ORDER BY e.last_name;

10.S? se afi?eze numele, salariul, titlul job-ului, ora?ul ?i ?ara în care lucreaz?
angaja?ii condu?i direct de King.

SELECT e.last_name, e.salary, j.job_title, l.city, c.country_name
FROM employees e
JOIN employees k
ON e.manager_id = k.employee_id
JOIN departments d
ON e.department_id = d.department_id
JOIN locations l
ON d.location_id = l.location_id
JOIN countries c
ON l.country_id = c.country_id
JOIN jobs j
ON e.job_id = j.job_id
WHERE INITCAP(k.last_name) = 'King';

11.S? se afi?eze codul departamentului, numele departamentului, numele ?i jobul tuturor angaja?ilor din departamentele al c?ror nume con?ine ?irul ‘ti’. De
asemenea, se va lista salariul angaja?ilor, în formatul “$99,999.00”. Rezultatul
se va ordona alfabetic dup? numele departamentului, ?i în cadrul acestuia,
dup? numele angaja?ilor.

SELECT d.department_id, department_name, job_id, last_name,
to_char(salary,'$99,999.00')
FROM employees e JOIN departments d ON (e.department_id =
d.department_id)
WHERE lower(department_name) like '%ti%'
ORDER BY department_name, last_name;

-- operatori pe multimi sau cv

1. Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” sau în care
lucreaz? angaja?i având codul job-ului “SA_REP”.

SELECT department_id
FROM departments
WHERE lower(department_name) like '%re%'

UNION

SELECT department_id
FROM employees
WHERE upper(job_id) = 'SA_REP';

2. Ce se întâmpl? dac? înlocuim UNION cu UNION ALL în comanda precedent?? -- imi ia 500 de departmente 80

SELECT department_id
FROM departments
WHERE lower(department_name) like '%re%'

UNION ALL

SELECT department_id
FROM employees
WHERE upper(job_id) = 'SA_REP';

3. S? se ob?in? codurile departamentelor în care nu lucreaz? nimeni (nu este
introdus niciun salariat în tabelul employees). Se cer dou? solu?ii.

-- 1 cu operatorul MINUS
SELECT department_id
FROM departments

MINUS

SELECT department_id
FROM employees;

-- 2 - cu subquery

SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT DISTINCT NVL(department_id, 0) FROM employees);

4. Se cer codurile departamentelor al c?ror nume con?ine ?irul “re” ?i în care
lucreaz? angaja?i având codul job-ului “HR_REP”. 

SELECT department_id
FROM departments
WHERE lower(department_name) like '%re%'

INTERSECT

SELECT department_id
FROM employees
WHERE upper(job_id) = 'HR_REP';

1. Afi?a?i o list? cu to?i utilizatorii ?i post?rile publicate de ace?tia. Se vor afi?a
inclusiv utilizatorii care nu au publicat nicio postare.
Se vor afi?a codul si numele utilizatorilor, împreuna cu codul ?i textul
post?rilor. Se vor ordona post?rile în func?ie de dat?, în ordine
descresc?toare, iar valorile NULL se vor afi?a la finalul valorilor diferite de
NULL.

SELECT u.id_utilizator "Cod user", u.nume "Nume user", p.id_postare "Cod postare", p.continut "Text postare"
FROM utilizatori u
LEFT JOIN postari p
ON u.id_utilizator = p.id_user;


2. Afi?a?i toate post?rile realizate în luna martie 2024 de c?tre prietenii
utilizatorului cu id-ul 1, cu excep?ia post?rilor realizate de utilizatorii care nu
îl urm?resc înapoi (adic? nu exist? rela?ia invers?).
S? se afi?eze codul ?i numele prietenului care a postat, con?inutul post?rii
?i data la care a fost realizat? postarea. Data o s? fie formatat? dd.mm.yyyy.
Se vor eticheta toate coloanele corespunz?tor.

SELECT prt.id_utilizator "Cod user", prt.nume "Nume user", p.continut "Text postare", p.data_postarii "Data postarii"
FROM utilizatori prt
JOIN prieteni f
ON prt.id_utilizator = f.id_user1
JOIN postari p
ON prt.id_utilizator = p.id_user
WHERE f.id_user2 = 1 AND TO_CHAR(p.data_postarii, 'MM-YYYY') = '03-2024'

UNION

SELECT prt.id_utilizator "Cod user", prt.nume "Nume user", p.continut "Text postare", p.data_postarii "Data postarii"
FROM utilizatori prt
JOIN prieteni f
ON prt.id_utilizator = f.id_user2
JOIN postari p
ON prt.id_utilizator = p.id_user
WHERE f.id_user1 = 1 AND TO_CHAR(p.data_postarii, 'MM-YYYY') = '03-2024'; 



-- LABORATOR 4 - SAPTAMANA 6 


1.	S? se creeze tabelele EMP_rpa, DEPT_rpa prin copierea structurii ?i con?inutului 
tabelelor EMPLOYEES, respectiv DEPARTMENTS. 

-- în care ?irul de caractere “rpa” ->
-- p reprezint? prima liter? a prenumelui ->
-- iar nu reprezint? primele dou? litere ale numelui)

CREATE TABLE EMP_rpa AS SELECT * FROM employees;
CREATE TABLE DEPT_rpa AS SELECT * FROM departments;


2.	Lista?i structura tabelelor surs? ?i a celor create anterior. Ce se observ??

-- listam structura
DESC employees;
DESC emp_rpa;



3.	Lista?i con?inutul tabelelor create anterior.

--listam continutul
SELECT * from emp_rpa;


-- COMENZILE LMD, LDD SI LCD 

LMD - 

LDD -

LCD -

COMMIT - 

ROLLBACK - 



Ce se intampla daca executam in acest punct comanda ROLLBACK?
Ce se intampla daca executam comanda COMMIT?

-- EXEMPLE




4.	Pentru introducerea constrângerilor de integritate, 
executa?i instruc?iunile LDD indicate în continuare.

ALTER TABLE emp_rpa
ADD CONSTRAINT pk_emp_rpa PRIMARY KEY(employee_id);


ALTER TABLE dept_rpa
ADD CONSTRAINT pk_dept_rpa PRIMARY KEY(department_id);


ALTER TABLE emp_rpa
ADD CONSTRAINT fk_emp_dept_rpa FOREIGN KEY(department_id) REFERENCES dept_rpa(department_id);
   
   
Obs: Ce constrângere nu am implementat?

___



DESC EMP_rpa;
DESC DEPT_rpa;



-- APOI SE REZOLVA, IN CADRUL LABORATORULUI CURENT, URMATOARELE EXERCITII


5.	S? se insereze departamentul 300, cu numele Programare în DEPT_rpa.
Analiza?i cazurile, precizând care este solu?ia corect? ?i explicând erorile 
celorlalte variante. 
Pentru a anula efectul instruc?iunii(ilor) corecte, utiliza?i comanda ROLLBACK.
       
       
DESC DEPT_;

SELECT * FROM dept_rpa;

--discutie tipuri de INSERT si erori posibile
--vezi laborator
                                                      
--a)	
INSERT INTO DEPT_rpa 
VALUES (300, 'Programare');


--b)	
INSERT INTO DEPT_rpa (department_id, department_name)
VALUES (300, 'Programare');

SELECT * FROM dept_rpa;


--c)	
INSERT INTO DEPT_rpa (department_name, department_id)
VALUES (300, 'Programare');


--d)	
INSERT INTO DEPT_rpa (department_id, department_name, location_id)
VALUES (300, 'Programare', null);	


-- varianta corecta
rollback;
_____	


SELECT * FROM dept_rpa;


--e)	
INSERT INTO DEPT_rpa (department_name, location_id)
VALUES ('Programare', null);


-- Ce se intampla daca executam rollback?

_____


-- Executati varianta corecta si permanentizati modificarile.

COMMIT;



6. S? se insereze un angajat corespunz?tor departamentului introdus anterior 
în tabelul EMP_rpa, precizând valoarea NULL pentru coloanele a c?ror valoare 
nu este cunoscut? la inserare (metoda implicit? de inserare). 
Determina?i ca efectele instruc?iunii s? devin? permanente.
Aten?ie la constrângerile NOT NULL asupra coloanelor tabelului!


-- inserare prin metoda IMPLICITA de inserare
-- dorim sa inseram un angajat in depart 300

DESC emp_rpa;
SELECT * FROM emp_rpa;


INSERT INTO emp_rpa
VALUES (250, NULL, 'nume250', 'email250', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);

-- Cum permanentizam efectul actiunii anterioare?

COMMIT;

SELECT * FROM emp_rpa;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_rpa
VALUES (250, NULL, 'nume251', 'email251', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);


-- Se poate anula inserarea anterioara?

_____;

SELECT * FROM emp_rpa;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_rpa
VALUES (251, NULL, 'nume251', 'email251', NULL, '03-10-2023', 
       'IT_PROG', NULL, NULL, NULL, 300);
       
SELECT * FROM emp_rpa;

ROLLBACK;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_rpa
VALUES (252, NULL, 'nume252', 'email252', NULL, SYSDATE, 
       'IT_PROG', NULL, NULL, NULL, 310);


-- IN CELE DIN URMA PASTRAM IN BAZA DE DATE ANGAJATUL CU ID-UL 250 IN DEPART. 300



7. S? se mai introduc? un angajat corespunz?tor departamentului 300, 
precizând dup? numele tabelului lista coloanelor în care se introduc valori 
(metoda explicita de inserare). 
Se presupune c? data angaj?rii acestuia este cea curent? (SYSDATE). 
Salva?i înregistrarea.

desc emp_rpa;

--inserare prin metoda EXPLICITA de inserare
INSERT INTO emp_rpa (hire_date, job_id, employee_id, last_name, email, department_id)
VALUES (sysdate, 'sa_man', 278, 'nume_278', 'email_278', 300);

COMMIT;

SELECT * FROM emp_rpa;


8. Crea?i un nou tabel, numit EMP1_rpa, care va avea aceea?i structur? ca ?i EMPLOYEES, 
dar fara inregistrari. Copia?i în tabelul EMP1_rpa salaria?ii (din tabelul EMPLOYEES) 
al c?ror comision dep??e?te 25% din salariu (se accepta omiterea constrangerilor).


-- crearea tabelului
CREATE TABLE emp1_rpa AS SELECT * FROM employees;

-- eliminarea inregistrarilor
DELETE FROM emp1_rpa;

-- adaugarea noilor valori (inserarea randurilor)
INSERT INTO emp1_rpa
    SELECT *
    FROM employees
    WHERE commission_pct > 0.25;

SELECT * FROM emp1_rpa;


-- Ce se intampla daca executam un rollback? 

ROLLBACK;




-- SA SE ANALIZEZE EXERCITIILE 9, 10 SI 11 

9. S? se creeze un fi?ier (script file) care s? permit? introducerea de înregistr?ri 
în tabelul EMP_rpa în mod interactiv. 
Se vor cere utilizatorului: codul, numele, prenumele si salariul angajatului. 
Câmpul email se va completa automat prin concatenarea primei litere din prenume 
?i a primelor 7 litere din nume.    
Executati script-ul pentru a introduce 2 inregistrari in tabel.


INSERT INTO emp_rpa (employee_id, first_name, last_name, email, hire_date, job_id, salary)
VALUES(&cod, '&&prenume', '&&nume', substr('&prenume',1,1) || substr('&nume',1,7), 
       sysdate, 'it_prog', &sal);
       
UNDEFINE prenume;
UNDEFINE nume;

SELECT * FROM emp_rpa;


10. Crea?i 2 tabele emp2_rpa ?i emp3_rpa cu aceea?i structur? ca tabelul EMPLOYEES, 
dar f?r? înregistr?ri (accept?m omiterea constrângerilor de integritate). 
Prin intermediul unei singure comenzi, copia?i din tabelul EMPLOYEES:

-  în tabelul EMP1_rpa salaria?ii care au salariul mai mic decât 5000;
-  în tabelul EMP2_rpa salaria?ii care au salariul cuprins între 5000 ?i 10000;
-  în tabelul EMP3_rpa salaria?ii care au salariul mai mare decât 10000.

Verifica?i rezultatele, apoi ?terge?i toate înregistr?rile din aceste tabele.

--VEZI INSERARI MULTI-TABEL IN LABORATORUL 4

CREATE TABLE emp1_rpa AS SELECT * FROM employees;

DELETE FROM emp1_rpa;

SELECT * FROM emp1_rpa; 

CREATE TABLE emp2_rpa AS SELECT * FROM employees;

DELETE FROM emp2_rpa;

CREATE TABLE emp3_rpa AS SELECT * FROM employees;

DELETE FROM emp3_rpa;

INSERT ALL
   WHEN salary < 5000 THEN
      INTO emp1_rpa					
   WHEN salary > = 5000 AND salary <= 10000 THEN
      INTO emp2_rpa
   ELSE 
      INTO emp3_rpa
SELECT * FROM employees;  


SELECT * FROM emp1_rpa;
SELECT * FROM emp2_rpa;
SELECT * FROM emp3_rpa;



11. S? se creeze tabelul EMP0_rpa cu aceea?i structur? ca tabelul EMPLOYEES 
(f?r? constrângeri), dar f?r? inregistrari. 
Copia?i din tabelul EMPLOYEES:

-  în tabelul EMP0_rpa salaria?ii care lucreaz? în departamentul 80;
-  în tabelul EMP1_rpa salaria?ii care au salariul mai mic decât 5000;
-  în tabelul EMP2_rpa salaria?ii care au salariul cuprins între 5000 ?i 10000;
-  în tabelul EMP3_rpa salaria?ii care au salariul mai mare decât 10000.

Dac? un salariat se încadreaz? în tabelul emp0_rpa, atunci acesta nu va mai fi inserat 
?i în alt tabel (tabelul corespunz?tor salariului s?u);

CREATE TABLE emp0_rpa AS SELECT * FROM employees;

DELETE FROM emp0_rpa;


INSERT FIRST
    WHEN department_id = 80 THEN
        INTO emp0_rpa
    WHEN salary < 5000 THEN
        INTO emp1_rpa
    WHEN salary > = 5000 AND salary <= 10000 THEN
        INTO emp2_rpa
    ELSE 
        INTO emp3_rpa
SELECT * FROM employees;

SELECT * FROM emp0_rpa;
SELECT * FROM emp1_rpa;
SELECT * FROM emp2_rpa;
SELECT * FROM emp3_rpa;


-- COMANDA UPDATE - VEZI LABORATOR (pentru notiunile teoretice)

12. M?ri?i salariul tuturor angaja?ilor din tabelul EMP_rpa cu 5%. 
Vizualizati, iar apoi anula?i modific?rile.

UPDATE emp_rpa
SET salary = salary * 1.05;

SELECT * FROM emp_rpa;

ROLLBACK;



13. Schimba?i jobul tuturor salaria?ilor din departamentul 80 care au comision, în 'SA_REP'. 
Anula?i modific?rile.

UPDATE emp_rpa
SET job_id = 'SA_REP'
WHERE department_id = 80 and commission_pct IS NOT NULL;

SELECT * FROM emp_rpa;

ROLLBACK;


14. S? se promoveze Douglas Grant la manager în departamentul 20 (tabelul dept_rpa), 
având o cre?tere de salariu cu 1000$. 


-- verificari

SELECT *
FROM emp_rpa
WHERE lower(last_name||first_name) = 'grantdouglas';

SELECT * FROM dept_rpa
WHERE department_id = 20;

-- solutia problemei

UPDATE dept_rpa
SET manager_id = (SELECT employee_id FROM emp_rpa WHERE lower(last_name||first_name) = 'grantdouglas')
WHERE department_id = 20;

UPDATE emp_rpa
SET salary = salary + 1000
WHERE lower(last_name||first_name) = 'grantdouglas';

ROLLBACK;

-- COMANDA DELETE - VEZI LABORATOR (pentru notiunile teoretice)

15.	?terge?i toate înregistr?rile din tabelul DEPT_rpa. 
Ce înregistr?ri se pot ?terge? Anula?i modific?rile. 

DELETE FROM dept_rpa; 

SELECT * FROM dept_rpa;

SELECT * FROM emp_rpa;

ROLLBACK;



16.	Suprima?i departamentele care nu au angajati. Anula?i modific?rile.

-- prima data afisam departamentele care nu au angajati

SELECT department_id
FROM dept_rpa

MINUS

SELECT department_id
FROM emp_rpa;

-- apoi stergem departamentele care nu au angajati

DELETE FROM dept_rpa
WHERE department_id IN (
SELECT department_id
FROM dept_rpa

MINUS

SELECT department_id
FROM emp_rpa
);

ROLLBACK;
17. S? se mai introduc? o linie in tabelul DEPT_rpa.

desc dept_rpa;

INSERT INTO dept_rpa
VALUES(320, 'dept_nou', NULL, NULL);

SELECT * FROM dept_rpa;


18. S? se marcheze un punct intermediar in procesarea tranzac?iei (SAVEPOINT p).

SAVEPOINT p;


19. S? se ?tearg? din tabelul DEPT_rpa departamentele care au codul de departament 
cuprins intre 160 si 200. Lista?i con?inutul tabelului.

DELETE FROM dept_rpa
WHERE department_id BETWEEN 160 AND 200; 

SELECT * FROM dept_rpa;


20. S? se renun?e la cea mai recent? opera?ie de ?tergere, f?r? a renun?a 
la opera?ia precedent? de introducere. 
Determina?i ca modific?rile s? devin? permanente;

SELECT * FROM dept_rpa;

ROLLBACK TO p;

COMMIT;




-- LABORATOR 5 - SAPTAMANILE 7 SI 8

-- Limbajul de definire a datelor (LDD) 

--COMENZI CARE FAC PARTE DIN LDD:

CREATE, ALTER, DROP, TRUNCATE, RENAME

--Ce comanda LCD se executa dupa instructiunile de tip LDD?

COMMIT

-- Crearea tabelelor (vezi notiunile in laborator 5)


-- EXERCITII 


1. Să se creeze tabelul ANGAJATI_rpa 
(rpa se alcatuieşte din prima literă din prenume şi primele două din numele studentului) 
corespunzător schemei relaţionale:

ANGAJATI_rpa(cod_ang number(4), nume varchar2(20), prenume varchar2(20), email char(15), 
             data_ang date, job varchar2(10), cod_sef number(4), salariu number(8, 2), 
             cod_dep number(2)
            );
  
a) cu precizarea cheilor primare la nivel de coloană 
si a constrangerilor NOT NULL pentru coloanele nume şi salariu;
De asemenea, se presupune că valoarea implicită a coloanei data_ang este SYSDATE, 
iar adresa de e-mail trebuie sa aiba o valoare unica    

CREATE TABLE angajati_rpa
      ( cod_ang number(4) PRIMARY KEY,
        nume varchar2(20) NOT NULL,
        prenume varchar2(20),
        email char(15) NOT NULL,
        data_ang date DEFAULT SYSDATE,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8,2) NOT NULL,
        cod_dep number(2)
       );
 
SELECT * FROM angajati_rpa;
DESC angajati_rpa;
    

b) cu precizarea cheii primare la nivel de tabel 
si a constrângerilor NOT NULL pentru coloanele nume şi salariu.

DROP TABLE angajati_rpa;

CREATE TABLE angajati_rpa
      ( cod_ang number(4),
        nume varchar2(20) constraint nume_ang not null,
        prenume varchar2(20),
        email char(15) unique,
        data_ang date default sysdate,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8, 2) constraint salariu_ang not null,
        cod_dep number(2),
        constraint pkey_ang primary key(cod_ang) --constrangere la nivel de tabel
       );
 



-- Rezolvati urmatoarele exercitii:


2. Adăugaţi următoarele înregistrări în tabelul ANGAJATI_rpa:

-- Analizati tabelul din Laborator 5

-- 1
-- metoda explicita (se precizeaza coloanele)
INSERT INTO angajati_rpa(cod_ang, nume, prenume, data_ang, job, salariu, cod_dep)
VALUES(100, 'nume1', 'prenume1', null, 'Director', 20000, 10);



-- DE CE NU SUNT TRECUTE, IN COMANDA INSERT INTO, TOATE COLOANELE DIN TABELUL ANGAJATI
-- (VEZI TABELUL DIN LABORATOR 5, EXERCITIUL 2)


DESC angajati_rpa;
SELECT * FROM angajati_rpa;



-- DE CE A FOST PRECIZATA COLOANA data_ang si nu a fost precizata coloana cod_sef?
R: Pt ca data_ang are default sysdate dar clar seful nu e angajat atunci si seful n-are sef cum ar veni



-- 2           
-- metoda implicita de inserare (nu se precizeaza coloanele)
INSERT INTO angajati_rpa
VALUES(101, 'nume2', 'prenume2', 'nume2', TO_DATE('02-02-2004','dd-mm-yyyy'), 
       'Inginer', 100, 10000, 10);
   

-- 3          
INSERT INTO angajati_rpa
VALUES(102, 'nume3', 'prenume3', 'nume3', TO_DATE('05-06-2000','dd-mm-yyyy'), 
       'Analist', 101, 5000, 20);


-- 4             
INSERT INTO angajati_rpa(cod_ang, nume, prenume, data_ang, job, cod_sef, salariu, cod_dep)
VALUES(103, 'nume4', 'prenume4', null, 'Inginer', 100, 9000, 20);


-- 5       
INSERT INTO angajati_rpa
VALUES(104, 'nume5', 'prenume5', 'nume5', null, 'Analist', 101, 3000, 30);



-- CE COMANDA SE EXECUTA, OBLIGATORIU, DUPA CE SE INSEREAZA DATE?

COMMIT;


SELECT * FROM angajati_rpa;



2. Modificarea (structurii) tabelelor (vezi notiunile din laborator - pagina 3)


-- EXERCITII


3. Introduceti coloana comision in tabelul ANGAJATI. 
Coloana va avea tipul de date NUMBER(4,2).

DESC angajati_rpa;

ALTER TABLE angajati_rpa
ADD comision number(4,2);

SELECT * FROM angajati_rpa;


4. Este posibilă modificarea tipului coloanei salariu în NUMBER(6,2) – 6 cifre si 2 zecimale?

SELECT * FROM angajati_rpa;
DESC angajati_rpa;

ALTER TABLE angajati_rpa
MODIFY (salariu number(6,2));


5. Setaţi o valoare DEFAULT pentru coloana salariu.

SELECT * FROM angajati_rpa;
DESC angajati_rpa;

ALTER TABLE angajati_rpa
MODIFY (salariu number(8,2) default 100); 
                 -- atentie la tipul de date si dimensiunea coloanei


6. Modificaţi tipul coloanei comision în NUMBER(2, 2) 
şi al coloanei salariu la NUMBER(10,2), în cadrul aceleiaşi instrucţiuni.

DESC angajati_rpa;

SELECT * FROM angajati_rpa;

ALTER TABLE angajati_rpa
MODIFY (comision number(2,2),
        salariu number(10,2)
        );

-- De ce au fost permise cele doua modificari de mai sus?

R: la salariu treceam la number mai mare si la comision erau toate null deci era ok



7. Actualizati valoarea coloanei comision, setând-o la valoarea 0.1 
pentru salariaţii al căror job începe cu litera A. (UPDATE)

UPDATE angajati_rpa
SET comision = 0.1
WHERE upper(job) LIKE 'A%';


SELECT * FROM angajati_rpa;

-- Comanda anterioara executa commit implicit?
R: NU



8. Modificaţi tipul de date al coloanei email în VARCHAR2.

DESC angajati_rpa;

ALTER TABLE angajati_rpa
MODIFY (email varchar2(15)); -- cititi observatiile din Laborator 5 - pagina 3


9. Adăugaţi coloana nr_telefon în tabelul ANGAJATI_rpa, setându-i o valoare implicită.

ALTER TABLE angajati_rpa
ADD (nr_telefon varchar2(10) default '0723111111');

SELECT * FROM angajati_rpa;


10. Vizualizaţi înregistrările existente. Suprimaţi coloana nr_telefon.

SELECT * FROM angajati_rpa;

ALTER TABLE angajati_rpa
DROP column nr_telefon;

ROLLBACK; -- ce efect are rollback?

R: niciunul



11. Creaţi şi tabelul DEPARTAMENTE_rpa, corespunzător schemei relaţionale:

DEPARTAMENTE_rpa (cod_dep# number(2), nume varchar2(15), cod_director number(4))

specificând doar constrângerea NOT NULL pentru nume 
(nu precizaţi deocamdată constrângerea de cheie primară);


CREATE TABLE departamente_rpa
    (cod_dep number(2),
     nume varchar2(15) constraint nume_dept not null,
     cod_director number(4)
    );
    

DESC departamente_rpa;

SELECT * FROM departamente_rpa;


12. Introduceţi următoarele înregistrări în tabelul DEPARTAMENTE

INSERT INTO departamente_rpa
VALUES (10, 'Administrativ', 100);

INSERT INTO departamente_rpa
VALUES (20, 'Proiectare', 101);

INSERT INTO departamente_rpa
VALUES (30, 'Programare', null);


13. Se va preciza apoi cheia primara cod_dep, fără suprimarea şi recrearea tabelului 
(comanda ALTER);

ALTER TABLE departamente_rpa
ADD CONSTRAINT pkey_dept PRIMARY KEY(cod_dep);

DESC departamente_rpa;

-- In acest punct mai este nevoie de comanda commit 
-- pentru salvarea celor 3 inserari anterioare?

R: nu, ca alter da commit singur


SELECT * FROM departamente_rpa;
SELECT * FROM angajati_rpa;

DESC departamente_rpa;
DESC angajati_rpa;


14. Să se precizeze constrângerea de cheie externă pentru coloana cod_dep din ANGAJATI_rpa:

a) fără suprimarea tabelului (ALTER TABLE);

ALTER TABLE angajati_rpa
ADD CONSTRAINT fkey_ang_dep FOREIGN KEY(cod_dep) REFERENCES departamente_rpa(cod_dep);


b) prin suprimarea şi recrearea tabelului, cu precizarea noii constrângeri la nivel de coloană 
({DROP, CREATE} TABLE). 

De asemenea, se vor mai preciza constrângerile (la nivel de coloană, dacă este posibil):
- PRIMARY KEY pentru cod_ang;
- FOREIGN KEY pentru cod_sef;
- UNIQUE pentru combinaţia nume + prenume;
- UNIQUE pentru email;
- NOT NULL pentru nume;
- verificarea cod_dep >0;
- verificarea ca salariul sa fie mai mare decat comisionul*100.

DROP TABLE angajati_rpa;

CREATE TABLE angajati_rpa
    (cod_ang number(4) constraint pkey_ang primary key,
     nume varchar2(20) constraint nume_ang not null,
     prenume varchar2(20),
     email char(15) constraint unique_mail unique,
     data_ang date default sysdate,
     job varchar2(10),
     cod_sef number(4) constraint sef_ang references angajati_rpa(cod_ang), -- cheie externa
     salariu number(8, 2) constraint salariu_ang not null,
     cod_dep number(2) constraint fk_ang_rep references departamente_rpa(cod_dep) constraint cod_dep_pos CHECK(cod_dep > 0), -- -> cheie externa  _____ -> cod_dep pozitiv, ?
     comision number(2,2),
     constraint nume_prenume_unice unique(nume, prenume),
     constraint salariu_ok CHECK(salariu > 100 * comision)
     );
     

15. Suprimaţi şi recreaţi tabelul, specificând toate constrângerile la nivel de tabel (în măsura în care este posibil).


CREATE TABLE ANGAJATI_rpa
    (cod_ang number(4),
    nume varchar2(20) constraint nume_rpa not null,
    prenume varchar2(20),
    email char(15),
    data_ang date default sysdate,
    job varchar2(10),
    cod_sef number(4),
    salariu number(8, 2) constraint salariu_rpa not null,
    cod_dep number(2),
    comision number(2,2),
    constraint nume_prenume_unique_rpa unique(nume,prenume),
    constraint verifica_sal_rpa check(salariu > 100*comision),
    constraint pk_angajati_rpa primary key(cod_ang),
    constraint email_unic1 unique(email),
    constraint sef_rpa foreign key(cod_sef) references angajati_rpa(cod_ang),
    constraint fk_dep_rpa foreign key(cod_dep) references departamente_rpa (cod_dep),
    constraint cod_dep_pos1 check(cod_dep > 0)
    );


16. Reintroduceţi date în tabel, utilizând (şi modificând, dacă este necesar) comenzile salvate anterior.

INSERT INTO angajati_rpa
VALUES(100, 'nume1', 'prenume1', 'email1', sysdate, 'Director', null, 20000, 10, 0.1);

INSERT INTO angajati_rpa
VALUES(101, 'nume2', 'prenume2', 'email2', to_date('02-02-2004','dd-mm-yyyy'), 'Inginer', 100, 10000, 10, 0.2);

INSERT INTO angajati_rpa
VALUES(102, 'nume3', 'prenume3', 'email3', to_date('05-06-2000','dd-mm-yyyy'), 'Analist', 101, 5000, 20, 0.1);

INSERT INTO angajati_rpa
VALUES(103, 'nume4', 'prenume4', 'email4', sysdate, 'Inginer', 100, 9000, 20, 0.1);

INSERT INTO angajati_rpa
VALUES(104, 'nume5', 'prenume5', 'email5', sysdate, 'Analist', 101, 3000, 30, 0.1);


-- Ce comanda trebuie executata?

R: COMMIT;



19. Introduceţi constrângerea NOT NULL asupra coloanei email.

desc angajati_rpa;

ALTER TABLE angajati_rpa
MODIFY(email not null);


20. (Incercaţi să) adăugaţi o nouă înregistrare în tabelul ANGAJATI_rpa, 
care să corespundă codului de departament 50. Se poate?

INSERT INTO angajati_rpa
VALUES(105, 'nume6', 'prenume6', 'email6', sysdate, 'Analist', 101, 3000, 50, 0.1);

-- De ce nu se poate insera?

R: nu exista dept 50 in departamente_rpa



SELECT * FROM angajati_rpa;



21. Adăugaţi un nou departament, cu numele Analiza, codul 60 şi 
directorul null în DEPARTAMENTE_rpa. Salvati inregistrarea. 

INSERT INTO departamente_rpa
VALUES (60, 'Analiza', null);

SELECT * FROM departamente_rpa;

COMMIT;



22. (Incercaţi să) ştergeţi departamentul 20 din tabelul DEPARTAMENTE. Comentaţi.

DELETE FROM departamente_rpa
WHERE cod_dep = 20;

-- De ce nu se poate sterge?

R: ca e referentiat in angajati



23. Ştergeţi departamentul 60 din DEPARTAMENTE. ROLLBACK;

DELETE FROM departamente_rpa
WHERE cod_dep = 60;  

-- De ce putem sterge departamentul 60?
R: ca nu avem angajati acolo


SELECT * FROM departamente_rpa;

ROLLBACK;



24. Se doreşte ştergerea automată a angajaţilor dintr-un departament, odată cu 
suprimarea departamentului. Pentru aceasta, este necesară introducerea clauzei 
ON DELETE CASCADE în definirea constrângerii de cheie externă. 

Suprimaţi constrângerea de cheie externă asupra tabelului ANGAJATI_rpa 
şi reintroduceţi această constrângere, specificând clauza ON DELETE CASCADE.


SELECT * 
FROM USER_CONSTRAINTS
WHERE lower(TABLE_NAME) = 'angajati_rpa'; -- dorim sa aflam numele constrangerii


-- stergem constrangerea 

ALTER TABLE angajati_rpa
DROP CONSTRAINT FK_DEP_rpa;


--adaugam constrangerea utilizand clauza ON DELETE CASCADE

ALTER TABLE angajati_rpa
ADD CONSTRAINT FK_DEP_rpa FOREIGN KEY(cod_dep)
REFERENCES departamente_rpa(cod_dep) ON DELETE CASCADE;



25. Ştergeţi departamentul 20 din DEPARTAMENTE. Ce se întâmplă? Rollback;

-- Inainte de stergere analizati datele, atat din angajati, cat si din departamente

SELECT * FROM angajati_rpa; 

-- Cati angajati lucreaza in departamentul 20?

R: 2


-- Ce este cod_dep in angajati_rpa?

R: fk


SELECT * FROM departamente_rpa;


-- Ce este cod_dep in departamente_rpa?

R: pk



-- Stergeti departamentul din departamente_rpa si analizati din nou datele din BD

DELETE FROM departamente_rpa
WHERE cod_dep = 20; 


SELECT * FROM departamente_rpa;


SELECT * FROM angajati_rpa; 


-- Ce se intampla daca executam ROLLBACK?

R: se reseteaza sper


ROLLBACK;


26. Introduceţi constrângerea de cheie externă asupra coloanei cod_director 
a tabelului DEPARTAMENTE. 
Se doreşte ca ştergerea unui angajat care este director de departament să atragă după sine 
setarea automată a valorii coloanei cod_director la null.

DESC departamente_rpa;

SELECT * FROM user_constraints where lower(table_name) = 'departamente_rpa';

ALTER TABLE departamente_rpa
ADD CONSTRAINT fk_director_rpa FOREIGN KEY(cod_director)
REFERENCES angajati_rpa(cod_ang) ON DELETE SET NULL;



27. Actualizaţi tabelul DEPARTAMENTE, astfel încât angajatul având codul 102 
să devină directorul departamentului 30. 

Ştergeţi angajatul având codul 102 din tabelul ANGAJATI_rpa. 
Analizaţi efectele comenzii. Rollback;


UPDATE departamente_rpa
SET cod_director = 102
WHERE cod_dep = 30;


SELECT * FROM departamente_rpa;

SELECT * FROM angajati_rpa;

DELETE FROM angajati_rpa
WHERE cod_ang = 102; 
      -- avand constrangerea on delete set null pe cheia externa cod_director din departamente
      -- observam ca stergerea angajatului 102 din angajati, 
      -- care era sef de departament in tabelul departamente
      -- a dus la setarea valorii cod_director din tabelul departamente la null

ROLLBACK;


-- Cititi notiunile din Laborator 5 - paginile 4 si 5
-- Studiati exercitiile rezolvate in laborator - exercitiile 28 si 29

28. Adăugaţi o constrângere de tip check asupra coloanei salariu, astfel încât acesta să nu poată
depăşi 30000.

ALTER TABLE angajati_pnu
ADD CONSTRAINT v_sal_pnu CHECK (salariu <= 30000);

UPDATE angajati_pnu
SET salariu = 35000
where cod_ang = 100;
-- nu putem adauga un salariu mai mare de 30000, conform noii
-- constrangeri adaugate.

29. Dezactivaţi constrângerea creată anterior.
ALTER TABLE angajati_pnu DISABLE CONSTRAINT v_sal_pnu;



-- Laborator 6

1. Folosind subcereri, să se afişeze numele şi data angajării pentru salariaţii care au fost
angajaţi după Gates.

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (
    SELECT hire_date
    FROM employees
    WHERE lower(last_name) = 'gates'
    );

2. Folosind subcereri, scrieţi o cerere pentru a afişa numele şi salariul pentru toţi colegii (din
acelaşi departament) lui Gates. Se va exclude Gates.

-- cu =
SELECT last_name, salary
FROM employees
WHERE department_id = (
    SELECT department_id
    FROM employees
    WHERE lower(last_name) = 'gates'
    )
AND lower(last_name) != 'gates';

-- cu IN 
SELECT last_name, salary
FROM employees 
WHERE employee_id IN (
SELECT employee_id
FROM employees
WHERE department_id = (
SELECT department_id
FROM employees
WHERE INITCAP(last_name) = 'Gates')) AND INITCAP(last_name) != 'Gates'

3. Scrieți o cerere pentru a afişa numele, codul departamentului și salariul angajaților al
căror cod de departament și salariu coincid cu codul departamentului și salariul unui angajat
care câștigă comision.

SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (
    SELECT department_id, salary
    FROM employees
    WHERE commission_pct IS NOT NULL
    AND department_id IS NOT NULL
    );
    
4. Să se afișeze codul, numele și salariul tuturor angajaților al căror salariu este mai mare
decât salariul mediu din companie.

SELECT employee_id, last_name, salary
FROM employees
WHERE salary > (
    SELECT avg(salary)
    FROM employees
    );
    
5. Scrieti o cerere pentru a afișa angajații care câștigă (castiga = salariul plus comision din
salariu) mai mult decât oricare funcționar (job-ul functionarilor conţine şirul “CLERK”). Sortați
rezultatele dupa salariu, în ordine descrescătoare.

SELECT last_name, salary
FROM employees
WHERE salary * (1 + NVL(commission_pct, 0)) > (
    SELECT MAX(salary * (1 + NVL(commission_pct, 0)))
    FROM employees
    WHERE UPPER(job_id) LIKE '%CLERK%'
    )
ORDER BY salary DESC;

6. Scrieţi o cerere pentru a afişa numele angajatilor, numele departamentului şi salariul
angajaţilor care câştigă comision, dar al căror şef direct nu câştigă comision.

SELECT e.last_name, d.department_name, e.salary
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
WHERE commission_pct IS NOT NULL
AND e.manager_id IN (
    SELECT employee_id
    FROM employees
    WHERE commission_pct IS NULL
    );
    
7. Să se afișeze numele și salariul angajaților care lucrează în departamente aflate în
locații din CANADA și care ocupă joburi ce aparțin unei liste de job_id-uri ce conțin
cuvântul man. Se vor afișa – numele, prenumele, salariul și id-ul jobului. 

Prima variantă – o să utilizeze doar subcereri nesincronizate.

SELECT last_name, first_name, salary, job_id
FROM employees
WHERE department_id IN (
    SELECT department_id
    FROM departments
    WHERE location_id IN (
        SELECT location_id
        FROM locations
        WHERE country_id = (
            SELECT country_id
            FROM countries
            WHERE LOWER(country_name) = 'canada'
        )
    )
)
AND LOWER(job_id) LIKE '%man%';

A doua variantă – o să utilizeze doar operații JOIN

SELECT e.last_name, e.first_name, e.salary, e.job_id
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
JOIN locations l
ON d.location_id = l.location_id
JOIN countries c
ON l.country_id = c.country_id
WHERE LOWER(country_name) = 'canada'
AND LOWER(job_id) LIKE '%man%';

8. Să se obțină codurile departamentelor în care nu lucreaza nimeni (nu este introdus
niciun salariat în tabelul employees). Să se utilizeze subcereri. 

SELECT department_id
FROM departments
WHERE department_id NOT IN (
    SELECT department_id
    FROM employees
    WHERE department_id IS NOT NULL
);

9. Să se creeze tabelul SUBALTERNI_PNU care să conțină codul, numele și prenumele
angajaților care îl au manager pe Steven King, alături de codul și numele lui King.
Coloanele se vor numi cod, nume, prenume, cod_manager, nume_manager.

CREATE TABLE subalterni_rpa AS
SELECT employee_id as "cod", last_name as "nume", first_name as "prenume", manager_id as "cod_manager", (SELECT last_name||' '||first_name FROM employees WHERE LOWER(first_name||last_name) = 'stevenking') as "nume_manager"
FROM employees e
WHERE manager_id = (
    SELECT employee_id
    FROM employees
    WHERE LOWER(first_name||last_name) = 'stevenking'
);

SELECT * from subalterni_rpa;



-- Laborator 7

2. Să se afişeze cel mai mare salariu, cel mai mic salariu, suma şi media salariilor
tuturor angajaţilor. Etichetaţi coloanele Maxim, Minim, Suma, respectiv Media. Sa se
rotunjeasca media salariilor. 

SELECT MAX(salary) "Maxim", MIN(salary) "Minim", SUM(salary) "Suma", ROUND(AVG(SALARY)) "Media"
FROM employees;

3. Să se modifice problema 2 pentru a se afişa minimul, maximul, suma şi media
salariilor pentru FIECARE job.

SELECT job_id, MAX(salary) "Maxim", MIN(salary) "Minim", SUM(salary) "Suma", ROUND(AVG(SALARY)) "Media"
FROM employees
GROUP BY job_id;

4. Să se afişeze numărul de angajaţi pentru FIECARE departament.

SELECT department_id, COUNT(employee_id)
FROM employees
GROUP BY department_id;

5. Să se determine numărul de angajaţi care sunt şefi. Etichetati coloana “Nr.
manageri”.

SELECT COUNT(DISTINCT manager_id) "Nr. manageri"
FROM employees;

6. Să se afişeze diferenţa dintre cel mai mare si cel mai mic salariu. Etichetati
coloana “Diferenta”.

SELECT MAX(salary) - MIN(salary) "Diferenta"
FROM employees;

7. Scrieţi o cerere pentru a se afişa numele departamentului, locaţia, numărul de
angajaţi şi salariul mediu pentru angajaţii din acel departament. Coloanele vor fi
etichetate corespunzător.

SELECT department_name "Nume dept", location_id "Id locatie dep", COUNT(employee_id) "Nr ang", AVG(salary) "Salariu mediu"
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
GROUP BY (department_name, location_id);

8. Pentru fiecare şef, să se afişeze codul său şi salariul celui mai prost platit
subordonat. Se vor exclude cei pentru care codul managerului nu este cunoscut. De
asemenea, se vor exclude grupurile în care salariul minim este mai mic de 1000$.
Sortaţi rezultatul în ordine descrescătoare a salariilor.

SELECT manager_id, MIN(salary)
FROM employees
GROUP BY manager_id
HAVING manager_id IS NOT NULL
AND MIN(salary) > 1000
ORDER BY MIN(salary) DESC;

9. Pentru departamentele in care salariul maxim depăşeşte 3000$, să se obţină codul,
numele acestor departamente şi salariul maxim pe departament.

SELECT e.department_id, department_name, max(salary)
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
GROUP BY (e.department_id, department_name)
HAVING MAX(salary) > 3000;

10. Care este salariul mediu minim al job-urilor existente? Salariul mediu al unui job va
fi considerat drept media aritmetică a salariilor celor care îl practică.

SELECT MIN(SalMed)
FROM (
    SELECT job_id, AVG(salary) SalMed
    FROM employees
    GROUP BY job_id
);

11. Să se afişeze maximul salariilor medii pe departamente

SELECT MAX(SalMed)
FROM (
    SELECT department_id, AVG(salary) SalMed
    FROM employees
    GROUP BY department_id
);

12. Sa se obtina codul, titlul şi salariul mediu al job-ului pentru care salariul mediu
este minim.

SELECT job_id, job_title, AVG(salary)
FROM employees e
JOIN jobs j
USING(job_id)
GROUP BY (job_id, job_title);

13. Să se afişeze salariul mediu din firmă doar dacă acesta este mai mare decât 2500.

SELECT AVG(salary)
FROM employees
HAVING AVG(salary) > 2500;

14. Să se afişeze suma salariilor pe departamente şi, în cadrul acestora, pe job-uri.

SELECT department_id, job_id, SUM(salary)
FROM employees
GROUP BY department_id, job_id;

15. Sa se afiseze codul, numele departamentului si numarul de angajati care
lucreaza in acel departament pentru:

a) departamentele in care lucreaza mai putin de 4 angajati;

SELECT department_id, department_name, COUNT(employee_id)
FROM employees 
JOIN departments
USING(department_id)
GROUP BY (department_id, department_name)
HAVING COUNT(employee_id) < 4;

b) departamentul care are numarul maxim de angajati.

SELECT department_id, department_name, COUNT(employee_id)
FROM employees 
JOIN departments
USING(department_id)
GROUP BY (department_id, department_name)
HAVING COUNT(employee_id) = (
    SELECT MAX(NrAng)
    FROM (
            SELECT department_id, department_name, COUNT(employee_id) NrAng
            FROM employees 
            JOIN departments
            USING(department_id)
            GROUP BY (department_id, department_name)
    )
);

16. Să se obţină numărul departamentelor care au cel puţin 15 angajaţi.

SELECT COUNT(NrAng)
FROM (
    SELECT department_id, COUNT(employee_id) NrAng
    FROM employees
    JOIN departments
    USING(department_id)
    GROUP BY department_id
    HAVING COUNT(employee_id) > 15
);

17. Să se obţină codul departamentelor şi suma salariilor angajaţilor care lucrează în
acestea, în ordine crescătoare. Se consideră departamentele care au mai mult de
10 angajaţi şi al căror cod este diferit de 30.

SELECT department_id, SUM(salary)
FROM employees
JOIN departments
USING (department_id)
WHERE department_id != 30
GROUP BY department_id
HAVING COUNT(employee_id) > 10;

18. Care sunt angajatii care au mai avut cel putin doua joburi?

SELECT employee_id, COUNT(start_date)
FROM employees
JOIN job_history
USING (employee_id)
GROUP BY employee_id
HAVING COUNT(start_date) > 1;




-- Lab 8

1. Scrieţi o cerere pentru a afişa job-ul, salariul total pentru job-ul respectiv pe departamente si
salariul total pentru job-ul respectiv pe departamentele 30, 50, 80. Se vor eticheta coloanele
corespunzător. Rezultatul va apărea sub forma de mai jos:

-- varianta 1
SELECT job_id job, SUM(DECODE(department_id, 30, salary)) Dep30, SUM(DECODE(department_id, 50, salary)) Dep50, SUM(DECODE(department_id, 80, SALARY)) Dep80, SUM(SALARY) Total
FROM employees
GROUP BY job_id;

-- varianta 2
SELECT job_id, (SELECT SUM(salary)
 FROM employees
 WHERE department_id = 30
 AND job_id = e.job_id) Dep30,
 (SELECT SUM(salary)
 FROM employees
 WHERE department_id = 50
 AND job_id = e.job_id) Dep50,
 (SELECT SUM(salary)
 FROM employees
 WHERE department_id = 80
 AND job_id = e.job_id) Dep80,
 SUM(salary) Total
FROM employees e

2. Să se afişeze codul, numele departamentului şi suma salariilor pe departamente

-- fara subcerere

SELECT department_id, department_name, SUM(salary)
FROM departments
JOIN employees
USING(department_id)
GROUP BY department_id, department_name;

-- cu subcerere in select

SELECT department_id, (
    SELECT department_name
    FROM departments
    WHERE department_id = e.department_id
), SUM(SALARY)
FROM employees e
GROUP BY department_id
HAVING department_id IS NOT NULL;

3. a) Să se afişeze numele, salariul, codul departamentului și salariul mediu din
departamentul respectiv.

SELECT e.last_name, e.salary, e.department_id, a.medie
FROM employees e, (
    SELECT department_id, AVG(salary) medie
    FROM employees
    GROUP BY department_id
) a
WHERE e.department_id = a.department_id;
    

b) Să se afişeze informaţii (numele, salariul si codul departamentului) despre angajaţii al căror
salariu depăşeşte valoarea medie a salariilor tuturor colegilor din companie.

SELECT last_name, salary, department_id
FROM employees
WHERE salary > (
    SELECT AVG(salary)
    FROM employees
);

c) Să se afişeze informaţii (numele, salariul si codul departamentului) despre angajaţii al căror
salariu depăşeşte valoarea medie a salariilor colegilor săi de departament.

SELECT e.last_name, e.salary, e.department_id
FROM employees e, (
    SELECT department_id, AVG(salary) SalMed
    FROM employees
    GROUP BY department_id
) a
WHERE e.department_id = a.department_id
AND e.salary > a.SalMed;

d) Analog cu cererea precedentă, afişându-se şi numele departamentului şi media salariilor
acestuia şi numărul de angajaţi.

SELECT e.last_name, e.salary, e.department_id, a.department_name, a.SalMed, a.NrAng
FROM employees e, (
    SELECT department_id, department_name, AVG(salary) SalMed, COUNT(employee_id) NrAng
    FROM employees
    JOIN departments
    USING(department_id)
    GROUP BY department_id, department_name
) a
WHERE e.department_id = a.department_id
AND e.salary > a.SalMed;

4. Să se afişeze numele şi salariul angajaţilor al căror salariu este mai mare decât salariile
medii din toate departamentele. Se cer 2 variante de rezolvare: cu operatorul ALL sau cu
funcţia MAX.

-- CU MAX
SELECT last_name, salary
FROM employees
WHERE salary > (
    SELECT MAX(SalMed)
    FROM (
            SELECT department_id, AVG(salary) SalMed
            FROM employees
            GROUP BY department_id
    )
);

-- CU ALL

SELECT last_name, salary
FROM employees
WHERE salary > ALL(
    SELECT SalMed
    FROM (
        SELECT department_id, AVG(salary) SalMed
        FROM employees
        GROUP BY department_id
    )
);

5. Să se afișeze numele și salariul celor mai prost plătiți angajați din fiecare departament.

-- Cu sincronizare
SELECT last_name, salary
FROM employees e
WHERE salary = (
    SELECT MIN(salary)
    FROM employees
    GROUP BY department_id
    HAVING e.department_id = department_id
);

-- subcerere in from
SELECT last_name, salary, e.department_id
FROM employees e, (
    SELECT department_id, MIN(salary) as SalMin
    FROM employees
    GROUP BY department_id
) a
WHERE e.department_id = a.department_id
AND e.salary = a.SalMin;

-- fara sincronizare

SELECT last_name, salary, department_id
FROM employees
WHERE (salary, department_id) IN (
    SELECT MIN(salary), department_id
    FROM employees
    GROUP BY department_id
);

6. Să se obțină numele și salariile salariaților care lucrează într-un departament în care există
cel puțin un angajat cu salariul egal cu salariul maxim din departamentul 30.

SELECT last_name, salary
FROM employees
WHERE department_id IN (
    SELECT department_id
    FROM employees
    WHERE salary = (
        SELECT MAX(salary)
        FROM employees
        GROUP BY department_id
        HAVING department_id = 30
    )
);

7. a) Să se afişeze codul, numele şi prenumele angajaţilor care au cel puţin doi subalterni.

SELECT employee_id, last_name, first_name
FROM employees
WHERE employee_id IN (
    SELECT manager_id
    FROM (
        SELECT manager_id, COUNT(employee_id)
        FROM employees
        GROUP BY manager_id
        HAVING COUNT(employee_id) > 1
    )
);

b) Cati subalterni are fiecare angajat? Se vor afisa codul, numele, prenumele si numarul de
subalterni. Daca un angajat nu are subalterni, o sa se afiseze 0 (zero). 

SELECT e.employee_id, e.last_name, e.first_name, NVL(NrSubAlterni, 0) as "Numar subalterni"
FROM employees e
LEFT JOIN (
    SELECT manager_id, COUNT(employee_id) as NrSubAlterni
    FROM employees
    GROUP BY manager_id
) a
ON e.employee_id = a.manager_id;

8. Să se determine locaţiile în care se află cel puţin un departament.

SELECT location_id
FROM locations
WHERE location_id IN (
    SELECT location_id
    FROM departments
);

9. Să se determine departamentele în care nu există niciun angajat.

SELECT department_id, department_name
FROM departments
WHERE department_id NOT IN (
    SELECT department_id
    FROM employees
    WHERE department_id IS NOT NULL
);

10. Utilizând clauza WITH, să se scrie o cerere care afişează numele departamentelor şi valoarea
totală a salariilor din cadrul acestora. Se vor considera departamentele a căror valoare totală a
salariilor este mai mare decât media valorilor totale ale salariilor tuturor angajatilor.

WITH val_dep AS (SELECT department_name, SUM(salary) AS total
 FROM departments d join employees e ON (d.department_id = e.department_id)
 GROUP BY department_name
 ),
val_medie AS (SELECT SUM(total)/COUNT(*) AS medie
 FROM val_dep)
SELECT *
FROM val_dep
WHERE total > (SELECT medie
 FROM val_medie)
ORDER BY department_name;

11. Să se afişeze codul, prenumele, numele şi data angajării, pentru angajatii condusi de Steven
King care au cea mai mare vechime dintre subordonatii lui Steven King. Rezultatul nu va
conţine angajaţii din anul 1970. 

WITH subord AS (
    SELECT employee_id, last_name, first_name, hire_date
    FROM employees
    WHERE manager_id = (
        SELECT employee_id
        FROM employees
        WHERE lower(last_name||first_name) = 'kingsteven'
    )
)
SELECT employee_id, last_name, first_name, hire_date
FROM subord
WHERE hire_date = (
    SELECT MIN(hire_date)
    FROM subord
) AND TO_CHAR(hire_date, 'yyyy') != '1970';

12. Să se obțină numele angajaților care au cele mai mari 10 salarii din companie. Rezultatul se va
afişa în ordinea crescătoare a salariilor.

Solutia 1: subcerere sincronizată

SELECT last_name, salary
FROM (
    SELECT last_name, salary
    FROM employees
    ORDER BY salary DESC
)
WHERE ROWNUM < 11;

Solutia 2: analiza top-n

SELECT last_name, salary
FROM employees
ORDER BY salary DESC
FETCH FIRST 10 ROWS ONLY;

13. Să se afişeze informaţii despre departamente, în formatul următor: „Departamentul
<department_name> este condus de {<manager_id> | nimeni} şi {are numărul de salariaţi <n>
| nu are salariati}“. 

WITH d AS (
    SELECT d.department_id, d.manager_id, d.department_name, COUNT(employee_id) as NrAng
    FROM employees e
    RIGHT JOIN departments d
    ON e.department_id = d.department_id
    GROUP BY d.department_id, d.department_name, d.manager_id
)

SELECT 'Departamentul ' || department_name || ' este condus de ' || NVL2(manager_id, TO_CHAR(manager_id, '999'), 'nimeni') || DECODE(NrAng, 0, ' si nu are angajati',  ' are numarul de salariati ' || TO_CHAR(NrAng, '999'))
FROM d;

14. Să se afişeze numele, data angajării, salariul şi o coloană reprezentând salariul după ce se
aplică o mărire, astfel: pentru salariaţii angajaţi în 1989 creşterea este de 20%, pentru cei
angajaţi în 1990 creşterea este de 15%, iar salariul celor angajaţi în anul 1991 creşte cu 10%.
Pentru salariaţii angajaţi în alţi ani valoarea nu se modifică.

SELECT last_name, hire_date, salary, DECODE(TO_CHAR(hire_date, 'yyyy'), '1989', salary * 1.2, '1990', salary * 1.15, '1991', salary * 1.1, salary) AS "Salariu crescut"
FROM employees;

15. Sa se afiseze salariatii care au fost angajati în aceeaşi zi a lunii în care cei mai multi dintre
salariati au fost angajati (ziua lunii insemnand numarul zilei, indiferent de luna si an). 

WITH Zile AS (
    SELECT Zi, COUNT(Zi) as NrAp
    FROM (
        SELECT TO_CHAR(hire_date, 'dd') Zi
        FROM employees
    )
    GROUP BY Zi
)

SELECT last_name
FROM employees
WHERE TO_CHAR(hire_date, 'DD') = (
    SELECT Zi
    FROM Zile
    WHERE NrAp = (
        SELECT MAX(NrAp)
        FROM Zile
    )
);

16. Sa se listeze pentru fiecare angajat orasul in care a lucrat cele mai multe zile
WITH t AS (SELECT employee_id, end_date - start_date AS NrZile, city
FROM job_history j
JOIN departments d
ON j.department_id = d.department_id
JOIN locations l
ON l.location_id = d.location_id

UNION 

SELECT employee_id, ROUND(SYSDATE - hire_date) AS NrZile, city
FROM employees e
JOIN departments d
ON e.department_id = d.department_id
JOIN locations l
ON d.location_id = l.location_id),
 da AS (
SELECT employee_id, city, SUM(NrZile) as NrTotalZile
FROM t
GROUP BY employee_id, city
)
SELECT employee_id, city, NrTotalZile
FROM da d
WHERE NrTotalZile = (
    SELECT MAX(NrTotalZile)
    FROM da 
    WHERE employee_id = d.employee_id
);



-- Laborator 9

Să se obţină codurile salariaţilor ataşaţi tuturor proiectelor pentru care s-a alocat un
buget egal cu 10000.

SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS
 (SELECT 1
 FROM project p
 WHERE budget = 10000
 AND NOT EXISTS
 (SELECT 'x'
 FROM works_on b
 WHERE p.project_id = b.project_id
 AND b.employee_id = a.employee_id
 )
 );
 
 
1. Să se listeze informaţii despre angajaţii care au lucrat în toate proiectele demarate în
primele 6 luni ale anului 2006.

SELECT DISTINCT employee_id
FROM works_on a
WHERE NOT EXISTS (
    SELECT 1
    FROM project p
    WHERE start_date BETWEEN TO_DATE('01-01-2006', 'DD-MM-YYYY') AND TO_DATE('01-07-2006', 'DD-MM-YYYY')
    AND NOT EXISTS (
        SELECT 'x'
        FROM works_on b
        WHERE a.employee_id = b.employee_id
        AND b.project_id = p.project_id
    )
);

2. Să se listeze informaţii despre proiectele la care au participat toţi angajaţii care au deţinut
alte 2 posturi în firmă.

WITH NrPosturi AS (
    SELECT employee_id, COUNT(job_id) NrJoburi
    FROM job_history
    GROUP BY employee_id
)
SELECT DISTINCT a.project_id, project_name
FROM works_on a
JOIN project p
ON p.project_id = a.project_id
WHERE NOT EXISTS (
    SELECT 1
    FROM NrPosturi n
    WHERE NrJoburi > 1
    AND NOT EXISTS (
        SELECT 'x'
        FROM works_on b
        WHERE b.project_id = a.project_id
        AND n.employee_id = b.employee_id
    )
);

3. Să se obţină numărul de angajaţi care au avut cel puţin trei job-uri, luându-se în
considerare şi job-ul curent.

WITH NrPosturi AS (
    SELECT employee_id, COUNT(job_id) NrJoburi
    FROM job_history
    GROUP BY employee_id
)
SELECT employee_id
FROM employees
JOIN NrPosturi
USING (employee_id)
WHERE NrJoburi > 1;

4. Pentru fiecare ţară, să se afişeze numărul de angajaţi din cadrul acesteia.

WITH t AS (
    SELECT employee_id, country_name
    FROM employees 
    JOIN departments
    USING (department_id)
    JOIN locations
    USING (location_id)
    JOIN countries
    USING (country_id)
)
SELECT country_name, COUNT(employee_id) NrAng
FROM t
GROUP BY country_name;

5. Să se listeze codurile angajaţilor şi codurile proiectelor pe care au lucrat. Listarea va
cuprinde şi angajaţii care nu au lucrat pe niciun proiect.

SELECT DISTINCT employee_id, project_id
FROM employees
LEFT JOIN works_on
USING (employee_id);

6. Să se afişeze angajaţii care lucrează în acelaşi departament cu cel puţin un manager de
proiect.

SELECT employee_id
FROM employees
WHERE department_id IN (
    SELECT DISTINCT department_id
    FROM project p
    JOIN employees e
    ON p.project_manager = e.employee_id
);

7. Să se afişeze angajaţii care nu lucrează în acelaşi departament cu niciun manager de
proiect.

SELECT employee_id
FROM employees
WHERE department_id NOT IN (
    SELECT DISTINCT department_id
    FROM project p
    JOIN employees e
    ON p.project_manager = e.employee_id
);

8. Să se afişeze lista angajaţilor care au lucrat numai pe proiecte conduse de managerul de
proiect având codul 102.

SELECT employee_id
FROM works_on a
WHERE NOT EXISTS (
    SELECT DISTINCT project_id
    FROM works_on
    JOIN employees
    USING (employee_id)
    WHERE employee_id = a.employee_id
    
    MINUS
    
    SELECT DISTINCT project_id
    FROM works_on
    JOIN project
    USING (project_id)
    WHERE project_manager = 102
);

9. a) Să se obţină numele si codul angajaţilor care au lucrat cel puţin pe aceleaşi proiecte ca
şi angajatul având codul 200.

SELECT DISTINCT last_name, a.employee_id
FROM employees e
JOIN works_on a
ON e.employee_id = a.employee_id
WHERE e.employee_id != 200
AND NOT EXISTS (
    SELECT DISTINCT project_id
    FROM works_on
    JOIN project
    USING (project_id)
    WHERE employee_id = 200

    MINUS

    SELECT DISTINCT project_id
    FROM works_on
    JOIN employees
    USING (employee_id)
    WHERE employee_id = a.employee_id
);

SELECT * from works_on;

Obs: Incluziunea dintre 2 mulţimi se testează cu ajutorul proprietăţii „A inclus în B => A-B
=Ø”. Cum putem implementa acest lucru în SQL?

SELECT * from works_on;

Pentru rezolvarea exerciţiului, trebuie selectaţi angajaţii pentru care este vidă lista proiectelor
pe care a lucrat angajatul 200 mai puţin lista proiectelor pe care au lucrat acei angajaţi.


b) Să se obţină numele si codul angajaţilor care au lucrat cel mult pe aceleaşi proiecte ca şi
angajatul având codul 200.

SELECT DISTINCT last_name, a.employee_id
FROM employees e
JOIN works_on a
ON e.employee_id = a.employee_id
WHERE e.employee_id != 200
AND NOT EXISTS (
    SELECT DISTINCT project_id
    FROM works_on
    JOIN employees
    USING (employee_id)
    WHERE employee_id = a.employee_id
    
    MINUS

    SELECT DISTINCT project_id
    FROM works_on
    JOIN project
    USING (project_id)
    WHERE employee_id = 200
);


10.Să se obţină angajaţii care au lucrat exact pe aceleaşi proiecte ca şi angajatul având
codul 200.

SELECT DISTINCT last_name, a.employee_id
FROM employees e
JOIN works_on a
ON e.employee_id = a.employee_id
WHERE e.employee_id != 200
AND NOT EXISTS (
    SELECT DISTINCT project_id
    FROM works_on
    JOIN employees
    USING (employee_id)
    WHERE employee_id = a.employee_id
    
    MINUS

    SELECT DISTINCT project_id
    FROM works_on
    JOIN project
    USING (project_id)
    WHERE employee_id = 200
)
AND NOT EXISTS (
    SELECT DISTINCT project_id
    FROM works_on
    JOIN project
    USING (project_id)
    WHERE employee_id = 200

    MINUS

    SELECT DISTINCT project_id
    FROM works_on
    JOIN employees
    USING (employee_id)
    WHERE employee_id = a.employee_id
)
