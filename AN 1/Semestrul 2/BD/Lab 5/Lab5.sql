-- 6. Scrieţi o cerere care afişează numele angajatului, codul departamentului în
-- care acesta lucrează şi numele colegilor săi de departament. Se vor eticheta
-- coloanele corespunzător.

SELECT ang.last_name AS "Nume angajat", ang.department_id AS "Departament angajat",
       coleg.last_name AS "Nume coleg", coleg.department_id AS "Departament coleg"
FROM employees ang JOIN employees coleg
ON (ang.department_id = coleg.department_id)
WHERE (ang.employee_id < coleg.employee_id);

-- 8. Să se afişeze numele şi data angajării pentru salariaţii care au fost angajaţi
-- după salariatul cu numele (last_name) Gates.

SELECT ang.last_name AS "Nume angajat", ang.hire_date AS "Data angajarii"
FROM employees ang JOIN employees coleg
ON (coleg.last_name = 'Gates')
WHERE (ang.hire_date > coleg.hire_date);

Scrieți o cerere pentru a afișa numele salariatului, luna (în litere), anul
angajării și valoarea comisionului pentru toți salariații din același departament
cu Gates (last_name este Gates) – se verifică numele scris cu prima literă mare
și restul literelor mici, al căror nume conţine litera “a”. Se va exclude Gates. Se
vor utiliza aliasuri pentru numele coloanelor din output. În cazul în care un
angajat nu câștigă comision, se va scrie în output, pe coloana respectivă,
mesajul “Nu câștigă comision”. Rezultatul se va ordona alfabetic după numele
salariaților. Output-ul este următorul:;

SELECT ang.last_name "Nume angajat",
TO_CHAR(ang.hire_date, 'Month - YYYY') "Luna si anul angajarii",
ang.department_id "Departament angajat",
g.last_name "Nume Gates",
g.department_id "Departament Gates",
NVL(TO_CHAR(ang.commission_pct), 'Nu castiga comision') "Comision angajat"
FROM employees ang JOIN employees g
ON (ang.department_id = g.department_id)
WHERE (INITCAP(g.last_name) = 'Gates') AND LOWER(ang.last_name) LIKE '%a%' AND ang.last_name != 'Gates'
ORDER BY ang.last_name;

12.Cum se poate implementa full outer join?

SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e JOIN departments d
ON (e.department_id = d.department_id);

-- LEFT JOIN
-- VOM AFISA ANGAJATII CARE LUCREAZA IN DEPARTAMENTE - 106
-- PLUS ANGAJATII CARE NU AU DEPARTAMENT - 1
-- CU ALTE CUVINTE, VOM AFISA TOTI ANGAJATII, INDIFERENT DACA AU DEPARTAMENT
SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e LEFT JOIN departments d
ON (e.department_id = d.department_id);

-- RIGHT JOIN
-- AFISAM DEPARTAMENTELE IN CARE LUCREAZA ANGAJATI - 106
-- PLUS DEPARTAMENTELE CARE NU AU ANGAJATI - 16
-- CU ALTE CUVINTELE, AFISAM TOATE DEP, INDIFERENT DACA AU SAU NU ANGAJATI
SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e RIGHT JOIN departments d
ON (e.department_id = d.department_id);

-- FULL JOIN
-- 106 ANGAJATI CU DEPARTAMENTE
-- PLUS 1 ANGAJAT FARA DEP
-- PLUS CELE 16 DEP CARE NU AU ANGAJATI
-- IN TOTAL, PE EXEMPLUL NOSTRU AVEM 123 RANDURI RETURNATE
SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e FULL JOIN departments d
ON (e.department_id = d.department_id);


-- UNION

SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e LEFT JOIN departments d
ON (e.department_id = d.department_id)

UNION

SELECT employee_id, last_name,
       d.department_id, department_name
FROM employees e RIGHT JOIN departments d
ON (e.department_id = d.department_id);

-- OBSERVATII
-- Nu este necesar ca numele coloanelor să fie identice. 
SELECT employee_id, last_name
FROM employees

UNION

SELECT department_id, department_name
FROM departments;

SELECT last_name,
       d.department_id, department_name
FROM employees e LEFT JOIN departments d
ON (e.department_id = d.department_id)

UNION -- afiseaza elementele comune si necomune o singura data

SELECT last_name,
       d.department_id, department_name
FROM employees e RIGHT JOIN departments d
ON (e.department_id = d.department_id);

1. Se cer codurile departamentelor al căror nume conţine şirul “re” sau în care
lucrează angajaţi având codul job-ului “SA_REP”.
Cum este ordonat rezultatul?

-- Varianta 1 operatori pe multimi

SELECT department_id
FROM departments
WHERE LOWER(department_name) LIKE '%re%'

UNION

SELECT department_id
FROM employees
WHERE UPPER(job_id) = 'SA_REP';
-- and department_id not null
-- sau pot elimina valorile null cu join cu departments

-- Varianta 2 join
-- avem departamente care contin sirul re in nume dar in care nu lucreaza nimeni.
-- vrem sa le afisam si pe acestea
SELECT DISTINCT d.department_id
FROM employees e RIGHT JOIN departments d
ON (e.department_id = d.department_id)
WHERE (LOWER(d.department_name) LIKE '%re%') 
OR (UPPER(job_id) = 'SA_REP');


3. Să se obțină codurile departamentelor în care nu lucrează nimeni (nu este
introdus niciun salariat în tabelul employees). Se cer două soluții.

-- Varianta 1 minus
SELECT department_id 
FROM departments

MINUS

SELECT department_id
FROM employees;

-- Varianta 2 join

SELECT d.department_id
FROM employees e RIGHT JOIN departments d
ON (e.department_id = d.department_id)
WHERE e.employee_id IS NULL;