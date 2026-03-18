-- VERSÃO LIMPA:
-- LADRÃO
WITH thief AS (SELECT name FROM people p
    JOIN bank_accounts b ON p.id = b.person_id
    JOIN atm_transactions atm ON b.account_number = atm.account_number
    JOIN phone_calls pc ON p.phone_number = pc.caller
    JOIN passengers pa ON p.passport_number = pa.passport_number
    JOIN flights f ON pa.flight_id = f.id
    JOIN airports a ON f.origin_airport_id = a.id
    JOIN bakery_security_logs b ON b.license_plate = p.license_plate
    WHERE atm.atm_location = "Leggett Street"
        AND atm.transaction_type = "withdraw" AND atm.month = 7 AND atm.day = 28
        AND pc.day = 28 AND pc.month = 7 and pc.year = 2023 AND pc.duration < 60
        AND a.city = "Fiftyville" AND f.year = 2023 AND f.month = 7 AND f.day = 29 AND f.hour = 8 AND f.minute = 20
        AND b.hour = 10 AND b.minute BETWEEN 15 AND 25
)

SELECT name FROM thief;

-- CÚMPLICE
SELECT p.name
FROM people p
JOIN phone_calls c ON p.phone_number = c.receiver
WHERE c.caller = (SELECT phone_number FROM thief)
  AND c.day = 28 AND c.month = 7 AND c.year = 2023
  AND c.duration < 60;

-- CIDADE
SELECT a.city
FROM airports a
JOIN flights f ON a.id = f.destination_airport_id
WHERE f.id = 36;
