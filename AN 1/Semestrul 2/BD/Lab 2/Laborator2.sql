--5. Să se listeze, cu şi fără duplicate, codurile job-urilor din tabelul EMPLOYEES.

SELECT job_id FROM employees;
SELECT DISTINCT job_id FROM employees;
SELECT UNIQUE job_id FROM employees; 

--6. Să se afişeze numele concatenat cu prenumele si cu job_id-ul, separate prin virgula și spatiu. Etichetați coloana “Detalii Angajat”.

SELECT last_name || ', ' || first_name || ', ' || job_id AS "Detalii Angajat"
FROM employees;

--SAU

SELECT CONCAT(CONCAT(CONCAT(last_name, ', '), CONCAT(first_name, ', ')), job_id) AS "Detalii Angajat"
FROM employees;

--7. Să se listeze numele și salariul angajaţilor care câştigă mai mult de 2850. 
SELECT last_name, salary
FROM employees
WHERE salary > 2850;

--8. Să se creeze o cerere pentru a afişa numele angajatului şi codul departamentului pentru angajatul având codul 104.
SELECT last_name, employee_id
FROM employees
WHERE employee_id = 104;

--9. Să se modifice cererea de la problema 7 pentru a afişa numele şi salariul angajaţilor al căror salariu nu se află în intervalul [14000, 24000].
SELECT last_name, salary
FROM employees
WHERE salary NOT BETWEEN 14000 AND 24000;

--9.1. Să se afișeze numele, prenumele și salariul angajaților al căror salariu este în intervalul [3000,7000] => utilizând between
SELECT last_name, first_name, salary
FROM employees
WHERE salary BETWEEN 3000 AND 7000;

--9.2. Modificarea cererii de la punctual 9.1 fara a utiliza de aceasta data between.
SELECT last_name, first_name, salary
FROM employees
WHERE salary >= 3000 AND salary <= 7000;

--10. Să se afişeze numele, job-ul şi data la care au început lucrul salariaţii angajaţi între 20 Februarie 1987 şi 1 Mai 1989. Rezultatul va fi ordonat crescător după data de început.
SELECT last_name, job_id, hire_date
FROM employees
WHERE hire_date BETWEEN TO_DATE('1987-02-20', 'YYYY-MM-DD') AND TO_DATE('1989-05-01', 'YYYY-MM-DD')
ORDER BY hire_date;

--11. Să se afişeze numele salariaţilor şi codul departamentelor pentru toti angajaţii din departamentele 10 şi 30 în ordine alfabetică a numelor.
SELECT last_name, department_id
FROM employees
WHERE department_id IN (10, 30)
ORDER BY last_name;

--12. Să se modifice cererea de la problema 11 pentru a lista numele şi salariile angajatilor care câştigă mai mult de 1500 şi lucrează în departamentul 10 sau 30. Se vor eticheta coloanele drept Angajat si Salariu lunar.
SELECT last_name AS "Angajat", salary AS "Salariu lunar"
FROM employees
WHERE salary > 1500 AND department_id IN (10, 30)
ORDER BY last_name;

--13. Care este data curentă? Afişaţi diferite formate ale acesteia.
SELECT SYSDATE
FROM dual;

SELECT TO_CHAR(SYSDATE, 'DD')
FROM dual;

SELECT TO_CHAR(SYSDATE, 'MON')
FROM dual;

SELECT TO_CHAR(SYSDATE, 'DD-MON-YY')
FROM dual;

SELECT TO_CHAR(SYSDATE, 'DD-MM-YYYY HH12 MI SS') "ORA/MIN/SEC"
FROM dual;

--14. Să se afișeze numele şi data angajării pentru fiecare salariat care a fost angajat în 1987. Se cer 2 soluţii: una în care se lucrează cu formatul implicit al datei şi alta prin care se formatează data.

SELECT last_name, hire_date
FROM employees
WHERE TO_CHAR(hire_date, 'YYYY') = 1987;

SELECT last_name, hire_date
FROM employees
WHERE hire_date LIKE '%87';

-- % - oricate caractere
-- _ - un singur caracter si numai unul

--17. Să se afișeze numele, job-ul și salariul pentru toți salariații al căror job conţine şirul “CLERK” sau “REP” și salariul nu este egal cu 1000, 2000 sau 3000 $. 
SELECT last_name, job_id, salary
FROM employees
WHERE (job_id LIKE '%CLERK%' OR job_id LIKE '%REP%') AND salary NOT IN (1000, 2000, 3000);

/*
20. Să se afișeze angajații care au salariul între 5000 și 9000, iar prenumele (first_name) lor
începe cu litera a sau m. Verificarea se va face utilizând literă mica. De asemenea, se
afișează doar acei angajați care au fost angajați într-un an impar, iar luna lor de angajare
coincide cu luna curentă (adică luna în care ne aflăm în acest moment). Se vor afișa:
numele concatenat cu spațiu, concatenat cu prenumele, salariul si data angajării. Coloana
pe care se află numele și prenumele se va numi Nume Complet. Rezultatele se vor ordona
descrescător, în funcție de data angajării. 
*/

SELECT first_name || ' ' || last_name AS "Nume complet", salary, hire_date
FROM employees
WHERE (salary BETWEEN 5000 AND 9000)
AND (LOWER(first_name) LIKE 'a%' OR LOWER(first_name) LIKE 'm%')
AND (MOD(TO_CHAR(hire_date, 'YYYY'), 2) = 1)
AND (TO_CHAR(hire_date, 'MM') = TO_CHAR(SYSDATE, 'MM'))
ORDER BY hire_date DESC;