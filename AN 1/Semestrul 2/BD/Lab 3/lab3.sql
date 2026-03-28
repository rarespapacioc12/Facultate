SELECT SUM(salary) FROM employees;

SELECT LTRIM('    info') -- info
FROM dual;

SELECT TRIM(BOTH 'X' FROM 'XinfoXxX') -- infoXx
FROM dual;

SELECT RTRIM ('XinfoXxXabc', 'bacX') -- XinfoXx
FROM dual;

SELECT RTRIM('XinfoXXXabc', 'bacX') -- Xinfo
FROM dual;

SELECT LPAD(LOWER('iNfO'), 6) -- '  info'
FROM dual;

SELECT REPLACE ('$b$bb','$','a') -- ababb
FROM dual;

SELECT REPLACE ('$b$bb','$b','ad') -- adadb
FROM dual;

SELECT TRANSLATE('$a$aa','$','b') -- babaa
FROM dual;

SELECT TRANSLATE('cerc', 'ce', 'd') -- drd
FROM dual;

SELECT TRANSLATE('$a$aaa', 'aa', 'bc') -- $b$bbb
FROM dual;

SELECT INSTR (LOWER('AbC aBcDe'),'ab', 5, 2) -- 0
FROM dual;

SELECT INSTR (LOWER('AbCdE aBcDe'),'ab', 5) -- 7
FROM dual;

SELECT ROUND(10.9) -- 11
FROM dual;

SELECT FLOOR(-10.9) -- -11
FROM dual;

SELECT TRUNC(-10.9) -- -10
FROM dual;

SELECT ROUND(10.5) -- 11
FROM dual;

SELECT ROUND(10.234, 2) -- 10.23
FROM dual;

SELECT TO_CHAR(TO_DATE('07-03-2026', 'DD-MM-YYYY') + 3, 'DD/MM/YYYY') -- 10/03/2026
FROM dual;

SELECT ROUND(SYSDATE - TO_DATE ('12-04-2006', 'DD-MM-YYYY'), 2) "Numar de zile"
FROM dual;

-- 13. Să se afişeze numele angajaţilor şi comisionul. Dacă un angajat nu câştigă comision, să
-- se scrie “Fara comision”. Etichetaţi coloana “Comision”.

SELECT last_name, NVL(TO_CHAR(commission_pct), 'Fara comision') AS "Comision"
FROM employees;

SELECT last_name,
    CASE
    WHEN commission_pct is NULL THEN 'Fara Comision'
    ELSE TO_CHAR(commission_pct)
    END AS "COMISION"
FROM employees;

-- 14. Să se listeze numele, salariul şi comisionul tuturor angajaţilor al căror venit lunar
-- (salariu + valoare comision) depăşeşte 10 000. 

SELECT last_name, salary, commission_pct
FROM employees
WHERE salary * (1 + NVL(commission_pct, 0)) > 10000;

-- ORICE OPERATIE CU NULL DA NULL

-- O alta varianta
SELECT last_name, salary, commission_pct
FROM employees
WHERE NVL(salary * (1 + commission_pct), salary) > 10000;

SELECT last_name, salary, commission_pct
FROM employees
WHERE salary * (1 + NVL(commission_pct, 0)) > 10000
ORDER BY commission_pct NULLS LAST;

SELECT last_name, salary, commission_pct
FROM employees
WHERE salary * (1 + NVL(commission_pct, 0)) > 10000
ORDER BY commission_pct NULLS FIRST;

--2. Scrieţi o cerere prin care să se afişeze prenumele salariatului cu prima litera majusculă
--şi toate celelalte litere minuscule, numele acestuia cu majuscule şi lungimea
--numelui, pentru angajaţii al căror nume începe cu J sau M sau care au a treia literă din
--nume A. Rezultatul va fi ordonat descrescător după lungimea numelui. Se vor eticheta
--coloanele corespunzător. Se cer 2 soluţii (cu operatorul LIKE şi funcţia SUBSTR).

SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM employees
WHERE (last_name LIKE 'J%')
OR (last_name LIKE 'M%')
OR (UPPER(last_name) LIKE '__A%');

SELECT INITCAP(first_name), UPPER(last_name), LENGTH(last_name)
FROM employees
WHERE (SUBSTR(last_name, 1, 1) = 'J')
OR (SUBSTR(last_name, 1, 1) = 'M')
OR (SUBSTR(UPPER(last_name), 3, 1) = 'A')