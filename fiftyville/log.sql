-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Take a look at all the crime reports first.
SELECT * FROM crime_scene_reports.


-- Take a look at the data from the 28th at around 10:15 AM, the reported crime time
SELECT * FROM bakery_security_logs


-- Select license_plate of all Exits between 10:16 AM and 10:35 AM (in a query)
-- JOIN on people.license_plate to get their names.
SELECT DISTINCT(people.name) FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28 AND hour >= 9 AND hour <= 10;


-- Read the interviews from the day of the crime
Select * FROM interviews WHERE day = 28 AND month = 7;
-- Thief left within 10 minutes, so between 10:15 and 10:25
-- Apparently, not Jose, Eugene, Ruth, Raymond nor Lily, Emma
-- Thief called someone for less than a minute. Took the earliest flight the next day (29).
-- The person they talked to bought them the ticket.


-- First flight out was at 8:20 AM, to destination 4.
SELECT * FROM flights WHERE month = 7 AND day = 29;


-- LaGuardia Airport, NYC. Flight ID 36
SELECT * FROM airports WHERE id = 4;


-- Get every passenger that was on the flight.
SELECT * FROM passengers WHERE flight_id = 36;
-- Get the names of :
-- passengers's passport to the people's passport,
-- JOIN on people's license_plate = bakery_security_logs.license_plate


-- The names of the people who's license plate are on the security logs and who also where on the flight
SELECT DISTINCT(name) FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE people.passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id = 36);


-- Find the names of the people who left within 10 minutes of the crime and also got on the next flight
SELECT name FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
WHERE day = 28
AND hour = 10
AND minute < 25
AND people.passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id = 36);


-- So the thief is either Bruce, Sofia or Kelsey, Taylor, Kenny
-- Now find out who was on a phone call that lasted less than a minute after the crime
-- and was also on the flight
SELECT name FROM people
JOIN bakery_security_logs
ON people.license_plate = bakery_security_logs.license_plate
JOIN phone_calls
ON phone_calls.caller = people.phone_number
WHERE phone_calls.day = 28
AND phone_calls.duration <= 60
AND people.passport_number
IN (SELECT passport_number FROM passengers WHERE flight_id = 36);


-- Take a look at transactions that ocurred on the day of the crime
SELECT * FROM atm_transactions
WHERE day = 28;

-- Connect bank accounts, people.name and transaction account number
SELECT name FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.day = 28
AND atm_transactions.atm_location = 'Leggett Street';


-- The accomplice
SELECT name FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = 28
AND duration <= 60
AND phone_calls.caller IN
(SELECT phone_number FROM people
WHERE name = 'Bruce');

-- Bruce must be the thief. He left within 10 minutes of the crime, was on the flight, made a call that lasted less than or equal to 60 seconds and used an ATM in Leggett Street
-- Escaped to New York City
-- Accomplice is Robin

-- The accomplice
SELECT name FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.receiver
WHERE day = 28
AND duration <= 60
AND phone_calls.caller IN
(SELECT phone_number FROM people
WHERE name = 'Bruce');
