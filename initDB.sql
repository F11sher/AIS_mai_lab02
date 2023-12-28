INSERT INTO `User` (`first_name`,`last_name`,`email`,`login`,`password`)
VALUES
('Vaalyun', 'Angren', 'angrenv@mail.ru', 'vaang', 'mnkyle7ncgAVnardcuar'),
('Nayoko', 'Weissmuller', 'weissmullern@mail.ru', 'nawei', 'mrNxeslroolyakKeX8Vusi8W'),
('Belegohtar', 'Kronecker', 'kroneckerb@mail.ru', 'bekro', 'l2yoecnUohareegkKexrrSntYB'),
('Andre', 'Roberts', 'robertsa@mail.ru', 'anrob', 'tiAs2rRrnReU2qTdboe'),
('Krumkohm', 'Sauty', 'sautyk@mail.ru', 'krsau', 'M8auttOhkmSMmoylKu7r'),
('Etchelion', 'Clebsch', 'clebsche@mail.ru', 'etcle', 'lelcbnlhGsCEoiecuZa3sth'),
('Rei', 'Tukey', 'tukeyr@mail.ru', 'retuk', 'euyCieR0TMkEiIv'),
('Sibille', 'Racah', 'racahs@mail.ru', 'sirac', 'lSIdibe4iRslachioao'),
('Toraldur', 'Cassegrain', 'cassegraint@mail.ru', 'tocas', 's3eo9riunsdPENClEar2rTgaa'),
('Viserra', 'Szarek', 'szarekv@mail.ru', 'visza', 't4bsVpz44ejarSaeirrk'),
('Angelica', 'Goldstein', 'goldsteina@mail.ru', 'angol', 'gGltocsekAn4ilNn1edzBaei'),
('Maemi', 'Bosch', 'boschm@mail.ru', 'mabos', 'mhZiTMocmsrdBe9sa'),
('Barry', 'dAlembert', 'dalembertb@mail.ru', 'bada', 'lqArerWdrAaG5hteybmfB'),
('Fidan', 'de', 'def@mail.ru', 'fide', 'iGdndP7eaaYf3F'),
('Bolanus', 'Kapitsa', 'kapitsab@mail.ru', 'bokap', 'aiNuaKlU2tv9osLnsBapJ');


INSERT INTO Delivery (`user_id`,`type`,`creation_date`,`departure_point`,`receipt_point`)
VALUES
(1, 'truck', '2023-08-13', 'Ivanteyevka', 'Druzhba'),
(2, 'fragile cargo', '2023-04-18', 'Ilinskiy', 'Dzerzhinskiy'),
(3, 'courier', '2023-07-04', 'Gzhel', 'Bykovo'),
(4, 'fragile cargo', '2023-07-11', 'Kashira', 'Bolshevo'),
(4, 'fragile cargo', '2023-04-25', 'Ivanteyevka', 'Golitsyno'),
(4, 'courier', '2023-11-21', 'Druzhba', 'Dmitrov'),
(5, 'fragile cargo', '2023-04-25', 'Istra', 'Khorlovo'),
(6, 'fragile cargo', '2023-02-23', 'Gzhel', 'Demikhovo'),
(7, 'light-car', '2023-02-16', 'Gzhel', 'Bykovo'),
(8, 'courier', '2023-02-30', 'Dedovsk', 'Kerva'),
(9, 'light-car', '2023-06-02', 'Elektrougli', 'Dubna'),
(9, 'courier', '2023-04-27', 'Dorogomilovo', 'Chekhov'),
(10, 'fragile cargo', '2023-06-19', 'Khoroshevo-Mnevniki', 'Dubrovitsy');

INSERT INTO Recipient (user_id, delivery_id, first_name, last_name, phone_number)
VALUES
(1, 1, 'Benjamin', 'Adams', '+7(996)645-44-42'),
(2, 2, 'William', 'Webb', '+7(905)588-58-95'),
(3, 3, 'Thomas', 'Duncan', '+7(999)645-27-76'),
(4, 4, 'Denise', 'Taylor', '+7(996)982-72-13'),
(4, 5, 'Kevin', 'Williams', '+7(905)622-33-65'),
(5, 6, 'Nancy', 'Duncan', '+7(928)818-32-26'),
(6, 7, 'Robert', 'Jones', '+7(977)936-60-89'),
(7, 8, 'Anne', 'Schneider', '+7(925)818-20-20'),
(8, 9, 'Benjamin', 'Hayes', '+7(925)336-25-48'),
(9, 10, 'Thomas', 'Hayes', '+7(999)932-51-85'),
(9, 11, 'Nancy', 'Jones', '+7(977)754-46-53'),
(10, 12, 'Nancy', 'Webb', '+7(999)392-52-10');