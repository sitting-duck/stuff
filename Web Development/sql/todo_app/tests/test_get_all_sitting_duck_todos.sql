BEGIN;

SELECT item FROM todo 
	WHERE todo.`user` = 0;

COMMIT;