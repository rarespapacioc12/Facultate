-- LABORATOR 4 - SAPTAMANA 6 


1.	S? se creeze tabelele EMP_pnu, DEPT_pnu prin copierea structurii ?i con?inutului 
tabelelor EMPLOYEES, respectiv DEPARTMENTS. 

-- în care ?irul de caractere “pnu” ->
-- p reprezint? prima liter? a prenumelui ->
-- iar nu reprezint? primele dou? litere ale numelui)


CREATE TABLE EMP_pnu AS SELECT * FROM employees;
CREATE TABLE DEPT_pnu AS SELECT * FROM departments;


2.	Lista?i structura tabelelor surs? ?i a celor create anterior. Ce se observ??

-- listam structura
_____



3.	Lista?i con?inutul tabelelor create anterior.

--listam continutul
_____


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

ALTER TABLE emp_pnu
ADD CONSTRAINT pk_emp_pnu PRIMARY KEY(employee_id);


ALTER TABLE dept_pnu
ADD CONSTRAINT pk_dept_pnu PRIMARY KEY(department_id);


ALTER TABLE emp_pnu
ADD CONSTRAINT fk_emp_dept_pnu FOREIGN KEY(department_id) REFERENCES dept_pnu(department_id);
   
   
Obs: Ce constrângere nu am implementat?

___



DESC EMP_PNU;
DESC DEPT_PNU;



-- APOI SE REZOLVA, IN CADRUL LABORATORULUI CURENT, URMATOARELE EXERCITII


5.	S? se insereze departamentul 300, cu numele Programare în DEPT_pnu.
Analiza?i cazurile, precizând care este solu?ia corect? ?i explicând erorile 
celorlalte variante. 
Pentru a anula efectul instruc?iunii(ilor) corecte, utiliza?i comanda ROLLBACK.
       
       
DESC DEPT_PNU;

SELECT * FROM dept_pnu;

--discutie tipuri de INSERT si erori posibile
--vezi laborator
                                                      
--a)	
INSERT INTO DEPT_pnu 
VALUES (300, 'Programare');


--b)	
INSERT INTO DEPT_pnu (department_id, department_name)
VALUES (300, 'Programare');

SELECT * FROM dept_pnu;


--c)	
INSERT INTO DEPT_pnu (department_name, department_id)
VALUES (300, 'Programare');


--d)	
INSERT INTO DEPT_pnu (department_id, department_name, location_id)
VALUES (300, 'Programare', null);	


-- varianta corecta
	
_____	


SELECT * FROM dept_pnu;


--e)	
INSERT INTO DEPT_pnu (department_name, location_id)
VALUES ('Programare', null);


-- Ce se intampla daca executam rollback?

_____


-- Executati varianta corecta si permanentizati modificarile.

_____



6. S? se insereze un angajat corespunz?tor departamentului introdus anterior 
în tabelul EMP_pnu, precizând valoarea NULL pentru coloanele a c?ror valoare 
nu este cunoscut? la inserare (metoda implicit? de inserare). 
Determina?i ca efectele instruc?iunii s? devin? permanente.
Aten?ie la constrângerile NOT NULL asupra coloanelor tabelului!


-- inserare prin metoda IMPLICITA de inserare
-- dorim sa inseram un angajat in depart 300

DESC emp_pnu;
SELECT * FROM emp_pnu;


INSERT INTO emp_pnu
VALUES (250, NULL, 'nume250', 'email250', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);

-- Cum permanentizam efectul actiunii anterioare?

_____;

SELECT * FROM emp_pnu;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_pnu
VALUES (250, NULL, 'nume251', 'email251', NULL, SYSDATE, 'IT_PROG', NULL, NULL, NULL, 300);


-- Se poate anula inserarea anterioara?

_____;

SELECT * FROM emp_pnu;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_pnu
VALUES (251, NULL, 'nume251', 'email251', NULL, '03-10-2023', 
       'IT_PROG', NULL, NULL, NULL, 300);
       
SELECT * FROM emp_pnu;

ROLLBACK;


-- De ce varianta urmatoare nu functioneaza?

INSERT INTO emp_pnu
VALUES (252, NULL, 'nume252', 'email252', NULL, SYSDATE, 
       'IT_PROG', NULL, NULL, NULL, 310);


-- IN CELE DIN URMA PASTRAM IN BAZA DE DATE ANGAJATUL CU ID-UL 250 IN DEPART. 300



7. S? se mai introduc? un angajat corespunz?tor departamentului 300, 
precizând dup? numele tabelului lista coloanelor în care se introduc valori 
(metoda explicita de inserare). 
Se presupune c? data angaj?rii acestuia este cea curent? (SYSDATE). 
Salva?i înregistrarea.

desc emp_pnu;

--inserare prin metoda EXPLICITA de inserare
INSERT INTO emp_pnu (hire_date, job_id, employee_id, last_name, email, department_id)
VALUES (sysdate, 'sa_man', 278, 'nume_278', 'email_278', 300);

COMMIT;

SELECT * FROM emp_pnu;


8. Crea?i un nou tabel, numit EMP1_PNU, care va avea aceea?i structur? ca ?i EMPLOYEES, 
dar fara inregistrari. Copia?i în tabelul EMP1_PNU salaria?ii (din tabelul EMPLOYEES) 
al c?ror comision dep??e?te 25% din salariu (se accepta omiterea constrangerilor).


-- crearea tabelului
CREATE TABLE emp1_pnu AS SELECT * FROM employees;

-- eliminarea inregistrarilor
DELETE FROM emp1_pnu;

-- adaugarea noilor valori (inserarea randurilor)
INSERT INTO emp1_pnu
    SELECT *
    FROM employees
    WHERE commission_pct > 0.25;

SELECT * FROM emp1_pnu;


-- Ce se intampla daca executam un rollback? 

______




-- SA SE ANALIZEZE EXERCITIILE 9, 10 SI 11 

9. S? se creeze un fi?ier (script file) care s? permit? introducerea de înregistr?ri 
în tabelul EMP_PNU în mod interactiv. 
Se vor cere utilizatorului: codul, numele, prenumele si salariul angajatului. 
Câmpul email se va completa automat prin concatenarea primei litere din prenume 
?i a primelor 7 litere din nume.    
Executati script-ul pentru a introduce 2 inregistrari in tabel.


INSERT INTO emp_pnu (employee_id, first_name, last_name, email, hire_date, job_id, salary)
VALUES(&cod, '&&prenume', '&&nume', substr('&prenume',1,1) || substr('&nume',1,7), 
       sysdate, 'it_prog', &sal);
       
UNDEFINE prenume;
UNDEFINE nume;

SELECT * FROM emp_pnu;


10. Crea?i 2 tabele emp2_pnu ?i emp3_pnu cu aceea?i structur? ca tabelul EMPLOYEES, 
dar f?r? înregistr?ri (accept?m omiterea constrângerilor de integritate). 
Prin intermediul unei singure comenzi, copia?i din tabelul EMPLOYEES:

-  în tabelul EMP1_PNU salaria?ii care au salariul mai mic decât 5000;
-  în tabelul EMP2_PNU salaria?ii care au salariul cuprins între 5000 ?i 10000;
-  în tabelul EMP3_PNU salaria?ii care au salariul mai mare decât 10000.

Verifica?i rezultatele, apoi ?terge?i toate înregistr?rile din aceste tabele.

--VEZI INSERARI MULTI-TABEL IN LABORATORUL 4

CREATE TABLE emp1_pnu AS SELECT * FROM employees;

DELETE FROM emp1_pnu;

SELECT * FROM emp1_pnu; 

CREATE TABLE emp2_pnu AS SELECT * FROM employees;

DELETE FROM emp2_pnu;

CREATE TABLE emp3_pnu AS SELECT * FROM employees;

DELETE FROM emp3_pnu;

INSERT ALL
   WHEN salary < 5000 THEN
      INTO emp1_pnu					
   WHEN salary > = 5000 AND salary <= 10000 THEN
      INTO emp2_pnu
   ELSE 
      INTO emp3_pnu
SELECT * FROM employees;  


SELECT * FROM emp1_pnu;
SELECT * FROM emp2_pnu;
SELECT * FROM emp3_pnu;



11. S? se creeze tabelul EMP0_PNU cu aceea?i structur? ca tabelul EMPLOYEES 
(f?r? constrângeri), dar f?r? inregistrari. 
Copia?i din tabelul EMPLOYEES:

-  în tabelul EMP0_PNU salaria?ii care lucreaz? în departamentul 80;
-  în tabelul EMP1_PNU salaria?ii care au salariul mai mic decât 5000;
-  în tabelul EMP2_PNU salaria?ii care au salariul cuprins între 5000 ?i 10000;
-  în tabelul EMP3_PNU salaria?ii care au salariul mai mare decât 10000.

Dac? un salariat se încadreaz? în tabelul emp0_pnu, atunci acesta nu va mai fi inserat 
?i în alt tabel (tabelul corespunz?tor salariului s?u);

CREATE TABLE emp0_pnu AS SELECT * FROM employees;

DELETE FROM emp0_pnu;


INSERT FIRST
    WHEN department_id = 80 THEN
        INTO emp0_pnu
    WHEN salary < 5000 THEN
        INTO emp1_pnu
    WHEN salary > = 5000 AND salary <= 10000 THEN
        INTO emp2_pnu
    ELSE 
        INTO emp3_pnu
SELECT * FROM employees;

SELECT * FROM emp0_pnu;
SELECT * FROM emp1_pnu;
SELECT * FROM emp2_pnu;
SELECT * FROM emp3_pnu;


-- COMANDA UPDATE - VEZI LABORATOR (pentru notiunile teoretice)

12. M?ri?i salariul tuturor angaja?ilor din tabelul EMP_PNU cu 5%. 
Vizualizati, iar apoi anula?i modific?rile.

UPDATE emp_pnu
SET salary = salary * 1.05;

SELECT * FROM emp_pnu;

ROLLBACK;



13. Schimba?i jobul tuturor salaria?ilor din departamentul 80 care au comision, în 'SA_REP'. 
Anula?i modific?rile.

UPDATE emp_pnu
SET job_id = 'SA_REP'
WHERE department_id = 80 and commission_pct IS NOT NULL;

SELECT * FROM emp_pnu;

ROLLBACK;


14. S? se promoveze Douglas Grant la manager în departamentul 20 (tabelul dept_pnu), 
având o cre?tere de salariu cu 1000$. 


-- verificari

SELECT *
FROM emp_pnu
WHERE lower(last_name||first_name) = 'grantdouglas';

SELECT * FROM dept_pnu
WHERE department_id = 20;

-- solutia problemei

-- modificam managerul din departamentul 20
UPDATE dept_pnu
SET manager_id = (
    SELECT employee_id
    FROM employees
    WHERE lower(last_name||first_name) = 'grantdouglas'
)
WHERE department_id = 20;
ROLLBACK;

-- modificam salariul angajatului grant
UPDATE emp_pnu
SET salary = salary + 1000
WHERE lower(last_name||first_name) = 'grantdouglas';


-- COMANDA DELETE - VEZI LABORATOR (pentru notiunile teoretice)

15.	?terge?i toate înregistr?rile din tabelul DEPT_PNU. 
Ce înregistr?ri se pot ?terge? Anula?i modific?rile. 

DELETE FROM dept_pnu; 
--integrity constraint (C##RARES_PAPACIOC.FK_EMP_DEPT_PNU) violated - child record found
SELECT * FROM dept_pnu;

SELECT * FROM emp_pnu;





16.	Suprima?i departamentele care nu au angajati. Anula?i modific?rile.

-- prima data afisam departamentele care nu au angajati
-- NOT IN
-- MINUS: din lista tuturor departamentelor eliminam  departamentele in care lucreaza
-- angajati
SELECT department_id 
FROM dept_pnu

MINUS

SELECT department_id
FROM emp_pnu;

-- cum se transforma minus in not in
-- ATNETIE!!!
-- Atunci cand apem operatorul NOT NULL iar subcererea returneaza cel putin o
-- valoare NULL trebuie sa eliminam acea valoare din output
-- atentie la NOT IN si NULL
-- SAU se poate elimina valoarea NULL folosind functia NVL
SELECT department_id
FROM dept_pnu
WHERE department_id NOT IN
(SELECT department_id FROM emp_pnu WHERE department_id IS NOT NULL);

-- apoi stergem departamentele care nu au angajati
DELETE FROM dept_pnu
WHERE department_id IN (
SELECT department_id
FROM dept_pnu
WHERE department_id NOT IN
(SELECT department_id FROM emp_pnu WHERE department_id IS NOT NULL)
);

ROLLBACK;
17. S? se mai introduc? o linie in tabelul DEPT_PNU.

desc dept_pnu;

INSERT INTO dept_pnu
VALUES(320, 'dept_nou', NULL, NULL);

SELECT * FROM dept_pnu;


18. S? se marcheze un punct intermediar in procesarea tranzac?iei (SAVEPOINT p).

SAVEPOINT p;


19. S? se ?tearg? din tabelul DEPT_PNU departamentele care au codul de departament 
cuprins intre 160 si 200. Lista?i con?inutul tabelului.

DELETE FROM dept_pnu
WHERE department_id BETWEEN 160 AND 200; 

SELECT * FROM dept_pnu;


20. S? se renun?e la cea mai recent? opera?ie de ?tergere, f?r? a renun?a 
la opera?ia precedent? de introducere. 
Determina?i ca modific?rile s? devin? permanente;

SELECT * FROM dept_pnu;

ROLLBACK TO p;

COMMIT;




1. S? se creeze tabelul ANGAJATI_pnu 
(pnu se alcatuie?te din prima liter? din prenume ?i primele dou? din numele studentului) 
corespunz?tor schemei rela?ionale:

ANGAJATI_pnu(cod_ang number(4), nume varchar2(20), prenume varchar2(20), email char(15), 
             data_ang date, job varchar2(10), cod_sef number(4), salariu number(8, 2), 
             cod_dep number(2)
            );
  
a) cu precizarea cheilor primare la nivel de coloan? 
si a constrangerilor NOT NULL pentru coloanele nume ?i salariu;
De asemenea, se presupune c? valoarea implicit? a coloanei data_ang este SYSDATE, 
iar adresa de e-mail trebuie sa aiba o valoare unica    

CREATE TABLE angajati_pnu
      ( cod_ang number(4) CONSTRAINT pk_ang_pnu PRIMARY KEY,
        nume varchar2(20) CONSTRAINT nume_ang_pnu NOT NULL,
        prenume varchar2(20),
        email char(15) UNIQUE,
        data_ang date DEFAULT SYSDATE,
        job varchar2(10),
        cod_sef number(4),
        salariu number(8,2) CONSTRAINT salariu_ang_pnu NOT NULL,
        cod_dep number(2)
       );
 
SELECT * FROM angajati_pnu;
DESC angajati_pnu;
    

b) cu precizarea cheii primare la nivel de tabel 
si a constrângerilor NOT NULL pentru coloanele nume ?i salariu.

DROP TABLE angajati_pnu;

CREATE TABLE angajati_pnu
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
 


