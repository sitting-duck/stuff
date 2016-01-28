
BEGIN;

UPDATE pet
SET name="Zed's Pet"
--if we're going to have to use multiple tables to make the selection 
--we have to use IN and a sub query with SELECT
WHERE id IN (

	SELECT pet_id FROM person_pet WHERE 
	--the relation shows that the pet is owned by Zed
	person_id = 0

);

COMMIT;