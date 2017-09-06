USE master;

IF EXISTS(SELECT name
          FROM sys.databases
          WHERE name = 'Travels')
  DROP DATABASE Travels;

CREATE DATABASE Travels;