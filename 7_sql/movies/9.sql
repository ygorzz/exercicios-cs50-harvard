-- A tabela people não sabe nada sobre movies, por isso usamos a tabela stars como ponte entre as duas
SELECT DISTINCT(name) FROM people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    WHERE movies.year = 2004 ORDER BY people.birth;
