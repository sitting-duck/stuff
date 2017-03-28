BEGIN;

--create test users
INSERT INTO `user`(id, name, password)
	VALUES (0, "sitting-duck", "herp");
	
INSERT INTO `user`(id, name, password)
	VALUES (1, "doctor_me", "derp");
	
--create some test todo items
INSERT INTO todo (id, `user`, item)
		VALUES (0, 0, "fold clothes");
		
INSERT INTO todo (id, `user`, item)
	VALUES (1, 1, "get engine checked");

COMMIT;