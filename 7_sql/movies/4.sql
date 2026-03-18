-- SELECT COUNT(title) FROM movies WHERE id IN (SELECT movie_id FROM ratings WHERE rating = 10.0);
SELECT COUNT(title) FROM movies INNER JOIN ratings ON movies.id = ratings.movie_id WHERE rating = 10.0;
