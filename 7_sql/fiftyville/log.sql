-- Obter informações através dos relatórios da data e local que sabemos
SELECT description FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- Obter as entrevistas da data que citam "bakery" (padaria)

Select transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2023 AND transcript LIKE "%bakery%";

-- Retorna o nome do ladrão
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (
    -- Retorna as Contas bancárias que sacaram naqueel dia de manhã:
    SELECT account_number FROM atm_transactions WHERE atm_location ="Leggett Street" and transaction_type = "withdraw" and month = 7 and day = 28
) AND phone_number IN (
    -- Telefone que fizeram a ligação;
    SELECT caller FROM phone_calls WHERE day = 28 and month = 7 and year = 2023 and duration < 60
) AND people.name in (
-- Retorna as pessoas que estavam no voo da fuga
    SELECT name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
    WHERE flights.id = (
        -- Retorna os ids dos voos do aeorporto da cidade no dia da fuga e os horarios
        SELECT flights.id from flights
        JOIN airports ON flights.origin_airport_id = airports.id
        WHERE airports.city = "Fiftyville"
        and flights.year = 2023 and flights.month = 7 and flights.day = 29 and flights.hour = 8 and flights.minute = 20
    )
) AND people.name IN (
    SELECT name FROM people WHERE license_plate IN (
        -- Obtém a placa do carro que foi embora do estacionamento na hora que a entrevista dizia
        SELECT license_plate FROM bakery_security_logs WHERE hour = 10 and minute > 15 and minute <= 25
    )
);

-- RETORN O NOMES DOS CÚMPLICE -
SELECT name FROM people WHERE phone_number in (
    SELECT receiver FROM phone_calls WHERE day = 28 and month = 7 and year = 2023 and duration < 60 and caller in (
        SELECT phone_number FROM people WHERE people.name IN (
           SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (
                -- Retorna as Contas bancárias
                SELECT account_number FROM atm_transactions WHERE atm_location ="Leggett Street" and transaction_type = "withdraw" and month = 7 and day = 28
            ) AND phone_number IN (
                -- Telefone que fizeram a ligação;
                SELECT caller FROM phone_calls WHERE day = 28 and month = 7 and year = 2023 and duration < 60
            ) AND people.name in (
            -- Retorna as pessoas que estavam no voo
                SELECT name FROM people
                JOIN passengers ON people.passport_number = passengers.passport_number
                JOIN flights ON passengers.flight_id = flights.id
                WHERE flights.id = (
                    -- Retorna os ids dos voos
                    SELECT flights.id from flights
                    JOIN airports ON flights.origin_airport_id = airports.id
                    WHERE airports.city = "Fiftyville"
                    and flights.year = 2023 and flights.month = 7 and flights.day = 29 and flights.hour = 8 and flights.minute = 20
                )
            ) AND people.name IN (
                SELECT name FROM people WHERE license_plate IN (
                    -- Obtém a placa do carro
                    SELECT license_plate FROM bakery_security_logs WHERE hour = 10 and minute > 15 and minute <= 25
                )
            )
        )
    )
);


-- LOCAL PARA ONDE O LADRÃO FUGIU:
-- New York City
SELECT city FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
    WHERE flights.id = 36;






