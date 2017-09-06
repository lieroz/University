#!bin/bash

python3 data_generator.py

sqlcmd -S localhost -U SA -P Parol123456 -i /home/lieroz/University/Sem_05/DbCourse/Lab_01/V0_db_init.sql
sqlcmd -S localhost -U SA -P Parol123456 -i /home/lieroz/University/Sem_05/DbCourse/Lab_01/V1_init.sql
sqlcmd -S localhost -U SA -P Parol123456 -i /home/lieroz/University/Sem_05/DbCourse/Lab_01/V2_alter.sql
sqlcmd -S localhost -U SA -P Parol123456 -i /home/lieroz/University/Sem_05/DbCourse/Lab_01/V3_insert.sql