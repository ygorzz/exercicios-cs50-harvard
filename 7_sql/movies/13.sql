-- Retorna o nome das pessoas
SELECT name FROM people
    -- tabela stars faz a ponta com a tabela movies
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON stars.movie_id = movies.id
    -- Onde os ids dos filmes está entre os retornados abaixo
    WHERE movies.id IN
    (
        -- Retorna os ids de todos os filme que Kevin estrelou
        SELECT movie_id FROM stars
            JOIN people ON stars.person_id = people.id
            WHERE people.name = 'Kevin Bacon' AND people.birth = 1958
    )
    -- E o próprio Kevin não deve estar incluído no SELECT
    AND people.name != 'Kevin Bacon';
