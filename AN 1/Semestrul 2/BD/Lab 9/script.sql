-- LABORATOR 6 - SAPTAMANA 9 - Subcereri Necorelate


1. Folosind subcereri, s? se afi?eze numele ?i data angaj?rii pentru salaria?ii 
care au fost angaja?i dup? Gates.

SELECT last_name, hire_date
FROM employees
WHERE hire_date > (SELECT hire_date
                   FROM employees
                   WHERE INITCAP(last_name)= 'Gates'
                   );


2. Folosind subcereri, scrie?i o cerere pentru a afi?a numele ?i salariul 
pentru to?i colegii (din acela?i departament) lui Gates. Se va exclude Gates. 

-- Varitanta 1 - folosind subcerere
SELECT last_name, salary
FROM employees
WHERE department_id = (SELECT department_id
                        FROM employees
                        WHERE initcap(last_name) = 'Gates')
AND initcap(last_name) != 'Gates';
-- Varianta 2 - cu JOIN




--Se va inlocui Gates cu King;
SELECT last_name, salary
FROM employees
WHERE department_id = (SELECT department_id
                        FROM employees
                        WHERE initcap(last_name) = 'King')
AND initcap(last_name) != 'King';





3. Scrie?i o cerere pentru a afi?a numele, codul departamentului ?i salariul angaja?ilor 
al c?ror cod de departament ?i salariu coincid cu codul departamentului ?i salariul 
unui angajat care câ?tig? comision. 

SELECT last_name, department_id, salary
FROM employees
WHERE (department_id, salary) IN (SELECT department_id, salary
               FROM employees
               WHERE commission_pct is not null
               );
           

                                                                       
4. S? se afi?eze codul, numele ?i salariul tuturor angaja?ilor al c?ror salariu 
este mai mare decât salariul mediu din companie.

SELECT employee_id, last_name, salary 
FROM employees 
WHERE salary > (SELECT AVG(salary) 
                FROM employees);




5. Scrieti o cerere pentru a afi?a angaja?ii care câ?tig? 
(castiga = salariul plus comision din salariu) 
mai mult decât oricare func?ionar (job-ul functionarilor  con?ine ?irul "CLERK"). 
Sorta?i rezultatele dupa salariu, în ordine descresc?toare;
SELECT employee_id, last_name, salary, commission_pct
FROM employees
WHERE salary + salary * NVL(commission_pct, 0)
            > (SELECT salary + salary * NVL(commission_pct, 0)
                FROM employees
                WHERE UPPER(job_id) = '%CLERK%'
                );
                




6. Scrie?i o cerere pentru a afi?a numele angajatilor, numele departamentului 
?i salariul angaja?ilor care câ?tig? comision, dar al c?ror ?ef direct nu câ?tig? comision.	

-- REZOLVATI IN ECHIPA DE 2 PERSOANE

-- CEREREA TREBUIE SA RETURNEZE 5 ANGAJATI
-- VEZI IMAGINEA ATASATA IN LABORATOR
SELECT ang.last_name, dep.department_name, ang.salary
FROM employees ang
JOIN departments dep
ON ang.department_id = dep.department_id
WHERE ang.commission_pct IS NOT NULL 
AND ang.manager_id IN (SELECT employee_id FROM employees WHERE commission_pct IS NULL);




7. S? se afi?eze numele ?i salariul angaja?ilor care lucreaz? în departamente aflate în loca?ii din CANADA ?i care ocup? joburi ce apar?in unei liste de job_id-uri ce con?in cuvântul man. Se vor afi?a – numele, prenumele, salariul ?i id-ul jobului. 

Prima variant? – o s? utilizeze doar subcereri nesincronizate
SELECT last_name, first_name, salary, job_id
FROM employees
WHERE deparment_id IN (SELECT department_id
                        FROM departments 
                        WHERE location_id (
                            SELECT location_id
                            FROM locations
                            WHERE country_id IN (
                                SELECT country_id
                                FROM countries
                                WHERE UPPER(country_name) = 'CANADA'
                            )
                        ))
AND LOWER(job_id) like '%man%';


A doua variant? – o s? utilizeze doar opera?ii JOIN
SELECT last_name, salary
FROM employees e JOIN departments d ON (e.department_id = d.department_id)
                JOIN locations l on (d.location_id = l.location_id)
                JOIN countries c on (l.country_id = c.country_id)
WHERE upper(country_name) = 'CANADA'
AND LOWER(job_id) LIKE '%man%';

--VARIANTA 1
SELECT first_name, last_name, salary, job_id
FROM 



--VARIANTA 2
SELECT first_name, last_name, salary, job_id
FROM 




8. S? se ob?in? codurile departamentelor în care nu lucreaza nimeni 
(nu este introdus nici un salariat în tabelul employees). Sa se utilizeze subcereri;

SELECT department_id
FROM departments
WHERE department_id NOT IN (SELECT department_id
                            FROM employees);



9. Sa se creeze tabelul SUBALTERNI care sa contina codul, numele si prenumele angajatilor 
care il au manager pe Steven King, alaturi de codul si numele lui King.
Coloanele se vor numi cod, nume, prenume, cod_manager, nume_manager.

DESC employees;

CREATE TABLE SUBALTERNI
    (
    );
     

INSERT INTO SUBALTERNI (cod, nume, prenume, cod_manager, nume_manager)
        (SELECT 
        
        );