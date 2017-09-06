#!bin/bash

python3 data_generator.py

sqlcmd -S localhost -U SA -P Parol123456 -i $PWD/V0_db_init.sql
sqlcmd -S localhost -U SA -P Parol123456 -i $PWD/V1_init.sql
sqlcmd -S localhost -U SA -P Parol123456 -i $PWD/V2_alter.sql
sqlcmd -S localhost -U SA -P Parol123456 -i $PWD/V3_insert.sql